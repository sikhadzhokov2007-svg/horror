#include "NightShift/NSDoor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ANSDoor::ANSDoor()
{
    PrimaryActorTick.bCanEverTick = true;
    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMesh;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (Cube.Succeeded()) DoorMesh->SetStaticMesh(Cube.Object);
    DoorMesh->SetRelativeScale3D(FVector(0.08f, 0.75f, 1.25f));
    DoorMesh->SetCollisionProfileName(TEXT("BlockAll"));
}

void ANSDoor::ToggleDoor()
{
    bOpen = !bOpen;
    DoorMesh->SetCollisionEnabled(bOpen ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);
}

void ANSDoor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    const float TargetYaw = bOpen ? OpenYaw : ClosedYaw;
    SetActorRotation(FMath::RInterpTo(GetActorRotation(), FRotator(0.f, TargetYaw, 0.f), DeltaSeconds, 4.f));
}
