// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "../AechoesGameMode.h"
#include "GridDisplay.h"


// Sets default values
AGridDisplay::AGridDisplay()
{
  USceneComponent *root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
  this->RootComponent = root;

  //PrimaryActorTick.bCanEverTick = true;
}

void AGridDisplay::Display(UStaticMesh *Mesh, TArray<GridPosition> &Plots)
{
  if (SMeshComp != nullptr)
    SMeshComp->UnregisterComponent();

  UWorldGrid *grid = ((AAechoesGameMode *) this->GetWorld()->GetAuthGameMode())->getGrid();

  SMeshComp = NewObject<UInstancedStaticMeshComponent>(this);
  SMeshComp->SetStaticMesh(Mesh);

  SMeshComp->RegisterComponent();
  SMeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

  float scale = grid->getScale() / 200.0f;
  FVector offset, vscale(scale, scale, 1.0f);
  TArray<GridPosition> keys = Plots;
  FTransform trans;
  for (GridPosition pos : keys) {
    offset = grid->ToWorldPos(pos, true, true);
    trans = FTransform(offset);
    trans.SetScale3D(vscale);
    SMeshComp->AddInstance(trans);
  }
}
