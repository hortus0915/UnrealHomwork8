// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SpartaGameStateBase.generated.h"

UCLASS()
class UNREALHOMEWORK8_API ASpartaGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
    ASpartaGameStateBase();


	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 SpawnedCoinCount;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 CollectedCoinCount;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	float LevelDuration;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CurrentWaveIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 MaxWaves = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	float WaveInterval = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	class ASpawnVolume* ConnectedSpawnVolume;
	
	FTimerHandle LevelTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;
	FTimerHandle WaveTimerHandle;

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();

	UFUNCTION(BlueprintImplementableEvent, Category = "Wave")
	void OnWaveStarted(int32 WaveIndex);

	
	void StartLevel();
	void StartWave();
	
	void HandleWaveProgression();

	void OnLevelTimeUp();
	void OnCoinCollected();
	void EndLevel();
	void UpdateHUD();
	
};
