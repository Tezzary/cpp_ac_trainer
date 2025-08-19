#include "player.h"
#include "offsets.h"

#include <iostream>
#include <string>

Player::Player() {}
Player::Player(HANDLE handle, uintptr_t address) : address(address) {
    UpdateData(handle);
}

void Player::UpdateData(HANDLE handle) {
    health = readMemory<int>(handle, address + HEALTH);
    ammo = readMemory<int>(handle, address + ASSAULT_RIFLE_AMMO);
    team = readMemory<int>(handle, address + TEAM);
    dead = readMemory<bool>(handle, address + DEAD);
    
    position.x = readMemory<float>(handle, address + X_POSITION);
    position.y = readMemory<float>(handle, address + Y_POSITION);
    position.z = readMemory<float>(handle, address + Z_POSITION);

    headPosition.x = readMemory<float>(handle, address + HEAD_X_POSITION);
    headPosition.y = readMemory<float>(handle, address + HEAD_Y_POSITION);
    headPosition.z = readMemory<float>(handle, address + HEAD_Z_POSITION);

    cameraX = readMemory<float>(handle, address + CAMERA_X);
    cameraY = readMemory<float>(handle, address + CAMERA_Y);
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

int Player::GetTeam() {
    return team;
}
bool Player::IsDead() {
    return dead;
}

float Player::GetCameraX(HANDLE handle) {
    return cameraX;
}

float Player::GetCameraY(HANDLE handle) {
    return cameraY;
}

void Player::SetCameraX(HANDLE handle, float angle) {
    if(writeMemory(handle, address + CAMERA_X, angle)) {
        cameraX = angle;
    }
}

void Player::SetCameraY(HANDLE handle, float angle) {
    if(writeMemory(handle, address + CAMERA_Y, angle)) {
        cameraY = angle;
    }
}

std::string PrintLine(std::string str, int lineLength) {
    int len = str.size();
    for(int i = 0; i < lineLength - len; ++i) {
        str += " ";
    }
    return str;
}
void Player::Print() {
    std::cout << "------------Player-----------" << std::endl;
    std::cout << PrintLine("| Health: " + std::to_string(health), 28) << " |" << std::endl;
    std::cout << PrintLine("| Ammo: " + std::to_string(ammo), 28) << " |" << std::endl;
    std::cout << PrintLine("| Position: ", 28) << " |" << std::endl;
    std::cout << PrintLine("|   X: " + std::to_string(position.x), 28) << " |" << std::endl;
    std::cout << PrintLine("|   Y: " + std::to_string(position.y), 28) << " |" << std::endl;
    std::cout << PrintLine("|   Z: " + std::to_string(position.z), 28) << " |" << std::endl;
    std::cout << PrintLine("| Camera: ", 28) << " |" << std::endl;
    std::cout << PrintLine("|   X: " + std::to_string(cameraX), 28) << " |" << std::endl;
    std::cout << PrintLine("|   Y: " + std::to_string(cameraY), 28) << " |" << std::endl;
    std::cout << "-----------------------------" << std::endl;
}