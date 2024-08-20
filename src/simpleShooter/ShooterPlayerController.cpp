// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    if (bIsWinner)
    {
        UUserWidget* WinScreenWidget = CreateWidget(this, WinScreenClass);
        if (WinScreenWidget != nullptr)
        {
            WinScreenWidget->AddToViewport();
        }
    }
    else
    {
        UUserWidget* LoseScreenWidget = CreateWidget(this, LoseScreenClass);
        if (LoseScreenWidget != nullptr)
        {
            LoseScreenWidget->AddToViewport();
        }
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
