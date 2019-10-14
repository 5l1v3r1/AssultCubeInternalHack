// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "mem.h"
#include "proc.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
	// create console
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	std::cout << "IAMM AAR HAXXORR\n";
	// get module
	uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");

	bool healthSwitch = false;
	bool rifleAmmoSwitch = false;
	bool pistalAmmoSwitch = false;
	bool grenadeSwitch = false;


	// hack loop
	while (true)
	{
		// key input
		// hack
		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			healthSwitch = !healthSwitch;
		}

		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			rifleAmmoSwitch = !rifleAmmoSwitch;
		}

		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			pistalAmmoSwitch = !pistalAmmoSwitch;
		}

		if (GetAsyncKeyState(VK_NUMPAD4) & 1)
		{
			grenadeSwitch = !grenadeSwitch;
		}


		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			return 0;
		}

		// freeze
		uintptr_t* localPlayerPtr = (uintptr_t*)(moduleBase + 0x10f4f4);

		if (localPlayerPtr)
		{
			if (healthSwitch)
			{
				*(int*)(*localPlayerPtr + 0xf8) = 1337;
			}

			if (rifleAmmoSwitch)
			{
				*(int*)(*localPlayerPtr + 0x150) = 1337;
			}

			if (pistalAmmoSwitch)
			{
				*(int*)(*localPlayerPtr + 0x13c) = 1337;
			}

			if (grenadeSwitch)
			{
				*(int*)(*localPlayerPtr + 0x158) = 1337;
			}
		}
	}



	// clean up
	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
		}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
