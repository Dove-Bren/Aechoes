// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Aechoes.h"
#include "OverworldCameraController.h"

//////////////////////////////////////////////////////////////////////////
// AOverworldCameraController

UOverworldCameraController::UOverworldCameraController()
{
	
}

void UOverworldCameraController::setFocus(AActor * newFocus)
{
	this->focus = newFocus;
}

void UOverworldCameraController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    //Taken from tutorial at
    //https://docs.unrealengine.com/latest/INT/Programming/Tutorials/Components/3/index.html

    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Make sure that everything is still valid, and that we are allowed to move.
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
    {
		UE_LOG(LogTemp, Warning, TEXT("Cancelling due to no owner, etc"))
        return;
    }

    // Get (and then clear) the movement vector that we set in ACollidingPawn::Tick
    FVector DesiredMovementThisFrame = ConsumeInputVector() * DeltaTime;
    if (!DesiredMovementThisFrame.IsNearlyZero())
    {
		AActor *owner = GetPawnOwner();

        FHitResult Hit;
        SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

        // If we bumped into something, try to slide along it
        if (Hit.IsValidBlockingHit())
        {
            SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
        }

		//With updated movement, are we too far out? If so, move within range

		if (owner != nullptr && focus != nullptr) {
			FVector targ = focus->GetActorLocation();
			FVector cur = owner->GetActorLocation();

			//Check 1 : Boundaries
			if (cur.Z < targ.Z + STAT_CAMERA_MINZ) {
				cur.Z = targ.Z + STAT_CAMERA_MINZ;
			}
			else if (cur.Z > targ.Z + STAT_CAMERA_MAXZ) {
				cur.Z = targ.Z + STAT_CAMERA_MAXZ;
			}

			//Check 2 : Don't stray out of bounds of focus
			/*float dist = FMath::Abs(FVector::Dist(
				FVector(targ.X, targ.Y, 0), FVector(cur.X, cur.Y, 0)));*/
			FVector distV = cur - targ, dir;
			float dist;
			distV.ToDirectionAndLength(dir, dist);
		
			if (dist > STAT_CAMERA_MAXPAN) {
				FVector anti = FVector(dir);
				float diff = dist - STAT_CAMERA_MAXPAN; //how much we're over
				anti *= diff;
				cur += -anti;
			}

			//finally, update position on modifications
			owner->SetActorLocation(cur);

		}
    }

}
