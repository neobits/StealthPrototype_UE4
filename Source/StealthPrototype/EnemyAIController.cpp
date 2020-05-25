// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "Enemy.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Engine.h"
#include "StealthPrototypeCharacter.h"


AEnemyAIController::AEnemyAIController()
{
	EnemyComponent = Cast<AEnemy>(GetPawn());
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	EnemyComponent = Cast<AEnemy>(GetPawn());

	FindPlayerActor();
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MainAIBehaviour();
}

void AEnemyAIController::TriggerNextWaypoint()
{
	EnemyComponent->SetNextWaypointOnPath();
}

void AEnemyAIController::MainAIBehaviour()
{
	if (Player == NULL)
	{
		FindPlayerActor();
	}

	float const Distance = FVector::Dist(Player->GetActorLocation(), EnemyComponent->GetActorLocation());

	//arccos(scalarProduct(viewDirection, (object - you)) / (norm(viewDirection)*norm(object - you))).

	// Near the player is...
	if (Distance < EnemyComponent->GetSightRadius())
	{
		//GLog->Log("Player is near!");
		FVector ViewDirection = GetActorForwardVector();
		FVector RestVector = Player->GetActorLocation() - EnemyComponent->GetActorLocation();
		RestVector.Normalize();
		float T = FVector::DotProduct(ViewDirection, RestVector);
		
		if (FMath::Cos(EnemyComponent->GetFOV()) < T)
		{
			MoveToPlayer();
		}
	}
	else
	{
		//GLog->Log("I will go to waypoint.");
		MoveToWaypoint();
	}
}

void AEnemyAIController::FindPlayerActor()
{
	for (TActorIterator<AStealthPrototypeCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		//GLog->Log(ActorItr->GetName());
		Player = *ActorItr;
	}
}

void AEnemyAIController::MoveToDestination(FVector DestLocation, bool bSetTimer)
{
	UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
	float const Distance = FVector::Dist(DestLocation, EnemyComponent->GetActorLocation());

	if (NavSys)
	{
		if (Distance > 120.0f)
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
			if (bSetTimer)
			{
				Super::GetWorld()->GetTimerManager().SetTimer(
					WaypointTimerHandle,
					this,
					&AEnemyAIController::TriggerNextWaypoint,
					EnemyComponent->GetWaypointWaitTime(),
					false);
			}
		}
	}
}

void AEnemyAIController::MoveToWaypoint()
{
	FVector DestLocation = EnemyComponent->GetTargetWaypoint()->GetActorLocation();	
	MoveToDestination(DestLocation, true);
}

void AEnemyAIController::MoveToPlayer()
{
	FVector DestLocation = Player->GetActorLocation();
	MoveToDestination(DestLocation);
}