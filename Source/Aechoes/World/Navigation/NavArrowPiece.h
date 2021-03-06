// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../WorldGrid.h"
#include "NavArrowPiece.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AECHOES_API UNavArrowPiece : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:
	/** Orientation given to this piece **/
	GridDirection Direction;

	//// This piece's mesh compoenent
	//UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = NavArrowComponent)
	//UStaticMeshComponent *MeshComponent;

public:	
	// Sets default values for this component's properties
	UNavArrowPiece();

	/**
	 * Set the orientation of this piece
	 * @param NewDirection
	 **/
	void SetDirection(GridDirection NewDirection);

  /**
   * Set the grid scale, for proper model scaling.
   * Compares to default grid size of 200 -- what I model to
   **/
  void SetGridScale(float scale);
		
	
};
