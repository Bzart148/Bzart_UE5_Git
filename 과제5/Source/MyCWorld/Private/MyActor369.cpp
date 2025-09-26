// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor369.h"

// Sets default values
AMyActor369::AMyActor369()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor369::BeginPlay()
{
	Super::BeginPlay();

	int Start = 1;
	int End = 30;
	for (int i = Start; i <= End; ++i)	//1부터 30반복
	{
		FString Number = FString::FromInt(i);	// 정수 int타입 변수 i를 Nuber라는 이름의 변수에 저장
		bool bIsClap = false;		//"짝"을 출력할지 여부

		for (TCHAR Char : Number)	//TCHAR를 사용해 플랫폼 독자적 문자 처리
		{
			if (Char == '3' || Char == '6' || Char == '9')	//3 6 9 인지 확인
			{
				bIsClap = true;	//"짝" 을 출력
				break;	//하나라도 3 6 9 발견되면 검사 종료
			}
		}
		if (bIsClap)
		{
			UE_LOG(LogTemp, Warning, TEXT("clap"));	//"짝" 3 6 9 중 하나가 포함된 경우
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%d"), i);	//3 6 9가 없는 경우 숫자로 출력
		}
	}
}

// Called every frame
void AMyActor369::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

