// Fill out your copyright notice in the Description page of Project Settings.


#include "G01Character.h"
#include "Components/CapsuleComponent.h"
#include "G01CharacterMovementComponent.h"
#include "G01PawnExtensionComponent.h"
#include "Camera/G01CameraComponent.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(G01Character)

static FName NAME_LyraCharacterCollisionProfile_Capsule(TEXT("PawnCapsule"));
static FName NAME_LyraCharacterCollisionProfile_Mesh(TEXT("PawnMesh"));

AG01Character::AG01Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UG01CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Avoid ticking characters if possible.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SetNetCullDistanceSquared(900000000.0f);

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->InitCapsuleSize(40.0f, 90.0f);
	CapsuleComp->SetCollisionProfileName(NAME_LyraCharacterCollisionProfile_Capsule);

	USkeletalMeshComponent* MeshComp = GetMesh();
	check(MeshComp);
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));  // Rotate mesh to be X forward since it is exported as Y forward.
	MeshComp->SetCollisionProfileName(NAME_LyraCharacterCollisionProfile_Mesh);

	UG01CharacterMovementComponent* MoveComp = CastChecked<UG01CharacterMovementComponent>(GetCharacterMovement());
	MoveComp->GravityScale = 1.0f;
	MoveComp->MaxAcceleration = 2400.0f;
	MoveComp->BrakingFrictionFactor = 1.0f;
	MoveComp->BrakingFriction = 6.0f;
	MoveComp->GroundFriction = 8.0f;
	MoveComp->BrakingDecelerationWalking = 1400.0f;
	MoveComp->bUseControllerDesiredRotation = false;
	MoveComp->bOrientRotationToMovement = false;
	MoveComp->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	MoveComp->bAllowPhysicsRotationDuringAnimRootMotion = false;
	MoveComp->GetNavAgentPropertiesRef().bCanCrouch = true;
	MoveComp->bCanWalkOffLedgesWhenCrouching = true;
	MoveComp->SetCrouchedHalfHeight(65.0f);

	PawnExtComponent = CreateDefaultSubobject<UG01PawnExtensionComponent>(TEXT("PawnExtensionComponent"));
	//PawnExtComponent->OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnAbilitySystemInitialized));
	//PawnExtComponent->OnAbilitySystemUninitialized_Register(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnAbilitySystemUninitialized));

	/*HealthComponent = CreateDefaultSubobject<ULyraHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDeathStarted.AddDynamic(this, &ThisClass::OnDeathStarted);
	HealthComponent->OnDeathFinished.AddDynamic(this, &ThisClass::OnDeathFinished);*/

	CameraComponent = CreateDefaultSubobject<UG01CameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetRelativeLocation(FVector(-300.0f, 0.0f, 75.0f));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	BaseEyeHeight = 80.0f;
	CrouchedEyeHeight = 50.0f;
}

// Called when the game starts or when spawned
void AG01Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AG01Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AG01Character::ToggleCrouch()
{
	const UG01CharacterMovementComponent* LyraMoveComp = CastChecked<UG01CharacterMovementComponent>(GetCharacterMovement());

	if (IsCrouched() || LyraMoveComp->bWantsToCrouch)
	{
		UnCrouch();
	}
	else if (LyraMoveComp->IsMovingOnGround())
	{
		Crouch();
	}
}

void AG01Character::OnRep_Controller()
{
	Super::OnRep_Controller();

	PawnExtComponent->HandleControllerChanged();
}

void AG01Character::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	PawnExtComponent->HandlePlayerStateReplicated();
}

// Called to bind functionality to input
void AG01Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PawnExtComponent->SetupPlayerInputComponent();
}

