#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

const unsigned char key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x75, 0x46, 0x60, 0x63, 0x64};

AES_KEY enc_key; 
AES_KEY dec_key; 

int aes_init() {
    if (AES_set_encrypt_key(key, 128, &enc_key) < 0) {
        printf("AES_set_encrypt_key error\n");
        return -1;
    }

    if (AES_set_decrypt_key(key, 128, &dec_key) < 0) {
        printf("AES_set_decrypt_key error\n");
        return -1;
    }

    return 0;
}

int aes_encrypt(unsigned char *plaintext, unsigned char *ciphertext) {
    AES_ecb_encrypt(plaintext, ciphertext, &enc_key, AES_ENCRYPT);
    return 0;
}

int aes_decrypt(unsigned char *ciphertext, unsigned char *plaintext) {
    AES_ecb_encrypt(ciphertext, plaintext, &dec_key, AES_DECRYPT);
    return 0;
}

int main() {
    unsigned char plaintext[] = "This is a.";
    unsigned char ciphertext[128];
    unsigned char decryptedtext[128];

    if (aes_init() != 0) {
        return -1;
    }

    printf("Raw message: %s\n", plaintext);
    if (aes_encrypt(plaintext, ciphertext) != 0) {
        printf("Encryption failed\n");
        return -1;
    }

    printf("Encrypted message (in hex):\n");
    for (int i = 0; i < strlen((const char *)plaintext); i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    // 执行 AES 解密
    if (aes_decrypt(ciphertext, decryptedtext) != 0) {
        printf("Decryption failed\n");
        return -1;
    }

    printf("Decrypted message: %s\n", decryptedtext);

    return 0;
}
