// Fill out your copyright notice in the Description page of Project Settings.

#include "BmViewportClient.h"
#include "Engine.h"

// Via: https://wiki.unrealengine.com/Local_Multiplayer_Tips
bool UBmViewportClient::InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	if (IgnoreInput() || bGamepad || Key.IsMouseButton())
	{
		return Super::InputKey(Viewport, ControllerId, Key, EventType, AmountDepressed, bGamepad);
	}
	else
	{
		UEngine* const engine = GetOuterUEngine();
		check(engine);
		int32 numPlayers = engine->GetNumGamePlayers(this);
		
		bool bRetVal = false;
		for (int32 i = 0; i < numPlayers; i++)
		{
			bRetVal = Super::InputKey(Viewport, i, Key, EventType, AmountDepressed, bGamepad) || bRetVal;
		}

		return bRetVal;
	}
}


