#pragma once

#include "memory.h"
#include "utils.h"
class Player {
    private:
        uintptr_t address;
        int health;
        int ammo;
        int team;
        bool dead;
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

        int GetTeam();
        
        bool IsDead();

        float GetCameraX(HANDLE handle);
        float GetCameraY(HANDLE handle);

        void SetCameraX(HANDLE handle, float angle);
        void SetCameraY(HANDLE handle, float angle);

        void Print();
};