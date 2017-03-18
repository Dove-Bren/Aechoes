// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "WorldGrid.h"
#include "GridDisplay.generated.h"

UCLASS()
class AECHOES_API AGridDisplay : public AActor
{
  GENERATED_BODY()

  UInstancedStaticMeshComponent *SMeshComp;
	
public:	
	// Sets default values for this actor's properties
	AGridDisplay();	

  /**
   * Displays the given plots.
   * Removes any previous display
   * @param Mesh The static mesh to use
   * @param Plots the cells to display
   */
  void Display(UStaticMesh *Mesh, TArray<GridPosition> &Plots);
	
};
