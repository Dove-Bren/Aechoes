// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "LivingCharacter.h"

void ALivingCharacter::die_Implementation()
{
    ; //Nothing to do yet
}


ALivingCharacter::ALivingCharacter() : AAechoesCharacter::AAechoesCharacter() {
    this->maxHealth = ALivingCharacter::DEFAULT_MAXHEALTH;
    this->health = this->maxHealth;
    this->healthRegenRate = ALivingCharacter::DEFAULT_HEALTHREGEN;
    this->dead = false;

    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bTickEvenWhenPaused = false;
    PrimaryActorTick.TickGroup = TG_PostPhysics;
}

ALivingCharacter::ALivingCharacter(int32 maxHealth) : AAechoesCharacter::AAechoesCharacter() {
    this->maxHealth = maxHealth;
    this->health = this->maxHealth;
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

}

