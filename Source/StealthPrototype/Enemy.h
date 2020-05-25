// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Waypoint.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"


UCLASS()
class STEALTHPROTOTYPE_API AEnemy : public ACharacter
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:
	AEnemy();
	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy, meta = (AllowPrivateAccess = "true"))
		float SightAngle;
	
	float GetSightAngle() { return SightAngle; }
	/// Return Half of the Field of View in RAD
	float GetFOV() { return FMath::DegreesToRadians(SightAngle); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy, meta = (AllowPrivateAccess = "true"))
		float SightRadius;

	float GetSightRadius() { return SightRadius; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AWaypoint* TargetWaypoint;

	AWaypoint* GetTargetWaypoint() { return TargetWaypoint; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WaypointWaitTime;

	float GetWaypointWaitTime() { return WaypointWaitTime; }

	UFUNCTION()
		void SetNextWaypointOnPath();

private:

	FVector TargetLocation;
	FVector StartLocation;
	void FindLocation();
	void MovePathBehaviour(float deltaTime);

	float CurrWpTime;
	bool bIsMoving;
};
