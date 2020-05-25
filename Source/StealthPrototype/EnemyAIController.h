// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHPROTOTYPE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private :
	AEnemy* EnemyComponent;

	void TriggerNextWaypoint();
	void MoveToDestination(FVector DestLocation, bool bSetTimer = false);
	void MoveToWaypoint();
	void MoveToPlayer();
	void MainAIBehaviour();

	FTimerHandle WaypointTimerHandle;

	UPROPERTY(VisibleAnywhere)
		class AActor* Player;

	void FindPlayerActor();
};
