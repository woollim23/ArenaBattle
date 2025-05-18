// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerController.h"

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(InputMode);
	// �÷��̾ ��� �Է��� ���������� �����ϴ� �Լ�
	// �ַ� APlayerController���� ȣ��Ǿ�, ���� �Է°� UI �Է� �� ��ȯ�� ����
}

void AABPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning); // ��Ʈ�ѷ��� ������Ʈ �ʱ�ȭ �Ϸ� �� ȣ���
}

void AABPlayerController::OnPossess(APawn* aPawn)
{
	ABLOG_S(Warning); // ��Ʈ�ѷ��� Pawn�� ����(Possess)�� �� ȣ���
	Super::OnPossess(aPawn);
}

