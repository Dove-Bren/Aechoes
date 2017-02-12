// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "NavArrow.h"
#include "../../AechoesGameMode.h"
#include "../../Control/OverworldController.h"


// Sets default values
ANavArrow::ANavArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent *root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	this->RootComponent = root;
}

//void ANavArrow::UpdateTarget(FVector NewTarget)
//{
//	UWorldGrid *grid = ((AAechoesGameMode *) this->GetWorld()->GetAuthGameMode())->getGrid();
//	UpdateTarget(grid->ToGridPos(NewTarget));
//}

void ANavArrow::UpdateTarget(TArray<GridPosition> input)
{
	/*if (NewTarget == LastTarget)
		return;
*/

	/*LastTarget = NewTarget;*/

	UE_LOG(LogTemp, Warning, TEXT("Update Arrow with %d plots"), input.Num());

	if (input.Num() == 0)
		return;

	if (Pieces.Num() != 0) {
		for (UNavArrowPiece *p : Pieces)
			p->UnregisterComponent();

		Pieces.Empty();
	}


	float Z = 120.0f;

	AOverworldController *GlobalController = (AOverworldController *)GetWorld()->GetFirstPlayerController();
	if (GlobalController != nullptr && GlobalController->GetControl() != nullptr)
		Z = GlobalController->GetControl()->GetActorLocation().Z;



	UWorldGrid *grid = ((AAechoesGameMode *) this->GetWorld()->GetAuthGameMode())->getGrid();
	
	/*GridPosition GPI[] = {GridPosition(-5, -1), GridPosition(-5, -2), GridPosition(-5, -3), GridPosition(-4, -3), GridPosition(-3, -3) };
	TArray<GridPosition> input;
	input.Append(GPI, ARRAY_COUNT(GPI));*/
	
	int index;
	enum : unsigned char {
		STRAIGHT,
		BEND,
		ARROW
	};
	GridDirection dir;
	GridPosition *next, *cur, *prev;
	UNavArrowPiece *piece;
	FVector loc;
	unsigned char type;

	//note: start at 1 to skip first piece. Easy.
	for (index = 1; index < input.Num(); index++) {

		/*
		Guaranteed to have valid path. Meaning each is different, and each
		successive position only differs by 1 in EITHER x or y.
		This is used when determining piece type
		*/

		//check for last piece
		if (index == input.Num() - 1) {
			//use arrow piece
			type = ARROW;
			int d = input[index - 1].x - input[index].x;
			if (d == -1)
				dir = GridDirection::NORTH;
			else if (d == 1)
				dir = GridDirection::SOUTH;
			else {
				d = input[index - 1].y - input[index].y;
				if (d == -1)
					dir = GridDirection::EAST;
				else
					dir = GridDirection::WEST;
			}
		}
		else {

			//look at prev and next and decide piece info
			//if x==otherx || y ==othery, straight piece
			prev = &(input[index - 1]);
			cur = &(input[index]);
			next = &(input[index + 1]);

			if (prev->x == next->x || prev->y == next->y) {
				type = STRAIGHT;
				if (prev->x == next->x)
					dir = GridDirection::EAST;
				else
					dir = GridDirection::NORTH;
			}
			else {
				type = BEND;
				bool left, up;
				left = up = false;


				if (prev->x > cur->x || next->x > cur->x)
					up = true;
				if (prev->y < cur->y || next->y < cur->y)
					left = true;
				
				if (up && left)
					dir = GridDirection::WEST;
				else if (!up && left)
					dir = GridDirection::SOUTH;
				else if (up && !left)
					dir = GridDirection::NORTH;
				else if (!up && !left)
					dir = GridDirection::EAST;


				//Need to look at prev and cur
				/*if (d == -1)
					dir = GridDirection::NORTH;
				else if (d == 1)
					dir = GridDirection::SOUTH;
				else {
					d = cur->y - next->y;
					if (d == -1)
						dir = GridDirection::EAST;
					else
						dir = GridDirection::WEST;
				}*/
			}


		}

		//now use type and dir to spawn piece
		loc = grid->ToWorldPos(input[index]);
		loc = grid->snapTo(loc, true);

		switch (type) {
		case STRAIGHT:
			piece = NewObject<UNavArrowPMid>(this);
			break;
		case BEND:
			piece = NewObject<UNavArrowPBend>(this);
			break;
		case ARROW:
		default:
			piece = NewObject<UNavArrowPHead>(this);
			break;
		}

		piece->RegisterComponent();
		piece->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		piece->SetWorldLocation(loc);
		piece->SetDirection(dir);
		

		Pieces.Add(piece);


		/*UE_LOG(LogTemp, Warning, TEXT("Generated piece: %s [%s]"),
			(type == STRAIGHT ? TEXT("Straight") : type == BEND ? TEXT("Bend") : TEXT("Arrow")),
			(dir == GridDirection::NORTH ? TEXT("North") : dir == GridDirection::SOUTH ? TEXT("South") : dir == GridDirection::EAST ? TEXT("East") : TEXT("West"))
			);*/

	}

}

GridPosition ANavArrow::GetLastTarget()
{
	return GridPosition();
}


