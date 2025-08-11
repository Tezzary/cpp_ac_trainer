#include "player.h"
#include "offsets.h"

Player::Player(HANDLE handle, uintptr_t address) : address(address) {
    UpdateData(handle);
}

void Player::UpdateData(HANDLE handle) {
    health = readMemory<int>(handle, address + HEALTH);
    ammo = readMemory<int>(handle, address + ASSAULT_RIFLE_AMMO);
}

int Player::GetHealth() {
    return health;
}

void Player::SetHealth(HANDLE handle, int health) {
    if(writeMemory(handle, address + HEALTH, health)) {
        this->health = health;
    }
}

int Player::GetAmmo() {
    return ammo;
}

void Player::SetAmmo(HANDLE handle, int ammo) {
    writeMemory(handle, address + ASSAULT_RIFLE_AMMO, ammo);
}