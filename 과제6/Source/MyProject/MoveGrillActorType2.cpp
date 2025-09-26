#include "MoveGrillActorType2.h"

AMoveGrillActorType2::AMoveGrillActorType2()
{
	PrimaryActorTick.bCanEverTick = true;
	//루트 컴포넌트 생성과 루트설정
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	//스태틱 매쉬 컴포넌트 생성과 루트에 Attach
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/SciFiPanels/Mesh/SM_Grill_278_Type1.SM_Grill_278_Type1'"));
	if (MeshAsset.Succeeded())//매쉬 연결 안전장치
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset(TEXT("/Script/Engine.Material'/Game/SciFiPanels/Material/Grill_278_MAT.Grill_278_MAT'"));
	if (MaterialAsset.Succeeded()) // 머터리얼 연결 안전장치
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);//0번째 머터리얼 에셋
	}
	MaxScale = 1.0f;//최대크기 값
	MinScale = 0.0f;//최소크기 값
	ScaleSpeed = 5.0f;// 크기 변화 속도
}

void AMoveGrillActorType2::BeginPlay()
{
	Super::BeginPlay();
	StartScale = GetActorScale3D(); //초기 스케일 저장
	SetActorLocation(FVector(1300.0f, 0.0f, -5.0f)); //시작위치 초기화
}

void AMoveGrillActorType2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;//누적시간

	float ScaleFactor = (FMath::Sin(ScaleSpeed * RunningTime) + 1.0f)*0.5f; // 크기반복 속도
	float CurrentScale = FMath::Lerp(MinScale, MaxScale, ScaleFactor);//맥스와 민옵 보간

	FVector NewScale = StartScale * CurrentScale;//크기 설정
	SetActorScale3D(NewScale);
}

