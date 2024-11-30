// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "work1GameMode.generated.h"

UCLASS(minimalapi)
class Awork1GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	Awork1GameMode();
	virtual void BeginPlay() override;
	virtual void EndGame() ;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int score1111;
};



