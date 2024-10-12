import { RNPackage, RNPackageContext, TurboModulesFactory, } from "@rnoh/react-native-openharmony/ts";
import type { TurboModule, TurboModuleContext, } from "@rnoh/react-native-openharmony/ts";
import { JPushTurboModule } from './JPushTurboModule';

class JPushTurboModulesFactory extends TurboModulesFactory {
  createTurboModule(name: string): TurboModule | null {
    if (name === "JPushTurboModule") {
      return new JPushTurboModule(this.ctx);
    }
    return null;
  }

  hasTurboModule(name: string): boolean {
    return name === "JPushTurboModule";
  }
}

export class JPushTurboModulePackage extends RNPackage {
  createTurboModulesFactory(ctx: TurboModuleContext): TurboModulesFactory {
    return new JPushTurboModulesFactory(ctx);
  }
}
