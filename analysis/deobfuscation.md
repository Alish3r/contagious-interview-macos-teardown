# The string obfuscation, fully reversed

The malware keeps its configuration (file names, directory names, the exfil endpoint, format
strings) encrypted inside the binary and only decrypts each string at runtime, in
`cloudsync_impl::sobf::reveal()`. That defeats a plain `strings` dump. Here is the whole scheme.

## The algorithm

```
plain[i] = cipher[i] XOR ((seed * 0x83 + i * 0x11) & 0xff) XOR K[seed & 31] XOR K[i & 31]
```

- `cipher` is the per-string encrypted byte array baked into the binary.
- `i` is the byte index.
- `seed` is a one-byte constant chosen per string (brute-forceable 0..255).
- `K` is a single 32-byte table shared by every string:

```
d7 19 bf 57 e6 5b a0 9d e1 ba cd b1 82 c9 91 18
ed af d5 18 fd 3a 4a 97 97 bc ad 22 1a db 81 51
```

Two terms make it look busier than it is: a position-dependent keystream
(`seed*0x83 + i*0x11`, wrapping at 256) and two table lookups folded in by `seed` and by `i`.
It is still just a reversible XOR. No network, no key exchange, nothing clever cryptographically.
It only raises the cost of a casual `strings` triage.

## Decoder

`decode_strings.py` re-implements `reveal()` and brute-forces the seed:

```
$ python3 decode_strings.py 15e55e98d071b5       # -> seed 191: '.config'
$ python3 decode_strings.py 526ac802ed67949a16   # -> seed 211: 'data.json'
```

## What it hides

- `~/.config` style staging directory
- `data.json` — the file the stolen password/credentials are written to before exfil
- install dir, process-disguise name, instance-lock name, tmp swap/spawn prefixes, `.sh` suffix

## The layer it does NOT cover

The runtime C2 URL is built from a second, inline string class (`sobf::CTEnc<N>`) whose keying
differs from the global strings above and did not fall to the same XOR, and the network stage
is likely the separate `cshelper` binary inside the DMG. So the literal C2 host is still
encrypted here. The *exfil body* is additionally ChaCha-encrypted (`APP_CHACHA_KEY`,
`APP_OPS_CHACHA_IV`) and wrapped with base64 + zero-width-character encoding — three layers:
transport TLS, ChaCha body, and the string table.
