#include "SlowingItem.h"

#include "SpartaPlayerController.h"
#include "UnrealHomework8Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

ASlowingItem::ASlowingItem()
{
	ItemType = "Slowing";
}

void ASlowingItem::ActivateItem(AActor* Activator)
{
	AUnrealHomework8Character* Player = Cast<AUnrealHomework8Character>(Activator);
	if (!Player) return;

	auto* Movement = Player->GetCharacterMovement();
	if (!Movement) return;

	float OriginalSpeed = Movement->MaxWalkSpeed;
	Movement->MaxWalkSpeed *= SlowMultiplier;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [Movement, OriginalSpeed]()
	{
		if (Movement)
		{
			Movement->MaxWalkSpeed = OriginalSpeed;
		}
	}, SlowDuration, false);
	
	if (APlayerController* PC = Cast<APlayerController>(Player->GetController()))
	{
		if (ASpartaPlayerController* SpartaPC = Cast<ASpartaPlayerController>(PC))
		{
			SpartaPC->AddDebuffMessage(TEXT("이동 속도 감소!"), 3.0f);
		}
	}
	
	DestroyItem();
}
