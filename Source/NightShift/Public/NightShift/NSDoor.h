#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NSDoor.generated.h"

class UStaticMeshComponent;

UCLASS()
class NIGHTSHIFT_API ANSDoor : public AActor
{
    GENERATED_BODY()

public:
    ANSDoor();
    void ToggleDoor();

private:
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> DoorMesh;

    bool bOpen = false;
    float ClosedYaw = 0.f;
    float OpenYaw = 90.f;
};
