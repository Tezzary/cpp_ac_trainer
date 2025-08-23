#include <iostream>
#include <vector>
#include <math.h>
#include <thread>
#include <chrono>

#include "offsets.h"
#include "memory.h"
#include "player.h"
#include "utils.h"
#include "settingsmanager.h"
#include "trainer.h"

const char* processName = "ac_client.exe";
const char* moduleName = "ac_client.exe";

const float cosineWeight = 0.9995;
//const float cosineWeight = 0.0;
const char aimbotKey = VK_XBUTTON1; //side mouse button
//const char aimbotKey = 'X'; //side mouse button

Player& getClosestPlayerToCrosshair(HANDLE handle, std::vector<Player> &players, Player &localPlayer) {
    float xAngle = localPlayer.GetCameraX(handle);
    float yAngle = localPlayer.GetCameraY(handle);

    float ratio = tan(xAngle * M_PI / 180);

    float z = -ratio;
    float x = 1;
    if(xAngle > 90 && xAngle < 270) {
        z = ratio;
        x = -1;
    }

    float hypo = sqrt(z*z+x*x);

    float y = -tan(yAngle * M_PI / 180) * hypo;

    Vector3 cameraDirection(x, y, z);

    float closestDistance = 1 << 16;
    Player* closest = &localPlayer;

    for(int i = 0; i < (int)players.size()-1; ++i) {
        Player& player = players[i];
        
        if(player.GetTeam() == localPlayer.GetTeam()) {
            continue;
        }
        if(player.IsDead()) {
            continue;
        }

        Vector3 difference = player.position - localPlayer.position;

        float cosineDistance = cameraDirection.CosineDistance(difference);
        float euclideanDistance = difference.GetLength();
        float weightedDistance = cosineWeight * cosineDistance + (1 - cosineWeight) * euclideanDistance;

        if(weightedDistance < closestDistance) {
            closestDistance = weightedDistance;
            closest = &player;
        }
    }
    return *closest;
}
void aimbot(HANDLE handle, std::vector<Player> &players, Player &localPlayer){
   
    Player closest = getClosestPlayerToCrosshair(handle, players, localPlayer);
    
    Vector3 difference = closest.position - localPlayer.position;
    // std::cout << difference.x << " " << difference.y << " " << difference.z << " " << std::endl;
    // std::cout << closest.position.x << " " << closest.position.y << " " << closest.position.z << " " << std::endl;
    float xAngle = atan2(-difference.z, difference.x) + M_PI;
    float yAngle = atan2(difference.y, sqrt(difference.x * difference.x + difference.z * difference.z));

    localPlayer.SetCameraX(handle, xAngle * 180 / M_PI);
    localPlayer.SetCameraY(handle, yAngle * 180 / M_PI);
}

void run() {
    HANDLE handle;
    uint32_t moduleBaseAddress;

    if(!getHandleModuleBaseAddress(processName, moduleName, handle, moduleBaseAddress)) {
        return;
    }

    uint32_t localPlayerAddress = readMemory<uint32_t>(handle, moduleBaseAddress + lOCAL_PLAYER);
    Player localPlayer = Player(handle, localPlayerAddress);

    //Set up player vector
    int playerCount = readMemory<int>(handle, moduleBaseAddress + PLAYER_COUNT);
    std::cout << "Player count: " << playerCount << std::endl;

    uint32_t entityList = readMemory<uint32_t>(handle, moduleBaseAddress + ENTITY_LIST);
    //skip i = 0 as for some reason entity pointers start after 4 bytes
    std::vector<Player> players;
    for(int i = 1; i <= playerCount; ++i) {
        uint32_t playerAddress = readMemory<uint32_t>(handle, entityList + i*4);
        Player player = Player(handle, playerAddress);
        players.push_back(player);
    }

    

    //mainLoop
    //find closest player
    while (true) {
        //update players
        localPlayer.UpdateData(handle);
        
        for(int i = 0; i < (int)players.size(); ++i) {
            players[i].UpdateData(handle);
        }

        localPlayer.SetAmmo(handle, 20);
        localPlayer.SetHealth(handle, 1000);

        if(isKeyToggled(aimbotKey, false)) {
            aimbot(handle, players, localPlayer);
        }

        //localPlayer.Print();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    return;

}