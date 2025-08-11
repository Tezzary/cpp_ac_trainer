#pragma once

#include "memory.h"

class Vector3 {
    float x;
    float y;
    float z;
};

class Player {
    private:
        uintptr_t address;
        int health;
        int ammo;
        int team;
        Vector3 position;
        Vector3 headPosition;
    public:
        Player(HANDLE handle, uintptr_t address);
        void UpdateData(HANDLE handle);
        int GetHealth();
        void SetHealth(HANDLE handle, int health);
        int GetAmmo();
        void SetAmmo(HANDLE handle, int ammo);
};