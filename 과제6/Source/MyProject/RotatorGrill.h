#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatorGrill.generated.h"

UCLASS()
class MYPROJECT_API ARotatorGrill : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ARotatorGrill();

protected:
	USceneComponent* SceneRoot;//루트 컴포넌트 Scene포인터
	UStaticMeshComponent* StaticMeshComp; //스태틱 매쉬 포인터

	FVector StartRotation; //초기 회전

	float RotationSpeed;//회전 속도
	float RunningTime;//누적 시간

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
