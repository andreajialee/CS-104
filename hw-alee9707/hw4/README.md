Implement the RSA encryption/decryption algorithm

This program executes the RSA encryption/decryption algorithm
using the Eucledian Algorithm

You will create an executable called rsa which takes in 2 command-line parameters: p and q (in either order). Your program will assume that p and q are large primes (if they are not prime, your algorithm should still run and not crash, but we cannot promise the decryption process will be secure or accurate). A list of prime numbers (for testing) can be found here, or you can write your own prime-finding algorithm.

When run, your program should immediately prompt the user for a command (via cin) and, after having executed that command, should loop and prompt the user again. If the user enters an invalid command, you may do anything except crash (including gracefully terminating the program, or asking for another command). The list of valid commands are as follows:

1. EXIT Gracefully terminate the program.
2. DECRYPT [input] [output] Opens the file at [input], reads the contents of the file, decrypts the message, and overwrites the contents of the file at [output] with the decrypted message.
3. ENCRYPT [filename] [n] [message] Creates/overwrites the file at the specified path, writing an encrypted version of [message], which is a string of lowercase letters a-z and spaces (but no tabs or newlines). [n] is an integer which will be used in the encryption process.

If Alice and Bob wanted to use this program for its intended purpose, Alice would determine two large primes p and q while keeping them private, calculate n = p*q, and share n with Bob. Bob can now encrypt messages that only Alice can decrypt. Bob can do the same thing, identifying a different p’ and q’, calculating n’ and sharing it with Alice. Now Alice can encrypt messages that only Bob can decrypt.