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
	for (int i = Start; i <= End; ++i)	//1���� 30�ݺ�
	{
		FString Number = FString::FromInt(i);	// ���� intŸ�� ���� i�� Nuber��� �̸��� ������ ����
		bool bIsClap = false;		//"¦"�� ������� ����

		for (TCHAR Char : Number)	//TCHAR�� ����� �÷��� ������ ���� ó��
		{
			if (Char == '3' || Char == '6' || Char == '9')	//3 6 9 ���� Ȯ��
			{
				bIsClap = true;	//"¦" �� ���
				break;	//�ϳ��� 3 6 9 �߰ߵǸ� �˻� ����
			}
		}
		if (bIsClap)
		{
			UE_LOG(LogTemp, Warning, TEXT("clap"));	//"¦" 3 6 9 �� �ϳ��� ���Ե� ���
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%d"), i);	//3 6 9�� ���� ��� ���ڷ� ���
		}
	}
}

// Called every frame
void AMyActor369::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

