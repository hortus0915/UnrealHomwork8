#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ReverseControlItem.generated.h"

UCLASS()
class UNREALHOMEWORK8_API AReverseControlItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AReverseControlItem();

protected:
	UPROPERTY(EditAnywhere, Category = "Debuff")
	float ReverseDuration = 5.f;

	virtual void ActivateItem(AActor* Activator) override;
};
