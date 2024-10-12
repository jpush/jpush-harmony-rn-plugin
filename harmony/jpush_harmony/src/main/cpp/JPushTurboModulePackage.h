#include "RNOH/Package.h"
namespace rnoh {
    class JPushTurboModulePackage : public Package {
    public:
        JPushTurboModulePackage(Package::Context ctx) : Package(ctx) {}
        std::unique_ptr<TurboModuleFactoryDelegate> createTurboModuleFactoryDelegate()
        override;
    };
} // namespace rnoh