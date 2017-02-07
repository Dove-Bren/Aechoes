// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "OverworldCharMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class AECHOES_API UOverworldCharMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
		virtual void TickComponent

		(
			float DeltaTime,
			enum ELevelTick TickType,
			FActorComponentTickFunction* ThisTickFunction
		) override;
	
	
	
};
