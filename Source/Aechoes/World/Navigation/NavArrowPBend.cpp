// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "NavArrowPBend.h"

UNavArrowPBend::UNavArrowPBend(const class FObjectInitializer& ObjectInitializer) : UNavArrowPiece()
{


	//RelativeScale3D = FVector(2.0f, 2.0f, 1.75f);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SMObj(TEXT("StaticMesh'/Game/ThirdPerson/Meshes/grid_arrow_bend2.grid_arrow_bend2'"));

	this->SetStaticMesh(SMObj.Object);

}


