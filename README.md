# Substitution Cipher (File-Based Encryption and Decryption)
This project is a C implementation of a substitution cipher that performs encryption and decryption on text files using a fixed 26-character alphabetic key. The program preserves letter case and leaves non-alphabetic characters unchanged.


## Features

* File-based encryption and decryption
* Case-sensitive letter substitution
* Preservation of non-alphabetic characters
* Strict validation of the substitution key
* Clear separation between encryption and decryption logic

## Compilation
```
gcc sub.c -o sub
```

## Usage
```
./sub KEY (-e | -d) INPUT_FILE OUTPUT_FILE
```

### Encrypt
```
./sub QWERTYUIOPASDFGHJKLZXCVBNM -e plaintext.txt ciphertext.txt
```

### Decrypt
```
./sub QWERTYUIOPASDFGHJKLZXCVBNM -d ciphertext.txt decrypted.txt
```
