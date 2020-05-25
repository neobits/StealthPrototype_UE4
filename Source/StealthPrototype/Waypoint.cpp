// Fill out your copyright notice in the Description page of Project Settings.

#include "Waypoint.h"
#include "StealthPrototype.h"

#define WAYPOINT_COLLISION ECollisionChannel::ECC_GameTraceChannel1

// Sets default values
AWaypoint::AWaypoint()
{

}

// Called when the game starts or when spawned
void AWaypoint::BeginPlay()
{
	Super::BeginPlay();
	
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 20.0f, 6, FColor::Red, true);
}

// Called every frame
void AWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

