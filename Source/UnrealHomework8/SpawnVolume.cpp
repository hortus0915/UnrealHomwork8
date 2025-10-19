#include "SpawnVolume.h"

#include "SpartaGameStateBase.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ASpawnVolume::ASpawnVolume()
{
    PrimaryActorTick.bCanEverTick = false;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
    SpawningBox->SetupAttachment(Scene);

    ItemDataTable = nullptr;
}

void ASpawnVolume::BeginPlay()
{
    Super::BeginPlay();

    AGameStateBase* GameStateBase = UGameplayStatics::GetGameState(this);
    if (ASpartaGameStateBase* SpartaState = Cast<ASpartaGameStateBase>(GameStateBase))
    {
        SpartaState->ConnectedSpawnVolume = this;
    }
}

AActor* ASpawnVolume::SpawnRandomItem()
{
    if (FItemSpawnRow* SelectedRow = GetRandomItem())
    {
        if (UClass* ActualClass = SelectedRow->ItemClass.Get())
        {
            return SpawnItem(ActualClass);
        }
    }
    return nullptr;
}

AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
    if (!ItemClass) return nullptr;

    AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
        ItemClass,
        GetRandomPointInVolume(),
        FRotator::ZeroRotator
    );

    return SpawnedActor;
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
    const FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
    const FVector BoxOrigin = SpawningBox->GetComponentLocation();

    return BoxOrigin + FVector(
        FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
        FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
        FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
    );
}

void ASpawnVolume::SpawnWaveSpecials(int32 WaveIndex)
{
    if (!WaveSpawnInfos.IsValidIndex(WaveIndex)) return;

    const FWaveSpawnInfo& Info = WaveSpawnInfos[WaveIndex];

    if (Info.ActorToSpawn && Info.Count > 0)
    {
        for (int32 i = 0; i < Info.Count; ++i)
        {
            SpawnItem(Info.ActorToSpawn);
        }

        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow,
            FString::Printf(TEXT("[Wave %d] %s x%d 스폰됨"),
            WaveIndex + 1,
            *Info.ActorToSpawn->GetName(),
            Info.Count));
    }
}

FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
    if (!ItemDataTable) return nullptr;

 
    TArray<FItemSpawnRow*> AllRows;
    static const FString ContextString(TEXT("ItemSpawnContext"));
    ItemDataTable->GetAllRows(ContextString, AllRows);

    if (AllRows.IsEmpty()) return nullptr;

    float TotalChance = 0.0f;
    for (const FItemSpawnRow* Row : AllRows)
    {
        if (Row) 
        {
            TotalChance += Row->SpawnChance; 
        }
    }

 
    const float RandValue = FMath::FRandRange(0.0f, TotalChance);
    float AccumulateChance = 0.0f;

    for (FItemSpawnRow* Row : AllRows)
    {
        AccumulateChance += Row->SpawnChance;
        if (RandValue <= AccumulateChance)
        {
            return Row;
        }
    }

    return nullptr;
}

