import NativeJPushModule from './NativeJPushTurboModule';
function normalizePushState(value: boolean | null | undefined): boolean | undefined {
  return value == null ? undefined : value;
}

const getCachedPushState = (): boolean | undefined =>
  normalizePushState(NativeJPushModule.isPushStopped());
const getCurrentPushState = (): Promise<boolean | undefined> =>
  NativeJPushModule.isPushStoppedAsync().then(normalizePushState);
const forwardedMethods = new Map<PropertyKey, { original: Function; bound: Function }>();

/** Keep the native module intact while normalizing its optional state values. */
export const JPushModule: typeof NativeJPushModule = new Proxy(NativeJPushModule, {
  get(target, property) {
    if (property === 'isPushStopped') return getCachedPushState;
    if (property === 'isPushStoppedAsync') return getCurrentPushState;
    const value = Reflect.get(target, property, target);
    if (typeof value !== 'function' || Object.prototype.hasOwnProperty.call(Object.prototype, property)) {
      return value;
    }
    const cached = forwardedMethods.get(property);
    if (cached?.original === value) return cached.bound;
    const bound = value.bind(target);
    forwardedMethods.set(property, { original: value, bound });
    return bound;
  },
});
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
