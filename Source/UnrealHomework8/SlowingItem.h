// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "SlowingItem.generated.h"

/**
 * 
 */
UCLASS()
class UNREALHOMEWORK8_API ASlowingItem : public ABaseItem
{
	GENERATED_BODY()

public:
	ASlowingItem();

protected:
	UPROPERTY(EditAnywhere, Category = "Debuff")
	float SlowMultiplier = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Debuff")
	float SlowDuration = 5.f;

	virtual void ActivateItem(AActor* Activator) override;
	
};
