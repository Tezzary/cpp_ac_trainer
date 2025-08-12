#pragma once

#include "memory.h"
#include "utils.h"
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
        void Print();
};