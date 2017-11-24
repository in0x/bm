// Fill out your copyright notice in the Description page of Project Settings.

#include "BmBaseBombActor.h"
#include "Engine.h"

ABmBaseBombActor::ABmBaseBombActor()
{
	PrimaryActorTick.bCanEverTick = true;
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

	ECollisionChannel hitScanChannel = GetCollsionChannelByName("OverlapAll");

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

	TArray<FHitResult> result_x = Trace(GetWorld(), location - FVector(explodeRange, 0, 0), location + FVector(explodeRange, 0, 0), {});
	TArray<FHitResult> result_y = Trace(GetWorld(), location - FVector(0, explodeRange, 0), location + FVector(0, explodeRange, 0), {});

	BombExploded.Broadcast(this);

	Destroy();
}


