# Live samples

The runnable binaries (`installer`, `BraveTalk.dmg`, `package.tar.gz`) are not in this repository.
Putting a working infostealer and its `curl | sh` installer in a public repo would be handing out a
loaded weapon, and GitHub would pull the repo anyway.

Researchers who need the sample can look it up by SHA-256 (see [`iocs/iocs.md`](iocs/iocs.md)) on a
vetted exchange such as MalwareBazaar or VirusTotal. This repo gives you everything needed to
understand and detect the family without the binary: the write-up, the deobfuscation algorithm and a
decoder, decompiled pseudocode of the key routines, the social-engineering scripts with their domains
defanged, IOCs and a YARA rule.

Analysis was done statically on an isolated VM with outbound traffic blocked. Nothing was executed.
