# RN鸿蒙1.4.0候选升级

原生@jg/push从1.2.0升级至1.5.0，官方OHPM HAR SHA512已核对；旧/新compatibleSdkVersion均12，保持最低系统声明。插件基线main fa6adc95e44fba82ad1a51f533839f06f135439b。用户已要求原生新增公开接口补齐，明确无鸿蒙真机，本轮真机豁免。

## 公开差分与桥接

| 原生公开接口/载荷 | 来源区间与当前缺口 | 本版JS/原生契约 |
| --- | --- | --- |
| init Promise、getRegistrationId Promise、isPushStopped Promise | 旧同步到新异步（1.4.0起查询变更） | 旧init():void派发，拒绝转onBridgeError；initAsync():Promise<void>等待SDK初始化及缓存刷新，不等同注册成功。旧同步getter保留缓存签名，新getRegistrationIdAsync()/isPushStoppedAsync()返回SDK实时Promise；初始化前RID空串、停止状态undefined，缓存不可当实时状态 |
| turnOffPush/turnOnPush | 1.4.2新增 | turnOffPush():Promise<{code,msg}>保留原生业务码，非0不是JS拒绝；turnOnPush():void仅派发。停恢复后刷新缓存，onCommandResult仍为原生JSON字符串，不假设dispatch等于服务端完成 |
| getPushStatus | 1.4.0新增 | void请求，最终通过onCommandResult；保留extra结构和原生码，不虚造Promise状态结果 |
| JPushLocalNotification及add/remove/clearLocalNotifications | 1.4.0新增 | addLocalNotification(options):Promise<void>，必需字段notificationId整数/title/content/extras JSON字符串/broadcastTime有限epoch毫秒/channelId/priority/url；即时使用0，日期自行转epoch；removeLocalNotification(id)/clearLocalNotifications()为Promise<void>。本地操作完成不代表系统已展示；原生失败拒绝 |
| onArrivedMessage/onUnShowMessage | 新增回调 | 新增同名事件，JSON字符串，按SDK真实回调触发，不把未展示等同已显示 |
| JMessage.channel/notificationType、JCustomMessage.channel | 新增字段 | 现有JSON.stringify保型；notificationType 0推送/1本地。msgId始终字符串，不做Number转换 |
| JMessageVoIP.callId | 1.4.1新增 | 旧onJMessageVoIP JSON新增字段原样透出，不猜布尔语义 |
| setClickWant可选ApplicationContext | 1.4.0变更 | 原生宿主static setClickWant(want,context?)返回Promise<JMessage|undefined>，冷启须传application context且await/catch；不将Want跨JS桥 |
| setContext | 1.3.7新增 | 桥接initAsync内部传当前application context，JS不暴露系统Context对象 |
| defaultMessageBackgroundData | 新增公开后台助手 | 原生static助手返回Promise<boolean>，宿主BackgroundAbility调用，不把PushPayload跨JS |
| setBackgroundEnable / setSmartPushEnable / setDataInsightsEnable / setUserRequestNotificationPermission | 新公开设置/旧缺口 | 显式bool入口，后两类自动补application context；dataInsights返回Promise<void>，其余void。插件不自动启用、不重复自动申请权限 |
| setHeartbeatTime / clearNotification / clearNotificationByMsgId / clearNotificationAll | 新公开入口 | 直接保留原生参数和void契约；清除单条消息使用字符串msgId |
| reportCustomDisplay/Click、reportNotificationDisplay/Click | 新公开入口 | channel:number + msgId:string，void派发；仅业务实际显示/点击后显式上报，插件不重复代报 |
| setMobileNumber及onMobileNumberOperatorResult | 旧SDK已有、插件未桥接 | 本次相关公开缺口补齐sequence/mobileNumber，返回结果同名JSON事件，不记录号码日志 |
| setCustomMessageMaxCacheCount | 旧SDK已有、插件未桥接 | 显式count入口，不自动改缓存策略 |
| JCollectControl.setListWifi/setEnableAppTerminate | 旧公开设置，目标改Promise | 显式bool调用，context内部取得，Promise<void>；不默认启用。旧setGPS目标已不公开，不新建接口 |
| 1.5.0覆盖/撤回、long ID精度 | SDK内部通知消费行为 | 无新增客户端API，保留字符串ID/载荷，不虚造cover/retract接口 |

## 生命周期、错误与集成

每次init建立generation，旧回调不能污染新实例状态；invalidate()清缓存并屏蔽迟到回调，RNOH实际__onDestroy__调用该入口并调用父类。重复初始化取最新回调；Async每次独立Promise。旧void init/后台缓存刷新失败通过onBridgeError JSON `{operation,code}`可观察，不输出SDK敏感日志；新Async错误保持拒绝由调用者catch。非Harmony宿主不支持该独立TurboModule，getEnforcing按RN契约报模块缺失。

旧同步查询本来可在注册前为空/undefined，但升级后为缓存：先监听onRegister/onConnected，推荐新业务await Async入口。例：

```ts
import { JPushModule } from 'jpush-harmony-rn-plugin';
import { DeviceEventEmitter } from 'react-native';
const subscription = DeviceEventEmitter.addListener('onBridgeError', value => {
  const error = JSON.parse(value); // 不记录账号/设备信息
});
await JPushModule.initAsync();
const rid = await JPushModule.getRegistrationIdAsync(); // 可能尚未注册，仍需监听onRegister
const stopped = await JPushModule.isPushStoppedAsync();
const result = await JPushModule.turnOffPush(); // 显式业务操作；检查result.code
JPushModule.turnOnPush(); // 仅派发，监听连接/命令结果
subscription.remove(); // 页面卸载只移除自己的监听；不要销毁仍被其它页面使用的全局模块
```

包只分发本次源码；根目录历史1.3.0 tgz与harmony/jpush_harmony.har不会打入候选包，不能复制它们冒充新版本。npm pack生成1.4.0 tgz后安装，并在Harmony宿主oh-package.json5依赖源码目录`file:../node_modules/jpush-harmony-rn-plugin/harmony/jpush_harmony`；原有@rnoh依赖为宿主本地HAR路径`../libs/react_native_openharmony-5.0.0.302.har`，须提供宿主匹配RNOH HAR或由宿主依赖覆盖配置，不擅升级框架版本。构建需要DevEco/HarmonyOS SDK与RNOH工具；普通TS转译/mock测试不能替代ArkTS/HAR/HAP编译。

验证与限制见PR及任务文档。不得用Pixel7替代HarmonyOS NEXT真机。所有权限/采集设置均保持显式，不带默认调用。发布需独立授权，本PR不npm/OHPM发布。

## 本轮验证边界

9项mock契约测试、最终npm tgz安装后的公共TypeScript构建、对官方@jg/push1.5.0真实导出声明的TypeScript兼容检查通过，HAR SHA512校验通过。所取官方RNOH0.72.145源码用于核对callAsync和__onDestroy__，不等于项目原声明本地react_native_openharmony-5.0.0.302.har已编译验证；未改变原依赖或最低支持声明。原本地HAR没有随仓提供，匹配宿主工具链集成仍需验证。

当前机器无DevEco、Harmony SDK/hdc/hvigor/ohpm可执行工具，HBuilderX仅含编辑器schema，不是SDK编译链；无法运行ArkTS/HAR/HAP构建。npm TypeScript构建通过不能替代上述原生编译。用户已明确没有鸿蒙测试机，本轮免真机。本PR保留上述原生构建待验，不宣称编译或运行通过。

## 必需：宿主RNOH依赖覆盖与安装前检查

本包不会携带或擅自升级宿主RNOH框架。模块oh-package中的legacy `file:../libs/react_native_openharmony-5.0.0.302.har`不是随包文件，**无宿主根overrides时不可解析，不能直接ohpm install后声称可安装**。保持该fallback仅为兼容已有宿主的依赖覆盖机制，不能把旧plugin HAR当框架HAR。

按RNOH官方生态库[根overrides集成方式](https://github.com/react-native-oh-library/react-native-harmony-screens/blob/sig/doc/en.md)，在你的Harmony工程根oh-package.json5明确覆盖所有transitive RNOH依赖：

```json5
{
  overrides: {
    // 路径相对于本文件。使用当前宿主已安装、与JS框架相匹配的HAR，不自动升级框架。
    // 已核验官方@react-native-oh/react-native-harmony@0.72.145 npm包实际HAR位于包根。
    '@rnoh/react-native-openharmony': 'file:../node_modules/@react-native-oh/react-native-harmony/react_native_openharmony.har',
  },
}
```

旧/别名框架包布局可能不同，须改为你现有HAR真实路径，不能照抄不存在的示例。框架来源为当前宿主匹配的官方npm包/HAR，而不是本插件分发。将本插件源码模块加入entry依赖后，**先运行**安装到本地node_modules的`jpush-harmony-check-host /你的工程/harmony/oh-package.json5`，再执行ohpm install和宿主构建。也可`node node_modules/jpush-harmony-rn-plugin/scripts/check-harmony-host.cjs <根配置>`。脚本仅读取指定配置与其显式HAR，不修改文件、不登录、不安装框架。

检查缺overrides、路径不存在/不是HAR、包name/version不匹配或不能确认__onDestroy__/callAsync声明时非0退出，不以TS成功替代依赖配置。正例使用实际官方0.72.145 HAR，反例覆盖缺override/缺文件/错误HAR。脚本通过只证明所检依赖路径/元数据/声明，不证明OHPM实际解析、ArkTS/HAR/HAP编译或所有RNOH版本兼容；旧本地5.0.0.302版本仍未编译验证。
