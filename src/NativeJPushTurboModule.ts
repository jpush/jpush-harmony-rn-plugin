import { TurboModule, TurboModuleRegistry } from 'react-native';

interface Spec extends TurboModule {
  init(): void;
  setDebug(d: boolean): void;
  setAppKey(appKey: string): void;
  setChannel(channel: string): void;
  getRegistrationId(): string;
  setTags(sequence: number, tags: string[]): void;
  addTags(sequence: number, tags: string[]): void;
  deleteTags(sequence: number, tags: string[]): void;
  cleanTags(sequence: number): void;
  getTags(sequence: number, cur: number): void;
  checkTagBindState(sequence: number, tag: string): void;
  setAlias(sequence: number, alias: string): void;
  deleteAlias(sequence: number): void;
  getAlias(sequence: number): void;
  stopPush(): void;
  resumePush(): void;
  isPushStopped(): boolean | undefined;
  setBadgeNumber(sequence: number): void;
}

export default TurboModuleRegistry.getEnforcing<Spec>('JPushTurboModule');


