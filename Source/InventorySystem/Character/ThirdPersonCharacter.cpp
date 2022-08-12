// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonCharacter.h"
#include "TPCController.h"

#include "Camera/CameraComponent.h"

#include "Components/InputComponent.h"

#include "../Components/InventoryComponent.h"

#include "../HUD/Inventory.h"
#include "../HUD/InteractionText.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"

#include "../Interfaces/Interactable.h"
#include "../Interfaces/ShowText.h"

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

	//Inventory Component
	m_pInventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	m_pInventoryComponent->SetCapacity(20);

	m_Health = 100;

	m_LineTraceLength = 200;
}

// Called when the game starts or when spawned
void AThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	m_pCameraBoom->TargetArmLength = m_BoomLength;

	m_pCameraBoom->AddLocalTransform(FTransform(FVector(0,0, m_BoomHeight)));

	//rotate camera boom to given start angle
	AddControllerPitchInput(m_StartPitch);

	m_pController = Cast<ATPCController>(Controller);
}

// Called every frame
void AThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector start = GetMesh()->GetComponentLocation();
	const FVector end = start + GetActorForwardVector() * m_LineTraceLength;

	if (AActor* hitActor = SingleLineTrace(start, end).GetActor())
	{
		if (IShowText* showTextInterface = Cast<IShowText>(hitActor))
		{
			m_pController->GetInteractionTextWidget()->SetText(showTextInterface->GetText());
		}
	}

	else
	{
		m_pController->GetInteractionTextWidget()->SetText("");
	}
}

// Called to bind functionality to input
void AThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("OpenCloseInventory", EInputEvent::IE_Pressed, this, &AThirdPersonCharacter::OpenCloseInventory);

	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &AThirdPersonCharacter::Interact);

	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersonCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdPersonCharacter::MoveLeftRight);

	//Mouse turn/rotate bindings
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//Controller turn/rotate
	PlayerInputComponent->BindAxis("TurnRate", this, &AThirdPersonCharacter::TurningUsingControllerAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AThirdPersonCharacter::LookUpUsingControllerAtRate);

}

float AThirdPersonCharacter::GetHealth() const
{
	return m_Health;
}

void AThirdPersonCharacter::AddHealth(float health)
{
	m_Health += health;
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("%f"), m_Health));
}

bool AThirdPersonCharacter::AddItemToInventory(UInventoryItem* item, int amount)
{
	if (item && amount > 0)
	{
		return m_pInventoryComponent->AddItem(item, amount);
	}

	return false;
}

void AThirdPersonCharacter::SetInventory(UInventory* inventory)
{
	m_pInventory = inventory;
	m_pInventory->SetInventoryComp(m_pInventoryComponent);
	m_pInventory->SetVisibility(ESlateVisibility::Hidden);
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

void AThirdPersonCharacter::OpenCloseInventory()
{
	if (m_pInventory)
	{
		if (m_pInventory->GetVisibility() == ESlateVisibility::Visible)
		{
			m_pInventory->SetVisibility(ESlateVisibility::Hidden);
			m_pController->SetInputMode(FInputModeGameOnly());
			m_pController->bShowMouseCursor = false;
		}

		else
		{
			m_pInventory->SetVisibility(ESlateVisibility::Visible);
			m_pInventory->UpdateInventory();
			m_pController->bShowMouseCursor = true;
			m_pController->SetInputMode(FInputModeGameAndUI());
			
		}
	}
}

void AThirdPersonCharacter::Interact()
{
	const FVector start = GetMesh()->GetComponentLocation();
	const FVector end = start + GetActorForwardVector() * m_LineTraceLength;

	if (AActor* hitActor = SingleLineTrace(start, end).GetActor())
	{
		if (IInteractable* interactableInterface = Cast<IInteractable>(hitActor))
		{
			interactableInterface->Interact(this);
		}
	}
}

FHitResult AThirdPersonCharacter::SingleLineTrace(const FVector& startLocation, const FVector& endLocation)
{
	FHitResult hitResult;

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_WorldStatic, params);

	return hitResult;
}

