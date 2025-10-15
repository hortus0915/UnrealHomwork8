// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealHomework8GameMode.h"
#include "UnrealHomework8Character.h"
#include "UObject/ConstructorHelpers.h"


AUnrealHomework8GameMode::AUnrealHomework8GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}



}
