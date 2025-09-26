#include "TestCharacter.h"

//카메라 , 스프링암 사용시
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATestCharacter::ATestCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	//스프링 암 생성
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);//스프링 암을 루트컴포넌트에 부착
	SpringArmComp->TargetArmLength = 300.0f;//카메라와 캐릭터 사이의 거리
	SpringArmComp->bUsePawnControlRotation = true;//컨트롤러 회전에 따라 스프링 암도 회전하도록 허용

	//카메라 컴포넌트 생성
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);//스프링암 소켓위치 카메라 부착
	CameraComp->bUsePawnControlRotation = false; //스프링암이 회전함으로 카메라까지 회전할 필요 없음.
}

void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//void ATestCharacter::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//void ATestCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//}