#include "MoveXYZActor.h"

AMoveXYZActor::AMoveXYZActor()
{
	PrimaryActorTick.bCanEverTick = true;
	//루트 컴포넌트 생성
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SecneRoot"));
	SetRootComponent(SceneRoot);

	//스태틱 매시 생성과 루트컴포넌트를 부모로 설정
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	MoveSpeed = 0.0f;
	MaxMove = 0.0f;
	RotationSpeed = 0.0f;
}

void AMoveXYZActor::BeginPlay()
{
	Super::BeginPlay();
	//시작 위치
	StartLocation = GetActorLocation();
}

void AMoveXYZActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//회전방향
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(RotationAxis.X * RotationSpeed * DeltaTime,
			RotationAxis.Y * RotationSpeed * DeltaTime,
			RotationAxis.Z * RotationSpeed * DeltaTime));
	}
	//무브방향
	if (!FMath::IsNearlyZero(MoveSpeed))
	{
		if (MaxMove != 0.0f)
		{
			RunningTime += DeltaTime;
			float DeltaMove = (FMath::Sin(RunningTime * MoveSpeed)+ 1.0f) * MaxMove;

			FVector NewLocation = StartLocation + LocationAxis * DeltaMove;
			SetActorLocation(NewLocation);
		}
		else//안전장치MaxMove가  0일때 연산이 일어나지 않게 해주는 조건부
		{
			// 직선 이동
			FVector Offset = LocationAxis * MoveSpeed * DeltaTime;
			AddActorLocalOffset(Offset, true);
		}

		////이동 구현
		//if (FMath::IsNearlyZero(MoveSpeed))
		//{
		//	AddActorLocalOffset(FVector(0.0f, MoveSpeed * DeltaTime, 0.0f));
		//}
	}
}

