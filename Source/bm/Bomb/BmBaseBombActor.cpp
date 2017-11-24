// Fill out your copyright notice in the Description page of Project Settings.

#include "BmBaseBombActor.h"
#include "Engine.h"

ABmBaseBombActor::ABmBaseBombActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bCanBeDamaged = true;
}

void ABmBaseBombActor::SetExplodeRange(float Range)
{
	explodeRange = Range;
}

TEnumAsByte<ECollisionChannel> GetCollsionChannelByName(FName ChannelName)
{
	const UCollisionProfile* collisionProfile = UCollisionProfile::Get();
	for (int32 channel = ECC_GameTraceChannel1; channel <= ECC_GameTraceChannel18; ++channel)
	{
		if (ChannelName == collisionProfile->ReturnChannelNameFromContainerIndex(channel))
		{
			return TEnumAsByte<ECollisionChannel>(channel);
		}
	}

	FString channelString = ChannelName.ToString();

	UE_LOG(LogTemp, Warning, TEXT("Collisionchannel \"%s\" not found!"), *channelString);
	return TEnumAsByte<ECollisionChannel>(ECollisionChannel::ECC_MAX);
}

TArray<FHitResult> ABmBaseBombActor::Trace(UWorld* world, FVector Start, FVector End, const TArray<TWeakObjectPtr<AActor>>& IgnoredActors) const
{
	TArray<FHitResult> result;

	FCollisionQueryParams CollisionParams("OverlapAll", true, /*Instigator*/nullptr);
	CollisionParams.AddIgnoredActors(IgnoredActors);

	ECollisionChannel hitScanChannel = GetCollsionChannelByName("BombExplosion");

	world->LineTraceMultiByChannel(result, Start, End, hitScanChannel, CollisionParams);
	return result;
}

void ABmBaseBombActor::Explode_Implementation()
{
	FVector location = GetActorLocation();

	DrawDebugLine(GetWorld(), 
				  location - FVector(explodeRange, 0, 0), location + FVector(explodeRange, 0, 0), 
				  FColor::Red,
				  false,
				  2.f,
				  0,
				  10.f);

	DrawDebugLine(GetWorld(),
				  location - FVector(0, explodeRange, 0), location + FVector(0, explodeRange, 0),
				  FColor::Red,
				  false,
				  2.f,
				  0,
				  10.f);

	TArray<FHitResult> result_xPos = Trace(GetWorld(), location, location + FVector(explodeRange, 0, 0), { this });
	TArray<FHitResult> result_xNeg = Trace(GetWorld(), location, location - FVector(explodeRange, 0, 0), { this });

	TArray<FHitResult> result_yPos = Trace(GetWorld(), location, location + FVector(0, explodeRange, 0), { this });
	TArray<FHitResult> result_yNeg = Trace(GetWorld(), location, location - FVector(0, explodeRange, 0), { this });

	AController* instigator = GetInstigator()->GetController();

	for (FHitResult hit : result_xPos)
	{
		hit.Actor->TakeDamage(100.f, FDamageEvent(), instigator, this);
	}

	for (FHitResult hit : result_xNeg)
	{
		hit.Actor->TakeDamage(100.f, FDamageEvent(), instigator, this);
	}

	for (FHitResult hit : result_yPos)
	{
		hit.Actor->TakeDamage(100.f, FDamageEvent(), instigator, this);
	}

	for (FHitResult hit : result_yNeg)
	{
		hit.Actor->TakeDamage(100.f, FDamageEvent(), instigator, this);
	}

	BombExploded.Broadcast(this);

	Destroy();
}


