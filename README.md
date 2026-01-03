# Performance - High-Performance Tcl Extension

A Tcl extension providing high-performance cryptographic operations implemented in C for speed. Currently implements XOR cipher operations for simple encryption and obfuscation of binary data.

## Features

- **High-Performance XOR Operations**: C-implemented XOR cipher for fast binary data processing
- **Symmetric Encryption**: Simple encryption/decryption with the same key
- **Binary Data Support**: Works with any binary data including files and byte arrays
- **Key Cycling**: Automatically repeats shorter keys across longer data
- **Zero Dependencies**: Pure C implementation with no external library requirements

## Building

Standard TEA build process:

```bash
autoconf
./configure --with-tcl=/path/to/tclConfig.sh
make
make install
```

### Build Requirements

- Tcl 8.6+
- C compiler (gcc/clang/MSVC)
- autoconf

### Windows Build

```bash
autoconf
./configure
make
make install
```

## Using in Your Application

```tcl
package require Performance 0.1

# Encrypt a string
set plaintext "Hello World"
set key "secret"
set encrypted [xor $plaintext $key]

# Decrypt back to original
set decrypted [xor $encrypted $key]
# $decrypted equals $plaintext
```

### Command Format

`xor` *data* *key*

Where:
- *data* is the binary data to XOR (string or byte array)
- *key* is the XOR key (repeats cyclically if shorter than data)

Returns the XOR result as a binary value (byte array).

### Error Conditions

Returns an error if:
- Wrong number of arguments provided (requires exactly 2 arguments)
- Invalid data types

## Examples

### Basic Encryption

```tcl
package require Performance

# Encrypt a string
set plaintext "Hello World"
set key "secret"
set encrypted [xor $plaintext $key]
puts "Encrypted: [binary encode hex $encrypted]"

# Decrypt back to original
set decrypted [xor $encrypted $key]
puts "Decrypted: $decrypted"
```

### Binary File Processing

```tcl
# Read binary file
set fd [open "data.bin" rb]
set data [read $fd]
close $fd

# XOR encrypt the data
set key "encryption_key"
set encrypted [xor $data $key]

# Write encrypted data
set fd [open "data.enc" wb]
puts -nonewline $fd $encrypted
close $fd
```

### Key Repeating

```tcl
# Short key repeats cyclically across longer data
set data "AAAAAAAAAA"
set key "XY"
set result [xor $data $key]
# Each byte alternates between A XOR X and A XOR Y
```

## Security Considerations

**IMPORTANT**: The XOR cipher is **not cryptographically secure** and should not be used for serious encryption.

### Suitable Uses

- Simple obfuscation of data
- Checksums and data integrity checks
- Educational purposes
- Performance testing and benchmarking

### Not Suitable For

- Protecting sensitive or confidential data
- Production security applications
- Any scenario requiring cryptographic security

### Secure Alternatives

For secure encryption, use proper cryptographic libraries:
- **tcltls** for TLS/SSL communications
- **Tcllib's aes** module for AES encryption
- External tools like OpenSSL or GPG

## Running Tests

```bash
make test
```

The test suite includes:
- Basic functionality tests (basic.test)
- XOR operation tests (xor.test)
- Round-trip encryption/decryption tests
- Binary data handling tests
- Key cycling verification

## Implementation Details

- XOR operations are performed byte-by-byte in C for maximum performance
- Keys shorter than data are repeated cyclically
- All operations are symmetric: `xor(xor(data, key), key) = data`
- Works with binary data, UTF-8 strings, and raw byte arrays

## Requirements

- Tcl 8.6 or higher
- C compiler with standard library support

## Version

**Current Version**: 0.1

## Author

Thomas Perschak (2025)

## License

MIT License - See LICENSE file for details.

## Use Cases

### Data Obfuscation
- Simple configuration file obfuscation
- Non-sensitive data encoding
- Quick data masking

### Educational
- Teaching basic encryption concepts
- Demonstrating XOR cipher properties
- Cryptography fundamentals

### Performance Testing
- Benchmarking binary data operations
- Testing Tcl extension performance
- Memory efficiency validation

## See Also

- binary(n) - Binary data handling in Tcl
- encoding(n) - Character encoding conversion
- tcltls(n) - TLS/SSL for secure communications
