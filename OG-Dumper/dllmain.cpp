#include <iostream>
#include <Windows.h>

#include <updater.h>

// Dumper created by i <3 crack
// Credits for Scanner : https://github.com/dano20zombie/FortUpdater

// Note
// You could use this dumper for other versions for fortnite ( or other unreal engine games ) too.
// All you need to do is update the offsets below or automatically scan for them using signatures.
// Enjoy!

static FortUpdater* updater = new FortUpdater( );

namespace offsets
{
    // Updated to 14.40
    std::uintptr_t UObjectArray = 0x91EDDD8;
    std::uintptr_t GetObjectName = 0x4D51C80;
    std::uintptr_t GetNameByIndex = 0x3558D20;
    std::uintptr_t FnFree = 0x34451C0;
}

void FindOffset(const char* class_name, const char* member)
{
    std::cout << " > " << member << " -> [ " << "0x" << std::hex << updater->FindOffset(class_name, member) << " ]" << std::endl;
}

void MainFunction( )
{
    printf("[ i <3 crack ]\n");

    printf("Getting required addresses...\n");

    uintptr_t BaseAddress = (uintptr_t)GetModuleHandle(nullptr);
    printf(" > Base Address -> [ 0x%llx ]\n", BaseAddress);

    std::uintptr_t UObjectArray = (BaseAddress + offsets::UObjectArray);
    printf(" > UObjectArray -> [ 0x%llx ]\n", UObjectArray);

    std::uintptr_t GetObjectName = (BaseAddress + offsets::GetObjectName);
    printf(" > GetObjectName -> [ 0x%llx ]\n", GetObjectName);

    std::uintptr_t GetNameByIndex = (BaseAddress + offsets::GetNameByIndex);
    printf(" > GetNameByIndex -> [ 0x%llx ]\n", GetNameByIndex);

    std::uintptr_t FnFree = (BaseAddress + offsets::FnFree);
    printf(" > FnFree -> [ 0x%llx ]\n\n", FnFree);

    printf("Starting dumping process...\n");

    if (updater->Init(UObjectArray, GetObjectName, GetNameByIndex, FnFree))
    {
        // To dump the offset you will need the class name and the member name to the offset. As if it wasn't obvious from before.
        FindOffset("World", "OwningGameInstance");
        FindOffset("World", "GameState");
        FindOffset("World", "Levels");
        FindOffset("World", "PersistentLevel");
        FindOffset("GameInstance", "LocalPlayers");
        FindOffset("Player", "PlayerController");
        FindOffset("PlayerController", "PlayerCameraManager");
        FindOffset("PlayerController", "AcknowledgedPawn");
        FindOffset("Pawn", "PlayerState");
        FindOffset("FortPlayerStateAthena", "TeamIndex");
        FindOffset("FortPlayerStateAthena", "KillScore");
        FindOffset("Actor", "RootComponent");
        FindOffset("SceneComponent", "RelativeLocation");
        FindOffset("SceneComponent", "RelativeRotation");
        FindOffset("SceneComponent", "RelativeScale3D");
        FindOffset("Character", "Mesh");
        FindOffset("SkinnedMeshComponent", "CachedWorldSpaceBounds");
        FindOffset("GameStateBase", "PlayerArray");
    }

    std::getchar();
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        MessageBox(0, L"dumper has been injected.", L"Dumper", 0);

        AllocConsole();
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);

        MainFunction();
    }
    return TRUE;
}

