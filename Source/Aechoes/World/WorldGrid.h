// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <cmath>

#include "Engine/Level.h"
#include "Engine/UserDefinedStruct.h"
#include "../Character/LivingCharacter.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include "WorldGrid.generated.h"

struct GridPosition {
    /** The x coordinate of this position **/
    int32 x;

    /** The y coordinate of this position **/
    int32 y;

    /** Static Helper Construcor **/
    static GridPosition from(float x, float y, float scale) {
        GridPosition pos;

        pos.x = (int)x / scale;
        pos.y = (int)y / scale;

        return pos;
    }

    /** Grid Alignment Helper **/
    static FVector alignToGrid(FVector input, float scale) {
        FVector out = input;

        out.X -= fmod(input.X, scale); // * scale;
        out.Y -= fmod(input.Y, scale); //* scale;

        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("fmod x [%f] by [%f]: %f"),
              input.X, scale, fmod(input.X, scale)));
        UE_LOG(LogTemp, Warning, TEXT("fmod y [%f] by [%f]: %f"),
              input.Y, scale, fmod(input.Y, scale));

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
class AECHOES_API UWorldGrid : public UUserDefinedStruct
{
	GENERATED_BODY()

public:
    /** Default Scale value **/
    float const DEFAULT_SCALE = 200.0;
	
protected:
    
    /** Size of each cell **/
    float scale;

    /** Map between coordinate hash and occupant **/
    TMap<GridPosition, TWeakObjectPtr<ALivingCharacter>> map;

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
    ALivingCharacter* get(float x, float y);

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
    bool place(float x, float y, ALivingCharacter *input);

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
	
	
};