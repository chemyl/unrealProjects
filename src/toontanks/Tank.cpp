// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Sprint Arm Comp"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Comp"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
    TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlivePlayer = false;
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility, false, HitResult);
        RotateTurret(HitResult.ImpactPoint);
    }
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent); //Но родительский класс базовой Pawn вызовет свою версию.

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float value)
{
	FVector DeltaLocation(0.f);
    DeltaLocation.X = value * GetWorld()->GetDeltaSeconds() * Speed;
	AddActorLocalOffset(DeltaLocation, true);
}


void ATank::Turn(float value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    // интересует вращение отностительно Z оси
    // yaw = value * Deltatime * TurnRate
    DeltaRotation.Yaw = value * GetWorld()->GetDeltaSeconds() * TurnRate;
    AddActorLocalRotation(DeltaRotation);
}
