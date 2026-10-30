# RN鸿蒙1.4.0升级说明

原生@jg/push升级至1.5.0，保持最低compatibleSdkVersion12。

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
| setMobileNumber及onMobileNumberOperatorResult | 旧SDK已有、插件未桥接 | 增加sequence/mobileNumber，返回结果同名JSON事件，不记录号码日志 |
| setCustomMessageMaxCacheCount | 旧SDK已有、插件未桥接 | 显式count入口，不自动改缓存策略 |
| JCollectControl.setListWifi/setEnableAppTerminate | 旧公开设置，目标改Promise | 显式bool调用，context内部取得，Promise<void>；不默认启用。旧setGPS目标已不公开，不新建接口 |
| 1.5.0覆盖/撤回、long ID精度 | SDK内部通知消费行为 | 无新增客户端API，保留字符串ID/载荷，不虚造cover/retract接口 |

## 生命周期、错误与集成

每次init建立generation，旧回调不能污染新实例状态；invalidate()清缓存并屏蔽迟到回调，RNOH实际__onDestroy__调用该入口并调用父类。重复初始化取最新回调；Async每次独立Promise。旧void init/后台缓存刷新失败通过onBridgeError JSON `{operation,code}`可观察，不输出SDK敏感日志；新Async错误保持拒绝由调用者catch。非Harmony宿主不支持该独立TurboModule，getEnforcing按RN契约报模块缺失。

同步查询在注册前可为空/undefined，本版同步getter返回缓存：先监听onRegister/onConnected，推荐新业务await Async入口。例：

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

## 源码集成

本版分发平台源码，Harmony宿主通过源码模块编译集成。将插件模块配置为

`file:../node_modules/jpush-harmony-rn-plugin/harmony/jpush_harmony`

不要使用旧版预编译插件HAR替代当前源码。框架HAR由宿主提供并与React Native版本匹配，插件不自动升级宿主框架。

## 必需：宿主RNOH依赖覆盖与安装前检查

本包不会携带或擅自升级宿主RNOH框架。模块oh-package中的legacy `file:../libs/react_native_openharmony-5.0.0.302.har`不是随包文件，**无宿主根overrides时不可解析，不能直接ohpm install后声称可安装**。保持该fallback仅为兼容已有宿主的依赖覆盖机制，不能把旧plugin HAR当框架HAR。

按RNOH官方生态库[根overrides集成方式](https://github.com/react-native-oh-library/react-native-harmony-screens/blob/sig/doc/en.md)，在你的Harmony工程根oh-package.json5明确覆盖所有transitive RNOH依赖：

```json5
{
  overrides: {
    // 路径相对于本文件。使用当前宿主已安装、与JS框架相匹配的HAR，不自动升级框架。
    // @react-native-oh/react-native-harmony@0.72.145的HAR位于包根。
    '@rnoh/react-native-openharmony': 'file:../node_modules/@react-native-oh/react-native-harmony/react_native_openharmony.har',
  },
}
```

旧/别名框架包布局可能不同，须改为你现有HAR真实路径，不能照抄不存在的示例。框架来源为当前宿主匹配的官方npm包/HAR，而不是本插件分发。将本插件源码模块加入entry依赖后，**先运行**安装到本地node_modules的`jpush-harmony-check-host /你的工程/harmony/oh-package.json5`，再执行ohpm install和宿主构建。也可`node node_modules/jpush-harmony-rn-plugin/scripts/check-harmony-host.cjs <根配置>`。脚本仅读取指定配置与其显式HAR，不修改文件、不登录、不安装框架。

检查缺overrides、路径不存在/不是HAR、包name/version不匹配或不能确认__onDestroy__/callAsync声明时以非0退出。该检查仅检查宿主依赖配置及必要声明；应用仍需使用所选RNOH与原生SDK支持的工具链集成。legacy 5.0.0.302路径不代表该框架文件随插件提供。
