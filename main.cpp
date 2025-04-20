#include <iostream>
#include "memory.h"
#include "Offsets.h"

//moduleBaseAddress + one of these
constexpr uintptr_t localPlayer{ 0x17E0A8 };
constexpr uintptr_t entityList{ 0x191FCC };
constexpr uintptr_t maxEntities{ 0x18AC0C };

int main()
{
	/*std::cout << "Key Of The Twilight\n";
	Memory mem{ L"ac_client.exe" };
	uintptr_t moduleBase = mem.GetModuleBaseAddress(L"ac_client.exe");*/

	return 0;
}