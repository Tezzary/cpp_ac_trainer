#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <string>

DWORD getProcessId(const char* processName);
uintptr_t GetModuleBaseAddress(DWORD procId, const char* moduleName);
HANDLE getProcessHandle(DWORD procId);

template <typename T> T readMemory(HANDLE handle, uintptr_t address) {
    T buffer;
    ReadProcessMemory(handle, (PVOID)address, &buffer, sizeof(buffer), nullptr);
    return buffer;
}

template <typename T> bool writeMemory(HANDLE handle, uintptr_t address, T data) {
    return WriteProcessMemory(handle, (LPVOID)address, (LPCVOID)(&data), sizeof(data), nullptr);
}