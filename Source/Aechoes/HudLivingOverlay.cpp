// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "HudLivingOverlay.h"

AHudLivingOverlay::AHudLivingOverlay()
{
	; //nothing to do
}

AHudLivingOverlay::AHudLivingOverlay(ALivingCharacter *character)
{
	this->character = character;
}

ALivingCharacter *AHudLivingOverlay::getCharacter()
{
	return this->character;
}

void AHudLivingOverlay::setCharacter(ALivingCharacter *in)
{
	this->character = in;
}
