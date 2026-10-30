const {test}=require('node:test');
const assert=require('node:assert/strict');
const fs=require('node:fs');
const path=require('node:path');
const vm=require('node:vm');
const ts=require(process.env.TYPESCRIPT_PATH || 'typescript');
function api(native) {
 const exports={};
 const code=ts.transpileModule(fs.readFileSync(process.env.JPUSH_API_SOURCE || path.join(__dirname,'../src/index.ts'),'utf8'),{compilerOptions:{target:ts.ScriptTarget.ES2020,module:ts.ModuleKind.CommonJS}}).outputText;
 vm.runInNewContext(code,{exports,require(id){assert.equal(id,'./NativeJPushTurboModule');return {__esModule:true,default:native};},Proxy,Reflect,Map,Object});
 return exports.JPushModule;
}
test('public stop getters normalize null and undefined while retaining both booleans',async()=>{
 for(const state of [undefined,null,false,true]){
  let sync=0,async=0;
  const n={isPushStopped(){assert.equal(this,n);sync++;return state;},isPushStoppedAsync(){assert.equal(this,n);async++;return Promise.resolve(state);}};
  const j=api(n),expected=state==null?undefined:state;
  assert.equal(j.isPushStopped(),expected);assert.equal(await j.isPushStoppedAsync(),expected);
  assert.equal(sync,1);assert.equal(async,1);
  assert.equal(j.isPushStopped,j.isPushStopped);assert.equal(j.isPushStoppedAsync,j.isPushStoppedAsync);
 }
});
test('public stop getters preserve synchronous errors and asynchronous rejection identity',async()=>{
 const error=Error('state unavailable');const n={isPushStopped(){throw error;},isPushStoppedAsync(){return Promise.reject(error);}};const j=api(n);
 assert.throws(()=>j.isPushStopped(),e=>e===error);await assert.rejects(j.isPushStoppedAsync(),e=>e===error);
});
test('every other declared method remains callable with its native receiver and arguments',async()=>{
 const spec=fs.readFileSync(path.join(__dirname,'../src/NativeJPushTurboModule.ts'),'utf8');
 const tree=ts.createSourceFile('NativeJPushTurboModule.ts',spec,ts.ScriptTarget.Latest,true);
 const declaration=tree.statements.find(n=>ts.isInterfaceDeclaration(n)&&n.name.text==='Spec');assert.ok(declaration);
 const declared=declaration.members.filter(ts.isMethodSignature);assert.ok(declared.length>30);
 const methods=declared.filter(m=>!['isPushStopped','isPushStoppedAsync'].includes(m.name.getText(tree))).map(m=>[null,m.name.getText(tree),m.parameters.map(p=>p.getText(tree)).join(','),m.type.getText(tree)]);
 const calls=[],n={isPushStopped(){return false;},isPushStoppedAsync(){return Promise.resolve(false);}};
 for(const m of methods)n[m[1]]=function(...args){assert.equal(this,n);calls.push([m[1],args]);return m[3].startsWith('Promise')?Promise.resolve(m[1]):m[1]};
 const j=api(n);
 for(const m of methods){const args=m[2]?m[2].split(',').map((_,i)=>i):[];assert.equal(await j[m[1]](...args),m[1]);assert.deepEqual(calls.at(-1),[m[1],args]);assert.equal(j[m[1]],j[m[1]]);}
 assert.equal(calls.length,methods.length);
});
test('module keys, symbols, prototype and non-method properties are preserved without spreading',()=>{
 const symbol=Symbol('metadata'),proto={shared:'sentinel'},n=Object.assign(Object.create(proto),{isPushStopped(){return null;},isPushStoppedAsync(){return Promise.resolve(null);},version:1});n[symbol]='value';const j=api(n);
 assert.deepEqual(Reflect.ownKeys(j),Reflect.ownKeys(n));assert.equal(Object.getPrototypeOf(j),proto);assert.equal(j.version,1);assert.equal(j.shared,'sentinel');assert.equal(j[symbol],'value');assert.equal(j.constructor,n.constructor);assert.equal(j.toString,n.toString);
 for(const key of Reflect.ownKeys(n))assert.deepEqual(Object.getOwnPropertyDescriptor(j,key),Object.getOwnPropertyDescriptor(n,key));
});
test('forwarded methods follow native replacements rather than retaining stale functions',()=>{
 const n={isPushStopped(){return false;},isPushStoppedAsync(){return Promise.resolve(false);},getRegistrationId(){return 'first';}};const j=api(n);assert.equal(j.getRegistrationId(),'first');const first=j.getRegistrationId;n.getRegistrationId=function(){assert.equal(this,n);return 'second';};assert.equal(j.getRegistrationId(),'second');assert.notEqual(j.getRegistrationId,first);
});
