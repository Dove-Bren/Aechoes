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
}

ALivingCharacter::ALivingCharacter(int maxHealth) : AAechoesCharacter::AAechoesCharacter() {
	this->maxHealth = maxHealth;
	this->health = this->maxHealth;
}

int ALivingCharacter::getHealth() {
	return this->health;
}

int ALivingCharacter::getMaxHealth() {
	return this->maxHealth;
}

void ALivingCharacter::damage(int amount)
{
	if (this->health > 0) {
		this->health -= amount;

		if (health <= 0)
			die();
	}
}

void ALivingCharacter::kill()
{
	if (this->health > 0)
		this->die();

	this->health = 0;
}

bool ALivingCharacter::isDead()
{
	return this->health > 0;
}

