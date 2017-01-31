// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine/Level.h"
#include "../Character/LivingCharacter.h"
#include "WorldGrid.generated.h"

struct GridPosition {
    int32 x;

    int32 y;

    static GridPosition *from(float x, float y, float scale) {
        GridPosition *pos = (GridPosition *)malloc(sizeof(GridPosition));

        pos->x = (int)x / scale;
        pos->y = (int)y / scale;

        return pos;
    }

    bool operator== (const GridPosition& Other)
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
class AECHOES_API AWorldGrid : public AActor
{
	GENERATED_BODY()

public:
    float DEFAULT_SCALE = 64.0;
	
protected:
    
    /** Size of each cell **/
    float scale;

    /** Map between coordinate hash and occupant **/
    TMap<GridPosition, TWeakObjectPtr<ALivingCharacter>> map;

    GridPosition *translate(float x, float y);

public:
    AWorldGrid();
    
    float getScale();

    TWeakObjectPtr<ALivingCharacter> get(float x, float y);

    bool isEmpty(float x, float y);

    bool place(float x, float y);

    bool clear(float x, float y);
	
	
};