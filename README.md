# C509-Native (Research Project)

C509-Native is a prototypical C++ implementation of [natively-signed C509 certificates](https://www.ietf.org/archive/id/draft-ietf-cose-cbor-encoded-cert-13.html) (and other CBOR encoded structures like CRLs, OCSP and SCVP messages ), integrating post-quantum cryptography using liboqs and OpenSSL. The project supports generating, parsing, and verifying natively-signed C509 certificates by implementing simplified versions of OpenSSL commands.

## Features
- CLI for generating CBOR-encoded hybrid (ML_DSA + ECC) post-quantum keys, certificates, and certificate requests.
- Integration with oqs-proivder (built as static library) and liboqs.
- Integration with ZCBOR and parser generation via CDDL scheme (requires Python).
- Does not use dynamic allocation.

## Project Structure & Dependencies

- `src/`: Implementation modules
  - **structures**: Define the data structures.
  - **codec**: encoding/decoding various *structures* (algorithms, attributes, extensions, etc.).
  - **crypto**: OpenSSL integration.
  - **core**: main logic based on *crypto*, *structures* and *codec*.
  - **cli**: interfacing with the *core*.

### External Dependencies
- **Argparse**: Command-line argument parsing.
- **ZCBOR**: CBOR encoding and decoding.
- **liboqs**: Quantum-safe cryptographic algorithms.
- **oqs-provider**: Open Quantum Safe integration with OpenSSL.
- **Catch2**: Testing framework.

## Building the Project

### Build Options
- `ENABLE_GEN_ZCBOR_CODEC`: Generates encoders and decoders from CDDL schemas.
- `ENABLE_TESTING`: Enables building and running tests.

### Example Build Steps
```shell
git clone https://github.com/rosualinpetru/c509-native.git
cd c509-native
mkdir build
cd build
cmake -DENABLE_GEN_ZCBOR_CODEC=ON -DENABLE_TESTING=ON ..
make
```

## Running the Demo
A demo script is included to guide users through key features:
```shell
./demo.sh
```

## Directory Structure
- `cmake/`: Build configuration files.
- `docs/`: Project documentation.
- `external/`: External dependencies.
- `resource/`: Schema files (CDDL).
- `src/`: Main source code.
- `test/`: Tests for validating encoding and decoding.

## Documentation
Work in progress.

## License
All code is available to you under the MIT license, available at http://opensource.org/licenses/mit-license.php and also in the LICENSE file.

## Contact
For questions or feedback:
- **Alin-Petru Roșu**
- Email: rosualinpetru@gmail.com

