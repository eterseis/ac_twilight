#include "memory.h"

//sets m_procId and m_hProcess
Memory::Memory(const wchar_t* procName)
{
	HANDLE hSnap(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

	PROCESSENTRY32 procEntry{};
	procEntry.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hSnap, &procEntry))
	{
		do
		{
			if (!_wcsicmp(procEntry.szExeFile, procName))
			{
				m_procId = procEntry.th32ProcessID;
				break;
			}
		} while (Process32Next(hSnap, &procEntry));
	}

	CloseHandle(hSnap);
	m_hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, false, m_procId);
}

const uintptr_t Memory::GetModuleBaseAddress(const wchar_t* procName) const
{
	uintptr_t modBaseAddr{};
	HANDLE hSnap{ CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, m_procId) };

	MODULEENTRY32 modEntry{};
	modEntry.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnap, &modEntry))
	{
		do
		{
			if (!_wcsicmp(modEntry.szModule, procName))
			{
				modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnap, &modEntry));
	}

	CloseHandle(hSnap);
	return modBaseAddr;
}

void Memory::ReadString(uintptr_t address, char buffer[], const size_t size)
{
	ReadProcessMemory(m_hProcess, (void*)address, buffer, size, nullptr);
}