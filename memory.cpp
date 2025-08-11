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
