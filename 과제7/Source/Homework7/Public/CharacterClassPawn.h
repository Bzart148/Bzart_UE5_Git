#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CharacterClassPawn.generated.h"

class UCapsuleComponent;				//캡슐컴포넌트 전방 선언
class USkeletalMeshComponent;	//스켈레탈매시 전방 선언
class UArrowComponent;				//캡슐 화살 컴포넌트 전방 선언
class USpringArmComponent;		//스프링 암 컴포넌트 전방선언
class UCameraComponent;				//카메라 컴포넌트 전방선언
struct FinputActionValue;				//인핸스드 인풋 액션 값 받을 때 사용하는 구조체
class UFloatingPawnMovement;	//입력>실행 함수 입력 전방선언

UCLASS()
class HOMEWORK7_API ACharacterClassPawn : public APawn
{
	GENERATED_BODY()

public:

	ACharacterClassPawn();

protected:
	
	
	//virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite )//접근권한 카테고리 설정
	UCapsuleComponent* CapsuleComp; //캡슐 컴포넌트 포인터
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")// meta = (AllowPrivateAccess = "true")) privete 접근 허용
	USkeletalMeshComponent* SkeletonComp;//스켈레톤 매시 포인터
	UPROPERTY()
	UArrowComponent* ArrowComp; //화실 포인터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")//에디터 사용 권한
	USpringArmComponent* SpringArmComp;//스프링암 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")//에디터 사용 권한
	UCameraComponent* CameraComp;//카메라 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UFloatingPawnMovement* MovementComp;//Pawn에서 작업해야되는 무브 함수

	//입력 바인딩 처이 함수
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//IA_PMove와 IA_PJump 등을 처리할 함수 원형
	//인핸스드 인풋에서 액션 값은 FInputActionValue로 전달된다.
	UFUNCTION()//UFUNCTION()을 안 붙이면 바인딩에 실패 할 수도 있다.
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	UFUNCTION()
	void EndJump(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void EndSprint(const FInputActionValue& value);

	float MoveSpeed; //이동속도
	float SprintSpeed;//스프린트속도

	bool bIsJump;//점프상태
	float JumpVelocity;//점프높이

	float VerticalVelocity; //수직속도
	float Gravity; //중력값

	//지면 체크
	bool IsGrounded() const;
};
