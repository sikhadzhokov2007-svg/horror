#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NSBlockoutLevel.generated.h"

class UStaticMesh;

UCLASS()
class NIGHTSHIFT_API ANSBlockoutLevel : public AActor
{
    GENERATED_BODY()

public:
    ANSBlockoutLevel();
    virtual void BeginPlay() override;

private:
    void AddBlock(const FVector& Location, const FVector& Scale, const FLinearColor& Color);
    UStaticMesh* CubeMesh = nullptr;
};
