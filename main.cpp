#include <iostream>
#include <dlfcn.h>


typedef char* (*encrypt_function)(char*, int);
typedef char* (*decrypt_function)(char*, int);


int main() {
    void* handle = dlopen("/Users/arturnanivskij/Documents/untitled/mylib.so", RTLD_LAZY);
    if (!handle) {
        printf("Error: %s\n", dlerror());
        return 1;
    }


    dlerror();
    encrypt_function encrypt = (encrypt_function)dlsym(handle, "encrypt");
    char* error = dlerror();
    if (error != nullptr) {
        printf("Error: %s\n", error);
        dlclose(handle);
        return 1;
    }

    decrypt_function decrypt = (decrypt_function)dlsym(handle, "decrypt");
    error = dlerror();
    if (error != nullptr) {
        printf("Error: %s\n", error);
        dlclose(handle);
        return 1;
    }

    char message[] = " So let's have fun, little people, in public\n"
                     "Let the mill grind its eternal grist.\n"
                     "The heart is stuck like a splinter in the chest,\n"
                     "Nothing, death will cure all this.";
    int key = 8;

    char* encryptedMessage = encrypt(message, key);
    std::cout << "Encrypted Message: " << encryptedMessage << std::endl;
    char* decryptedMessage = decrypt(encryptedMessage, key);
    std::cout << "Decrypted Message: " << decryptedMessage << std::endl;
    delete[] encryptedMessage;
    delete[] decryptedMessage;
    dlclose(handle);
    return 0;
}
