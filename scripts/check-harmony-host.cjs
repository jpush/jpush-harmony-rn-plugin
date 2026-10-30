#!/usr/bin/env node
'use strict';
const fs = require('node:fs');
const path = require('node:path');
const { execFileSync } = require('node:child_process');
const JSON5 = require('json5');
const NAME = '@rnoh/react-native-openharmony';
function archive(har, member) {
  try { return execFileSync('tar', ['-xOf', har, '--', member], {encoding:'utf8', maxBuffer:8*1024*1024, stdio:['ignore','pipe','pipe']}); }
  catch (_) { throw new Error('Cannot inspect the host RNOH HAR; provide a readable official HAR and tar.'); }
}
function checkHost(configPath) {
  const config = path.resolve(configPath);
  const host = JSON5.parse(fs.readFileSync(config, 'utf8'));
  const override = host.overrides && host.overrides[NAME];
  if (typeof override !== 'string' || !override.startsWith('file:')) {
    throw new Error('Harmony root oh-package.json5 must override @rnoh/react-native-openharmony to the existing host-matched local HAR. The legacy plugin fallback is not shipped.');
  }
  const candidate = path.resolve(path.dirname(config), override.slice(5));
  if (!fs.existsSync(candidate) || !fs.statSync(candidate).isFile() || !candidate.endsWith('.har')) {
    throw new Error('The host RNOH override must resolve to an existing .har file. Do not copy the legacy fallback path or upgrade the framework implicitly.');
  }
  const har = fs.realpathSync(candidate);
  const metadata = JSON5.parse(archive(har, 'package/oh-package.json5'));
  if (metadata.name !== NAME || typeof metadata.version !== 'string') throw new Error('Host HAR is not a versioned @rnoh/react-native-openharmony package.');
  let entries;
  try { entries = execFileSync('tar', ['-tf', har], {encoding:'utf8', maxBuffer:8*1024*1024, stdio:['ignore','pipe','pipe']}).split('\n'); }
  catch (_) { throw new Error('Cannot enumerate the host HAR.'); }
  const lifecycleFiles = entries.filter(n => /(?:^|\/)(?:TurboModule|UITurboModule)\.(?:d\.)?(?:ets|ts)$/.test(n));
  const lifecycle = lifecycleFiles.map(n => archive(har,n)).join('\n');
  const asyncHeader = entries.find(n => n.endsWith('/ArkTSTurboModule.h'));
  if (!lifecycle.includes('__onDestroy__') || !asyncHeader || !archive(har,asyncHeader).includes('callAsync(')) {
    throw new Error('Cannot confirm required __onDestroy__/callAsync declarations in this host HAR; validate its actual RNOH integration instead of assuming compatibility.');
  }
  return {name:metadata.name, version:metadata.version, overrideFileExists:true, lifecycleDeclaration:true, asyncDeclaration:true, nativeBuildValidated:false};
}
module.exports = {checkHost};
if (require.main === module) {
  try {
    if (process.argv.length !== 3) throw new Error('Usage: jpush-harmony-check-host /absolute/path/to/harmony/oh-package.json5');
    console.log(JSON.stringify(checkHost(process.argv[2])));
  } catch (error) { console.error(error.message); process.exitCode=1; }
}
