// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RotatorGrill.h"
#include "TimeRotatorGrill1.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ATimeRotatorGrill1 : public ARotatorGrill
{
	GENERATED_BODY()
	
public:
	ATimeRotatorGrill1();//생성자


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float RotationSpeed; //회전 속도

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Rotation")
	FVector RotationAxis = FVector(0.0f, 0.0f, 01.0f);//회전방향

    //FTimerHandle StartRotationTimerHandle;//시작 속도 변경

	FVector StartLocation;

	virtual void BeginPlay() override;
	//void StartRotation();
	virtual void Tick(float DeltaTime) override;
};
