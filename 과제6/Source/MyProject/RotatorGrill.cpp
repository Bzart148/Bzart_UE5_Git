#include "RotatorGrill.h"

ARotatorGrill::ARotatorGrill()
{
	PrimaryActorTick.bCanEverTick = true;
	//루트 컴포넌트 생성 
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	//스태틱 매쉬 생성하고 루트에 어태치
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	//매쉬 연결
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/SciFiPanels/Mesh/SM_Grill_284_Type1.SM_Grill_284_Type1'"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	//머터리얼 연결
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Script/Engine.Material'/Game/SciFiPanels/Material/Grill_282_284_MAT.Grill_282_284_MAT'"));
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}
	RotationSpeed = 180.0f;//회전 속도

}

void ARotatorGrill::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));//회전 초기축
	//SetActorLocation(FVector(1220.0f, -680.0f, 410.0f));
}

void ARotatorGrill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, 0.0f, RotationSpeed * DeltaTime));//X축 회전
	}
	RunningTime += DeltaTime; //시간 누적
}

