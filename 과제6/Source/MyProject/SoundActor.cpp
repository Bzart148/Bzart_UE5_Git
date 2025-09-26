#include "SoundActor.h"
#include "Sound/SoundCue.h"//소리 재생시

ASoundActor::ASoundActor()
{
	PrimaryActorTick.bCanEverTick = false;
	//씬 루트컴포넌트 생성과 루트 설정
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	//오디오 컴포넌트 생성과 씬루트에 어태치
	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<USoundBase>AudioAsset(TEXT("/Script/Engine.SoundWave'/Game/Sound/BadBoy.BadBoy'"));
	if (AudioAsset.Succeeded())
	{
		AudioComp->SetSound(AudioAsset.Object);
	}
}

void ASoundActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASoundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

