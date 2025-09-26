#include "MoveGrillActor.h"

AMoveGrillActor::AMoveGrillActor()
{
	PrimaryActorTick.bCanEverTick = true;
	//루트 컴포넌트 생성
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	//스태틱 매시 생성과 루트컴포넌트를 부모로 설정
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	//스태틱 메쉬 연결
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/SciFiPanels/Mesh/SM_Grill_289_Type1.SM_Grill_289_Type1'"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset(TEXT("/Script/Engine.Material'/Game/SciFiPanels/Material/Grill_289_MAT.Grill_289_MAT'"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	MoveSpeed = 1.0f; //움직임 속도
	MaxMove = 500.0f;
}

void AMoveGrillActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorLocation(FVector(170.0f,0.0f, -5.0f));//초기 위치
}

void AMoveGrillActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//액터 움직임 구현
	if (!FMath::IsNearlyZero(MoveSpeed))
	{
		AddActorLocalOffset(FVector(MoveSpeed * DeltaTime, 0.0f, 0.0f));//x축 이동 설정
	}
	RunningTime += DeltaTime;//누적 시간 더하기
	
	//이동 반복
	float DeltaMove = (FMath::Sin(RunningTime * MoveSpeed) + 1.0f) * MaxMove;
	FVector NewLocation = StartLocation;//새 위치 계산
	NewLocation.X += DeltaMove + 170.0f;

	SetActorLocation(NewLocation);//위치 재설정
}

