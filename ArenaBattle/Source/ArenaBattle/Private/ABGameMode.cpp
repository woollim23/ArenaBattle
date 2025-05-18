// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameMode.h"
#include "ABCharacter.h"
#include "ABPlayerController.h"

AABGameMode::AABGameMode()
{
	DefaultPawnClass = AABCharacter::StaticClass();
	PlayerControllerClass = AABPlayerController::StaticClass();
}

void AABGameMode::PostLogin(APlayerController* NewPlayer)
{
	ABLOG(Warning, TEXT("PostLogin Begin")); 
	// 새 플레이어가 게임에 접속했을 때 호출됨
	Super::PostLogin(NewPlayer);
	ABLOG(Warning, TEXT("PostLogin End"));
	// PostLogin 처리 완료
	// 멀티플레이 게임에서 플레이어 초기화나 인사 메시지 전송, 팀 배정 등을 수행하기 좋은 위치
}
