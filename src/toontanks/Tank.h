#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

protected:
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

	APlayerController* PlayerControllerRef;

};
