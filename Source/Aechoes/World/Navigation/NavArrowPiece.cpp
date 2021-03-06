// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "NavArrowPiece.h"


// Sets default values for this component's properties
UNavArrowPiece::UNavArrowPiece()
{
	//PrimaryComponentTick.bCanEverTick = false;

	SetMobility(EComponentMobility::Movable);
	RelativeScale3D = FVector(1.05f, 1.05f, 1.05f);

	//bAbsoluteLocation = true;
	bAbsoluteRotation = true;
	bGenerateOverlapEvents = false;
	bCanEverAffectNavigation = false;

	/*this->MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DefaultMesh"));
	this->MeshComponent->AttachTo(this);*/
	
}

void UNavArrowPiece::SetGridScale(float scale)
{
  float val = scale / 200.0f;
  val *= 1.05f;
  SetWorldScale3D(FVector(val, val, val));
  //RelativeScale3D = ;
}

void UNavArrowPiece::SetDirection(GridDirection NewDirection)
{
	this->Direction = NewDirection;
	SetWorldRotation(FRotator(0, (float)NewDirection, 0));
	//RelativeRotation = 
	/*if (this->MeshComponent != nullptr) {
		this->MeshComponent->RelativeRotation = FRotator(0, (float) NewDirection, 0);
	}*/
}



