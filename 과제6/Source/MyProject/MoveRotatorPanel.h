// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveRotatorPanel.generated.h"

UCLASS()
class MYPROJECT_API AMoveRotatorPanel : public AActor
{
	GENERATED_BODY()
	
public:	

	AMoveRotatorPanel(); //생성자

protected:
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	FVector RotationAxis = FVector(0.0f, 0.0f, 1.0f);//회전방향

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float MoveSpeed;// 무브 속도
	float RunningTime;//누적시간

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float MaxMove;//이동거리

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float RotationSpeed;//회전속도

	//cpp에서 연결작업 없이 언리얼에서 편집가능
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SceneRoot")
	USceneComponent* SceneRoot;//루트 포인터
	//cpp에서 연결작업 없이 언리얼에서 편집가능
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Matelial")
	UStaticMeshComponent* StaticMeshComp; //스태틱매쉬 포인터
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
