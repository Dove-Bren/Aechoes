// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "OverworldCameraController.h"
#include "OverworldCamera.generated.h"

UCLASS(config=Control)
class AOverworldCamera : public APawn
{
	GENERATED_BODY()

	/** Camera Controller */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UOverworldCameraController* CameraController;

    /** Camera Focus **/
    AActor *focus;

    /** Actual camera **/
    UCameraComponent *Camera;

    /** Camera Spring **/
    USpringArmComponent *CameraArm;
    
public:
    AOverworldCamera();

    ~AOverworldCamera();

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookRate;

protected:

	/** Called for up/down input */
	void MoveUp(float Rate);

	/** Called for side to side input */
	void MoveRight(float Rate);

	/** 
	 * Called via input to go up or down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void MoveUpRate(float Rate);

	/**
	 * Called via input to turn look side-to-side at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void MoveRightRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

    /** Handles left clicks **/
    void OnSelectClick(FVector location);

    /** Handles right clicks **/
    void OnActionClick(FVector location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Controller subobject **/
	virtual UPawnMovementComponent* GetMovementComponent() const override;

    /** Return current focus (if any!) of the camera **/
    UFUNCTION(BlueprintCallable, Category = Camera)
    AActor *getFocus();

	/** Set the focus of the camera **/
	UFUNCTION(BlueprintCallable, Category = Camera)
	void SetFocus(AActor *in);

    /** Returns camera component **/
    UCameraComponent *getCamera();
};

