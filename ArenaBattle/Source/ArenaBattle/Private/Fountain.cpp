// Fill out your copyright notice in the Description page of Project Settings.


#include "Fountain.h"

// Sets default values
AFountain::AFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 생성, 해쉬값으로 구별
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WATER"));
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT"));
	Splash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SPLASH"));

	RootComponent = Body; // 루트 컴포넌트를 Body로 지정
	Water->SetupAttachment(Body); // 그외 컴포넌트는 루트컴포넌트에 붙였음
	Light->SetupAttachment(Body);
	Splash->SetupAttachment(Body);

	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 135.0f)); // 루트로 부터 상대적 위치 설정, 위치 기본값이 됨
	Light->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f));
	Splash->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BODY(TEXT("/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Ruins/StaticMesh/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01"));
	// ConstructorHelpers::FObjectFinder<UStaticMesh>:언리얼에서 에셋을 C++ 생성자에서 로드할 때 사용하는 도우미 클래스
	// SM_BODY: FObjectFinder 인스턴스의 변수 이름
	// 언리얼 프로젝트 시작 시(특히 생성자에서) 정적 메시 에셋을 메모리에 로드하기 위해 사용
	// 반드시 생성자 내에서만 사용해야 합니다 (런타임에서는 사용 불가)
	if (SM_BODY.Succeeded()) // 성공적으로 에셋 로드 하면
	{
		Body->SetStaticMesh(SM_BODY.Object); // 분수대 바디에 해당 오브젝트를 기본 템플릿으로 설정함
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

