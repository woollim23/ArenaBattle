// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerController.h"

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(InputMode);
	// 플레이어가 어디에 입력을 전달할지를 결정하는 함수
	// 주로 APlayerController에서 호출되어, 게임 입력과 UI 입력 간 전환을 설정
}

void AABPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning); // 컨트롤러의 컴포넌트 초기화 완료 후 호출됨
}

void AABPlayerController::OnPossess(APawn* aPawn)
{
	ABLOG_S(Warning); // 컨트롤러가 Pawn을 소유(Possess)할 때 호출됨
	Super::OnPossess(aPawn);
}

