// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Aechoes.h"
#include "CameraPawn.h"


ACameraPawn::ACameraPawn()
{
    ; //leave null
}

void ACameraPawn::Init(UCameraComponent * cam)
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraArm->SetupAttachment(RootComponent);
    CameraArm->TargetArmLength = 1.0f; // The camera follows at this distance behind the character	
    CameraArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

    // Create a follow camera
    Camera = cam;
    Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}
