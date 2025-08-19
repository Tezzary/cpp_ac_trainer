#include "keymanager.h"

#include <windows.h>
#include <iostream>
#include <bitset>

//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

void printKeyState(char key) {
    std::bitset<16> bits(GetKeyState(key));
    std::cout << "Key - '" << key << "' has state: " << bits << std::endl;
}

bool isKeyDown(char key, bool debug) {
    if(debug) {
        printKeyState(key);
    }
    return GetKeyState(key) & (1 << 15);
}
bool isKeyToggled(char key, bool debug) {
    if(debug) {
        printKeyState(key);
    }
    return GetKeyState(key) & 1;
}