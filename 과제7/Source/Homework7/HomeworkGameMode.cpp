#include "HomeworkGameMode.h"
#include "CharacterClassPawn.h"//캐릭터 헤더
#include "PawnCharacterPlayerController.h"//플레이어 컨트롤러 클래스를 사용

//엔진이 캐릭터클래스 정보를 런타임 참조 제공 정적 함수
AHomeworkGameMode::AHomeworkGameMode()
{	
	DefaultPawnClass = ACharacterClassPawn::StaticClass();
	PlayerControllerClass = ACharacterClassPawn::StaticClass();
}

