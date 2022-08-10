// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonCharacter.h"

#include "Camera/CameraComponent.h"

#include "Components/InputComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"

AThirdPersonCharacter::AThirdPersonCharacter()
{
 	
	// only let the camera rotate
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	//camera boom, pulls to character when there is a collision
	m_pCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	m_pCameraBoom->SetupAttachment(RootComponent);
	m_pCameraBoom->bUsePawnControlRotation = true; // rotate arm based on controller

	//camera
	m_pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_pCamera->SetupAttachment(m_pCameraBoom, USpringArmComponent::SocketName);//attach camera to the end of the boom
	m_pCamera->bUsePawnControlRotation = false; // rotate with boom
}

// Called when the game starts or when spawned
void AThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	m_pCameraBoom->TargetArmLength = m_BoomLength;

	m_pCameraBoom->AddLocalTransform(FTransform(FVector(0,0, m_BoomHeight)));

	//rotate camera boom to given start angle
	AddControllerPitchInput(m_StartPitch);
}

// Called every frame
void AThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersonCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdPersonCharacter::MoveLeftRight);

	//Mouse turn/rotate bindings
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//Controller turn/rotate
	PlayerInputComponent->BindAxis("TurnRate", this, &AThirdPersonCharacter::TurningUsingControllerAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AThirdPersonCharacter::LookUpUsingControllerAtRate);

}

void AThirdPersonCharacter::MoveForwardBackward(float value)
{
	if (Controller && value != 0.0f)
	{
		// find out which way is forward
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void AThirdPersonCharacter::MoveLeftRight(float value)
{
	if (Controller && value != 0.0f)
	{
		// find out which way is right
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, value);
	}
}

void AThirdPersonCharacter::TurningUsingControllerAtRate(float rate)
{
	AddControllerYawInput(rate * m_BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersonCharacter::LookUpUsingControllerAtRate(float rate)
{
	AddControllerPitchInput(rate * m_BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

