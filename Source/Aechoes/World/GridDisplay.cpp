// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "../AechoesGameMode.h"
#include "GridDisplay.h"


// Sets default values
AGridDisplay::AGridDisplay()
{
 	
}

void AGridDisplay::Display(UStaticMesh *Mesh, TArray<GridPosition> &Plots)
{
  if (SMeshComp != nullptr)
    SMeshComp->UnregisterComponent();

  UWorldGrid *grid = ((AAechoesGameMode *) this->GetWorld()->GetAuthGameMode())->getGrid();

  SMeshComp = NewObject<UInstancedStaticMeshComponent>(this);
  float scale = grid->getScale() / 200.0f;
  SMeshComp->SetRelativeScale3D(FVector(scale, scale, 1.0f));
  SMeshComp->SetStaticMesh(Mesh);

  SMeshComp->RegisterComponent();
  SMeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

  FVector offset;
  TArray<GridPosition> keys = Plots;
  for (GridPosition pos : keys) {
    offset = grid->ToWorldPos(pos, true, true);
    SMeshComp->AddInstance(FTransform(offset));
  }
}

