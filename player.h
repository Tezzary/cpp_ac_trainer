#pragma once

#include "memory.h"
#include "utils.h"
class Player {
    private:
        uintptr_t address;
        int health;
        int ammo;
        int team;
        float cameraX;
        float cameraY;
    public:
        Vector3 position;
        Vector3 headPosition;

        Player();
        Player(HANDLE handle, uintptr_t address);
        void UpdateData(HANDLE handle);
        int GetHealth();
        void SetHealth(HANDLE handle, int health);
        int GetAmmo();
        void SetAmmo(HANDLE handle, int ammo);
        void SetCameraX(HANDLE handle, float angle);
        void SetCameraY(HANDLE handle, float angle);
        void Print();
};