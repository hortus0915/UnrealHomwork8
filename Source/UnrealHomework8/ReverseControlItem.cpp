#include "ReverseControlItem.h"

#include "SpartaPlayerController.h"
#include "UnrealHomework8Character.h"
#include "TimerManager.h"

AReverseControlItem::AReverseControlItem()
{
	ItemType = "ReverseControl";
}

void AReverseControlItem::ActivateItem(AActor* Activator)
{
	AUnrealHomework8Character* Player = Cast<AUnrealHomework8Character>(Activator);
	if (!Player) return;
	
	Player->bIsReversed = true;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [Player]()
	{
		if (Player)
		{
			Player->bIsReversed = false;
		}
	}, ReverseDuration, false);

	if (APlayerController* PC = Cast<APlayerController>(Player->GetController()))
	{
		if (ASpartaPlayerController* SpartaPC = Cast<ASpartaPlayerController>(PC))
		{
			SpartaPC->AddDebuffMessage(TEXT("이동 반전!"), 3.0f);
		}
	}
	
	DestroyItem();
}
