// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "NavArrowPiece.h"
#include "NavArrowPHead.h"
#include "NavArrowPMid.h"
#include "NavArrowPBend.h"
#include "../WorldGrid.h"
#include "../GridDisplay.h"
#include "NavArrow.generated.h"

/**
 * Arrow drawn on grid to represent path to the targetted location.
 * Comprised of NavArrowPiece components to build actual path
 **/
UCLASS()
class AECHOES_API ANavArrow : public AActor
{
	GENERATED_BODY()

protected:
	/** Collection of current pieces **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = NavArrow)
	TArray<UNavArrowPiece *> Pieces;

  AGridDisplay *GridDisplay;

  /** Grid Mesh used **/
  UStaticMesh *MeshObject;

	/** Last used target location -- for optimization checks **/
	GridPosition LastTarget;


	
public:	
	// Sets default values for this actor's properties
	ANavArrow();
	
	///**
	// * Sets the given target as the current target, possibly triggering a full update.
	// * This includes creating all subpieces to form a coherent arrow to the target
	// * @param NewTarget the new target location to point towards
	// **/
	//virtual void UpdateTarget(GridPosition NewTarget);

	/**
	* Sets the given target as the current target, possibly triggering a full update.
	* This includes creating all subpieces to form a coherent arrow to the target
	* @param Path the list of positions to run path over
	**/
	//UFUNCTION(BlueprintCallable, Category = NavArrow)
	virtual void UpdateTarget(TArray<GridPosition> &path);

	/**
	 * Return the kept value for the last target
	 * @return The last target given, or null
	 **/
	GridPosition GetLastTarget();

	/**
	 * Tell the arrow to destroy all subpieces and stop rendering
	 **/
	UFUNCTION(BlueprintCallable, Category = NavArrow)
	void DestroyArrow();

	
};
