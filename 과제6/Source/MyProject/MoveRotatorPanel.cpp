#include "MoveRotatorPanel.h"

AMoveRotatorPanel::AMoveRotatorPanel()
{
 	PrimaryActorTick.bCanEverTick = true;
	//루트 컴포넌트 생성 
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SecneRoot"));
	SetRootComponent(SceneRoot);
	//스태틱 매시 생성과 루트컴포넌트를 부모로 설정
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	
	////스태틱매쉬 연결
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/SciFiPanels/Mesh/SM_Panel_215_Type1.SM_Panel_215_Type1'"));
	//if (MeshAsset.Succeeded())
	//{
	//	StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	//}
	////머터리얼 연결
	//static ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset(TEXT(""));


	MoveSpeed = 1.0f;
	MaxMove = 500.0f;
	RotationSpeed = 0.0f;
	
}

void AMoveRotatorPanel::BeginPlay()
{
	Super::BeginPlay();
	//위치값
	StartLocation = GetActorLocation();
}

void AMoveRotatorPanel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//회전방향
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(RotationAxis.X * RotationSpeed * DeltaTime,
																	RotationAxis.Y * RotationSpeed * DeltaTime,
																	RotationAxis.Z * RotationSpeed * DeltaTime));
	}
	//이동 구현
	if (FMath::IsNearlyZero(MoveSpeed))
	{
		AddActorLocalOffset(FVector(0.0f, MoveSpeed * DeltaTime, 0.0f));
	}
	RunningTime += DeltaTime;//누적시간 더하기
	//이동반복
	float DeltaMove = (FMath::Sin(RunningTime * MoveSpeed) + 1.0f) * MaxMove;
	FVector NewLocation = StartLocation;
	NewLocation.Y += DeltaMove;

	SetActorLocation(NewLocation);//위치 재설정
}

