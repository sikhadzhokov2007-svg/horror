#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NSGameMode.generated.h"

UCLASS()
class NIGHTSHIFT_API ANSGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ANSGameMode();
    virtual void BeginPlay() override;
};
