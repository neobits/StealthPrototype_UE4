// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Waypoint.generated.h"

UCLASS()
class STEALTHPROTOTYPE_API AWaypoint : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		TArray<AActor*> Neighbours;
	UPROPERTY(EditAnywhere)
		AActor* NextWaypoint;
	UPROPERTY(EditAnywhere)
		AActor* PrevWaypoint;
	UPROPERTY(VisibleAnywhere)
		UPrimitiveComponent* Trigger;

public:

	AWaypoint();

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE AActor* GetNextWaypoint() { return NextWaypoint; }
	FORCEINLINE AActor* GetPrevWaypoint() { return PrevWaypoint; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};