// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "EngineGlobals.h"
#include "AIController.h"
#include "Engine.h"
#include "../AechoesGameMode.h"
#include "LivingCharacter.h"

void ALivingCharacter::die_Implementation()
{
    ; //Nothing to do yet
}


ALivingCharacter::ALivingCharacter(const class FObjectInitializer& ObjectInitializer) : AAechoesCharacter::AAechoesCharacter(ObjectInitializer) {
    this->maxHealth = ALivingCharacter::DEFAULT_MAXHEALTH;
    this->health = this->maxHealth;
    this->healthRegenRate = ALivingCharacter::DEFAULT_HEALTHREGEN;
    this->dead = false;

    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bTickEvenWhenPaused = false;
    PrimaryActorTick.TickGroup = TG_PostPhysics;
}

int32 ALivingCharacter::getHealth() {
    return this->health;
}

int32 ALivingCharacter::getMaxHealth() {
    return this->maxHealth;
}

void ALivingCharacter::damage(int32 amount)
{
    if (this->health > 0) {
        this->health -= amount;

        if (health <= 0) {
            kill();
        }
        else if (health > maxHealth) {
            health = maxHealth;
        }

    }
}

void ALivingCharacter::addHealth(int32 amount)
{
    this->health += amount;
    if (health <= 0) {
        kill();
    }

    if (health > maxHealth)
        health = maxHealth;
}

void ALivingCharacter::kill()
{
    if (!this->isDead()) {
        this->dead = true;
        this->die();
    }

    this->health = 0;
}

bool ALivingCharacter::isDead()
{
    return this->dead;
}

int32 ALivingCharacter::getHealthRegen()
{
    return this->healthRegenRate;
}

void ALivingCharacter::setHealthRegen(int32 regenRate)
{
    this->healthRegenRate = regenRate;
}

void ALivingCharacter::SetEffectiveLocation(FVector in, bool rebuild)
{
	EffectiveLocation = in;
}

void ALivingCharacter::Tick(float delta)
{
    AAechoesCharacter::Tick(delta);

    static float time = 0.0;

    time += delta;
    while (time >= 5.0) {
        time -= 5.0;
        //every 5 seconds, do:

        if (!this->isDead() && this->health < this->maxHealth)
            this->addHealth(getHealthRegen());
    }


	if (IsPathfinding) {
		static float lastLen = 0.0f;
		FVector dir;
		float len;
		this->GetVelocity().ToDirectionAndLength(dir, len);
		if (len <= 0.01 || (len - lastLen) < -0.1f) {
			//pathfinding, but came to a stop
			//need to update movement?
			if (MovementWaypoints.Num() == 0)
				IsPathfinding = false;
			else {
				FVector next = MovementWaypoints.Pop();
				/*next = UNavigationSystem::ProjectPointToNavigation(GetWorld(), next, nullptr, 0, FVector(0.0f, 0.0f, 30.0f));*/
				if (((AAIController *)GetController())->MoveToLocation(next, 0.05f, false, true, true, false, 0, true)
					== EPathFollowingRequestResult::Failed) {
					UE_LOG(LogTemp, Warning, TEXT("Failed to submit movement request!"));
					
				}

				//UNavigationSystem::SimpleMoveToLocation(GetController(), next);
			}
		}

		lastLen = len;
	}

}

void ALivingCharacter::BeginPlay()
{
    Super::BeginPlay();
	
	UWorldGrid *grid = ((AAechoesGameMode *) this->GetWorld()->GetAuthGameMode())->getGrid();
    FVector old = this->GetActorLocation();
    FVector out = grid->snapTo(old, true);
    this->SetActorLocation(out);
	grid->place(out.X, out.Y, this);

	EffectiveLocation = GetActorLocation();

}

FVector ALivingCharacter::GetEffectiveLocation()
{
	return EffectiveLocation;
}

bool ALivingCharacter::isCommandReady()
{

	if (IsPathfinding)
		return false;

	FVector dir;
	float len;
	this->GetVelocity().ToDirectionAndLength(dir, len);
	return (FMath::Abs(len) < 0.01);
		
}

bool ALivingCharacter::SetMovementPath(TArray<FVector> PathPoints, bool force)
{
	if (MovementWaypoints.Num() != 0 && !force)
		return false;

	MovementWaypoints = PathPoints;
	IsPathfinding = true;

	return true;
}


