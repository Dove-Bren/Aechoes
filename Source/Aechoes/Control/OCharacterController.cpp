// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "OCharacterController.h"


AOCharacterController::AOCharacterController()
{
	UE_LOG(LogTemp, Warning, TEXT("Starting character controller"));
}


void AOCharacterController::TickActor(float DeltaTime,
	enum ELevelTick TickType,
	FActorTickFunction & ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	//if (GEngine->GameViewport) {
	//	//if game in focus
	//	FVector2D pos, size;
	//	GEngine->GameViewport->GetViewportSize(size);
	//	pos = GEngine->GameViewport->GetMousePosition();
	//	if (pos.X > 0 && (pos.X < 100 || pos.X > size.X - 100))
	//		MoveRight(pos.X < 100 ? -1 + (pos.X / 100) : 1 - ( (size.X - pos.X) / 100));

	//	if (pos.Y > 0 && (pos.Y < 100 || pos.Y > size.Y - 100))
	//		MoveUp(pos.Y < 100 ? 1 - (pos.Y / 100) : -1 + ((size.Y - pos.Y) / 100));

	//}

}