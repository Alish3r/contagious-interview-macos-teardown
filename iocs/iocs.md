# Indicators of compromise

All domains are defanged. Re-fang only inside an isolated lab. They were Cloudflare-fronted
(`188.114.96.6` / `188.114.97.6`), so the IP is Cloudflare, not origin.

## Domains
- `talkbrave[.]org` — fake "Brave Talk" meeting page (real product is `talk.brave.com`)
- `macos.talkbrave[.]org` — macOS download portal + installer script + payload host
- `m.fallproject[.]com` — DMG content-delivery host
- `fallproject[.]com`
- `saifuro[.]com` (+ `docs.`, `verdicts.`) — fake recruiter / company front

## URL patterns
- `/meet/<numericId>?p=<code>` — fake prejoin page
- `/teams/retreive/<code>/` — returns one-time, cloaked download link (note the misspelling "retreive")
- `/evidence/<code>` — POST target for the covert webcam JPEG + mic event
- `/unix/<uuid>` — second-stage `package.tar.gz`
- `/apple/macos/install/interactive/bash` — the `curl | sh` installer script

## Files / hashes (SHA-256)
| File | SHA-256 |
|---|---|
| installer (2nd stage Mach-O, universal) | `782f21b0ce945931bab8b1d84dc57d542a510ec66b80f9034fefd04dcd53572b` |
| BraveTalk.dmg | `8380cf9369598e292bb8403460f183fd038cb25288f57eccc42c4fc8e6f4399c` |
| package.tar.gz | `8ad8a7388f19028846f89faa3c9f205a3eb39b5095f6cb8cb44a9b9b1f2eea66` |
| install.sh | `6203255053fad3014a6dc8afcff811b309c4fdf3fd223fc2da80531915a5ce65` |

## Host artifacts (macOS, if executed)
- a `data.json` written under a `.config` subdirectory in the user's home, inside a disguised app folder
- a process masquerading under a benign "cloudsync"-style name
- outbound HTTPS to the C2 with cookies disabled and any TLS certificate accepted

## Mach-O
- arm64 slice UUID: `D8889234-7422-3CA7-9A1F-759F99E597E9`
- built against macOS SDK 14.0, minimum macOS 13.0, universal arm64 + x86_64
