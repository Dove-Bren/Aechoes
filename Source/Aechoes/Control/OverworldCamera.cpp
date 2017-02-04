// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Aechoes.h"
#include "OverworldCamera.h"

//////////////////////////////////////////////////////////////////////////
// AOverworldCamera

AOverworldCamera::AOverworldCamera()
{

	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	PanSpeed = 5.0f;
	ZoomSpeed = 10.0f;

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraArm->SetupAttachment(RootComponent);
    CameraArm->TargetArmLength = 1.0f; // The camera follows at this distance behind the character	
    CameraArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-90.0f, 0.0f, 0.0f));
    CameraArm->bUsePawnControlRotation = false; // Rotate the arm based on the controller
    

                                               // Create a follow camera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

    AutoPossessPlayer = EAutoReceiveInput::Player0;

    //Setup controller
    CameraController = CreateDefaultSubobject<UOverworldCameraController>(TEXT("MovementController"));
    CameraController->UpdatedComponent = RootComponent;
}

AOverworldCamera::~AOverworldCamera()
{
//    delete this->Camera;
//    delete this->CameraArm;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AOverworldCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	//InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//InputComponent->BindAxis("MoveForward", this, &AAechoesCharacter::MoveForward);
	//InputComponent->BindAxis("MoveRight", this, &AAechoesCharacter::MoveRight);

	//// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	//// "turn" handles devices that provide an absolute delta, such as a mouse.
	//// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	//InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//InputComponent->BindAxis("TurnRate", this, &AAechoesCharacter::TurnAtRate);
	//InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	//InputComponent->BindAxis("LookUpRate", this, &AAechoesCharacter::LookUpAtRate);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &AOverworldCamera::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AOverworldCamera::TouchStopped);

	//MoveUp, MoveRight, *Rate
	//Also SelectClick, ActionClick
	//InputComponent->BindAction("MoveUp", IE_Pressed, this, &AOverworldCamera::MoveUp);
	//InputComponent->BindAction("MoveRight", IE_Pressed, this, &AOverworldCamera::MoveRight);

	InputComponent->BindAxis("MoveUpRate", this, &AOverworldCamera::MoveUpRate);
	InputComponent->BindAxis("MoveRightRate", this, &AOverworldCamera::MoveRightRate);
	InputComponent->BindAxis("MoveUp", this, &AOverworldCamera::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &AOverworldCamera::MoveRight);
	
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AOverworldCamera::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AOverworldCamera::ZoomOut);
}

UPawnMovementComponent * AOverworldCamera::GetMovementComponent() const
{
    return CameraController;
}

AActor * AOverworldCamera::getFocus()
{
    return this->focus;
}


void AOverworldCamera::MoveRightRate(float Rate)
{
	MoveRight(Rate);
}

void AOverworldCamera::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		//Jump();
	}
}

void AOverworldCamera::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		//StopJumping();
	}
}

void AOverworldCamera::OnSelectClick(FVector location)
{
}

void AOverworldCamera::OnActionClick(FVector location)
{
}

//void AOverworldCamera::TurnAtRate(float Rate)
//{
//	// calculate delta for this frame from the rate information
//	//AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
//}

//void AOverworldCamera::LookUpAtRate(float Rate)
//{
//	// calculate delta for this frame from the rate information
//	//AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
//}
//
//void AOverworldCamera::MoveForward(float Value)
//{
//	if ((Controller != NULL) && (Value != 0.0f))
//	{
//		// find out which way is forward
//		const FRotator Rotation = Controller->GetControlRotation();
//		const FRotator YawRotation(0, Rotation.Yaw, 0);
//
//		// get forward vector
//		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
//		AddMovementInput(Direction, Value);
//	}
//}

void AOverworldCamera::MoveUp(float Rate)
{

	if (Rate == 0.0f)
		return;
	
	//const FVector dir = FVector(1.0f, 0.0f, 0.0f);
	//AddMovementInput(dir, 1.0f);
	this->CameraController->AddInputVector(FVector(Rate * PanSpeed, 0.0f, 0.0f));
	

}

void AOverworldCamera::MoveRight(float Rate)
{
	
	//// find out which way is right
	//const FRotator Rotation = Controller->GetControlRotation();
	//const FRotator YawRotation(0, Rotation.Yaw, 0);
	//
	//// get right vector 
	//const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//// add movement in that direction
	////AddMovementInput(Direction, 1.0f);
	if (Rate == 0.0f)
		return;

	CameraController->AddInputVector(FVector(0.0f, Rate * PanSpeed, 0.0f), false);
	
}

void AOverworldCamera::MoveUpRate(float Rate)
{
	if (Rate != 0.0f) {
		MoveUp(Rate);
	}
}

void AOverworldCamera::ZoomIn()
{
	CameraController->AddInputVector(FVector(0.0f, 0.0f, -ZoomSpeed));
}

void AOverworldCamera::ZoomOut()
{
	CameraController->AddInputVector(FVector(0.0f, 0.0f, ZoomSpeed));
}

UCameraComponent *AOverworldCamera::getCamera()
{
    return this->Camera;
}

void AOverworldCamera::SetFocus(AActor *in)
{
	this->focus = in;
	if (this->focus != nullptr) {
		const FVector vec = focus->GetActorLocation();
		this->SetActorLocation(FVector(vec.X, vec.Y, vec.Z + 100.0f));
	}

}
