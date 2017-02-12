// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "NavArrowPMid.h"

UNavArrowPMid::UNavArrowPMid(const class FObjectInitializer& ObjectInitializer) : UNavArrowPiece()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SMObj(TEXT("StaticMesh'/Game/ThirdPerson/Meshes/grid_arrow_straight2.grid_arrow_straight2'"));

	this->SetStaticMesh(SMObj.Object);
	//this->bAbsoluteLocation = false;

}


