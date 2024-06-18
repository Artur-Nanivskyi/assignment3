#include <iostream>
#include <cstring>
#include <cctype>

extern "C" {
char* encrypt(char *rawText, int key) {
    int length = strlen(rawText);
    char *encryptedText = new char[length + 1];

    for (int i = 0; i < length; i++) {
        if (isalpha(rawText[i])) {
            char base = islower(rawText[i]) ? 'a' : 'A';
            encryptedText[i] = (rawText[i] - base + key) % 26 + base;
        } else {
            encryptedText[i] = rawText[i];
        }
    }
    encryptedText[length] = '\0';
    return encryptedText;
}
};