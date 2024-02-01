// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;;

public:
	ATank();
private:
	UPROPERTY(VisibleAnywhere, Category = "Tank Components")
		class USpringArmComponent* ArmComp;
	UPROPERTY(VisibleAnywhere, Category = "Tank Components")
		class UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere, Category = "Tank Variables")
		float Speed = 400.f;
	UPROPERTY(EditAnywhere, Category = "Tank Variables")
		float TurnRate = 45.f;

	//Movement handling
	void Move(float Value);
	void Turn(float Value);

	APlayerController* PlayerController;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return PlayerController; }

	bool bAlive = true;
};
