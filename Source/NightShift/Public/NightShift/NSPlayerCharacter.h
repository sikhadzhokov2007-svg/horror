#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NSPlayerCharacter.generated.h"

class UCameraComponent;

UCLASS()
class NIGHTSHIFT_API ANSPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ANSPlayerCharacter();
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void StartSprint();
    void StopSprint();
    void StartCrouching();
    void StopCrouching();
    void Interact();

    UPROPERTY(VisibleAnywhere, Category = "Camera")
    TObjectPtr<UCameraComponent> FirstPersonCamera;

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    float WalkSpeed = 320.f;

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    float SprintSpeed = 540.f;

    UPROPERTY(EditDefaultsOnly, Category = "Interaction")
    float InteractionDistance = 250.f;
};
