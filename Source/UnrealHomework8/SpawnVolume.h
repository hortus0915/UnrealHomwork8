#pragma once

#include "CoreMinimal.h"
#include "ItemSpawnRow.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;

USTRUCT(BlueprintType)
struct FWaveSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorToSpawn;
};

UCLASS()
class UNREALHOMEWORK8_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	ASpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere,BluePrintReadWrite,Category = "Wave Spawning")
	TArray<FWaveSpawnInfo> WaveSpawnInfos;
	
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	AActor* SpawnRandomItem(); 

	FItemSpawnRow* GetRandomItem() const;
	AActor* SpawnItem(TSubclassOf<AActor> ItemClass);
	FVector GetRandomPointInVolume() const;

	UFUNCTION(BlueprintCallable, Category = "Wave Spawning")
	void SpawnWaveSpecials(int32 WaveIndex);

	virtual void BeginPlay()override;

};