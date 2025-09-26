#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveGrillActor.generated.h"

UCLASS()
class MYPROJECT_API AMoveGrillActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMoveGrillActor();//생성자

protected:
	FVector StartLocation;//

	float MoveSpeed;//움직임 속도
	float RunningTime;//누적시간
	float MaxMove;//이동거리
	
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
