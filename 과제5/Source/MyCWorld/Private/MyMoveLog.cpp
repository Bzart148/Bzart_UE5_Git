// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMoveLog.h"

// Sets default values
AMyMoveLog::AMyMoveLog()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	X = 0;
	Y = 0;
}

// Called when the game starts or when spawned
void AMyMoveLog::BeginPlay()
{
	Super::BeginPlay();
	Move();
}

int AMyMoveLog::Step()
{
	return FMath::RandRange(0, 1);	//랜덤 반환
}

void AMyMoveLog::Move()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Position : (%d, %d)"), X, Y);	//처음 위치

	for (int i = 0; i < 10; i++)
	{
		X += Step();
		Y += Step();

		UE_LOG(LogTemp, Warning, TEXT("Step %d -> Position : (%d, %d)"), i + 1, X, Y);	
	}
}
// Called every frame
void AMyMoveLog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
