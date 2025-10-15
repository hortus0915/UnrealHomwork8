#include "HealingItem.h"
#include "UnrealHomework8Character.h"

AHealingItem::AHealingItem()
{
	HealAmount = 20.0f;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{

    if (Activator && Activator->ActorHasTag("Player"))
    {
		if (AUnrealHomework8Character* PlayerCharacter = Cast<AUnrealHomework8Character>(Activator))
		{
			// 캐릭터의 체력을 회복
			PlayerCharacter->AddHealth(HealAmount);
		}
		DestroyItem();
    }
}