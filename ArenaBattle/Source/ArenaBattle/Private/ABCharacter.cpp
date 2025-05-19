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

	SetControlMode(0);
}

// Called when the game starts or when spawned
void AABCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABCharacter::SetControlMode(int32 ControlMode)
{
	if (ControlMode == 0) // ControlMode�� 0�� ��� ���� ���� (GTA ���)
	{
		SpringArm->TargetArmLength = 450.0f;
		// ī�޶�� ĳ���� ���� �Ÿ� ���� (3��Ī �Ÿ�)
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		// �������� ȸ�� �ʱ�ȭ (ĳ���� ���� ���������� ����)
		SpringArm->bUsePawnControlRotation = true;
		// ��Ʈ�ѷ� ȸ����(ControlRotation)�� ���� ȸ���ϰ� ��
		SpringArm->bInheritPitch = true;
		// ��Ʈ�ѷ� Pitch(����) ȸ�� ����
		SpringArm->bInheritRoll = true;
		// ��Ʈ�ѷ� Roll(����) ȸ�� ����
		SpringArm->bInheritYaw = true;
		// ��Ʈ�ѷ� Yaw(�¿�) ȸ�� ����
		SpringArm->bDoCollisionTest = true;
		// �� �� ��ֹ��� ī�޶� ������ ��� ī�޶� ��ġ �ڵ� ����
		bUseControllerRotationYaw = false;
		// ĳ���ʹ� ��Ʈ�ѷ� Yaw ȸ���� ������ ����
		// ��, ī�޶�� ȸ�������� ĳ���� ��ü�� ȸ������ ����
		GetCharacterMovement()->bOrientRotationToMovement = true;
		// ĳ���Ͱ� �̵� ������ �ٶ󺸵��� �ڵ� ȸ���ϰ� ����
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		// ȸ�� �ӵ��� �ʴ� Yaw 720���� ����
	}
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
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
	// ī�޶�(�Ǵ� ��Ʈ�ѷ�)�� �ٶ󺸴� ���� ����(X��)���� NewAxisValue��ŭ ĳ���͸� �̵����Ѷ�
	// AddMovementInput() : ���� Pawn �Ǵ� Character�� �̵� ��û�� ������ �Լ�
	// GetControlRotation() : PlayerController�� ���� ȸ����(���� ����)�� ������
	// FRotationMatrix() : ȸ������ 3D ȸ�� ��ķ� ��ȯ
	// GetUnitAxis() : ����� X�� ���� ����(= ���� ����)�� ������
	// NewAxisValue : �Է� ��ġ(Ű����, �е� ��)���� ���޵� �� (��: +1.0, -1.0 ��)

	// GetActorForwardVector() : �� ����(ĳ����)�� ���� �ٶ󺸴� ������ ���� (Z�� ����)
}

void AABCharacter::LeftRight(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
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