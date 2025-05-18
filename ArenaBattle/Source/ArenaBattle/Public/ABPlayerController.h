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
	// 언리얼 엔진(UE)에서 입력 모드(Input Mode)를 설정할 때 사용하는 구조체
	// 주로 플레이어가 UI가 아닌 게임 월드에만 입력을 보내도록 제한하고 싶을 때 사용
	// 생성자가 있는 구조체, 초기화 안해도 안전
};
