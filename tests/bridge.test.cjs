const {test}=require('node:test');
const assert=require('node:assert/strict');
const fs=require('node:fs');
const vm=require('node:vm');
const path=require('node:path');
const ts=require(process.env.TYPESCRIPT_PATH || 'typescript');
const file=path.join(__dirname,'../harmony/jpush_harmony/src/main/ets/JPushTurboModule.ets');
function host() {
 let callback, rid='r1', stopped=false, failInit=false;
 const events=[], calls=[];
 const sdk={
  setCallBackMsg(c){callback=c;}, setContext(){},
  async init(){if(failInit)throw Error('native init');},
  async getRegistrationId(){return rid;}, async isPushStopped(){return stopped;},
  async turnOffPush(){stopped=true;return {code:0,msg:'ok'};},
  turnOnPush(){stopped=false;},stopPush(){stopped=true;},resumePush(){stopped=false;},
  async addLocalNotification(n){calls.push(n);},
 };
 const exports={};
 const code=ts.transpileModule(fs.readFileSync(file,'utf8'),{compilerOptions:{target:ts.ScriptTarget.ES2020,module:ts.ModuleKind.CommonJS}}).outputText;
 const native=new Proxy(sdk,{get(o,k){return o[k]||((...args)=>{calls.push([k,...args]);return Promise.resolve();});}});
 vm.runInNewContext(code,{exports,require(id){if(id==='@jg/push')return {JPushInterface:native,CallBackMsg:class{},JPushLocalNotification:class{},JCollectControl:native};if(id.startsWith('@rnoh'))return {TurboModule:class{__onDestroy__(){}}};if(id==='./Logger')return {default:{info(){}}};return {};},console,Promise,Number,Error});
 const ctx={uiAbilityContext:{getApplicationContext(){return {};}},rnInstance:{emitDeviceEvent(name,payload){events.push([name,payload]);}}};
 const module=new exports.JPushTurboModule(ctx);
 return {module,events,calls,sdk,callback:()=>callback,fail(){failInit=true;},setRid(x){rid=x;}};
}
const tick=()=>new Promise(r=>setImmediate(r));
test('legacy cache starts empty; async getters and registration update cache',async()=>{
 const h=host();assert.equal(h.module.getRegistrationId(),'');assert.equal(h.module.isPushStopped(),undefined);
 await h.module.initAsync();assert.equal(h.module.getRegistrationId(),'r1');assert.equal(h.module.isPushStopped(),false);
 h.callback().onRegister('r2');assert.equal(h.module.getRegistrationId(),'r2');
 h.setRid('r3');assert.equal(await h.module.getRegistrationIdAsync(),'r3');assert.equal(h.module.getRegistrationId(),'r3');
});
test('void init consumes native rejection and exposes error; async init rejects',async()=>{
 const h=host();h.fail();h.module.init();await tick();assert.equal(h.events[0][0],'onBridgeError');
 await assert.rejects(h.module.initAsync(),/native init/);
});
test('superseded and invalidated callbacks do not emit or change cache',async()=>{
 const h=host();await h.module.initAsync();const old=h.callback();await h.module.initAsync();old.onRegister('stale');assert.equal(h.module.getRegistrationId(),'r1');
 const active=h.callback();h.module.__onDestroy__();active.onRegister('late');active.onClickMessage({msgId:'late'});assert.equal(h.module.getRegistrationId(),'');assert.equal(h.events.length,0);
});
test('concurrent async results independent; late getter cannot repopulate invalidated cache',async()=>{
 const h=host();let resolve;h.sdk.getRegistrationId=()=>new Promise(r=>resolve=r);const result=h.module.getRegistrationIdAsync();h.module.invalidate();resolve('late');assert.equal(await result,'late');assert.equal(h.module.getRegistrationId(),'');
 const h2=host();const values=await Promise.all([h2.module.getRegistrationIdAsync(),h2.module.isPushStoppedAsync()]);assert.deepEqual(values,['r1',false]);
});
test('stop/resume and UPS update cached state without reporting dispatch as server result',async()=>{
 const h=host();await h.module.initAsync();const result=await h.module.turnOffPush();assert.equal(result.code,0);assert.equal(h.module.isPushStopped(),true);
 h.module.turnOnPush();await tick();assert.equal(h.module.isPushStopped(),false);
 h.module.stopPush();await tick();assert.equal(h.module.isPushStopped(),true);h.module.resumePush();await tick();assert.equal(h.module.isPushStopped(),false);
});
test('new notifications and VoIP preserve large string ID/new payload fields and old JSON event shape',async()=>{
 const h=host();await h.module.initAsync();const message={msgId:'9223372036854775807',channel:1,notificationType:1};h.callback().onArrivedMessage(message);h.callback().onUnShowMessage(message);h.callback().onJMessageVoIP({msgId:message.msgId,callId:'call'});
 assert.equal(JSON.parse(h.events[0][1]).msgId,message.msgId);assert.equal(JSON.parse(h.events[1][1]).notificationType,1);assert.equal(JSON.parse(h.events[2][1]).callId,'call');
});
test('local notification invalid numbers reject before SDK; valid fields forward',async()=>{
 const h=host();await assert.rejects(h.module.addLocalNotification({notificationId:1.5,broadcastTime:0}),/E_INVALID_ARGUMENT/);
 await h.module.addLocalNotification({notificationId:1,title:'test',content:'body',extras:'{}',broadcastTime:0,channelId:'',priority:0,url:''});assert.equal(h.calls[0].notificationId,1);
});
test('every new TS method has C++ metadata with correct argument count and Promise dispatch',()=>{
 const spec=fs.readFileSync(path.join(__dirname,'../src/NativeJPushTurboModule.ts'),'utf8');const cpp=fs.readFileSync(path.join(__dirname,'../harmony/jpush_harmony/src/main/cpp/JPushTurboModuleSpec.cpp'),'utf8');
 for(const m of spec.matchAll(/^  (\w+)\(([^)]*)\): (.+);$/gm)) {
  const count=m[2]?m[2].split(',').length:0;
  assert.match(cpp,new RegExp('methodMap_\\["'+m[1]+'"\\]\\s*=\\s*MethodMetadata\\{'+count+','));
  if(m[3].startsWith('Promise'))assert.ok(cpp.includes('callAsync(rt, "'+m[1]+'"'));
 }
});

test('dispose releases context and captured closures without clearing another module callback',async()=>{
 const a=host();await a.module.initAsync();const old=a.callback();await a.module.initAsync();
 for(const key of ['context','isActive','registered','stateChanged'])assert.equal(old[key],undefined);
 const b=host();await b.module.initAsync();const current=b.callback();a.module.__onDestroy__();
 for(const key of ['context','isActive','registered','stateChanged'])assert.equal(a.callback()[key],undefined);
 current.onRegister('other');assert.equal(b.module.getRegistrationId(),'other');assert.ok(current.context);
});
