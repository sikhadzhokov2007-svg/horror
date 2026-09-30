#include "NightShift/NSGameMode.h"
#include "NightShift/NSPlayerCharacter.h"
#include "NightShift/NSBlockoutLevel.h"

ANSGameMode::ANSGameMode()
{
    DefaultPawnClass = ANSPlayerCharacter::StaticClass();
}

void ANSGameMode::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->SpawnActor<ANSBlockoutLevel>();
}
