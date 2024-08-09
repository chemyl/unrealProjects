// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (InFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
}
void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorldTimerManager().SetTimer(FireRateTimerHandler, this, &ATower::CheckFireCondition, FireRate, true);   //true/false будет ли это лупом, каждые 2 секунды пока игра не закончится
}

void ATower::CheckFireCondition()
{
    if (Tank == nullptr)
    {
        return;
    }
    if (InFireRange() && Tank->bAlivePlayer)
    {
        Fire();
    }
}

bool ATower::InFireRange()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if (Distance <= FireRange)
        {
            return true;
        }
    }
    return false;
}