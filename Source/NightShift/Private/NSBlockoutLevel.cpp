#include "NightShift/NSBlockoutLevel.h"
#include "NightShift/NSDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

ANSBlockoutLevel::ANSBlockoutLevel()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (Cube.Succeeded()) CubeMesh = Cube.Object;
}

void ANSBlockoutLevel::BeginPlay()
{
    Super::BeginPlay();
    // Первый проходимый блок-аут: ночной вестибюль, длинный коридор и три учебных кабинета.
    AddBlock(FVector(0, 0, -110), FVector(30, 20, 0.1f), FLinearColor(0.08f, 0.09f, 0.12f));
    AddBlock(FVector(2600, 0, -110), FVector(25, 5, 0.1f), FLinearColor(0.08f, 0.09f, 0.12f));
    AddBlock(FVector(5200, 0, -110), FVector(12, 20, 0.1f), FLinearColor(0.08f, 0.09f, 0.12f));
    for (float X = 0; X <= 5200; X += 200) {
        AddBlock(FVector(X, -520, 350), FVector(1, 0.1f, 4.5f), FLinearColor(0.04f, 0.05f, 0.07f));
        AddBlock(FVector(X, 520, 350), FVector(1, 0.1f, 4.5f), FLinearColor(0.04f, 0.05f, 0.07f));
    }
    AddBlock(FVector(5200, 0, 350), FVector(0.1f, 20, 4.5f), FLinearColor(0.04f, 0.05f, 0.07f));
    AddBlock(FVector(2600, 0, 800), FVector(30, 6, 0.1f), FLinearColor(0.04f, 0.05f, 0.07f));
    for (int32 Index = 0; Index < 3; ++Index) {
        const float X = 3600.f + Index * 600.f;
        AddBlock(FVector(X, 1150, -110), FVector(2.8f, 6.5f, 0.1f), FLinearColor(0.12f, 0.10f, 0.08f));
        AddBlock(FVector(X, 1800, 350), FVector(2.8f, 0.1f, 4.5f), FLinearColor(0.04f, 0.05f, 0.07f));
        AddBlock(FVector(X - 280, 1150, 350), FVector(0.1f, 6.5f, 4.5f), FLinearColor(0.04f, 0.05f, 0.07f));
        AddBlock(FVector(X + 280, 1150, 350), FVector(0.1f, 6.5f, 4.5f), FLinearColor(0.04f, 0.05f, 0.07f));
        GetWorld()->SpawnActor<ANSDoor>(FVector(X, 530, 125), FRotator::ZeroRotator);
    }
}

void ANSBlockoutLevel::AddBlock(const FVector& Location, const FVector& Scale, const FLinearColor& Color)
{
    UStaticMeshComponent* Block = NewObject<UStaticMeshComponent>(this);
    Block->SetStaticMesh(CubeMesh);
    Block->SetWorldLocation(Location);
    Block->SetWorldScale3D(Scale);
    Block->SetCollisionProfileName(TEXT("BlockAll"));
    Block->RegisterComponent();
}
