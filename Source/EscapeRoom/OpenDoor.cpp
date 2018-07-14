// Fill out your copyright notice in the Description page of Project Settings.
#include "OpenDoor.h"

#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"


#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	if (!PressurePlate) UE_LOG(LogTemp, Error, TEXT("PressurePlate is missing !"));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) //TODO: make parameter
	{
		if (!Owner) return;
		OnOpen.Broadcast();
	}
	else
	{
		///TODO: close door
		if (!Owner) return;
		OnClose.Broadcast();
	}

}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	if (!PressurePlate) return TotalMass;

	TArray<AActor*> OverlappingActors;
	//Find all overlaping accors
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto* Actor : OverlappingActors)
	{
		//
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());
	}

	// Iterate and take mass

	return TotalMass;
}
