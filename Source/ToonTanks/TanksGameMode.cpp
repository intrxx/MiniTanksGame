// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTankPlayerController.h"

void ATanksGameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor == Tank)
	{
		Tank->HandleDestruction();

		if(ToonTankPlayerController)
		{
			ToonTankPlayerController->SetPLayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestrucion();
		TargetTowers--;
		if(TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void ATanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}


void ATanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	//Implemented in BP
	StartGame();

	if(ToonTankPlayerController)
	{
		ToonTankPlayerController->SetPLayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;

		FTimerDelegate TimerDelegate;
		TimerDelegate = FTimerDelegate::CreateUObject(
			ToonTankPlayerController,
			&AToonTankPlayerController::SetPLayerEnabledState,
			true
		);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, TimerDelegate, StartDelay, false);
	}
}

int32 ATanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> Towers;

	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

	return Towers.Num();
}

