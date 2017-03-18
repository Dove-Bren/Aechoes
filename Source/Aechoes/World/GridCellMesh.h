// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "GridCellMesh.generated.h"

/**
 * Grid cell mesh. A mesh that fills a single grid cell
 */
UCLASS()
class AECHOES_API UGridCellMesh : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UGridCellMesh();

  /**
  * Set the grid scale, for proper model scaling.
  * Compares to default grid size of 200 -- what I model to
  **/
  void SetGridScale(float scale);
	
};