#pragma once

#include <windows.h>
#include <string>

struct Key {
    char keyName[32];
    char keyCode;
}; 

struct Settings {
    bool aimbotEnabled = true;
    bool toggle = true;
    Key aimbotKey = {"A", 'A'};

};

void SaveSettings(Settings settings);
Settings LoadSettings();

Key GetKeyToBind();

bool isKeyDown(char key, bool debug = false);
bool isKeyToggled(char key, bool debug = false);
