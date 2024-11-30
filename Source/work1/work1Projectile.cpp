// Copyright Epic Games, Inc. All Rights Reserved.

#include "work1Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/GameModeBase.h" 
#include "work1GameMode.h"
#include "Engine/StaticMeshActor.h"

Awork1Projectile::Awork1Projectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &Awork1Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void Awork1Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		Awork1GameMode* GameMode = Cast<Awork1GameMode>(GetWorld()->GetAuthGameMode());
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		//UE_LOG(LogTemp, Warning, TEXT("Awork1Projectile::OnHit: %d"), GameMode->score1111);
		AStaticMeshActor* Affected = Cast<AStaticMeshActor>(OtherActor);
		if (Affected != nullptr)
		{
			GameMode->score1111+= Affected->addScore;
			// ��ȡ����ײ����ľ�̬�������
			if (Affected->HasBeenHit) {
				Affected->Destroy();
			}
			UStaticMeshComponent* StaticMesh = Affected->FindComponentByClass<UStaticMeshComponent>();
			if (StaticMesh != nullptr)
			{
				// ��ȡ��ǰ�����ű���
				FVector CurrentScale = StaticMesh->GetRelativeScale3D();
				// ��ÿ��ά�ȵ����ű�������
				StaticMesh->SetRelativeScale3D(CurrentScale * 2.0f);
				Affected->HasBeenHit = true;
			}
		}
		Destroy();
	}
}