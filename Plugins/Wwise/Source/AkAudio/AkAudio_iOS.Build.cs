// Copyright (c) 2006-2019 Audiokinetic Inc. / All Rights Reserved
using UnrealBuildTool;
using System;
using System.IO;
using System.Collections.Generic;

public class AkUEPlatform_IOS : AkUEPlatform
{
	public AkUEPlatform_IOS(ReadOnlyTargetRules in_TargetRules, string in_ThirdPartyFolder) : base(in_TargetRules, in_ThirdPartyFolder) {}

#if !UE_4_24_OR_LATER
	public override string SanitizeLibName(string in_libName)
	{
		return in_libName;
	}
#endif

	public override string GetLibraryFullPath(string LibName, string LibPath)
	{
		return Path.Combine(LibPath, "lib" + LibName + ".a");
	}

	public override bool SupportsAkAutobahn { get { return false; } }

	public override bool SupportsCommunication { get { return true; } }

	public override List<string> GetPublicLibraryPaths()
	{
		return new List<string>
		{
			Path.Combine(ThirdPartyFolder, "iOS", akConfigurationDir + "-iphoneos", "lib")
		};
	}

	public override List<string> GetAdditionalWwiseLibs()
	{
		var libs = GetAllLibrariesInFolder(Path.Combine(ThirdPartyFolder, "iOS", akConfigurationDir + "-iphoneos", "lib"), "*.a");
		libs.Add("AkAACDecoder");
		return libs;
	}

	public override List<string> GetPublicDelayLoadDLLs()
	{
		return new List<string>();
	}
	
	public override List<string> GetPublicSystemLibraries()
	{
		return new List<string>();
	}

	public override List<string> GetPublicDefinitions()
	{
		return new List<string>();
	}

	public override Tuple<string, string> GetAdditionalPropertyForReceipt(string ModuleDirectory)
	{
		return null;
	}

	public override List<string> GetPublicAdditionalFrameworks()
	{
		return new List<string>
		{
			"AudioToolbox",
			"CoreAudio"
		};
	}
}
