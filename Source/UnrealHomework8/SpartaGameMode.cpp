// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaGameMode.h"
#include "UnrealHomework8Character.h"
#include "SpartaGameStateBase.h"

ASpartaGameMode::ASpartaGameMode()
{
	
	GameStateClass = ASpartaGameStateBase::StaticClass();
}
