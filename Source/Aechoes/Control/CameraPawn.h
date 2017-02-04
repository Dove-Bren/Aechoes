// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS(config=Control)
class ACameraPawn : public APawn
{
    GENERATED_BODY()

private:

    /** The camera being controlled **/
    UCameraComponent *Camera;

    /** Arm used to control camera **/
    USpringArmComponent *CameraArm;

protected:

public:

    ACameraPawn();

    void Init(UCameraComponent *cam);

};
