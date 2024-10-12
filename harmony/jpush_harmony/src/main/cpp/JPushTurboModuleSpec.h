#include <ReactCommon/TurboModule.h>
#include "RNOH/ArkTSTurboModule.h"
namespace rnoh {
    class JSI_EXPORT NativeJPushTurboModuleSpecJSI : public ArkTSTurboModule {
    public:
    NativeJPushTurboModuleSpecJSI(const ArkTSTurboModule::Context ctx, const
    std::string name);
};
}