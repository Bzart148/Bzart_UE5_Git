#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestCharacter.generated.h"

class USpringArmComponent; // 스프링 암 클래스 전방선언
class UCameraComponent; //카메라 컴포넌트 전방선언

UCLASS()
class HOMEWORK7_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ATestCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")//에디터 사용 권한
	USpringArmComponent* SpringArmComp;//스프링암 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")//에디터 사용 권한
	UCameraComponent* CameraComp;//카메라 컴포넌트

	//virtual void BeginPlay() override;
	//virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
