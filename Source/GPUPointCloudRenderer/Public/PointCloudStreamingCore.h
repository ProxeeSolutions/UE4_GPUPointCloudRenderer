/*************************************************************************************************
* Copyright (C) Valentin Kraft - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Valentin Kraft <valentin.kraft@online.de>, http://www.valentinkraft.de, February 2018
**************************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"

DECLARE_STATS_GROUP(TEXT("GPUPointCloudRenderer"), STATGROUP_GPUPCR, STATCAT_Advanced);

class GPUPOINTCLOUDRENDERER_API FPointCloudStreamingCore
{
public:
	FPointCloudStreamingCore(UMaterialInstanceDynamic* pointCloudShaderDynInstance = nullptr) { mDynamicMatInstance = pointCloudShaderDynInstance; };
	~FPointCloudStreamingCore();
	//virtual unsigned int GetInstanceId() const { return _instanceId; };
	unsigned int GetPointCount() { return mPointCount; };

	void Update(float deltaTime);
	void UpdateDynamicMaterialForStreaming(UMaterialInstanceDynamic* pointCloudShaderDynInstance) { mDynamicMatInstance = pointCloudShaderDynInstance; };
	void SetInput(TArray<FLinearColor> &pointPositions, TArray<uint8> &pointColors, bool sortDataEveryFrame);
	void SetInput(TArray<FLinearColor> &pointPositions, TArray<FColor> &pointColors, bool sortDataEveryFrame);
	void SetInput(TArray<FVector> &pointPositions, TArray<FColor> &pointColors, bool sortDataEveryFrame);

private:
	void InitializeStreaming(unsigned int pointCount);
	void UpdateStreamingTextures();
	void UpdateShaderParameter();
	void SortPointCloudData();
	void FreeData();

	class UMaterialInstanceDynamic* mDynamicMatInstance = nullptr;
	unsigned int mPointCount = 0;

	float TotalElapsedTime = 0.f;	//#Temp?

	// CPU buffers
	TArray<FLinearColor> mPointPosData;
	TArray<FLinearColor>* mPointPosDataPointer = nullptr;
	TArray<uint8> mColorData;
	TArray<uint8>* mColorDataPointer = nullptr;
	TArray<FVector> mPointScalingData;

	// GPU texture buffers
	struct FUpdateTextureRegion2D* mUpdateTextureRegion = nullptr;
	UTexture2D* mPointPosTexture = nullptr;
	UTexture2D* mPointScalingTexture = nullptr;
	UTexture2D* mColorTexture = nullptr;
	
};

