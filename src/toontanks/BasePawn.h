// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"


UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	
	void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Pawn")
	class UParticleSystem* Blowparticles;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Pawn")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};
