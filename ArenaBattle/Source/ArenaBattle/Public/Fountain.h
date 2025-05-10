// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Fountain.generated.h"

UCLASS()
class ARENABATTLE_API AFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere) // 디테일에서 객체를 볼 수 있게 함. 객체의 속성 편집가능. 단, 타 객체로 변경 불가능(데이터 변경 불가)
	UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Water;

	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* Light;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* Splash;

	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* Movement;

	UPROPERTY(EditAnywhere, Category = "ID") // 데이터도 변경 가능
	int32 ID; // UPROPERTY 매크로 사용시 기본값 0

private:
	UPROPERTY(EditAnywhere, Category=Stat, Meta = (AllowPrivateAccess = true))
	float RotateSpeed;
};
