#include "settingsmanager.h"

#include <windows.h>
#include <iostream>
#include <bitset>
#include <fstream>

//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

Key keys[] = {
    {"A", 'A'}, {"B", 'B'}, {"C", 'C'}, {"D", 'D'}, {"E", 'E'}, {"F", 'F'},
    {"G", 'G'}, {"H", 'H'}, {"I", 'I'}, {"J", 'J'}, {"K", 'K'}, {"L", 'L'},
    {"M", 'M'}, {"N", 'N'}, {"O", 'O'}, {"P", 'P'}, {"Q", 'Q'}, {"R", 'R'},
    {"S", 'S'}, {"T", 'T'}, {"U", 'U'}, {"V", 'V'}, {"W", 'W'}, {"X", 'X'},
    {"Y", 'Y'}, {"Z", 'Z'},

    {"0", '0'}, {"1", '1'}, {"2", '2'}, {"3", '3'}, {"4", '4'},
    {"5", '5'}, {"6", '6'}, {"7", '7'}, {"8", '8'}, {"9", '9'},

    {"F1", VK_F1}, {"F2", VK_F2}, {"F3", VK_F3}, {"F4", VK_F4}, {"F5", VK_F5},
    {"F6", VK_F6}, {"F7", VK_F7}, {"F8", VK_F8}, {"F9", VK_F9}, {"F10", VK_F10},
    {"F11", VK_F11}, {"F12", VK_F12},

    {"Space", VK_SPACE}, {"Enter", VK_RETURN}, {"Tab", VK_TAB},
    {"Shift", VK_SHIFT}, {"Ctrl", VK_CONTROL}, {"Alt", VK_MENU},
    {"Esc", VK_ESCAPE}, {"Backspace", VK_BACK},
    {"Up", VK_UP}, {"Down", VK_DOWN}, {"Left", VK_LEFT}, {"Right", VK_RIGHT},

    // Mouse buttons
    {"Mouse Left", VK_LBUTTON},
    {"Mouse Right", VK_RBUTTON},
    {"Mouse Middle", VK_MBUTTON},
    {"Mouse Side 1", VK_XBUTTON1},
    {"Mouse Side 2", VK_XBUTTON2},
};

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

Key GetKeyToBind() {
    for(Key key : keys) {
        if(isKeyDown(key.keyCode)) {
            return key;
        }
    }
    return {"", ' '};
}

void SaveSettings(Settings settings) {
    return;
    std::ofstream oFS("ac_trainer.data", std::ios::binary);
    oFS.write((char*)&settings, sizeof(Settings));
}

Settings LoadSettings() {
    Settings settings;
    return settings;
    std::ifstream iFS("ac_trainer.data", std::ios::binary);
    if(!iFS.is_open()) {
        SaveSettings(settings);
        return settings;
    }
    iFS.read((char*)(&settings), sizeof(Settings));

    iFS.close();

    return settings;
}