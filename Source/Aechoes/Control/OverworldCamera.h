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


protected:

	/** Base look movement rate */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Camera)
		float PanSpeed;

	/** Base zoom movement rate */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Camera)
		float ZoomSpeed;
	
public:

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

	void ZoomIn();

	void ZoomOut();

	/** Returns Controller subobject **/
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	/** Returns the camera controller, without cast **/
	UOverworldCameraController *getCameraController();

    /** Return current focus (if any!) of the camera **/
    UFUNCTION(BlueprintCallable, Category = Camera)
    AActor *getFocus();

	/** Set the focus of the camera **/
	UFUNCTION(BlueprintCallable, Category = Camera)
	void SetFocus(AActor *in);

    /** Returns camera component **/
    UCameraComponent *getCamera();
};

