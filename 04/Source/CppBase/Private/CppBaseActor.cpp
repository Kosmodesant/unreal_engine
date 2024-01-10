// Fill out your copyright notice in the Description page of Project Settings.


#include "CppBaseActor.h"
#include "Engine/Engine.h"

// Sets default values
ACppBaseActor::ACppBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void ACppBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLocation = FVector(FMath::FRandRange(-100.0f, 100.0f), FMath::FRandRange(0.0f, 350.0f), 0.0f);
	SetActorLocation(InitialLocation);
}


float ACppBaseActor::SinMovement(const float z)
{
	UWorld* World = GetWorld();

	float multJump = (FMath::Sin(Frequency * World->GetTimeSeconds()) + 1.0) / 2;

	return (Amplitude * multJump + z);
}

// Called every frame
void ACppBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
