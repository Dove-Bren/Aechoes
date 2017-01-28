// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "HudLivingOverlay.h"

AHudLivingOverlay::AHudLivingOverlay(ALivingCharacter character)
{
	this->character = character;
}

ALivingCharacter AHudLivingOverlay::getCharacter()
{
	return this->character;
}

void AHudLivingOverlay::setCharacter(ALivingCharacter character)
{
	this->character = character;
}
