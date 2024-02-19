#include "resources.h"
#include "cryptoPals.h"
#include <openssl/evp.h>
#include <openssl/aes.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./challenge_7 [ciphertext.txt]" << endl;
        return 1;
    }
    
    // Import cipher text and declare key
    const string ciphertext = readFile(argv[1]);
    const unsigned char key[] = "YELLOW SUBMARINE";
    // Create openssl context, cipher, decryption variables
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    const EVP_CIPHER* cipher = EVP_aes_128_ecb();
    EVP_DecryptInit(ctx, cipher, key, NULL);
    
    // Allocate memory for plaintext 
    unsigned char* plaintext = (unsigned char*) malloc(
                                ciphertext.length() +
                                EVP_CIPHER_block_size(cipher)
                                );
    int length;
    // Begin Decryption 
    EVP_DecryptUpdate(ctx, 
                      plaintext, 
                      &length, 
                      reinterpret_cast<const unsigned char*>(ciphertext.c_str()),
                      ciphertext.length()
                     );
    
   // Last block 
    EVP_DecryptFinal(ctx, 
                     plaintext + length,
                     &length);
   
    cout << plaintext;

    // Remove sensitive data from memory
    free(plaintext);
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}
