import NativeJPushModule from './NativeJPushTurboModule';
export const JPushModule = NativeJPushModule;
export type { LocalNotificationOptions, PushResult } from './NativeJPushTurboModule';

/** Native events retain JSON strings; parse before using these payload types. */
export type NotificationMessage = {
  msgId?: string; title?: string; content?: string; extras?: Record<string, Object>;
  channel: number; notificationType: number;
};
export type VoIPMessage = { msgId?: string; extraData?: string; callId?: string };
export type CommandMessage = {
  cmd?: number; errorCode?: number; msg?: string; extra?: Record<string, Object>;
};
