// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Desktop)]
public class UnrealPakViewerTarget : TargetRules
{
    public UnrealPakViewerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Program;
        LinkType = TargetLinkType.Monolithic;
        LaunchModuleName = "UnrealPakViewer";
        SolutionDirectory = "Games/Programs";
        DefaultBuildSettings = BuildSettingsVersion.V2;

        // Lean and mean
        bBuildDeveloperTools = true;

        // Never use malloc profiling in Unreal Header Tool.  We set this because often UHT is compiled right before the engine
        // automatically by Unreal Build Tool, but if bUseMallocProfiler is defined, UHT can operate incorrectly.
        bUseMallocProfiler = false;

        // Editor-only data, however, is needed
        bBuildWithEditorOnlyData = true;

        // Currently this app is not linking against the engine, so we'll compile out references from Core to the rest of the engine
        bCompileAgainstEngine = false;
        bCompileAgainstCoreUObject = false;
        bCompileAgainstApplicationCore = true;

        // UnrealHeaderTool is a console application, not a Windows app (sets entry point to main(), instead of WinMain())
        bIsBuildingConsoleApplication = false;

        bUseLoggingInShipping = true;
        bCompileWithPluginSupport = true;
    }
}
