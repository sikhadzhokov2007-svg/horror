#include "NightShift/NSPlayerCharacter.h"
#include "NightShift/NSDoor.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ANSPlayerCharacter::ANSPlayerCharacter()
{
    bUseControllerRotationYaw = true;
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    GetCharacterMovement()->MaxWalkSpeedCrouched = 170.f;
    GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
    FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, 64.f));
    FirstPersonCamera->bUsePawnControlRotation = true;
}

void ANSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* Input)
{
    Super::SetupPlayerInputComponent(Input);
    Input->BindAxis(TEXT("MoveForward"), this, &ANSPlayerCharacter::MoveForward);
    Input->BindAxis(TEXT("MoveRight"), this, &ANSPlayerCharacter::MoveRight);
    Input->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
    Input->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
    Input->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
    Input->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);
    Input->BindAction(TEXT("Sprint"), IE_Pressed, this, &ANSPlayerCharacter::StartSprint);
    Input->BindAction(TEXT("Sprint"), IE_Released, this, &ANSPlayerCharacter::StopSprint);
    Input->BindAction(TEXT("Crouch"), IE_Pressed, this, &ANSPlayerCharacter::StartCrouching);
    Input->BindAction(TEXT("Crouch"), IE_Released, this, &ANSPlayerCharacter::StopCrouching);
    Input->BindAction(TEXT("Interact"), IE_Pressed, this, &ANSPlayerCharacter::Interact);
}

void ANSPlayerCharacter::MoveForward(float Value) { AddMovementInput(GetActorForwardVector(), Value); }
void ANSPlayerCharacter::MoveRight(float Value) { AddMovementInput(GetActorRightVector(), Value); }
void ANSPlayerCharacter::StartSprint() { if (!bIsCrouched) GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; }
void ANSPlayerCharacter::StopSprint() { GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; }
void ANSPlayerCharacter::StartCrouching() { Crouch(); }
void ANSPlayerCharacter::StopCrouching() { UnCrouch(); }

void ANSPlayerCharacter::Interact()
{
    FHitResult Hit;
    const FVector Start = FirstPersonCamera->GetComponentLocation();
    const FVector End = Start + FirstPersonCamera->GetForwardVector() * InteractionDistance;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(Interact), false, this);
    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
    {
        if (ANSDoor* Door = Cast<ANSDoor>(Hit.GetActor())) Door->ToggleDoor();
    }
}
