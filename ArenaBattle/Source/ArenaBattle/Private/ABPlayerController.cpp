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
	ABLOG_S(Warning); // ��Ʈ�ѷ� ���� �Ϸ�
}

void AABPlayerController::OnPossess(APawn* aPawn)
{
	ABLOG_S(Warning); // ���� ��Ʈ�ѷ� ���� ����
	Super::OnPossess(aPawn);
}

