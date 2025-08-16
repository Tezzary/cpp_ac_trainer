#include "memory.h"

#include <iostream>


DWORD getProcessId(const char* processName) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    Process32First(snapshot, &processEntry);
    DWORD procId = 0;
    while(true) {
        
        std::string procName = processEntry.szExeFile;
        
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

uintptr_t GetModuleBaseAddress(DWORD procId, const char* moduleName) {
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

bool getHandleModuleBaseAddress(const char* processName, const char* moduleName, HANDLE &handle, uint32_t &moduleBaseAddress) {
    DWORD procId = getProcessId(processName);
    if(procId == 0) {
        std::cout << "Could not find process: " << std::endl;
        std::cout << processName;
        std::cout << "... Exiting" << std::endl;
        return 0;
    }

    std::cout << "Gathered Process ID of " << processName << ": " << procId << std::endl;

    moduleBaseAddress = GetModuleBaseAddress(procId, moduleName);
    if(moduleBaseAddress == 0) {
        std::cout << "Could not find module: " << std::endl;
        std::cout << moduleName;
        std::cout << "... Exiting" << std::endl;
        return 0;
    }

    std::cout << "Gathered Module Base Address of " << moduleName << ": " << moduleBaseAddress << std::endl;

    handle = getProcessHandle(procId);

    if(handle == NULL) {
        std::cout << "Could not gain handle to process: " << std::endl;
        std::cout << processName;
        std::cout << "... Exiting" << std::endl;
        return 0;
    }

    std::cout << "Gathered Handle to process: " << processName << std::endl;
    return 1;
}