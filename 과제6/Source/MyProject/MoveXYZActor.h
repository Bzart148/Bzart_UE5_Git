#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveXYZActor.generated.h"

UCLASS()
class MYPROJECT_API AMoveXYZActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMoveXYZActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SceneRoot")
	USceneComponent* SceneRoot;//씬 포인터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UStaticMeshComponent* StaticMeshComp;//스태틱 매시 포인터

	FVector StartLocation;//초기 위치값

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FVector LocationAxis = FVector(0.0f, 0.0f, 0.0f);//이동방향
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	FVector RotationAxis = FVector(0.0f, 0.0f, 0.0f);//회전방향

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	float MoveSpeed;//무브 속도
	float RunningTime;//누적 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	float MaxMove;//이동거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float RotationSpeed;//회전속도
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
