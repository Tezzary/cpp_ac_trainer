#pragma once

#include <windows.h>
#include <string>

struct Key {
    std::string keyName;
    char keyCode;
}; 

struct Setting {
    std::string settingName;
    bool enabled;
    Key key;
    bool toggle;
    float value;
    float min;
    float max;
};

Key GetKeyToBind();

bool isKeyDown(char key, bool debug = false);
bool isKeyToggled(char key, bool debug = false);
