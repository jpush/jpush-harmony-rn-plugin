#include "JPushTurboModulePackage.h"
#include "JPushTurboModuleSpec.h"


using namespace rnoh;
using namespace facebook;

class JPushTurboModuleFactoryDelegate : public TurboModuleFactoryDelegate {
    
    public:
    SharedTurboModule createTurboModule(Context ctx, const std::string &name) const override {
        if (name == "JPushTurboModule") {
            return std::make_shared<NativeJPushTurboModuleSpecJSI>(ctx, name);
        }
        return nullptr;
    };
};

std::unique_ptr<TurboModuleFactoryDelegate> JPushTurboModulePackage::createTurboModuleFactoryDelegate() {
    return std::make_unique<JPushTurboModuleFactoryDelegate>();
}


