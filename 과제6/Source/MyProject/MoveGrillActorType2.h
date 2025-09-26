#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveGrillActorType2.generated.h"

UCLASS()
class MYPROJECT_API AMoveGrillActorType2 : public AActor
{
	GENERATED_BODY()
	
public:	
	AMoveGrillActorType2();

protected:
	USceneComponent* SceneRoot; //루트 컴포넌트 포인터
	UStaticMeshComponent* StaticMeshComp; //스태틱매쉬 포인터

	FVector StartScale;//초기 크기

	float MaxScale; //최대 크기
	float MinScale;//최소 크기
	float ScaleSpeed;//크기 변화 속도
	float RunningTime; //누적시간

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
