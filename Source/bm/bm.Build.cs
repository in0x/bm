// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class bm : ModuleRules
{
	public bm(ReadOnlyTargetRules Target) : base(Target)
	{
		// Speed up compilation by always forcing a PCH and not using Unity Builds,
		// which are only preferable in engine builds or very large projects.
		MinFilesUsingPrecompiledHeaderOverride = 1;
		bFasterWithoutUnity = true;

		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		// Lets us use some Blueprint functionality in C++.
		PublicIncludePaths.Add("Runtime/Engine/Classes/Kismet");

		if (UEBuildConfiguration.bBuildEditor == true)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
