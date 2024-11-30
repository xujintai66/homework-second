// Copyright Epic Games, Inc. All Rights Reserved.

#include "work1GameMode.h"
#include "work1Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

Awork1GameMode::Awork1GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	score1111 = 0;
}

void Awork1GameMode::BeginPlay()
{
	Super::BeginPlay();
	//定时器
	FTimerHandle EndGameTimerHandle;
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	// 设置一个定时器，10秒后执行EndGame函数，且只执行一次
	TimerManager.SetTimer(EndGameTimerHandle, this, &Awork1GameMode::EndGame, 10.0f, false);

	//函数逻辑
	TArray<AActor*> MyActorInstances;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), MyActorInstances);
	uint32 count0 = 0;
	for (AActor* Actor : MyActorInstances)
	{
		count0++;
		if (AStaticMeshActor* StaticMeshActor = Cast<AStaticMeshActor>(Actor))
		{
			uint32 Seed = FDateTime::Now().GetTicks();
			Seed += count0;
			FRandomStream RandomStream(Seed);
			int RandomInt = RandomStream.RandRange(0, 100);
			StaticMeshActor->addScore = 1;
			if (RandomInt <= 20) {
				StaticMeshActor->isImportant = 1;
				UStaticMeshComponent* StaticMesh = StaticMeshActor->FindComponentByClass<UStaticMeshComponent>();
				UMaterialInstanceDynamic* MaterialInstance = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);
				FLinearColor NewColor = FLinearColor(1.0f, 0.0f, 0.0f);
				MaterialInstance->SetVectorParameterValue("Base Color", NewColor);
				StaticMeshActor->addScore = 2;
			}
		}
	}
}

void Awork1GameMode::EndGame()
{
	// 结束游戏，具体方式取决于你的游戏架构和需求，以下是一种常见的示例
	UE_LOG(LogTemp, Warning, TEXT("final Score is : %d"), score1111);
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
