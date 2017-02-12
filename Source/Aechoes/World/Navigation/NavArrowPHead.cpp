// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "NavArrowPHead.h"

UNavArrowPHead::UNavArrowPHead(const class FObjectInitializer& ObjectInitializer) : UNavArrowPiece()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SMObj(TEXT("StaticMesh'/Game/ThirdPerson/Meshes/grid_arrow_head.grid_arrow_head'"));
	
	this->SetStaticMesh(SMObj.Object);
	//this->bAbsoluteLocation = false;

}


