#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"//오디오 사용시
#include "SoundActor.generated.h"

UCLASS()
class MYPROJECT_API ASoundActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASoundActor();//생성자

protected:
	//루트 포인터
	USceneComponent* SceneRoot;
	//오디오 포인터
	UAudioComponent* AudioComp;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Matelial")
	//UStaticMeshComponent* StaticMeshComp;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
