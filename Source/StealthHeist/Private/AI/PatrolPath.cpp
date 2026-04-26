// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PatrolPath.h"

// Sets default values
APatrolPath::APatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Billboard = CreateDefaultSubobject<UBillboardComponent>("Billboard");
	SetRootComponent(Billboard);

	FacingDirection = CreateDefaultSubobject<UArrowComponent>("FacingDirection");
	FacingDirection->SetupAttachment(Billboard);

	Path = CreateDefaultSubobject<USplineComponent>("Path");
	Path->SetupAttachment(RootComponent);
	Path->bDrawDebug = true;

}

// Called when the game starts or when spawned
void APatrolPath::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i <= Path->GetNumberOfSplinePoints(); i++)
	{
		Locations.Add(Path->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World));
	}
	

}

// Called every frame
void APatrolPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

