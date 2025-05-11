// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameMode.h"
#include "ABPawn.h"
#include "ABPlayerController.h"

AABGameMode::AABGameMode()
{
	DefaultPawnClass = AABPawn::StaticClass();
	PlayerControllerClass = AABPlayerController::StaticClass();
}

void AABGameMode::PostLogin(APlayerController* NewPlayer)
{
	ABLOG(Warning, TEXT("PostLogin Begin")); // 로그인 시작
	Super::PostLogin(NewPlayer);
	ABLOG(Warning, TEXT("PostLogin End")); // 로그인 끝
}
