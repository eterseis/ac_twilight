#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <wchar.h>

class Memory
{
public:
	Memory(const char* proc); //gets and sets the process id to m_procId
	~Memory()
	{
		CloseHandle(m_hProcess);
	}
public:
	const uintptr_t GetModuleBaseAddress(const char* proc) const;

	template <typename T>
	constexpr T Read(const uintptr_t& address) const
	{
		T buffer{};
		ReadProcessMemory(m_hProcess, reinterpret_cast<void*>(address), &buffer, sizeof(T), nullptr);
		return buffer;
	}
	const void ReadString(const uintptr_t& address, char buffer[], const size_t size) const;

	template <class T>
	const bool ReadStruct(const uintptr_t& address, T& buffer) const
	{
		SIZE_T size{};
		return
			ReadProcessMemory(m_hProcess, reinterpret_cast<LPCVOID>(address), &buffer, sizeof(buffer), &size)
			&& size == sizeof(buffer);
	}

	template <typename T>
	const void ReadArray(const uintptr_t& address, T* buffer) const
	{
		ReadProcessMemory(m_hProcess, reinterpret_cast<LPCVOID>(address), buffer, sizeof(buffer), nullptr);
	}

	template <typename T>
	constexpr void Write(const uintptr_t& address, const T value) const
	{
		WriteProcessMemory(m_hProcess, reinterpret_cast<void*>(address), &value, sizeof(T), nullptr);
	}
private:
	DWORD m_procId{};
	HANDLE m_hProcess{};
};