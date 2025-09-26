#include "CharacterClassPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputComponent.h"
#include "PawnCharacterPlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ACharacterClassPawn::ACharacterClassPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// 캡슐
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CapsuleComp->SetCapsuleHalfHeight(90.f);
	CapsuleComp->SetCapsuleRadius(35.f);
	CapsuleComp->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
	RootComponent = CapsuleComp;

	// 화살표
	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	ArrowComp->SetupAttachment(CapsuleComp);

	// 메시
	SkeletonComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	SkeletonComp->SetupAttachment(CapsuleComp);

	// 스프링암
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(CapsuleComp);
	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->bUsePawnControlRotation = true;

	// 카메라
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

	// 이동 컴포넌트
	MovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	MovementComp->SetUpdatedComponent(RootComponent);

	MoveSpeed = 600.f;
	SprintSpeed = 1000.f;
	MovementComp->MaxSpeed = MoveSpeed;

	// 점프
	bIsJump = false;
	JumpVelocity = 600.f;

	// 중력
	VerticalVelocity = 0.f;
	Gravity = -980.f;
}

void ACharacterClassPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APawnCharacterPlayerController* PlayerController = Cast<APawnCharacterPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &ACharacterClassPawn::Move);

			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Triggered, this, &ACharacterClassPawn::StartJump);
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Completed, this, &ACharacterClassPawn::EndJump);
			}

			if (PlayerController->LookAction)
				EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &ACharacterClassPawn::Look);

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Triggered, this, &ACharacterClassPawn::StartSprint);
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Completed, this, &ACharacterClassPawn::EndSprint);
			}
		}
	}
}

void ACharacterClassPawn::Move(const FInputActionValue& Value)
{
	if (!Controller) return;

	const FVector2D MoveInput = Value.Get<FVector2D>();

	FRotator ControlRot = Controller->GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	const FVector Forward = FRotationMatrix(ControlRot).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(ControlRot).GetUnitAxis(EAxis::Y);

	FVector MoveDirection = Forward * MoveInput.X + Right * MoveInput.Y;

	if (!MoveDirection.IsNearlyZero())
	{
		// 이동
		AddMovementInput(MoveDirection.GetSafeNormal(), 1.0f);

		// 캐릭터 회전
		FRotator TargetRotation = MoveDirection.Rotation();
		FRotator CurrentRotation = GetActorRotation();
		TargetRotation.Pitch = 0.f;
		TargetRotation.Roll = 0.f;

		// 스무스하게 회전하려면 Lerp 사용 가능
		SetActorRotation(FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 10.f));
	}
}

void ACharacterClassPawn::StartJump(const FInputActionValue& Value)
{
	if (IsGrounded())
	{
		VerticalVelocity = JumpVelocity;
	}
}

void ACharacterClassPawn::EndJump(const FInputActionValue& Value)
{
	bIsJump = false;
}

void ACharacterClassPawn::Look(const FInputActionValue& Value)
{
	const FVector2D LookInput = Value.Get<FVector2D>();
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void ACharacterClassPawn::StartSprint(const FInputActionValue& Value)
{
	MovementComp->MaxSpeed = SprintSpeed;
}

void ACharacterClassPawn::EndSprint(const FInputActionValue& Value)
{
	MovementComp->MaxSpeed = MoveSpeed;
}

void ACharacterClassPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool bGrounded = IsGrounded();

	// 지면에 있으면 아래로 이동 금지
	if (bGrounded)
	{
		VerticalVelocity = FMath::Max(VerticalVelocity, 0.f); // 지면에서 떨어지는 속도 없앰

		// 위치가 지면 아래로 내려가는 것을 방지
		FVector ActorLocation = GetActorLocation();
		float CapsuleHalfHeight = CapsuleComp->GetScaledCapsuleHalfHeight();
		float GroundZ = ActorLocation.Z;

		// 라인 트레이스 끝점과 비교해서 약간 밑으로 내려가는 것을 막음
		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		FVector Start = ActorLocation;
		FVector End = Start - FVector(0.f, 0.f, CapsuleHalfHeight + 1.f);
		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
		{
			float DesiredZ = Hit.ImpactPoint.Z + CapsuleHalfHeight;
			if (ActorLocation.Z < DesiredZ)
			{
				SetActorLocation(FVector(ActorLocation.X, ActorLocation.Y, DesiredZ));
			}
		}
	}

	// 중력 적용
	VerticalVelocity += Gravity * DeltaTime;

	FVector MoveOffset = FVector(0.f, 0.f, VerticalVelocity * DeltaTime);
	FHitResult Hit;
	AddActorWorldOffset(MoveOffset, true, &Hit);

	if (Hit.IsValidBlockingHit() && VerticalVelocity < 0.f)
	{
		VerticalVelocity = 0.f;
	}
}

bool ACharacterClassPawn::IsGrounded() const
{
	if (!CapsuleComp) return false;

	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0.f, 0.f, CapsuleComp->GetScaledCapsuleHalfHeight() + 1.f);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	return GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);
}
