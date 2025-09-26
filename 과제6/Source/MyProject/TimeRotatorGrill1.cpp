#include "TimeRotatorGrill1.h"

ATimeRotatorGrill1::ATimeRotatorGrill1()
{
	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 0.0f; //회전속도 초기값
}

void ATimeRotatorGrill1::BeginPlay()
{
	Super::BeginPlay();
	//위치
	StartLocation = GetActorLocation();
	//SetActorLocation(FVector(1100.0f, -680.0f, 410.0f));
	//시작  타이머
	//GetWorldTimerManager() .SetTimer(StartRotationTimerHandle, this, &ATimeRotatorGrill1::StartRotation, 1.0f, true);
}

void ATimeRotatorGrill1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))//x y z 회전속도
	{
		AddActorLocalRotation(FRotator(RotationAxis.X * RotationSpeed * DeltaTime,
																	RotationAxis.Y * RotationSpeed * DeltaTime,
																	RotationAxis.Z * RotationSpeed * DeltaTime));
	}
}

//void ATimeRotatorGrill1::StartRotation()//회전속도
//{
//	RotationSpeed = 150.0f;
//}