#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PawnCharacterPlayerController.generated.h"

class UInputMappingContext; // IMC전방 선언
class UInputAction; //IA 관련 전방 선언

UCLASS()
class HOMEWORK7_API APawnCharacterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APawnCharacterPlayerController(); //생성자

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;//IMC세팅

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;//IA_PMove 지정한 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;//IA_PJump 지정 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;//IA_PLook 지정 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SprintAction;//IA_PSprint 지정 변수

	virtual void BeginPlay() override;
};
