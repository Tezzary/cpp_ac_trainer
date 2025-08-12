#include <iostream>
#include <vector>
#include <math.h>
#include <thread>
#include <chrono>

#include "offsets.h"
#include "memory.h"
#include "player.h"
#include "utils.h"
const char* processName = "ac_client.exe";
const char* moduleName = "ac_client.exe";

int main() {

    DWORD procId = getProcessId(processName);
    if(procId == 0) {
        std::cout << "Could not find process: " << std::endl;
        std::cout << processName;
        std::cout << "... Exiting" << std::endl;
        return 0;
    }

    std::cout << "Gathered Process ID of " << processName << ": " << procId << std::endl;

    uint32_t moduleBaseAddress = GetModuleBaseAddress(procId, moduleName);
    if(moduleBaseAddress == 0) {
        std::cout << "Could not find module: " << std::endl;
        std::cout << moduleName;
        std::cout << "... Exiting" << std::endl;
        return 0;
    }

    std::cout << "Gathered Module Base Address of " << moduleName << ": " << moduleBaseAddress << std::endl;

    HANDLE handle = getProcessHandle(procId);

    if(handle == NULL) {
        std::cout << "Could not gain handle to process: " << std::endl;
        std::cout << processName;
        std::cout << "... Exiting" << std::endl;
        return 0;
    }

    std::cout << "Gathered Handle to process: " << processName << std::endl;

    uint32_t localPlayerAddress = readMemory<uint32_t>(handle, moduleBaseAddress + lOCAL_PLAYER);
    Player localPlayer = Player(handle, localPlayerAddress);


    //Set up player vector
    int playerCount = readMemory<int>(handle, moduleBaseAddress + PLAYER_COUNT);
    std::cout << "Player count: " << playerCount << std::endl;

   // std::cout << sizeof(int) << std::endl;
    uint32_t entityList = readMemory<uint32_t>(handle, moduleBaseAddress + ENTITY_LIST);
    //std::cout << entityList << std::endl;
    localPlayer.Print();
    //skip i = 0 as for some reason entity pointers start after 4 bytes
    std::vector<Player> players;
    for(int i = 1; i < playerCount; ++i) {
       // std::cout << entityList + i*4 << std::endl;
        uint32_t playerAddress = readMemory<uint32_t>(handle, entityList + i*4);
       // std::cout << playerAddress << std::endl;
        Player player = Player(handle, playerAddress);
       // std::cout<< player.position.x << " " << player.position.y << " " << player.position.z << std::endl;
        players.push_back(player);
    }

    localPlayer.Print();
    //aimlock
    //find closest player
    while (true) {
        //update players
        localPlayer.UpdateData(handle);
        for(int i = 0; i < playerCount-1; ++i) {
            players[i].UpdateData(handle);
        }

        float closestDistance = 1 << 16;
        Player closest;
        for(int i = 0; i < playerCount-1; ++i) {
            Player& player = players[i];
            Vector3 difference = player.position - localPlayer.position;
          //  std::cout<< player.position.x << " " << player.position.y << " " << player.position.z << std::endl;
            float distance = difference.GetLength();
           // std::cout << distance << std:: endl;
            if(distance < closestDistance) {
                closestDistance = distance;
                closest = player;
            }
        }

        Vector3 difference = closest.position - localPlayer.position;
        
        float xAngle = atan2(-difference.z, difference.x) + M_PI;
        float yAngle = atan2(difference.y, sqrt(difference.x * difference.x + difference.z * difference.z));

        localPlayer.SetCameraX(handle, xAngle * 180 / M_PI);
        localPlayer.SetCameraY(handle, yAngle * 180 / M_PI);
        std::cout << yAngle * 180 / M_PI << std::endl;
        localPlayer.Print();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    localPlayer.Print();
    return 0;
}
