import { TurboModule, TurboModuleRegistry } from 'react-native';

export type PushResult = { code: number; msg: string };
export type LocalNotificationOptions = {
  notificationId: number; title: string; content: string; extras: string;
  broadcastTime: number; channelId: string; priority: number; url: string;
};

interface Spec extends TurboModule {
  init(): void;
  initAsync(): Promise<void>;
  getRegistrationIdAsync(): Promise<string>;
  isPushStoppedAsync(): Promise<boolean | undefined>;
  turnOffPush(): Promise<PushResult>;
  turnOnPush(): void;
  getPushStatus(): void;
  invalidate(): void;
  setBackgroundEnable(enable: boolean): void;
  setSmartPushEnable(enable: boolean): void;
  setDataInsightsEnable(enable: boolean): Promise<void>;
  setUserRequestNotificationPermission(enable: boolean): void;
  setListWifi(enable: boolean): Promise<void>;
  setEnableAppTerminate(enable: boolean): Promise<void>;
  setHeartbeatTime(seconds: number): void;
  clearNotification(id: number): void;
  clearNotificationByMsgId(msgId: string): void;
  clearNotificationAll(): void;
  reportCustomDisplay(channel: number, msgId: string): void;
  reportCustomClick(channel: number, msgId: string): void;
  reportNotificationDisplay(channel: number, msgId: string): void;
  reportNotificationClick(channel: number, msgId: string): void;
  setMobileNumber(sequence: number, mobileNumber: string): void;
  setCustomMessageMaxCacheCount(count: number): void;
  addLocalNotification(options: LocalNotificationOptions): Promise<void>;
  removeLocalNotification(id: number): Promise<void>;
  clearLocalNotifications(): Promise<void>;

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


