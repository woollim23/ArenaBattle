// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerController.h"

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();


	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

void AABPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning); // 컨트롤러 생성 완료
}

void AABPlayerController::OnPossess(APawn* aPawn)
{
	ABLOG_S(Warning); // 폰에 컨트롤러 빙의 시작
	Super::OnPossess(aPawn);
}

