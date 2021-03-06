// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Aechoes.h"
#include "OverworldCameraMovement.h"

//////////////////////////////////////////////////////////////////////////
// AOverworldCameraController

UOCameraMovement::UOCameraMovement()
{
	
}

void UOCameraMovement::setFocus(AActor * newFocus)
{
	this->focus = newFocus;
}

void UOCameraMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
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
			FVector distV = (FVector(cur.X, cur.Y, 0) - FVector(targ.X, targ.Y, 0)), dir;
			float dist;

			//only check x, y
			//distV.Z = 0;

			distV.ToDirectionAndLength(dir, dist);
		
			if (dist > STAT_CAMERA_MAXPAN) {
				FVector anti = FVector(dir);
				float diff = dist - STAT_CAMERA_MAXPAN; //how much we're over
				anti *= diff;
				cur += -anti;
			}

      ////Check 3 : Pitch -- Angle depending on height
      //dist = cur.Z - targ.Z;
      ////convert to rate. 0 being as close as we can. 1 is as far as we can
      //dist /= (STAT_CAMERA_MAXZ - STAT_CAMERA_MINZ);

      ////at min, 45 deg pitch. At max, 20 deg pitch
      //float pitch = STAT_CAMERA_MINPITCH;
      //pitch += (45 - STAT_CAMERA_MINPITCH) * dist;


			//finally, update position on modifications
			owner->SetActorLocation(cur);
      //owner->SetActorRotation(FRotator(pitch, 45.0f, 0));

		}
    }

}
