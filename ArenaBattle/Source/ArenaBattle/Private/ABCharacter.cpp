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
	// GetMesh() : �̹� Character�� ���Ե� Mesh�� ����
	// �޽� ��ġ�� ��Ʈ(ĸ��) �������� �Ʒ������� �̵����� ���� ĳ���� ���� ����
	// Mesh�� �⺻������ CapsuleComponent �Ʒ��� �پ� ������, �⺻ ��ġ�� -88 ������ ������ ����. �׷��� Z�� ��ġ ���� �ʿ�
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

	//SpringArm->bUsePawnControlRotation = true;
	//Camera->bUsePawnControlRotation = false; // SpringArm�� ȸ�� ó����
	//bUseControllerRotationPitch = false;
	//bUseControllerRotationYaw = true;
	//bUseControllerRotationRoll = false;

}

// Called when the game starts or when spawned
void AABCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AABCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// ȣ�� ���� : Pawn �Ǵ� Character�� PlayerController�� ���� ��Possess�� �Ǿ��� �� �ڵ����� ȣ��
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABCharacter::UpDown);
	//UpDown�̶�� �Է� �� �̸��� �߻��� ������ AABCharacter�� UpDown �Լ��� ȣ���ض�
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AABCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AABCharacter::Turn);
}

void AABCharacter::UpDown(float NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
	// AddMovementInput() : ���� Pawn �Ǵ� Character�� �̵� ��û�� ������ �Լ�
	// GetActorForwardVector() : �� ����(ĳ����)�� ���� �ٶ󺸴� ������ ���� (Z�� ����)
	// NewAxisValue : �Է� ��ġ(Ű����, �е� ��)���� ���޵� �� (��: +1.0, -1.0 ��)
}

void AABCharacter::LeftRight(float NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}

void AABCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
	// AddControllerPitchInput() : ���콺 ���� �����ӿ� ���� ������ ���Ʒ��� ȸ����Ű�� �Լ�
	// Pawn ��ü�� ȸ����Ű�� ����. ���� PlayerController�� ControlRotation.Pitch�� ����
	// ĳ���� �Ӹ��� ������ ���Ϸ� �ٲ���� SpringArm �Ǵ� Camera�� �� ȸ���� ����� ��
	// SpringArm->bUsePawnControlRotation = true;
}

void AABCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
	// AddControllerYawInput() : �� �Լ��� ���콺 �¿� �̵��̳� �е� ��ƽ �Է¿� ���� ĳ���� �Ǵ� ī�޶��� �¿� ���� �̵��� ����
	// ControlRotation.Yaw �� ����
	// ĳ���Ͱ� bUseControllerRotationYaw = true�̸� ������ ���� ȸ��
}