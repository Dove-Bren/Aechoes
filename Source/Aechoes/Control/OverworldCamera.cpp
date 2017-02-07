// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Aechoes.h"
#include "OverworldCamera.h"

//////////////////////////////////////////////////////////////////////////
// AOverworldCamera

AOverworldCamera::AOverworldCamera()
{

	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	PanSpeed = 500.0f;
	ZoomSpeed = 2000.0f;

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
    CameraController = CreateDefaultSubobject<UOCameraMovement>(TEXT("MovementController"));
    CameraController->UpdatedComponent = RootComponent;
}

AOverworldCamera::~AOverworldCamera()
{
//    delete this->Camera;
//    delete this->CameraArm;
}

//////////////////////////////////////////////////////////////////////////
// Input

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

void AOverworldCamera::MoveUp(float Rate)
{

	if (Rate == 0.0f)
		return;
	
	//const FVector dir = FVector(1.0f, 0.0f, 0.0f);
	//AddMovementInput(dir, 1.0f);
	float speed = Rate * PanSpeed;

	//scale up speed if focus target far away
	if (this->focus != nullptr) {
		float diff = FMath::Abs((this->GetActorLocation() - focus->GetActorLocation()).Z);
		speed *= 1 + (diff / 1000.0f);
	}

	this->CameraController->AddInputVector(FVector(speed, 0.0f, 0.0f));
	

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

	float speed = Rate * PanSpeed;
	if (this->focus != nullptr) {
		float diff = FMath::Abs((this->GetActorLocation() - focus->GetActorLocation()).Z);
		speed *= 1 + (diff / 1000.0f);
	}

	CameraController->AddInputVector(FVector(0.0f, speed, 0.0f), false);
	
}

void AOverworldCamera::MoveUpRate(float Rate)
{
	if (Rate != 0.0f) {
		MoveUp(Rate);
	}
}

void AOverworldCamera::ZoomIn()
{
	float speed = ZoomSpeed;
	if (this->focus != nullptr) {
		float diff = FMath::Abs((this->GetActorLocation() - focus->GetActorLocation()).Z);
		speed *= 1 + (diff / 2000.0f);
	}

	CameraController->AddInputVector(FVector(0.0f, 0.0f, -speed));
}

void AOverworldCamera::ZoomOut()
{
	CameraController->AddInputVector(FVector(0.0f, 0.0f, ZoomSpeed));
}

UCameraComponent *AOverworldCamera::getCamera()
{
    return this->Camera;
}

UOCameraMovement *AOverworldCamera::getCameraController()
{
	return this->CameraController;
}

void AOverworldCamera::SetFocus(AActor *in)
{
	this->focus = in;
	CameraController->setFocus(focus);

	if (this->focus != nullptr) {
		const FVector vec = focus->GetActorLocation();
		this->SetActorLocation(FVector(vec.X, vec.Y, vec.Z + 500.0f));
	}

}
