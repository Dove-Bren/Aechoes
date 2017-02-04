// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Aechoes.h"
#include "OverworldCameraController.h"

//////////////////////////////////////////////////////////////////////////
// AOverworldCameraController

UOverworldCameraController::UOverworldCameraController()
{
	
}

void UOverworldCameraController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    //Taken from tutorial at
    //https://docs.unrealengine.com/latest/INT/Programming/Tutorials/Components/3/index.html

    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Make sure that everything is still valid, and that we are allowed to move.
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }

    // Get (and then clear) the movement vector that we set in ACollidingPawn::Tick
    FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
    if (!DesiredMovementThisFrame.IsNearlyZero())
    {
        FHitResult Hit;
        SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

        // If we bumped into something, try to slide along it
        if (Hit.IsValidBlockingHit())
        {
            SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
        }
    }

}
