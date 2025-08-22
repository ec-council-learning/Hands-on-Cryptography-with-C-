# Hands-on-Cryptography-with-C-
Hands-on Cryptography with C++, by EC-Council

## Structure

Files are organized in different subfolders, as follows:

- `snippets/`: Stand-alone source code files that can be compiled with `make`.
- `programs/`: Stand-alone programs and software as designed during the online course.
- `executables/Win`: Pre-compiled executable files for WINDOWS operating system (.exe).
- `executables/Linux`: Pre-compiled executable files for Linux operating system (.bin).
- `executables/MacOS`: Pre-compiled executable files for MacOS operating system (.bin).

## Outline

Some of the most advanced cryptographic concepts are implemented in smaller programs distributed with this repository. Following table lists some of the most prominent *programs* in this repository:

| Program | Description |
| --- | --- |
| `NextVersion` | A C++-language updates and version features tester utility. |
| `ROT13` | Implementation of the **ROT13** algorithm using the standard library. |
| `Randomizer` | Uses random number generators to generate 32-bytes random bytes (Crypto++). |
| `Caesar++` | A digital remake of the popular Caesar Cipher from 2000 years ago (Crypto++). |
| `Curvy++` | Elliptic curve cryptography with **ed25519**, **secp256** and **PKCS1** (Crypto++). |
| `CryptoStars` | Mastering Crypto++: **ECDSA**, **AES**, **ECDH**, **ChaCha20** and **ROT13** (Crypto++). |
| `Flowers` | A minimal implementation of **Camellia** encryption/decryption (Botan). |
| `Handshaker` | A handshake-only implementation of **TLS** communication channels (Botan). |
| `BeeTransport` | A more elaborated use-case for symmetric encryption with **Camellia** (Botan). |
| `SecretMaker` | A simplistic Makefile with **RSA** keys, **AES** encryption and **ECDSA** signatures (Botan). |
| `WhatBlock` | Encryption block-by-block using block ciphers: **AES**, **ARIA**, **Blowfish**, and others (Botan). |
| `SymmetryRace` | A race between Symmetric- and Asymmetric Encryption Algorithms: **AES** vs. **RSA** (Botan). |
| `Siggie` | A DSA command line utility featuring **secp256**, sign documents using **ECDSA** (Botan). |
| `HTTPSafe` | An example implementation for TLS channels over HTTP to configure HTTPS connections (Botan). |
| `SMS++` | An asynchronous authenticated messaging system using **ECIES** system and **ECDH** (Botan). |
| `Whispers` | An end-to-end encrypted offline chat using **ECIES** system, **ECDH** and ephemeral keys (Botan). |
| `ZThanks` | A pot-pourri of Botan *and* Crypto++ integrations with: **AES**, **SHA-256**, **ECDSA** and **ECDH**. |

## License

This software is released under the [MIT](./LICENSE) License.

Copyright © 2023-present EC-Council Learning.
