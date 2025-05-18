// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/PlayerController.h"
#include "ABPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API AABPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

	FInputModeGameOnly InputMode;
	// �𸮾� ����(UE)���� �Է� ���(Input Mode)�� ������ �� ����ϴ� ����ü
	// �ַ� �÷��̾ UI�� �ƴ� ���� ���忡�� �Է��� �������� �����ϰ� ���� �� ���
	// �����ڰ� �ִ� ����ü, �ʱ�ȭ ���ص� ����
};
