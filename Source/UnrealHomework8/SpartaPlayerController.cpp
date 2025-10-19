// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaPlayerController.h"
#include "Blueprint/UserWidget.h" 
#include "SpartaGameStateBase.h"
#include "SpartaGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"


ASpartaPlayerController::ASpartaPlayerController():
    HUDWidgetClass(nullptr),
    HUDWidgetInstance(nullptr),
    MainMenuWidgetClass(nullptr),
    MainMenuWidgetInstance(nullptr)
{
}

void ASpartaPlayerController::BeginPlay()
{
    Super::BeginPlay();

    ASpartaGameStateBase* GS = GetWorld() ? GetWorld()->GetGameState<ASpartaGameStateBase>() : nullptr;
    if (GS)
    {
        GS->UpdateHUD();
    }

    FString CurrentMapName = GetWorld()->GetMapName();
    if (CurrentMapName.Contains("MenuLevel"))
    {
        ShowMainMenu(false);
    }
}

UUserWidget* ASpartaPlayerController::GetHUDWidget() const
{
    return HUDWidgetInstance;
}

void ASpartaPlayerController::ShowMainMenu(bool bIsRestart)
{
	
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}


	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	
	if (MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();

			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}

		if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{
			if (bIsRestart)
			{
				ButtonText->SetText(FText::FromString(TEXT("Restart")));
			}
			else
			{
				ButtonText->SetText(FText::FromString(TEXT("Start")));
			}
		}

		if (bIsRestart)
		{
			UFunction* PlayAnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
			if (PlayAnimFunc)
			{
				MainMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
			}

			if (UTextBlock* TotalScoreText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName("TotalScoreText")))
			{
				if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this)))
				{
					TotalScoreText->SetText(FText::FromString(
						FString::Printf(TEXT("Total Score: %d"), SpartaGameInstance->TotalScore)
					));
				}
			}
		}
	}
}


void ASpartaPlayerController::ShowGameHUD()
{

	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();

			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());

			ASpartaGameStateBase* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameStateBase>() : nullptr;
			if (SpartaGameState)
			{
				SpartaGameState->UpdateHUD();
			}
		}
	}
}

void ASpartaPlayerController::StartGame()
{
	if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		SpartaGameInstance->CurrentLevelIndex = 0;
		SpartaGameInstance->TotalScore = 0;
	}

	UGameplayStatics::OpenLevel(GetWorld(), FName("BasicLevel"));
}

void ASpartaPlayerController::GoToMainMenu()
{
	UGameplayStatics::OpenLevel(this, FName("MenuLevel"));
}

void ASpartaPlayerController::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, this, EQuitPreference::Quit, false);
}

void ASpartaPlayerController::AddDebuffMessage(const FString& Message, float Duration)
{
	if (!HUDWidgetInstance) return;

	
	if (UVerticalBox* MessageBox = Cast<UVerticalBox>(HUDWidgetInstance->GetWidgetFromName(TEXT("DebuffMessageBox"))))
	{
		
		UTextBlock* NewMessage = NewObject<UTextBlock>(MessageBox);
		if (NewMessage)
		{
			NewMessage->SetText(FText::FromString(Message));
			NewMessage->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
			NewMessage->Font.Size = 18;

			MessageBox->AddChildToVerticalBox(NewMessage);
			
			FTimerHandle TimerHandle;
			FTimerDelegate RemoveDelegate;
			RemoveDelegate.BindLambda([=]() {
				if (NewMessage->IsValidLowLevel() && MessageBox->HasChild(NewMessage))
				{
					MessageBox->RemoveChild(NewMessage);
				}
			});
			GetWorldTimerManager().SetTimer(TimerHandle, RemoveDelegate, Duration, false);
		}
	}
}
