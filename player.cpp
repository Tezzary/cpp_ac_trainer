#include "player.h"
#include "offsets.h"

Player::Player(HANDLE handle, uintptr_t address) : address(address) {
    UpdateData(handle);
}

void Player::UpdateData(HANDLE handle) {
    health = readMemory<int>(handle, address + HEALTH);
}

int Player::GetHealth() {
    return health;
}

void Player::SetHealth(HANDLE handle, int health) {
    if(writeMemory(handle, address + HEALTH, health)) {
        this->health = health;
    }
}