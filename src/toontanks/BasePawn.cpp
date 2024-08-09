// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider")); 
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::HandleDestruction()
{
	if (Blowparticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, Blowparticles, GetActorLocation(), GetActorRotation());
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{	
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();		//  LookAtTarget - endpoint, GetComponentLocation from USceneComponent
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);		// все происхдит в WorldSpace. создать новый объект вращениятолько для Yaw вектора
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), 5.f));								
}

void ABasePawn::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}
