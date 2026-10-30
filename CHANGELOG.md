# 1.4.0

- 鸿蒙原生@jg/push升级至1.5.0，增加本地通知、UPS、推送状态、到达/未展示事件与公开载荷字段。
- 同步RID/停止状态getter保留缓存签名，增加Async查询、可等待初始化与显式失效入口；旧void初始化错误通过onBridgeError报告。
- 保留JSON字符串事件与字符串消息ID，扩展channel/notificationType/callId。
- 增加显式权限/采集控制、通知清理及业务上报入口，不自动启用采集。
- 对齐RNOH TurboModule构造上下文类型，保留现有JS接口。
- Harmony端采用源码模块及宿主匹配的RNOH依赖集成。
