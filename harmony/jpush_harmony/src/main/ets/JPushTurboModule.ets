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
  JCmdMessage
} from '@jg/push';


export class JPushTurboModule extends TurboModule {
  protected _context: common.UIAbilityContext;
  protected _RnContext: RNOHContext;

  constructor(ctx: RNOHContext) {
    super(ctx);
    this._context = ctx?.uiAbilityContext;
    this._RnContext = ctx;

  }

  async init() {
    Logger.info(`init `);
    JPushInterface.init(this._context.getApplicationContext())
    JPushInterface.setCallBackMsg(new MyCallBackMsg(this._RnContext))
  }

  static setClickWant(want: Want) {
    JPushInterface.setClickWant(want)
  }

  setDebug(d: boolean) {
    Logger.info(`setDebug `);
    JPushInterface.setDebug(d)
  }

  setAppKey(appKey: string) {
    Logger.info(`setAppKey:`+appKey);
    JPushInterface.setAppKey(appKey)
  }

  setChannel(channel: string) {
    Logger.info(`setChannel: `+channel);
    JPushInterface.setChannel(channel)
  }

  getRegistrationId(): string {
    Logger.info(`getRegistrationId `);
    return JPushInterface.getRegistrationId()
  }

  setTags(sequence: number, tags: string[]) {
    Logger.info(`setTags tags:`+tags);
    JPushInterface.setTags(sequence, tags)
  }

  addTags(sequence: number, tags: string[]) {
    Logger.info(`addTags tags:`+tags);
    JPushInterface.addTags(sequence, tags)
  }

  deleteTags(sequence: number, tags: string[]) {
    Logger.info(`deleteTags tags:`+tags);
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
    Logger.info(`checkTagBindState tag:`+tag);
    JPushInterface.checkTagBindState(sequence, tag)
  }

  setAlias(sequence: number, alias: string) {
    Logger.info(`setAlias alias:`+alias);
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
  }

  resumePush() {
    Logger.info(`resumePush `);
    JPushInterface.resumePush()
  }

  isPushStopped(): boolean | undefined {
    Logger.info(`isPushStopped `);
    return JPushInterface.isPushStopped()
  }

  setBadgeNumber(badgeNumber: number) {
    Logger.info(`setBadgeNumber:`+badgeNumber);
    JPushInterface.setBadgeNumber(badgeNumber)
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
    return JPushInterface.receiveExtraDataMessage(remoteNotificationInfo)
  }
}

class MyCallBackMsg extends CallBackMsg {
  protected context: RNOHContext;

  constructor(co: RNOHContext) {
    super();
    this.context = co
  }

  onRegister(registrationId: string): void {
    Logger.info(`onRegister:` + registrationId);
    this.context?.rnInstance?.emitDeviceEvent('onRegister', registrationId);
  }

  onConnected(isConnected: boolean): void {
    Logger.info(`onConnected:` + isConnected);
    this.context?.rnInstance?.emitDeviceEvent('onConnected', isConnected);
  }

  onTagOperatorResult(jTagMessage: JTagMessage): void {
    let message = JSON.stringify(jTagMessage);
    Logger.info(`onTagOperatorResult:` + message);
    this.context?.rnInstance?.emitDeviceEvent('onTagOperatorResult', message);
  }

  onAliasOperatorResult(jAliasMessage: JAliasMessage): void {
    let message = JSON.stringify(jAliasMessage);
    Logger.info(`onAliasOperatorResult:` + message);
    this.context?.rnInstance?.emitDeviceEvent('onAliasOperatorResult', message);
  }

  onClickMessage(jMessage: JMessage) {
    let message = JSON.stringify(jMessage);
    Logger.info(`onClickMessage:` + message);
    this.context?.rnInstance?.emitDeviceEvent('onClickMessage', message);
  }

  onCustomMessage(jCustomMessage: JCustomMessage) {
    let message = JSON.stringify(jCustomMessage);
    Logger.info(`onCustomMessage:` + message);
    this.context?.rnInstance?.emitDeviceEvent('onCustomMessage', message);
  }

  onJMessageExtra(jme: JMessageExtra) {
    let message = JSON.stringify(jme);
    Logger.info(`onJMessageExtra:` + message);
    this.context?.rnInstance?.emitDeviceEvent('onJMessageExtra', message);
  }

  onJMessageVoIP(jmVoIP: JMessageVoIP) {
    let message = JSON.stringify(jmVoIP);
    Logger.info(`onJMessageVoIP:` + message);
    this.context?.rnInstance?.emitDeviceEvent('onJMessageVoIP', message);
  }

  onCommandResult(cmdMessage: JCmdMessage) {
    let message = JSON.stringify(cmdMessage);
    Logger.info(`onCommandResult:` + message);
    this.context?.rnInstance?.emitDeviceEvent('onCommandResult', message);
  }
}

