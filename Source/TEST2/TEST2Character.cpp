// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TEST2Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "message/game.pb.h"
#include "WinTcp/ClientSocket.h"
#include "WinTcp/Account.h"

using namespace WinTcp;
using namespace message;

//////////////////////////////////////////////////////////////////////////
// ATEST2Character

ATEST2Character::ATEST2Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	m_fMoveTick = 0;
	m_Xval = 0;
	m_Yval = 0;
	m_bMove = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATEST2Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATEST2Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATEST2Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATEST2Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATEST2Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATEST2Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATEST2Character::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATEST2Character::OnResetVR);
}


void ATEST2Character::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATEST2Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ATEST2Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ATEST2Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATEST2Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATEST2Character::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
		m_Xval = Value;
		m_bMove = true;
	}
}

void ATEST2Character::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
		m_Yval = Value;
		m_bMove = true;
	}
}

// Called every frame
void ATEST2Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_bMove) {
		const FRotator Rotation = Controller->GetControlRotation();
		float xval = FMath::Acos(m_Xval), yval = FMath::Asin(m_Yval);
		float yaw = 0;
		if (m_Xval != 0 && m_Yval != 0) {
			yaw = (FMath::Acos(m_Xval)+ FMath::Asin(m_Yval)) /2;
		}else if (m_Xval != 0) {
			yaw = FMath::Acos(m_Xval);
		}else {
			yaw = FMath::Asin(m_Yval);
		}
		MovePacket(GetActorLocation(), yaw + FMath::DegreesToRadians(Rotation.Yaw), 100);
		m_bMove = false;
		m_Xval = 0;
		m_Yval = 0;
	}
}

void ATEST2Character::MovePacket(FVector location, float yaw, float duration){
    if(GetWorld()->TimeSince(m_fMoveTick) < 0.1){
        return;
	}   
    m_fMoveTick = GetWorld()->GetTimeSeconds();
	auto packet = new C_W_Move();
	auto packetHead = packet->mutable_packethead();
	Packet::BuildPacketHead(packetHead, Id);
	auto move = packet->mutable_move();
	move->set_mode(0);
	auto normal = move->mutable_normal();
	auto pos = normal->mutable_pos();
	pos->set_x(-location.X);
	pos->set_y(-location.Y);
	pos->set_z(location.Z);
	normal->set_yaw(yaw + PI);
	normal->set_duration(duration);
	ClientSocket::Instance()->Send(packet);
}
