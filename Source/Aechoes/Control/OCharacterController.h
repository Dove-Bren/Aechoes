// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "OCharacterController.generated.h"

/**
 * Character slave controller for grid characters
 */
UCLASS()
class AECHOES_API AOCharacterController : public AAIController
{
	GENERATED_BODY()

protected:

	

	virtual void TickActor(float DeltaTime,
		enum ELevelTick TickType,
		FActorTickFunction & ThisTickFunction
	) override;
	
public:
	AOCharacterController();
		
};
