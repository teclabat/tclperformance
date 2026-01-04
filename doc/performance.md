# Tcl Performance Extension - High-Speed XOR Operations

A Tcl extension providing high-performance cryptographic operations implemented in C for maximum speed. Currently implements XOR cipher operations for simple encryption and obfuscation of binary data.

**Version:** 1.0.0 \
**Package:** `performance` \
**Namespace:** `performance::`

---

## Table of Contents

1. [Overview](#overview)
2. [Key Features](#key-features)
3. [Use Cases](#use-cases)
4. [Installation](#installation)
5. [Command Reference](#command-reference)
   - 5.1 [XOR Operations](#xor-operations)
6. [Usage Examples](#usage-examples)
7. [Security Considerations](#security-considerations)
8. [Best Practices](#best-practices)
9. [Troubleshooting](#troubleshooting)
10. [Technical Notes](#technical-notes)
11. [See Also](#see-also)
12. [License](#license)
13. [Version History](#version-history)

---

## Overview

The **performance** package provides a Tcl interface to high-performance XOR cipher operations implemented in C. The XOR cipher is a simple symmetric encryption algorithm that performs bitwise XOR operations between data and a key.

**IMPORTANT**: This implementation is designed for **non-cryptographic** purposes only. XOR cipher is not cryptographically secure and should never be used to protect sensitive or confidential data.

## Key Features

- **High-Performance C Implementation**: Native C code for maximum speed
- **Binary Data Support**: Works with any binary data including files and byte arrays
- **Symmetric Operations**: Same key encrypts and decrypts data
- **Automatic Key Cycling**: Keys shorter than data repeat automatically
- **Zero External Dependencies**: Pure C implementation with standard library
- **Cross-Platform**: Supports Windows, Linux, and macOS
- **Lightweight**: Minimal memory footprint and fast execution
- **TEA Compliant**: Follows Tcl Extension Architecture standards

## Use Cases

### Data Obfuscation
- Simple configuration file obfuscation
- Non-sensitive data encoding
- Quick data masking for storage
- License key generation (non-security)

### Educational Purposes
- Teaching basic encryption concepts
- Demonstrating XOR cipher properties
- Understanding symmetric encryption
- Cryptography fundamentals

### Performance Testing
- Benchmarking binary data operations
- Testing Tcl extension performance
- Memory efficiency validation
- Data throughput measurements

### Checksums and Validation
- Simple data integrity checks
- Checksum generation
- Data verification (non-cryptographic)

---

## Installation

```tcl
package require performance
```

### Requirements

**Build-time**:
- Tcl 8.6 or later
- C compiler (gcc, clang, or MSVC)
- Autoconf and GNU Make
- Standard C library

**Runtime**:
- Tcl 8.6+
- No external dependencies

### Building from Source

**Unix/Linux/macOS:**
```bash
cd D:\CM.tcltk\tclperformance
autoconf
./configure --with-tcl=/path/to/tclConfig.sh
make
make test
make install
```

**Windows (MSYS/MinGW):**
```bash
cd D:\CM.tcltk\tclperformance
autoconf
./configure
make
make test
make install
```

**Configuration Options:**
```bash
./configure --help                    # Show all options
./configure --prefix=/usr/local       # Set installation prefix
./configure --enable-threads          # Enable thread support
```

---

## Command Reference

### XOR Operations

#### `performance::xor`

Performs XOR operation between data and key, returning the result as a binary byte array.

**Syntax:**
```tcl
set result [performance::xor data key]
```

**Parameters:**

- `data` - Binary data to XOR (string or byte array)
- `key` - XOR key (repeats cyclically if shorter than data)

**Returns:**

- Byte array containing XOR result
- Length equals length of `data` parameter

**Key Cycling:**

If the key is shorter than the data, it automatically repeats:
- Data: `[A B C D E F G H]` (8 bytes)
- Key: `[X Y]` (2 bytes)
- Result: `[A^X B^Y C^X D^Y E^X F^Y G^X H^Y]`

**Properties:**

- **Symmetric**: `xor(xor(data, key), key) = data`
- **Commutative**: `xor(a, b) = xor(b, a)`
- **Associative**: `xor(xor(a, b), c) = xor(a, xor(b, c))`
- **Identity**: `xor(a, 0) = a`
- **Self-inverse**: `xor(a, a) = 0`

**Errors:**

- Wrong number of arguments (requires exactly 2)
- Invalid data types

**Example:**
```tcl
set plaintext "Hello World"
set key "secret"
set encrypted [performance::xor $plaintext $key]
puts "Encrypted: [binary encode hex $encrypted]"
# Output: "Encrypted: 3f0a0d1900584c1a0306"

# Decrypt back to original
set decrypted [performance::xor $encrypted $key]
puts "Decrypted: $decrypted"
# Output: "Decrypted: Hello World"
```

---

## Usage Examples

### Example 1: Basic String Encryption

```tcl
package require performance

# Encrypt a string
set plaintext "Hello World"
set key "secret"
set encrypted [performance::xor $plaintext $key]
puts "Encrypted (hex): [binary encode hex $encrypted]"

# Decrypt back to original
set decrypted [performance::xor $encrypted $key]
puts "Decrypted: $decrypted"
# Output: "Hello World"
```

---

### Example 2: Binary File Encryption

```tcl
package require performance

# Read binary file
set fd [open "data.bin" rb]
set data [read $fd]
close $fd

puts "Original size: [string length $data] bytes"

# XOR encrypt the data
set key "encryption_key_12345"
set encrypted [performance::xor $data $key]

# Write encrypted data
set fd [open "data.enc" wb]
puts -nonewline $fd $encrypted
close $fd

puts "Encrypted file saved: data.enc"
```

---

### Example 3: Round-Trip File Processing

```tcl
package require performance

proc encrypt_file {input_file output_file key} {
    # Read original file
    set fd [open $input_file rb]
    set data [read $fd]
    close $fd

    # Encrypt
    set encrypted [performance::xor $data $key]

    # Write encrypted file
    set fd [open $output_file wb]
    puts -nonewline $fd $encrypted
    close $fd

    puts "Encrypted: $input_file -> $output_file"
}

proc decrypt_file {input_file output_file key} {
    # Read encrypted file
    set fd [open $input_file rb]
    set encrypted [read $fd]
    close $fd

    # Decrypt (same operation as encrypt)
    set decrypted [performance::xor $encrypted $key]

    # Write decrypted file
    set fd [open $output_file wb]
    puts -nonewline $fd $decrypted
    close $fd

    puts "Decrypted: $input_file -> $output_file"
}

# Usage
set key "my_secret_key"
encrypt_file "document.txt" "document.enc" $key
decrypt_file "document.enc" "document_restored.txt" $key
```

---

### Example 4: Key Cycling Demonstration

```tcl
package require performance

# Short key repeats cyclically across longer data
set data "AAAAAAAAAA"
set key "XY"
set result [performance::xor $data $key]

# Display results
puts "Data: $data"
puts "Key:  $key (repeats)"
puts "Result (hex): [binary encode hex $result]"

# Each byte alternates between A XOR X and A XOR Y
# A=0x41, X=0x58, Y=0x59
# 0x41 ^ 0x58 = 0x19
# 0x41 ^ 0x59 = 0x18
# Output: "191819181918191819"
```

---

### Example 5: Unicode Text Handling

```tcl
package require performance

# Unicode string
set plaintext "Hello 世界"
set key "secret"

# Convert to UTF-8 binary
set utf8_data [encoding convertto utf-8 $plaintext]
puts "UTF-8 length: [string length $utf8_data] bytes"

# Encrypt
set encrypted [performance::xor $utf8_data $key]
puts "Encrypted (hex): [binary encode hex $encrypted]"

# Decrypt
set decrypted_utf8 [performance::xor $encrypted $key]

# Convert back from UTF-8
set decrypted [encoding convertfrom utf-8 $decrypted_utf8]
puts "Decrypted: $decrypted"
# Output: "Hello 世界"
```

---

### Example 6: Large File Processing with Progress

```tcl
package require performance

proc encrypt_large_file {input_file output_file key {chunk_size 1048576}} {
    # Open files
    set in_fd [open $input_file rb]
    set out_fd [open $output_file wb]

    # Get file size
    set file_size [file size $input_file]
    set processed 0

    puts "Encrypting: $input_file ($file_size bytes)"

    # Process in chunks
    while {![eof $in_fd]} {
        set chunk [read $in_fd $chunk_size]
        if {$chunk eq ""} break

        # Encrypt chunk
        set encrypted [performance::xor $chunk $key]
        puts -nonewline $out_fd $encrypted

        # Update progress
        set processed [expr {$processed + [string length $chunk]}]
        set percent [expr {$processed * 100 / $file_size}]
        puts -nonewline "\rProgress: $percent% ($processed / $file_size bytes)"
        flush stdout
    }

    puts "\nEncryption complete: $output_file"

    close $in_fd
    close $out_fd
}

# Process large file (1MB chunks)
set key "large_file_encryption_key"
encrypt_large_file "large_data.bin" "large_data.enc" $key
```

---

### Example 7: Data Obfuscation for Configuration

```tcl
package require performance

proc obfuscate_config {config_dict} {
    set key "config_obfuscation_key"
    set json [::json::write object {*}$config_dict]
    set obfuscated [performance::xor $json $key]
    return [binary encode base64 $obfuscated]
}

proc deobfuscate_config {obfuscated_data} {
    set key "config_obfuscation_key"
    set binary [binary decode base64 $obfuscated_data]
    set json [performance::xor $binary $key]
    return [::json::json2dict $json]
}

# Obfuscate configuration
set config {
    database_host "localhost"
    database_port 5432
    api_endpoint "https://api.example.com"
}

set obfuscated [obfuscate_config $config]
puts "Obfuscated config: $obfuscated"

# Save to file
set fd [open "config.obf" w]
puts $fd $obfuscated
close $fd

# Later: read and deobfuscate
set fd [open "config.obf" r]
set obfuscated [read $fd]
close $fd

set restored_config [deobfuscate_config $obfuscated]
puts "Restored config: $restored_config"
```

---

### Example 8: Checksum Generation

```tcl
package require performance

proc generate_checksum {data} {
    # Simple checksum using XOR with fixed pattern
    set pattern "\x5A\xA5\x55\xAA"
    set xored [performance::xor $data $pattern]

    # Fold the result into 32 bits
    set checksum 0
    binary scan $xored c* bytes
    foreach byte $bytes {
        set checksum [expr {($checksum ^ ($byte & 0xFF)) & 0xFFFFFFFF}]
    }

    return [format "0x%08X" $checksum]
}

# Generate checksum
set data "Important data to verify"
set checksum [generate_checksum $data]
puts "Data: $data"
puts "Checksum: $checksum"
```

---

### Example 9: Error Handling

```tcl
package require performance

proc safe_xor {data key} {
    if {[catch {
        performance::xor $data $key
    } result error_dict]} {
        puts stderr "XOR operation failed: $result"
        puts stderr "Error details: $error_dict"
        return ""
    }
    return $result
}

# Test with valid input
set encrypted [safe_xor "Hello" "key"]
if {$encrypted ne ""} {
    puts "Encryption successful"
}

# Test with invalid input (wrong number of arguments)
# This would normally cause an error
if {[catch {
    performance::xor "data"
}]} {
    puts "Error: Missing key argument"
}
```

---

## Security Considerations

### XOR Cipher Security Warning

**CRITICAL**: The XOR cipher implemented in this extension is **NOT cryptographically secure** and must **NEVER** be used for protecting sensitive or confidential data.

### Known Vulnerabilities

1. **Known-Plaintext Attack**: If an attacker knows part of the plaintext, they can recover the key
2. **Frequency Analysis**: Repeated patterns reveal key length and content
3. **Key Reuse**: Using the same key for multiple messages is highly insecure
4. **Short Keys**: Keys shorter than data are extremely vulnerable
5. **No Authentication**: No protection against data tampering

### Suitable Uses

- Simple data obfuscation (non-sensitive)
- Educational demonstrations
- Performance benchmarking
- Checksums (non-cryptographic)
- Configuration file masking (low-security)

### NOT Suitable For

- Protecting passwords or credentials
- Financial data encryption
- Personal identifying information (PII)
- Any production security application
- Compliance requirements (GDPR, HIPAA, PCI-DSS, etc.)

### Secure Alternatives

For cryptographically secure encryption, use:

| Use Case | Recommended Solution |
|----------|---------------------|
| File encryption | OpenSSL, GPG, age |
| Network communication | TLS/SSL (tcltls package) |
| Symmetric encryption | AES (Tcllib aes module, OpenSSL) |
| Password hashing | bcrypt, Argon2, PBKDF2 |
| Data at rest | AES-256-GCM, ChaCha20-Poly1305 |

---

## Best Practices

### 1. Always Use Binary Mode for Files

```tcl
# Good - binary mode preserves data integrity
set fd [open "file.bin" rb]
set data [read $fd]
close $fd

set encrypted [performance::xor $data $key]

set fd [open "file.enc" wb]
puts -nonewline $fd $encrypted
close $fd

# Bad - text mode may corrupt binary data
set fd [open "file.bin" r]  # Missing 'b'
```

### 2. Use Appropriate Key Lengths

```tcl
# Good - key length matches or exceeds data length
set data "Short message"
set key "this_is_a_long_enough_key_for_security"
set encrypted [performance::xor $data $key]

# Less secure - short key repeats
set data "This is a very long message with lots of content"
set key "XY"  # Only 2 bytes, highly predictable
set encrypted [performance::xor $data $key]
```

### 3. Verify Round-Trip Operations

```tcl
# Always verify encryption/decryption works
set original "Test data"
set key "test_key"

set encrypted [performance::xor $original $key]
set decrypted [performance::xor $encrypted $key]

if {$decrypted ne $original} {
    error "Round-trip verification failed!"
}
```

### 4. Handle Binary Data with puts -nonewline

```tcl
# Good - preserves binary data exactly
set fd [open "output.bin" wb]
puts -nonewline $fd $binary_data
close $fd

# Bad - adds unwanted newline at end
set fd [open "output.bin" wb]
puts $fd $binary_data  # Adds \n
close $fd
```

### 5. Use encoding for Text Data

```tcl
# Good - explicit UTF-8 encoding for text
set text "Unicode: 世界"
set utf8_binary [encoding convertto utf-8 $text]
set encrypted [performance::xor $utf8_binary $key]

# To decrypt
set decrypted_binary [performance::xor $encrypted $key]
set decrypted_text [encoding convertfrom utf-8 $decrypted_binary]
```

### 6. Chunk Large Files

```tcl
# Good - process large files in chunks
set chunk_size 1048576  ;# 1 MB
while {![eof $fd]} {
    set chunk [read $fd $chunk_size]
    set encrypted [performance::xor $chunk $key]
    puts -nonewline $out_fd $encrypted
}

# Bad - load entire large file into memory
set entire_file [read $fd]  ;# May exhaust memory
```

---

## Troubleshooting

### Wrong Number of Arguments

**Problem:** Error message "Invalid command count, use: xor <string> <salt>"

**Solution:**
```tcl
# Wrong
performance::xor $data  # Missing key

# Correct
performance::xor $data $key
```

---

### Decrypted Data Doesn't Match Original

**Problem:** Round-trip decryption produces different data

**Causes & Solutions:**

1. **Different key used**
   ```tcl
   # Wrong
   set encrypted [performance::xor $data "key1"]
   set decrypted [performance::xor $encrypted "key2"]

   # Correct - same key for encrypt/decrypt
   set key "same_key"
   set encrypted [performance::xor $data $key]
   set decrypted [performance::xor $encrypted $key]
   ```

2. **File mode corruption**
   ```tcl
   # Wrong - text mode corrupts binary data
   set fd [open "file.enc" w]

   # Correct - binary mode
   set fd [open "file.enc" wb]
   ```

3. **Missing -nonewline**
   ```tcl
   # Wrong - adds newline
   puts $fd $encrypted

   # Correct
   puts -nonewline $fd $encrypted
   ```

---

### Unicode Characters Corrupted

**Problem:** Unicode text becomes corrupted after XOR

**Solution:** Use explicit UTF-8 encoding
```tcl
# Correct approach for Unicode
set unicode_text "Hello 世界"
set utf8_bytes [encoding convertto utf-8 $unicode_text]
set encrypted [performance::xor $utf8_bytes $key]
set decrypted_bytes [performance::xor $encrypted $key]
set restored_text [encoding convertfrom utf-8 $decrypted_bytes]
```

---

### Package Not Found

**Problem:** `package require performance` fails

**Solutions:**

1. Check installation:
   ```bash
   make install
   ```

2. Verify package path:
   ```tcl
   puts $auto_path
   lappend auto_path "/path/to/performance"
   ```

3. Check package index:
   ```bash
   ls /path/to/performance/pkgIndex.tcl
   ```

---

### Memory Issues with Large Files

**Problem:** Out of memory errors with large files

**Solution:** Process in chunks
```tcl
# Instead of loading entire file
set data [read $fd]  # Don't do this for large files

# Use chunked processing
set chunk_size 1048576
while {![eof $fd]} {
    set chunk [read $fd $chunk_size]
    # Process chunk
}
```

---

## Technical Notes

### Implementation Details

- **Language**: Pure C implementation for performance
- **Algorithm**: Byte-by-byte XOR operation
- **Memory**: Dynamic allocation with automatic cleanup
- **Key Cycling**: Modulo arithmetic for automatic key repetition

### Performance Characteristics

- **Time Complexity**: O(n) where n is data length
- **Space Complexity**: O(n) for result buffer
- **Throughput**: Limited primarily by memory bandwidth
- **Overhead**: Minimal - direct byte operations

### XOR Operation

```c
// Core implementation (simplified)
for (ti = 0; ti < textLen; ti++) {
    result[ti] = text[ti] ^ salt[si++];
    if (si >= saltLen) si = 0;
}
```

### Binary Data Handling

All data is handled as Tcl byte arrays using:
- `Tcl_GetByteArrayFromObj()` - Read binary data
- `Tcl_NewByteArrayObj()` - Return binary result

This preserves binary integrity without encoding issues.

### Thread Safety

The extension supports Tcl thread capabilities when Tcl is compiled with `--enable-threads`. Each XOR operation is independent and thread-safe.

### TEA Compliance

Built using Tcl Extension Architecture (TEA) version 3.13, ensuring:
- Standard build process
- Cross-platform compatibility
- Proper namespace isolation
- Standard package loading

### Platform Support

- **Windows**: MSVC, MinGW, MSYS
- **Linux**: GCC, Clang
- **macOS**: Apple Clang, GCC
- **Unix**: Most POSIX-compliant systems

---

## Mathematical Properties

The XOR operation has several useful mathematical properties:

### Symmetry (Self-Inverse)
```tcl
xor(xor(A, B), B) = A
```
This property enables using the same operation for encryption and decryption.

### Commutativity
```tcl
xor(A, B) = xor(B, A)
```

### Associativity
```tcl
xor(xor(A, B), C) = xor(A, xor(B, C))
```

### Identity Element
```tcl
xor(A, 0) = A
```

### Self-Cancellation
```tcl
xor(A, A) = 0
```

---

## See Also

- [Tcl binary command](https://www.tcl.tk/man/tcl8.6/TclCmd/binary.html) - Binary data handling
- [Tcl encoding command](https://www.tcl.tk/man/tcl8.6/TclCmd/encoding.html) - Character encoding conversion
- [tcltls](https://core.tcl-lang.org/tcltls/) - TLS/SSL for secure communications
- [Tcllib aes](https://core.tcl-lang.org/tcllib/doc/trunk/embedded/md/tcllib/files/modules/aes/aes.md) - AES encryption
- [OpenSSL](https://www.openssl.org/) - Cryptographic library
- [XOR Cipher (Wikipedia)](https://en.wikipedia.org/wiki/XOR_cipher) - Background information

---

## License

**MIT License**

Copyright (c) 2025 Thomas Perschak

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

## Version History

**1.0.0** (2025-01-04)
- Initial release
- XOR cipher implementation in C
- Binary data support
- Automatic key cycling
- Comprehensive test suite (20+ test cases)
- Full documentation
- TEA-compliant build system
- Cross-platform support (Windows/Linux/macOS)

---

## Contact & Support

**Author**: Thomas Perschak

**Repository**: https://github.com/teclabat/tclperformance

**Issues**: Please report bugs and feature requests via GitHub issues

**Contributing**: Contributions welcome! Please submit pull requests with:
- Clear description of changes
- Test cases for new features
- Documentation updates
- Follow existing code style

---

## Acknowledgments

- Tcl Core Team for the excellent extension framework
- TEA (Tcl Extension Architecture) maintainers
- Tcl community for feedback and testing

---

*This documentation follows the format of the rsvisa.md reference documentation.*
