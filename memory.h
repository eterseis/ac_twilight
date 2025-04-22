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
	const uintptr_t GetModuleBaseAddress(const wchar_t* proc) const;

	template <typename T>
	constexpr T Read(const uintptr_t& address) const
	{
		T buffer{};
		ReadProcessMemory(m_hProcess, (void*)address, &buffer, sizeof(T), nullptr);
		return buffer;
	}
	const void ReadString(const uintptr_t& address, char buffer[], const size_t size) const;

	template <typename T>
	constexpr void Write(const uintptr_t& address, const T value) const
	{
		WriteProcessMemory(m_hProcess, (void*)address, &value, sizeof(T), nullptr);
	}
private:
	DWORD m_procId{};
	HANDLE m_hProcess{};
};