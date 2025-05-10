// Fill out your copyright notice in the Description page of Project Settings.


#include "Fountain.h"

// Sets default values
AFountain::AFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������Ʈ ����, �ؽ������� ����
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WATER"));
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT"));
	Splash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SPLASH"));

	RootComponent = Body; // ��Ʈ ������Ʈ�� Body�� ����
	Water->SetupAttachment(Body); // �׿� ������Ʈ�� ��Ʈ������Ʈ�� �ٿ���
	Light->SetupAttachment(Body);
	Splash->SetupAttachment(Body);

	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 135.0f)); // ��Ʈ�� ���� ����� ��ġ ����, ��ġ �⺻���� ��
	Light->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f));
	Splash->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BODY(TEXT("/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Ruins/StaticMesh/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01"));
	// ConstructorHelpers::FObjectFinder<UStaticMesh>:�𸮾󿡼� ������ C++ �����ڿ��� �ε��� �� ����ϴ� ����� Ŭ����
	// SM_BODY: FObjectFinder �ν��Ͻ��� ���� �̸�
	// �𸮾� ������Ʈ ���� ��(Ư�� �����ڿ���) ���� �޽� ������ �޸𸮿� �ε��ϱ� ���� ���
	// �ݵ�� ������ �������� ����ؾ� �մϴ� (��Ÿ�ӿ����� ��� �Ұ�)
	if (SM_BODY.Succeeded()) // ���������� ���� �ε� �ϸ�
	{
		Body->SetStaticMesh(SM_BODY.Object); // �м��� �ٵ� �ش� ������Ʈ�� �⺻ ���ø����� ������
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_WATER(TEXT("/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Ruins/StaticMesh/SM_Plains_Castle_Fountain_02.SM_Plains_Castle_Fountain_02"));
	if (SM_WATER.Succeeded())
	{
		Water->SetStaticMesh(SM_WATER.Object);
	}


	static ConstructorHelpers::FObjectFinder <UParticleSystem> PS_SPLASH(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Ambient/Water/P_Water_Fountain_Splash_Base_01.P_Water_Fountain_Splash_Base_01"));
	if (PS_SPLASH.Succeeded())
	{
		Splash->SetTemplate(PS_SPLASH.Object);
	}

}

// Called when the game starts or when spawned
void AFountain::BeginPlay()
{
	Super::BeginPlay();
	
	ABLOG_S(Warning);
	ABLOG(Warning, TEXT("Actor Name : %s, ID : %d, Location X : %.3f"), *GetName(), ID, GetActorLocation().X);
}

// Called every frame
void AFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

