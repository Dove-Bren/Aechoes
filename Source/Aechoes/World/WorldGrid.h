// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <cmath>

#include "Engine/Level.h"
#include "Components/ActorComponent.h"
#include "../Character/LivingCharacter.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include "WorldGrid.generated.h"

enum class GridDirection {
	EAST = 180,
	NORTH = 90,
	WEST = 0,
	SOUTH = 270
};

struct GridPosition {
    /** The x coordinate of this position **/
    int32 x;

    /** The y coordinate of this position **/
    int32 y;

	GridPosition(int32 inX, int32 inY)
	{
		this->x = inX;
		this->y = inY;
	}

	GridPosition()
	{
		;
	}

    /** Static Helper Construcor **/
    static GridPosition from(float x, float y, float scale) {
        GridPosition pos;

        pos.x = FMath::FloorToInt(x / scale);
        pos.y = FMath::FloorToInt(y / scale);

        return pos;
    }

    /** Grid Alignment Helper **/
    static FVector alignToGrid(FVector input, float scale) {
        FVector out = input;
		int facX, facY;

		facX = FMath::FloorToInt(input.X / scale);
		facY = FMath::FloorToInt(input.Y / scale);

		out.X = ((float) facX) * scale;
		out.Y = ((float) facY) * scale;

        //out.X -= fmod(input.X, scale); // * scale;
        //out.Y -= fmod(input.Y, scale); //* scale;

        //if (GEngine)
        //    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("fmod x [%f] by [%f]: %f"),
        //      input.X, scale, fmod(input.X, scale)));
        //UE_LOG(LogTemp, Warning, TEXT("fmod y [%f] by [%f]: %f"),
        //      input.Y, scale, fmod(input.Y, scale));

        return out;
    }

    bool operator== (const GridPosition& Other) const
    {
        return (x == Other.x && y == Other.y);
    }

    friend uint32 GetTypeHash(const GridPosition& Other)
    {
        return (uint32) Other.x ^ (uint32) Other.y;
    }
};

/**
 * Grid on which entities reside and are constrained to
 */
UCLASS()
class AECHOES_API UWorldGrid : public UActorComponent
{
	GENERATED_BODY()

public:
    /** Default Scale value **/
    float const DEFAULT_SCALE = 200.0;
	
protected:
    
    /** Size of each cell **/
    float scale;

    /** Map between coordinate hash and occupant **/
    TMap<GridPosition, TWeakObjectPtr<AAechoesCharacter>> map;

    /** Helper function to spawn up Grid Positions easily **/
    GridPosition translate(float x, float y);

public:
    UWorldGrid();
    
    /** Returns the scale of the grid **/
    UFUNCTION(BlueprintCallable, Category = "Combat|Layout")
    float getScale();

    /** Returns a pointer to a living Character, if there was one at the cell
     * @return null if cell is empty, pointer to character otherwise 
     **/
    UFUNCTION(BlueprintCallable, Category = "Combat|Layout")
		AAechoesCharacter* get(float x, float y);

	/** Returns a pointer to a living Character, if there was one at the cell
	* @return null if cell is empty, pointer to character otherwise
	**/
	AAechoesCharacter* get(GridPosition At);

    /** Checks whether the cell at the given position is empty
     * @return true when the cells is empty; false otherwise 
     **/
    UFUNCTION(BlueprintCallable, Category = "Combat|Layout")
    bool isEmpty(float x, float y);

    /**
     * Sets the cell to hold the provided character. If a character was
     * previously in the cell, it is overwritten.
     * @return true when the cell was not empty, and a character has been overwritten
     **/
    UFUNCTION(BlueprintCallable, Category = "Combat|Layout")
    bool place(float x, float y, AAechoesCharacter *input);

    /**
     * Removes any character from the given cell.
     * @return true when the cell was not empty, and a character has been removed
     **/
    UFUNCTION(BlueprintCallable, Category = "Combat|Layout")
    bool clear(float x, float y);

    /**
     * Removes all characters from the grid, clearing the map.
     * This function can be used for cleaning a map before moving to a new map
     **/
    UFUNCTION(BlueprintCallable, Category = "Combat|Layout")
    void clearAll();

    /** Helper function to snap things to the grid
    * @param in the input vector.
    * @param middle align to middle of cell?
    * @return a new FVector with the corrected coordinates
    **/
    FVector snapTo(FVector const in, bool middle);
	
	/**
	 * Do an opposite conversion between GridPosition and world location
	 * NOTE: The returned pos will have a value of 0 for Z!
	 * @param GridPos the grid position to swap out
	 * @return A new FVector holding world location information
	 * Note: This is equivalent to ToWorldPos(GridPos, false);
	 **/
	FVector ToWorldPos(GridPosition GridPos);

	/**
	* Do an opposite conversion between GridPosition and world location
	* NOTE: The returned pos will have a value of 0 for Z!
	* @param GridPos the grid position to swap out
	* @param Middle Whether or not to shift to the center of the cell
	* @return A new FVector holding world location information
	**/
	FVector ToWorldPos(GridPosition GridPos, bool Middle);

	/**
	* Do an opposite conversion between GridPosition and world location
	* @param GridPos the grid position to swap out
	* @param Middle Whether or not to shift to the center of the cell
	* @param UseNavZ try to project the given point onto the nav system to get a Z
	* @return A new FVector holding world location information
	**/
	FVector ToWorldPos(GridPosition GridPos, bool Middle, bool UseNavZ);

	//Converts from world pos to a GridPosition
	GridPosition ToGridPos(FVector WorldPos);

	/**
	 * Calculates the Manhattan Distance (number of distance in cells) between
	 * the given world vectors.
	 * @param Pos1 
	 * @param Pos2
	 * @return The integer distance, > 0. This is equivalent to how many
	 *         cells would need to be moved to move between the points
	 **/
	UFUNCTION(BlueprintCallable, Category = Movement)
	virtual int32 GetGridDistance(FVector Pos1, FVector Pos2);
};