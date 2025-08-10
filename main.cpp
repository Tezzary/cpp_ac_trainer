#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <cwchar>
#include <array>

const char* processName = "ac_client.exe";
const char* moduleName = "ac_client.exe";

const uintptr_t localPlayer = 0x0017E0A8; 
const uintptr_t healthAddress = 0xEC;

DWORD getProcessId() {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    Process32First(snapshot, &processEntry);
    DWORD procId = 0;
    while(true) {
        
        std::string procName = processEntry.szExeFile;
        //std::cout << procName << std::endl;
        
        if(processName == procName) {  
            procId = processEntry.th32ProcessID;
            break;
        }

        bool success = Process32Next(snapshot, &processEntry);

        if(!success) {
            break;
        }
    }
    return procId;
}

uintptr_t GetModuleBaseAddress(DWORD procId) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, procId);

    MODULEENTRY32 moduleEntry;
    moduleEntry.dwSize = sizeof(MODULEENTRY32);

    Module32First(snapshot, &moduleEntry);
    uintptr_t baseAddress = 0;
    while(true) {
        std::string modName = moduleEntry.szModule;
        std::cout << modName << std::endl;
        if(moduleName == modName) {
            baseAddress = (uintptr_t)moduleEntry.modBaseAddr;
            break;
        }

        bool success = Module32Next(snapshot, &moduleEntry);
        if(!success) {
            break;
        }
    }
    return baseAddress;
}

HANDLE getProcessHandle(DWORD procId) {
    return OpenProcess(PROCESS_ALL_ACCESS, false, procId);
}

template <typename T> T readMemory(HANDLE handle, uintptr_t address) {
    T buffer;
    ReadProcessMemory(handle, (PCVOID)address, &buffer, sizeof(buffer), nullptr);
    return buffer;
}

int main() {

    DWORD procId = getProcessId();
    if(procId == 0) {
        std::cout << "Could not find process: " << std::endl;
        std::cout << processName;
        std::cout << "... Exiting" << std::endl;
        return 0;
    }

    std::cout << "Gathered Process ID of " << processName << ": " << procId << std::endl;

    uintptr_t moduleBaseAddress = GetModuleBaseAddress(procId);
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

    uintptr_t playerAddress = readMemory<uintptr_t>(handle, moduleBaseAddress + localPlayer);
    int health = readMemory<int>(handle, playerAddress + healthAddress);

    std::cout << "Player has: " << health << " health" << std::endl;
    return 0;
}
