#include <iostream>
#include <vector>

#include "offsets.h"
#include "memory.h"
#include "player.h"

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

    uintptr_t moduleBaseAddress = GetModuleBaseAddress(procId, moduleName);
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

    uintptr_t localPlayerAddress = readMemory<uintptr_t>(handle, moduleBaseAddress + lOCAL_PLAYER);
    Player localPlayer = Player(handle, localPlayerAddress);

    int playerCount = readMemory<int>(handle, moduleBaseAddress + PLAYER_COUNT);
    std::cout << "Player count: " << playerCount;

    uintptr_t entityList = readMemory<uintptr_t>(handle, moduleBaseAddress + ENTITY_LIST);
    //skip i = 0 as for some reason entity pointers start after 4 bytes

    std::vector<Player> players;
    for(int i = 1; i < playerCount; ++i) {
        uintptr_t playerAddress = readMemory<uintptr_t>(handle, entityList + i*4);
        Player player = Player(handle, playerAddress);
        players.push_back(player);
    }
    return 0;
}
