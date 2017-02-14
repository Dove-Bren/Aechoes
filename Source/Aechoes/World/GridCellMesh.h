// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "GridCellMesh.generated.h"

/**
 * Interface class that represents something that blocks movement on a grid
 */
UCLASS()
class AECHOES_API UGridCellMesh : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UGridCellMesh();
	
};