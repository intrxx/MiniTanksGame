// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTankPlayerController.h"
#include "GameFramework/Pawn.h"


void AToonTankPlayerController::SetPLayerEnabledState(bool bPLayerEnabled)
{
	if(bPLayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPLayerEnabled;
}
