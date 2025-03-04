// Copyright (c) 2006-2018 Audiokinetic Inc. / All Rights Reserved
#pragma once

#include "Engine/EngineTypes.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "AssetRegistryModule.h"
#include "AkSettings.generated.h"

class UAkAcousticTexture;

USTRUCT()
struct FAkGeometrySurfacePropertiesToMap
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "AkGeometry Surface Properties Map")
	TSoftObjectPtr<class UAkAcousticTexture> AcousticTexture = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "AkGeometry Surface Properties Map", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float OcclusionValue = 1.f;
};

struct AkGeometrySurfaceProperties
{
	UAkAcousticTexture* AcousticTexture = nullptr;
	float OcclusionValue = 1.f;
};

#define AK_MAX_AUX_PER_OBJ	4

DECLARE_EVENT(UAkSettings, AutoConnectChanged);

UCLASS(config = Game, defaultconfig)
class AKAUDIO_API UAkSettings : public UObject
{
	GENERATED_UCLASS_BODY()

	// The number of AkReverbVolumes that will be simultaneously applied to a sound source
	UPROPERTY(Config, EditAnywhere, Category="Ak Reverb Volume")
	uint8 MaxSimultaneousReverbVolumes = AK_MAX_AUX_PER_OBJ;

	// Wwise Project Path
	UPROPERTY(Config, EditAnywhere, Category="Installation", meta=(FilePathFilter="wproj", AbsolutePath))
	FFilePath WwiseProjectPath;

	// Where the Sound Bank will be generated in the Content Folder
	UPROPERTY(Config, EditAnywhere, Category = "Sound Bank", meta=(RelativeToGameContentDir))
	FDirectoryPath WwiseSoundBankFolder;

	UPROPERTY(Config, EditAnywhere, Category = "Installation")
	bool bAutoConnectToWAAPI = false;

	// Default value for Occlusion Collision Channel when creating a new Ak Component.
	UPROPERTY(Config, EditAnywhere, Category = "Occlusion")
	TEnumAsByte<ECollisionChannel> DefaultOcclusionCollisionChannel = ECollisionChannel::ECC_Visibility;
	
	// PhysicalMaterial to AcousticTexture and Occlusion Value Map
	UPROPERTY(Config, EditAnywhere, EditFixedSize, Category = "AkGeometry Surface Properties Map")
	TMap<TSoftObjectPtr<class UPhysicalMaterial>, FAkGeometrySurfacePropertiesToMap> AkGeometryMap;

	UPROPERTY(Config)
	bool bEnableMultiCoreRendering_DEPRECATED = false;

	UPROPERTY(Config)
	bool MigratedEnableMultiCoreRendering = false;

	UPROPERTY(Config)
	FDirectoryPath WwiseWindowsInstallationPath_DEPRECATED;

	UPROPERTY(Config)
	FFilePath WwiseMacInstallationPath_DEPRECATED;

	static FString DefaultSoundBankFolder;

	virtual void PostInitProperties() override;

	bool GetAssociatedAcousticTexture(const UPhysicalMaterial* physMaterial, UAkAcousticTexture*& acousticTexture) const;
	bool GetAssociatedOcclusionValue(const UPhysicalMaterial* physMaterial, float& occlusionValue) const;

#if WITH_EDITOR
	void EnsureSoundBankPathIsInPackagingSettings();
	void InitAkGeometryMap();
#endif

protected:
#if WITH_EDITOR
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent ) override;
	virtual void PreEditChange(UProperty* PropertyAboutToChange) override;
#endif

private:
	FString PreviousWwiseProjectPath;
	FString PreviousSoundBankFolder;

#if WITH_EDITOR
	FAssetRegistryModule* AssetRegistryModule;
	void OnAssetAdded(const FAssetData& NewAssetData);
	void OnAssetRemoved(const struct FAssetData& AssetData);
	void FillAkGeometryMap(const TArray<FAssetData>& PhysicalMaterials, const TArray<FAssetData>& AcousticTextureAssets);
	void UpdateAkGeometryMap();

	bool bAkGeometryMapInitialized = false;
	TMap< UPhysicalMaterial*, UAkAcousticTexture* > PhysicalMaterialAcousticTextureMap;
	TMap< UPhysicalMaterial*, float > PhysicalMaterialOcclusionMap;
#endif

public:
	bool bRequestRefresh = false;
    mutable AutoConnectChanged OnAutoConnectChanged;
};

