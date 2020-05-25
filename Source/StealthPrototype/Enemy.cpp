// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Engine.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	CurrWpTime = 0;
	bIsMoving = true;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FindLocation();
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::FindLocation()
{
	TargetLocation = TargetWaypoint->GetActorLocation();
}

void AEnemy::SetNextWaypointOnPath()
{
	TargetWaypoint = Cast<AWaypoint>(TargetWaypoint->GetNextWaypoint());
}

void AEnemy::MovePathBehaviour(float DeltaTime)
{
	FVector LocRest = TargetLocation - GetActorLocation();
	LocRest.Z = 0;
	if (LocRest.IsNearlyZero(0.5f))
	{
		if (bIsMoving)
		{
			GLog->Log("Enemy arrived to waypoint!!");
			FVector NewLocation = FVector(TargetLocation.X, TargetLocation.Y, GetActorLocation().Z);
			SetActorLocation(NewLocation);
			bIsMoving = false;
		}
	}
	else {
		FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), TargetLocation, DeltaTime, WalkSpeed);
		SetActorLocation(NewLocation);
	}

	if (!bIsMoving)
	{
		CurrWpTime += DeltaTime;
		if (CurrWpTime >= WaypointWaitTime)
		{
			CurrWpTime = 0;
			SetNextWaypointOnPath();
			bIsMoving = true;
		}
	}
}