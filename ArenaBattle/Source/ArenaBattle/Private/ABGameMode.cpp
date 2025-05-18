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
	// �� �÷��̾ ���ӿ� �������� �� ȣ���
	Super::PostLogin(NewPlayer);
	ABLOG(Warning, TEXT("PostLogin End"));
	// PostLogin ó�� �Ϸ�
	// ��Ƽ�÷��� ���ӿ��� �÷��̾� �ʱ�ȭ�� �λ� �޽��� ����, �� ���� ���� �����ϱ� ���� ��ġ
}
