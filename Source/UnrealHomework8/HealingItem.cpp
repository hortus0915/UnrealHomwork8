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
			// ĳ������ ü���� ȸ��
			PlayerCharacter->AddHealth(HealAmount);
		}
		DestroyItem();
    }
}