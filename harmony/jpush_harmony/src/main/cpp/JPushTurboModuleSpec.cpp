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
    return jsi::Value(static_cast<ArkTSTurboModule &>(turboModule).callAsync(rt, "setAppKey", args, count));
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
}