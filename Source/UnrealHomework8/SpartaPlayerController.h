// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpartaPlayerController.generated.h"


UCLASS()
class UNREALHOMEWORK8_API ASpartaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASpartaPlayerController();

	void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	UUserWidget* HUDWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Menu")
	UUserWidget* MainMenuWidgetInstance;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowGameHUD();
	
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void ShowMainMenu(bool bIsRestart);
	
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void GoToMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void QuitGame();

	UFUNCTION(BlueprintCallable)
	void AddDebuffMessage(const FString& Message, float Duration = 3.0f);

	UFUNCTION(BlueprintPure, Category = "HUD")
	UUserWidget* GetHUDWidget() const;
	
};
