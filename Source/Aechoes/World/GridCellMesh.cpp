// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "GridCellMesh.h"

UGridCellMesh::UGridCellMesh() : UStaticMeshComponent()
{
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SMObj(TEXT("StaticMesh'/Game/ThirdPerson/Meshes/TileMove.TileMove'"));

	this->SetStaticMesh(SMObj.Object);

}
