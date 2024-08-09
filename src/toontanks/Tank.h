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

public:
	ATank();
	void HandleDestruction();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	APlayerController* GetTankPlayerController() const { return TankPlayerController; };

	bool bAlivePlayer = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Views", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Views", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;


	void Move(float value);
	UPROPERTY(EditAnywhere)
	float Speed = 10.f;

	void Turn(float value);
	UPROPERTY(EditAnywhere)
	float TurnRate = 10.f;

	APlayerController* TankPlayerController;

};
