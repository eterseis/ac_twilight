#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <wchar.h>

class Memory
{
public:
	Memory(const wchar_t* proc); //gets and sets the process id to m_procId
	~Memory()
	{
		CloseHandle(m_hProcess);
	}
public:
	uintptr_t GetModuleBaseAddress(const wchar_t* proc);

	template <typename T>
	T Read(uintptr_t address)
	{
		T buffer{};
		ReadProcessMemory(m_hProcess, (void*)address, &buffer, sizeof(T), nullptr);
		return buffer;
	}
	void ReadString(uintptr_t address, char buffer[], size_t size);

	template <typename T>
	void Write(uintptr_t address, T value)
	{
		WriteProcessMemory(m_hProcess, (void*)address, &value, sizeof(T), nullptr);
	}
private:
	DWORD m_procId{};
	HANDLE m_hProcess{};
};