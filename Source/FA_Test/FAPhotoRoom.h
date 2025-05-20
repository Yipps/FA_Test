// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FAPhotoRoom.generated.h"

class USpotLightComponent;

UCLASS()
class FA_TEST_API AFAPhotoRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFAPhotoRoom();

	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "PhotoRoom")
	void RotateMesh(FVector2D YawPitch);
	UFUNCTION(BlueprintCallable, Category = "PhotoRoom")
	void ZoomMesh(float ZoomAmount);
	void UpdateZoom();
	UFUNCTION(BlueprintCallable, Category = "PhotoRoom")
	void ResetMesh();
	UFUNCTION(BlueprintCallable, Category = "PhotoRoom")
	void SwapMesh(UStaticMesh* NewMesh);
	UFUNCTION(BlueprintCallable, Category = "PhotoRoom")
	void SetupRoom();
	UFUNCTION(BlueprintCallable, Category = "PhotoRoom")
	void StartRoom();
	UFUNCTION(BlueprintCallable, Category = "PhotoRoom")
	void StopRoom();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PhotoRoom")
	USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhotoRoom")
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhotoRoom")
	USceneCaptureComponent2D* SceneCapture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lights")
	USpotLightComponent* KeyLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lights")
	USpotLightComponent* FillLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lights")
	USpotLightComponent* BackLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhotoRoom")
	float CurrentZoom = 0.5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhotoRoom")
	float ZoomSpeed = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhotoRoom")
	float RotateSpeed = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhotoRoom")
	FRotator DefaultLocalRotation = FRotator(0, 0, 180);

	float MeshRadius = 0;
	FVector MeshBounds;
	FVector MeshCenter;
	FVector MeshCenterOffset;


};
