// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "NavArrowPiece.h"


// Sets default values for this component's properties
UNavArrowPiece::UNavArrowPiece()
{
	//PrimaryComponentTick.bCanEverTick = false;
	bAbsoluteLocation = true;
	bAbsoluteRotation = true;

	this->MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DefaultMesh"));
	this->MeshComponent->AttachTo(this);
	
}

void UNavArrowPiece::SetDirection(GridDirection NewDirection)
{
	this->Direction = NewDirection;
	if (this->MeshComponent != nullptr) {
		this->MeshComponent->RelativeRotation = FRotator(0, (float) NewDirection, 0);
	}
}



