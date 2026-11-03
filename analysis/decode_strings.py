#!/usr/bin/env python3
"""
Reverse cloudsync_impl::sobf::reveal() - the malware's compile-time string XOR.
Defensive IOC / config extraction only. Pure data transform; runs nothing.

    plain[i] = cipher[i] ^ ((seed*0x83 + i*0x11) & 0xff) ^ K[seed & 31] ^ K[i & 31]

K is the 32-byte table embedded in the binary (recovered below). Each obfuscated
string carries its own 1-byte `seed`. We brute-force seed 0..255 and keep the
decodes that are fully printable ASCII.

Usage:  python3 decode_strings.py <hex-ciphertext>
Example (the global _ct_APP_* strings that decode cleanly this way):
    python3 decode_strings.py 15e55e98d071b5        ->  seed 191: '.config'
    python3 decode_strings.py 526ac802ed67949a16    ->  seed 211: 'data.json'
"""
import sys

K = bytes.fromhex("d719bf57e65ba09de1bacdb182c99118edafd518fd3a4a9797bcad221adb8151")

def reveal(cipher: bytes, seed: int) -> bytes:
    return bytes(
        cipher[i] ^ ((seed * 0x83 + i * 0x11) & 0xFF) ^ K[seed & 31] ^ K[i & 31]
        for i in range(len(cipher))
    )

def printable(b: bytes) -> bool:
    return bool(b) and all(0x20 <= x < 0x7F for x in b)

def main():
    if len(sys.argv) != 2:
        print(__doc__); return
    ct = bytes.fromhex(sys.argv[1].replace(" ", ""))
    found = [(s, reveal(ct, s).decode()) for s in range(256) if printable(reveal(ct, s))]
    if not found:
        print("no fully-printable seed; wrong length or a different (CTEnc) keying")
        return
    for seed, text in found:
        print(f"seed {seed:3d}: {text!r}")

if __name__ == "__main__":
    main()
