// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacter.h"

// Sets default values
AABCharacter::AABCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	// GetMesh() : 이미 Character에 포함된 Mesh에 접근
	// 메시 위치를 루트(캡슐) 기준으로 아래쪽으로 이동시켜 실제 캐릭터 형태 맞춤
	// Mesh는 기본적으로 CapsuleComponent 아래에 붙어 있으며, 기본 위치가 -88 정도로 내려가 있음. 그래서 Z축 위치 조정 필요
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("/Game/Book/Animations/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if (WARRIOR_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}

	SetControlMode(EControlMode::DIABLO);
}

// Called when the game starts or when spawned
void AABCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABCharacter::SetControlMode(EControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode)
	{
	case AABCharacter::EControlMode::GTA:
		SpringArm->TargetArmLength = 450.0f;
		// 카메라와 캐릭터 사이 거리 설정 (3인칭 거리)
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		// 스프링암 회전 초기화 (캐릭터 기준 정방향으로 리셋)
		SpringArm->bUsePawnControlRotation = true;
		// 컨트롤러 회전값(ControlRotation)을 따라 회전하게 함
		SpringArm->bInheritPitch = true;
		// 컨트롤러 Pitch(상하) 회전 따라감
		SpringArm->bInheritRoll = true;
		// 컨트롤러 Roll(기울기) 회전 따라감
		SpringArm->bInheritYaw = true;
		// 컨트롤러 Yaw(좌우) 회전 따라감
		SpringArm->bDoCollisionTest = true;
		// 벽 등 장애물에 카메라가 가려질 경우 카메라 위치 자동 조정
		bUseControllerRotationYaw = false;
		// 캐릭터는 컨트롤러 Yaw 회전을 따르지 않음
		// 즉, 카메라는 회전하지만 캐릭터 본체는 회전하지 않음
		GetCharacterMovement()->bOrientRotationToMovement = true;
		// 캐릭터가 이동 방향을 바라보도록 자동 회전하게 설정
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		// 회전 속도를 초당 Yaw 720도로 설정
		break;
	case AABCharacter::EControlMode::DIABLO:
		SpringArm->TargetArmLength = 800.0f;
		SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = true;
		break;
	default:
		break;
	}
}

// Called every frame
void AABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentControlMode)
	{
	case AABCharacter::EControlMode::DIABLO:
		if (DirectionToMove.SizeSquared() > 0.0f)
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
		}
		break;
	}
}

// Called to bind functionality to input
void AABCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// 호출 시점 : Pawn 또는 Character가 PlayerController에 의해 “Possess” 되었을 때 자동으로 호출
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABCharacter::UpDown);
	//UpDown이라는 입력 축 이름이 발생할 때마다 AABCharacter의 UpDown 함수를 호출해라
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AABCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AABCharacter::Turn);
}

void AABCharacter::UpDown(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
		// 카메라(또는 컨트롤러)가 바라보는 전방 방향(X축)으로 NewAxisValue만큼 캐릭터를 이동시켜라
		// AddMovementInput() : 현재 Pawn 또는 Character에 이동 요청을 보내는 함수
		// GetControlRotation() : PlayerController의 현재 회전값(시점 방향)을 가져옴
		// FRotationMatrix() : 회전값을 3D 회전 행렬로 변환
		// GetUnitAxis() : 행렬의 X축 방향 벡터(= 전방 방향)을 가져옴
		// NewAxisValue : 입력 장치(키보드, 패드 등)에서 전달된 값 (예: +1.0, -1.0 등)
		break;
	case EControlMode::DIABLO:
		DirectionToMove.X = NewAxisValue;
		break;
	}
}

void AABCharacter::LeftRight(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case AABCharacter::EControlMode::GTA:
		AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), NewAxisValue);
		break;
	case AABCharacter::EControlMode::DIABLO:
		DirectionToMove.Y = NewAxisValue;
		break;
	}
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void AABCharacter::LookUp(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case AABCharacter::EControlMode::GTA:
		AddControllerPitchInput(NewAxisValue);
		break;
	}
	// AddControllerPitchInput() : 마우스 상하 움직임에 따라 시점을 위아래로 회전시키는 함수
	// Pawn 자체는 회전시키지 않음. 단지 PlayerController의 ControlRotation.Pitch만 변경
	// 캐릭터 머리나 시점이 상하로 바뀌려면 SpringArm 또는 Camera가 이 회전을 따라야 함
	// SpringArm->bUsePawnControlRotation = true;
}

void AABCharacter::Turn(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case AABCharacter::EControlMode::GTA:
		AddControllerYawInput(NewAxisValue);
		break;
	}
	// AddControllerYawInput() : 이 함수는 마우스 좌우 이동이나 패드 스틱 입력에 따라 캐릭터 또는 카메라의 좌우 시점 이동을 제어
	// ControlRotation.Yaw 값 증가
	// 캐릭터가 bUseControllerRotationYaw = true이면 실제로 몸도 회전
}