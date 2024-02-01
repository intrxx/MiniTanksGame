// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "TanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

		if(CheckIfInRange())
		{
			RotateTurret(Tank->GetActorLocation());
		}
}


void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle,this,&ATower::CheckFireCondition,FireRate,true);
}

void ATower::HandleDestrucion()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::CheckFireCondition()
{
	if(Tank == nullptr)
	{
		return;
	}
	if(CheckIfInRange() && Tank->bAlive)
	{
		Fire();
	}
}

bool ATower::CheckIfInRange()
{
	if(Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}