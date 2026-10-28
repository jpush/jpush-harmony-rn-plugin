import { RNOHContext, TurboModule } from '@rnoh/react-native-openharmony/ts';
import { common, Want } from '@kit.AbilityKit';
import { pushCommon, RemoteNotificationExtensionAbility } from '@kit.PushKit';
import Logger from './Logger';
import {
  JPushInterface,
  CallBackMsg,
  JAliasMessage,
  JMessage,
  JTagMessage,
  JCustomMessage,
  JMessageExtra,
  JMessageVoIP,
  JCmdMessage,
  JPushResult,
  JMobileNumberMessage,
  JPushLocalNotification,
  JCollectControl
} from '@jg/push';


export interface LocalNotificationOptions {
  notificationId: number;
  title: string;
  content: string;
  extras: string;
  broadcastTime: number;
  channelId: string;
  priority: number;
  url: string;
}

export class JPushTurboModule extends TurboModule {
  protected _context: common.UIAbilityContext;
  protected _RnContext: RNOHContext;
  private registrationId: string = '';
  private pushStopped: boolean | undefined = undefined;
  private generation: number = 0;
  private callback: MyCallBackMsg | undefined = undefined;

  constructor(ctx: RNOHContext) {
    super(ctx);
    this._context = ctx?.uiAbilityContext;
    this._RnContext = ctx;

  }

  init(): void {
    const pending = this.initAsync();
    const generation = this.generation;
    pending.catch(() => {
      if (generation !== this.generation) return;
      this._RnContext?.rnInstance?.emitDeviceEvent('onBridgeError',
        JSON.stringify({ operation: 'init', code: 'E_INIT' }));
    });
  }

  async initAsync(): Promise<void> {
    const generation = ++this.generation;
    this.callback?.dispose();
    this.callback = new MyCallBackMsg(this._RnContext,
      () => this.generation === generation,
      (rid: string) => { this.registrationId = rid; },
      () => this.refreshStateAfterCommand());
    JPushInterface.setCallBackMsg(this.callback);
    JPushInterface.setContext(this._context.getApplicationContext());
    await JPushInterface.init(this._context);
    await this.refreshState(generation);
  }

  invalidate(): void {
    ++this.generation;
    this.callback?.dispose();
    this.callback = undefined;
    this.registrationId = '';
    this.pushStopped = undefined;
  }

  __onDestroy__(): void {
    this.invalidate();
    super.__onDestroy__();
  }

  private async refreshState(generation: number): Promise<void> {
    const rid = await JPushInterface.getRegistrationId();
    const stopped = await JPushInterface.isPushStopped();
    if (generation === this.generation) {
      this.registrationId = rid;
      this.pushStopped = stopped;
    }
  }

  private refreshStateAfterCommand(): void {
    const generation = this.generation;
    this.refreshState(generation).catch(() => {
      if (generation !== this.generation) return;
      this._RnContext?.rnInstance?.emitDeviceEvent('onBridgeError',
        JSON.stringify({ operation: 'refreshState', code: 'E_STATE' }));
    });
  }

  static setClickWant(want: Want, context?: common.ApplicationContext): Promise<JMessage | undefined> {
    return JPushInterface.setClickWant(want, context)
  }

  setDebug(d: boolean) {
    Logger.info(`setDebug `);
    JPushInterface.setDebug(d)
  }

  setAppKey(appKey: string) {
    JPushInterface.setAppKey(appKey)
  }

  setChannel(channel: string) {
    JPushInterface.setChannel(channel)
  }

  getRegistrationId(): string {
    Logger.info(`getRegistrationId `);
    return this.registrationId
  }

  setTags(sequence: number, tags: string[]) {
    JPushInterface.setTags(sequence, tags)
  }

  addTags(sequence: number, tags: string[]) {
    JPushInterface.addTags(sequence, tags)
  }

  deleteTags(sequence: number, tags: string[]) {
    JPushInterface.deleteTags(sequence, tags)
  }

  cleanTags(sequence: number) {
    Logger.info(`cleanTags `);
    JPushInterface.cleanTags(sequence)
  }

  getTags(sequence: number, curr: number) {
    Logger.info(`getTags curr:`+curr);
    JPushInterface.getTags(sequence, curr)
  }

  checkTagBindState(sequence: number, tag: string) {
    JPushInterface.checkTagBindState(sequence, tag)
  }

  setAlias(sequence: number, alias: string) {
    JPushInterface.setAlias(sequence, alias)
  }

  deleteAlias(sequence: number) {
    Logger.info(`deleteAlias `);
    JPushInterface.deleteAlias(sequence)
  }

  getAlias(sequence: number) {
    Logger.info(`getAlias `);
    JPushInterface.getAlias(sequence)
  }

  stopPush() {
    Logger.info(`stopPush `);
    JPushInterface.stopPush()
    this.refreshStateAfterCommand()
  }

  resumePush() {
    Logger.info(`resumePush `);
    JPushInterface.resumePush()
    this.refreshStateAfterCommand()
  }

  isPushStopped(): boolean | undefined {
    Logger.info(`isPushStopped `);
    return this.pushStopped
  }

  setBadgeNumber(badgeNumber: number) {
    Logger.info(`setBadgeNumber:`+badgeNumber);
    JPushInterface.setBadgeNumber(badgeNumber)
  }

  async getRegistrationIdAsync(): Promise<string> {
    const generation = this.generation;
    const rid = await JPushInterface.getRegistrationId();
    if (generation === this.generation) this.registrationId = rid;
    return rid;
  }

  async isPushStoppedAsync(): Promise<boolean | undefined> {
    const generation = this.generation;
    const value = await JPushInterface.isPushStopped();
    if (generation === this.generation) this.pushStopped = value;
    return value;
  }

  async turnOffPush(): Promise<JPushResult> {
    const generation = this.generation;
    const result = await JPushInterface.turnOffPush(this._context);
    await this.refreshState(generation);
    return result;
  }

  turnOnPush(): void {
    JPushInterface.turnOnPush(this._context);
    this.refreshStateAfterCommand();
  }

  getPushStatus(): void { JPushInterface.getPushStatus(); }
  setBackgroundEnable(enable: boolean): void { JPushInterface.setBackgroundEnable(enable); }
  setSmartPushEnable(enable: boolean): void {
    JPushInterface.setSmartPushEnable(this._context.getApplicationContext(), enable);
  }
  setDataInsightsEnable(enable: boolean): Promise<void> {
    return JPushInterface.setDataInsightsEnable(this._context.getApplicationContext(), enable);
  }
  setUserRequestNotificationPermission(enable: boolean): void {
    JPushInterface.setUserRequestNotificationPermission(this._context.getApplicationContext(), enable);
  }
  setListWifi(enable: boolean): Promise<void> {
    return JCollectControl.setListWifi(this._context.getApplicationContext(), enable);
  }
  setEnableAppTerminate(enable: boolean): Promise<void> {
    return JCollectControl.setEnableAppTerminate(this._context.getApplicationContext(), enable);
  }
  setHeartbeatTime(seconds: number): void { JPushInterface.setHeartbeatTime(seconds); }
  clearNotification(id: number): void { JPushInterface.clearNotification(id); }
  clearNotificationByMsgId(msgId: string): void { JPushInterface.clearNotificationByMsgId(msgId); }
  clearNotificationAll(): void { JPushInterface.clearNotificationAll(); }
  reportCustomDisplay(channel: number, msgId: string): void { JPushInterface.reportCustomDisplay(channel, msgId); }
  reportCustomClick(channel: number, msgId: string): void { JPushInterface.reportCustomClick(channel, msgId); }
  reportNotificationDisplay(channel: number, msgId: string): void { JPushInterface.reportNotificationDisplay(channel, msgId); }
  reportNotificationClick(channel: number, msgId: string): void { JPushInterface.reportNotificationClick(channel, msgId); }
  setMobileNumber(sequence: number, mobileNumber: string): void { JPushInterface.setMobileNumber(sequence, mobileNumber); }
  setCustomMessageMaxCacheCount(count: number): void { JPushInterface.setCustomMessageMaxCacheCount(count); }

  addLocalNotification(options: LocalNotificationOptions): Promise<void> {
    if (!Number.isInteger(options.notificationId) || !Number.isFinite(options.broadcastTime)) {
      return Promise.reject(new Error('E_INVALID_ARGUMENT: notificationId/broadcastTime'));
    }
    const notification = new JPushLocalNotification();
    notification.notificationId = options.notificationId;
    notification.title = options.title;
    notification.content = options.content;
    notification.extras = options.extras;
    notification.broadcastTime = options.broadcastTime;
    notification.channelId = options.channelId;
    notification.priority = options.priority;
    notification.url = options.url;
    return JPushInterface.addLocalNotification(notification);
  }
  removeLocalNotification(id: number): Promise<void> { return JPushInterface.removeLocalNotification(id); }
  clearLocalNotifications(): Promise<void> { return JPushInterface.clearLocalNotifications(); }
  static defaultMessageBackgroundData(data: pushCommon.PushPayload): Promise<boolean> {
    return JPushInterface.defaultMessageBackgroundData(data);
  }

  static async customMessageBackgroundData(data: pushCommon.PushPayload) {
    return JPushInterface.customMessageBackgroundData(data)
  }


  static async extraMessageBackgroundData(data: pushCommon.PushPayload) {
    return JPushInterface.extraMessageBackgroundData(data)
  }

  static async voIPMessageBackgroundData(data: pushCommon.PushPayload) {
    return JPushInterface.voIPMessageBackgroundData(data)
  }

  static receiveExtraDataMessage(rNEAbility: RemoteNotificationExtensionAbility,
    remoteNotificationInfo: pushCommon.RemoteNotificationInfo): Promise<JMessageExtra | undefined> {
    return JPushInterface.receiveExtraDataMessage(rNEAbility,remoteNotificationInfo)
  }
}

class MyCallBackMsg extends CallBackMsg {
  protected context: RNOHContext | undefined;
  private isActive: (() => boolean) | undefined;
  private registered: ((rid: string) => void) | undefined;
  private stateChanged: (() => void) | undefined;

  constructor(co: RNOHContext, isActive: () => boolean,
    registered: (rid: string) => void, stateChanged: () => void) {
    super();
    this.context = co;
    this.isActive = isActive;
    this.registered = registered;
    this.stateChanged = stateChanged;
  }

  dispose(): void {
    this.context = undefined;
    this.isActive = undefined;
    this.registered = undefined;
    this.stateChanged = undefined;
  }

  onRegister(registrationId: string): void {
    if (!this.isActive?.()) return;
    this.registered?.(registrationId);
    this.context?.rnInstance?.emitDeviceEvent('onRegister', registrationId);
  }

  onConnected(isConnected: boolean): void {
    if (!this.isActive?.()) return;
    Logger.info(`onConnected:` + isConnected);
    this.context?.rnInstance?.emitDeviceEvent('onConnected', isConnected);
  }

  onTagOperatorResult(jTagMessage: JTagMessage): void {
    if (!this.isActive?.()) return;
    let message = JSON.stringify(jTagMessage);
    this.context?.rnInstance?.emitDeviceEvent('onTagOperatorResult', message);
  }

  onAliasOperatorResult(jAliasMessage: JAliasMessage): void {
    if (!this.isActive?.()) return;
    let message = JSON.stringify(jAliasMessage);
    this.context?.rnInstance?.emitDeviceEvent('onAliasOperatorResult', message);
  }

  onClickMessage(jMessage: JMessage) {
    if (!this.isActive?.()) return;
    let message = JSON.stringify(jMessage);
    this.context?.rnInstance?.emitDeviceEvent('onClickMessage', message);
  }

  onArrivedMessage(message: JMessage): void {
    if (!this.isActive?.()) return;
    this.context?.rnInstance?.emitDeviceEvent('onArrivedMessage', JSON.stringify(message));
  }

  onUnShowMessage(message: JMessage): void {
    if (!this.isActive?.()) return;
    this.context?.rnInstance?.emitDeviceEvent('onUnShowMessage', JSON.stringify(message));
  }

  onMobileNumberOperatorResult(message: JMobileNumberMessage): void {
    if (!this.isActive?.()) return;
    this.context?.rnInstance?.emitDeviceEvent('onMobileNumberOperatorResult', JSON.stringify(message));
  }

  onCustomMessage(jCustomMessage: JCustomMessage) {
    if (!this.isActive?.()) return;
    let message = JSON.stringify(jCustomMessage);
    this.context?.rnInstance?.emitDeviceEvent('onCustomMessage', message);
  }

  onJMessageExtra(jme: JMessageExtra) {
    if (!this.isActive?.()) return;
    let message = JSON.stringify(jme);
    this.context?.rnInstance?.emitDeviceEvent('onJMessageExtra', message);
  }

  onJMessageVoIP(jmVoIP: JMessageVoIP) {
    if (!this.isActive?.()) return;
    let message = JSON.stringify(jmVoIP);
    this.context?.rnInstance?.emitDeviceEvent('onJMessageVoIP', message);
  }

  onCommandResult(cmdMessage: JCmdMessage) {
    if (!this.isActive?.()) return;
    this.stateChanged?.();
    let message = JSON.stringify(cmdMessage);
    this.context?.rnInstance?.emitDeviceEvent('onCommandResult', message);
  }
}

