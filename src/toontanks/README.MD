####
BasePawn
    - Base pawn based on APawn
    - components for child class
        - UCapsuleComponent | CapsuleComp
        - UStaticMeshComponent | BaseMesh
        - UStaticMeshComponent | TurretMesh
        - USceneComponent | ProjectileSpawnPoint
    - exposed ProjectileClass as UClass(TSubclassOf)
    - functions
        - Fire()
        - RotateTurret(FVector LookAtTarget)
####
Tank child class
    - Pawn based on ABasePawn
    - components
        - UCapsuleComponent | CapsuleComp
        - UStaticMeshComponent | BaseMesh
        - UStaticMeshComponent | TurretMesh
        - USceneComponent | ProjectileSpawnPoint
        - USpringArmComponent | SpringArm
        - UCameraComponent | Camera
    - functions
        - ATank::ATank()
            - CreateDefaultSubobject
        - ATank::BeginPlay()
            - PlayerControllerRef -> Cast<APlayerController>(GetController()
        - ATank::Tick
            - PlayerControllerRef->GetHitResultUnderCursor()
        - SetupPlayerInputComponent()
            - BindAxis
            - BinActions
        - Move(float value)
            -AddActorLocalOffset
        - Turn(float value)
            -AddActorLocalRotation
    - variables
        - Speed
        - TurnRate
####
Tower child class
    - Pawn based on BasePawn
    - components
        - UCapsuleComponent* CapsuleComp
        - UStaticMeshComponent* BaseMesh
        - UStaticMeshComponent* TurretMesh
        - USceneComponent* ProjectileSpawnPoint
    - functions
        - ATower::Tick
            - RotateTurret(Tank->GetActorLocation())
        - ATower::BeginPlay()
            - Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0))
            - GetWorldTimerManager().SetTimer()
        - void CheckFireCondition()
        - bool InFireRange()
            - FVector::Dist
    - variables
        - FireRange
        - FireRate
        - class ATank* Tank;
####
Projectile class
    -Pawn based on AActor
    - components
        - UStaticMeshComponent* ProjectileMesh
        - UProjectileMovementComponent* ProjectileMovementComp
    - functions
        - AProjectile::BeginPlay()
            - ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit)
        - UFUNCTION() OnHit
            - UGameplayStatics::ApplyDamage
    - variables
        - Damage(float)
####
HealthComponent
    - Component based on UActorComponent
    - functions
        - UHealthComponent::BeginPlay()
            - GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
            - Health = MaxHealth;
        - UHealthComponent::DamageTaken
    - variables
        - float MaxHealth
        - float Health