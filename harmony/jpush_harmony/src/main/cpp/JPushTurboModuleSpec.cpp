// NOTE: This entire file should be codegen'ed.

#include "JPushTurboModuleSpec.h"

using namespace rnoh;
using namespace facebook;

static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_init(jsi::Runtime &rt,
                                                                                       react::TurboModule &turboModule,
                                                                                       const jsi::Value *args,
                                                                                       size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "init", args, count));
}

static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_setDebug(jsi::Runtime &rt,
                                                                                    react::TurboModule &turboModule,
                                                                                    const jsi::Value *args,
                                                                                    size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "setDebug", args, count));
}

static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_setAppKey(jsi::Runtime &rt,
                                                                              react::TurboModule &turboModule,
                                                                              const jsi::Value *args, size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "setAppKey", args, count));
}

static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_setChannel(jsi::Runtime &rt,
                                                                         react::TurboModule &turboModule,
                                                                         const jsi::Value *args, size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "setChannel", args, count));
}

static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_getRegistrationId(jsi::Runtime &rt,
                                                                                      react::TurboModule &turboModule,
                                                                                      const jsi::Value *args,
                                                                                      size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "getRegistrationId", args, count));
}

static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_setTags(jsi::Runtime &rt,
                                                                                      react::TurboModule &turboModule,
                                                                                      const jsi::Value *args,
                                                                                      size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "setTags", args, count));
}
static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_addTags(jsi::Runtime &rt,
                                                                                      react::TurboModule &turboModule,
                                                                                      const jsi::Value *args,
                                                                                      size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "addTags", args, count));
}
static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_deleteTags(jsi::Runtime &rt,
                                                                                      react::TurboModule &turboModule,
                                                                                      const jsi::Value *args,
                                                                                      size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "deleteTags", args, count));
}
static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_cleanTags(jsi::Runtime &rt,
                                                                                      react::TurboModule &turboModule,
                                                                                      const jsi::Value *args,
                                                                                      size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "cleanTags", args, count));
}
static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_getTags(jsi::Runtime &rt,
                                                                                      react::TurboModule &turboModule,
                                                                                      const jsi::Value *args,
                                                                                      size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "getTags", args, count));
}
static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_checkTagBindState(jsi::Runtime &rt,
                                                                                      react::TurboModule &turboModule,
                                                                                      const jsi::Value *args,
                                                                                      size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "checkTagBindState", args, count));
}
static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_setAlias(jsi::Runtime &rt,
                                                                                      react::TurboModule &turboModule,
                                                                                      const jsi::Value *args,
                                                                                      size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "setAlias", args, count));
}
static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_deleteAlias(jsi::Runtime &rt,
                                                                                      react::TurboModule &turboModule,
                                                                                      const jsi::Value *args,
                                                                                      size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "deleteAlias", args, count));
}
static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_getAlias(jsi::Runtime &rt,
                                                                                      react::TurboModule &turboModule,
                                                                                      const jsi::Value *args,
                                                                                      size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "getAlias", args, count));
}
static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_stopPush(jsi::Runtime &rt,
                                                                                      react::TurboModule &turboModule,
                                                                                      const jsi::Value *args,
                                                                                      size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "stopPush", args, count));
}
static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_resumePush(jsi::Runtime &rt,
                                                                                      react::TurboModule &turboModule,
                                                                                      const jsi::Value *args,
                                                                                      size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "resumePush", args, count));
}
static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_isPushStopped(jsi::Runtime &rt,
                                                                                      react::TurboModule &turboModule,
                                                                                      const jsi::Value *args,
                                                                                      size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "isPushStopped", args, count));
}
static jsi::Value __hostFunction_NativeJPushCxxModuleSpecJSI_setBadgeNumber(jsi::Runtime &rt,
                                                                                      react::TurboModule &turboModule,
                                                                                      const jsi::Value *args,
                                                                                      size_t count) {
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).call(rt, "setBadgeNumber", args, count));
}
static jsi::Value bridge_initAsync(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).callAsync(rt, "initAsync", args, count);
}
static jsi::Value bridge_getRegistrationIdAsync(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).callAsync(rt, "getRegistrationIdAsync", args, count);
}
static jsi::Value bridge_isPushStoppedAsync(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).callAsync(rt, "isPushStoppedAsync", args, count);
}
static jsi::Value bridge_turnOffPush(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).callAsync(rt, "turnOffPush", args, count);
}
static jsi::Value bridge_turnOnPush(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "turnOnPush", args, count);
}
static jsi::Value bridge_getPushStatus(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "getPushStatus", args, count);
}
static jsi::Value bridge_invalidate(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "invalidate", args, count);
}
static jsi::Value bridge_setBackgroundEnable(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "setBackgroundEnable", args, count);
}
static jsi::Value bridge_setSmartPushEnable(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "setSmartPushEnable", args, count);
}
static jsi::Value bridge_setDataInsightsEnable(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).callAsync(rt, "setDataInsightsEnable", args, count);
}
static jsi::Value bridge_setUserRequestNotificationPermission(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "setUserRequestNotificationPermission", args, count);
}
static jsi::Value bridge_setListWifi(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).callAsync(rt, "setListWifi", args, count);
}
static jsi::Value bridge_setEnableAppTerminate(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).callAsync(rt, "setEnableAppTerminate", args, count);
}
static jsi::Value bridge_setHeartbeatTime(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "setHeartbeatTime", args, count);
}
static jsi::Value bridge_clearNotification(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "clearNotification", args, count);
}
static jsi::Value bridge_clearNotificationByMsgId(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "clearNotificationByMsgId", args, count);
}
static jsi::Value bridge_clearNotificationAll(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "clearNotificationAll", args, count);
}
static jsi::Value bridge_reportCustomDisplay(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "reportCustomDisplay", args, count);
}
static jsi::Value bridge_reportCustomClick(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "reportCustomClick", args, count);
}
static jsi::Value bridge_reportNotificationDisplay(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "reportNotificationDisplay", args, count);
}
static jsi::Value bridge_reportNotificationClick(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "reportNotificationClick", args, count);
}
static jsi::Value bridge_setMobileNumber(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "setMobileNumber", args, count);
}
static jsi::Value bridge_setCustomMessageMaxCacheCount(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).call(rt, "setCustomMessageMaxCacheCount", args, count);
}
static jsi::Value bridge_addLocalNotification(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).callAsync(rt, "addLocalNotification", args, count);
}
static jsi::Value bridge_removeLocalNotification(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).callAsync(rt, "removeLocalNotification", args, count);
}
static jsi::Value bridge_clearLocalNotifications(jsi::Runtime &rt, react::TurboModule &module,
    const jsi::Value *args, size_t count) {
  return static_cast<ArkTSTurboModule &>(module).callAsync(rt, "clearLocalNotifications", args, count);
}
NativeJPushTurboModuleSpecJSI::NativeJPushTurboModuleSpecJSI(const ArkTSTurboModule::Context ctx,
                                                               const std::string name)
    : ArkTSTurboModule(ctx, name) {
    methodMap_["init"] =
        MethodMetadata{0, __hostFunction_NativeJPushCxxModuleSpecJSI_init};
    methodMap_["setDebug"] =
        MethodMetadata{1, __hostFunction_NativeJPushCxxModuleSpecJSI_setDebug};
    methodMap_["setAppKey"] =
        MethodMetadata{1, __hostFunction_NativeJPushCxxModuleSpecJSI_setAppKey};
    methodMap_["setChannel"] =
        MethodMetadata{1, __hostFunction_NativeJPushCxxModuleSpecJSI_setChannel};
    methodMap_["getRegistrationId"] =
        MethodMetadata{0, __hostFunction_NativeJPushCxxModuleSpecJSI_getRegistrationId};
    methodMap_["setTags"] =
        MethodMetadata{2, __hostFunction_NativeJPushCxxModuleSpecJSI_setTags};
    methodMap_["addTags"] =
        MethodMetadata{2, __hostFunction_NativeJPushCxxModuleSpecJSI_addTags};
    methodMap_["deleteTags"] =
        MethodMetadata{2, __hostFunction_NativeJPushCxxModuleSpecJSI_deleteTags};
    methodMap_["cleanTags"] =
        MethodMetadata{1, __hostFunction_NativeJPushCxxModuleSpecJSI_cleanTags};
    methodMap_["getTags"] =
        MethodMetadata{2, __hostFunction_NativeJPushCxxModuleSpecJSI_getTags};
    methodMap_["checkTagBindState"] =
        MethodMetadata{2, __hostFunction_NativeJPushCxxModuleSpecJSI_checkTagBindState};
    methodMap_["setAlias"] =
        MethodMetadata{2, __hostFunction_NativeJPushCxxModuleSpecJSI_setAlias};
    methodMap_["deleteAlias"] =
        MethodMetadata{1, __hostFunction_NativeJPushCxxModuleSpecJSI_deleteAlias};
    methodMap_["getAlias"] =
        MethodMetadata{1, __hostFunction_NativeJPushCxxModuleSpecJSI_getAlias};
    methodMap_["stopPush"] =
        MethodMetadata{0, __hostFunction_NativeJPushCxxModuleSpecJSI_stopPush};
    methodMap_["resumePush"] =
        MethodMetadata{0, __hostFunction_NativeJPushCxxModuleSpecJSI_resumePush};
    methodMap_["isPushStopped"] =
        MethodMetadata{0, __hostFunction_NativeJPushCxxModuleSpecJSI_isPushStopped};
    methodMap_["setBadgeNumber"] =
        MethodMetadata{1, __hostFunction_NativeJPushCxxModuleSpecJSI_setBadgeNumber};
    methodMap_["initAsync"] = MethodMetadata{0, bridge_initAsync};
    methodMap_["getRegistrationIdAsync"] = MethodMetadata{0, bridge_getRegistrationIdAsync};
    methodMap_["isPushStoppedAsync"] = MethodMetadata{0, bridge_isPushStoppedAsync};
    methodMap_["turnOffPush"] = MethodMetadata{0, bridge_turnOffPush};
    methodMap_["turnOnPush"] = MethodMetadata{0, bridge_turnOnPush};
    methodMap_["getPushStatus"] = MethodMetadata{0, bridge_getPushStatus};
    methodMap_["invalidate"] = MethodMetadata{0, bridge_invalidate};
    methodMap_["setBackgroundEnable"] = MethodMetadata{1, bridge_setBackgroundEnable};
    methodMap_["setSmartPushEnable"] = MethodMetadata{1, bridge_setSmartPushEnable};
    methodMap_["setDataInsightsEnable"] = MethodMetadata{1, bridge_setDataInsightsEnable};
    methodMap_["setUserRequestNotificationPermission"] = MethodMetadata{1, bridge_setUserRequestNotificationPermission};
    methodMap_["setListWifi"] = MethodMetadata{1, bridge_setListWifi};
    methodMap_["setEnableAppTerminate"] = MethodMetadata{1, bridge_setEnableAppTerminate};
    methodMap_["setHeartbeatTime"] = MethodMetadata{1, bridge_setHeartbeatTime};
    methodMap_["clearNotification"] = MethodMetadata{1, bridge_clearNotification};
    methodMap_["clearNotificationByMsgId"] = MethodMetadata{1, bridge_clearNotificationByMsgId};
    methodMap_["clearNotificationAll"] = MethodMetadata{0, bridge_clearNotificationAll};
    methodMap_["reportCustomDisplay"] = MethodMetadata{2, bridge_reportCustomDisplay};
    methodMap_["reportCustomClick"] = MethodMetadata{2, bridge_reportCustomClick};
    methodMap_["reportNotificationDisplay"] = MethodMetadata{2, bridge_reportNotificationDisplay};
    methodMap_["reportNotificationClick"] = MethodMetadata{2, bridge_reportNotificationClick};
    methodMap_["setMobileNumber"] = MethodMetadata{2, bridge_setMobileNumber};
    methodMap_["setCustomMessageMaxCacheCount"] = MethodMetadata{1, bridge_setCustomMessageMaxCacheCount};
    methodMap_["addLocalNotification"] = MethodMetadata{1, bridge_addLocalNotification};
    methodMap_["removeLocalNotification"] = MethodMetadata{1, bridge_removeLocalNotification};
    methodMap_["clearLocalNotifications"] = MethodMetadata{0, bridge_clearLocalNotifications};
}