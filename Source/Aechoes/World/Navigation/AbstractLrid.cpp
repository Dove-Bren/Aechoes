// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
//#include "../GridCellMesh.h"
#include "../../AechoesGameMode.h"
#include "../GridDisplay.h"
#include "AbstractLrid.h"

UAbstractLrid::UAbstractLrid()
{
	MaxLen = 0;
	Owner = nullptr;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Anchor"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MObj(TEXT("StaticMesh'/Game/ThirdPerson/Meshes/TileMove.TileMove'"));
	this->MeshObject = MObj.Object;
}

int32 UAbstractLrid::GetMaxLen()
{
	return MaxLen;
}

ALivingCharacter * UAbstractLrid::GetOwner()
{
	return Owner;
}

void UAbstractLrid::SetOwner(ALivingCharacter * NewOwner)
{
	this->Owner = NewOwner;
}

void UAbstractLrid::SetMaxLength(int32 length)
{
	this->MaxLen = length;
}

void UAbstractLrid::Update()
{
	; //Do nothing
}

void UAbstractLrid::DisplayGrid()
{
	/*if (SMeshComp != nullptr)
		SMeshComp->UnregisterComponent();

  UWorldGrid *grid = ((AAechoesGameMode *) this->GetWorld()->GetAuthGameMode())->getGrid();
		
	SMeshComp = NewObject<UInstancedStaticMeshComponent>(this);
  float scale = grid->getScale() / 200.0f;
  SMeshComp->SetRelativeScale3D(FVector(scale, scale, 1.0f));
	SMeshComp->SetStaticMesh(MeshObject);
		
	SMeshComp->RegisterComponent();
	SMeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	FVector offset;
	TArray<GridPosition> keys = GetEndpoints();
	for (GridPosition pos : keys) {
		offset = grid->ToWorldPos(pos, true, true);
		SMeshComp->AddInstance(FTransform(offset));
	}*/

  GridDisplay = GetWorld()->SpawnActor<AGridDisplay>(
    AGridDisplay::StaticClass(),
    FVector(0, 0, 0),
    FRotator(0, 0, 0)
    );

  TArray<GridPosition> points = GetEndpoints();
  GridDisplay->Display(MeshObject, points);

}

TArray<GridPosition> const UAbstractLrid::GetEndpoints() const
{
	//Default broken behavior
	return TArray<GridPosition>();
}
