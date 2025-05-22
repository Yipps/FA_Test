// Fill out your copyright notice in the Description page of Project Settings.


#include "FAPhotoRoom.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Components/SpotLightComponent.h"
#include "Kismet/KismetRenderingLibrary.h"

// Sets default values
AFAPhotoRoom::AFAPhotoRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	SceneCapture->SetupAttachment(Root);
	SceneCapture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	SceneCapture->ShowFlags.Atmosphere = false;
	SceneCapture->ShowFlags.SkyLighting = false;
	SceneCapture->ShowFlags.VolumetricFog = false;
	SceneCapture->ShowOnlyActors.Add(this);
	SceneCapture->ShowOnlyComponents.Add(Mesh);
	SceneCapture->CaptureSource =  ESceneCaptureSource::SCS_FinalColorLDR;
	//USceneCaptureComponent2D::Show
	
	

	KeyLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("KeyLight"));
	KeyLight->SetupAttachment(Root);

	FillLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FillLight"));
	FillLight->SetupAttachment(Root);
	FillLight->SoftSourceRadius = 500;
	FillLight->OuterConeAngle = 65;
	
	BackLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("BackLight"));
	BackLight->SetupAttachment(Root);
	BackLight->SoftSourceRadius = 1000;
}

void AFAPhotoRoom::SetupRoom()
{
	
	ResetMesh();
	
	if (MeshRadius < 1)
		UE_LOG(LogTemp, Warning, TEXT("PhotoRoom mesh radius is suspiciously small"));

	
}

void AFAPhotoRoom::StartRoom()
{
	SceneCapture->Activate(true);
}

void AFAPhotoRoom::StopRoom()
{
	SceneCapture->Activate(false);
	UKismetRenderingLibrary::ClearRenderTarget2D(this,SceneCapture->TextureTarget, FColor::Black);
	
}

// Called when the game starts or when spawned
void AFAPhotoRoom::BeginPlay()
{
	Super::BeginPlay();
	SetupRoom();

	EnableInput(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void AFAPhotoRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFAPhotoRoom::RotateMesh(FVector2D YawPitch)
{
	
	FQuat CurrentRotation = Mesh->GetComponentQuat();

	// Step 3: Create a combined rotation for yaw and pitch (in local space)
	// FQuat YawRotation = FQuat(FRotator(0.f, YawPitch.X * RotateSpeed, 0.f)); // Add yaw (around Z-axis)
	// FQuat PitchRotation = FQuat(FRotator(YawPitch.Y * RotateSpeed, 0.f, 0.f)); // Add pitch (around X-axis)
	// FQuat CombinedRotation = PitchRotation * YawRotation;

	//Create the rotation offset
	FQuat RotationDelta = FQuat(FRotator(YawPitch.Y * RotateSpeed, YawPitch.X * RotateSpeed, 0.f));

	//Get the vector offset between mesh pivot and center
	MeshCenterOffset = Mesh->GetComponentLocation() - MeshCenter;

	//Apply the rotation offset to the mesh offset
	MeshCenterOffset = RotationDelta.RotateVector(MeshCenterOffset);

	//Combine the rotation of the current mesh
	FQuat NewRotation = RotationDelta * CurrentRotation;

	//Update rotation and apply mesh center offset
	Mesh->SetWorldLocationAndRotation(MeshCenter + MeshCenterOffset, NewRotation);

	//We've rotated the mesh, so the mesh center is different
	MeshCenter = Mesh->Bounds.Origin;


}

void AFAPhotoRoom::ZoomMesh(float ZoomAmount)
{
	CurrentZoom += -ZoomAmount * ZoomSpeed;
	CurrentZoom = FMath::Clamp(CurrentZoom, 0, 1);

	UpdateZoom();
	
}

void AFAPhotoRoom::UpdateZoom()
{
	//TODO Find a better way to determine a min and max zoom. Likely some bounds or camera functions that can be used
	float Distance = FMath::Lerp(MeshRadius + 10, MeshRadius * 2, CurrentZoom);

	//Keep the mesh centered on the camera
	FVector Direction = SceneCapture->GetForwardVector();

	//Apply magnitude to create the distance based on the lerp
	Direction *= Distance;

	//Apply the mesh center offset, otherwise the camera would be centered on the pivot
	Mesh->SetWorldLocation(Direction + SceneCapture->GetComponentLocation() + MeshCenterOffset);
	
}

void AFAPhotoRoom::ResetMesh()
{
	Mesh->SetRelativeRotation(DefaultLocalRotation);
	
	MeshRadius = Mesh->Bounds.SphereRadius;
	
	MeshCenter = Mesh->Bounds.Origin;
	MeshCenterOffset = Mesh->GetComponentLocation() - MeshCenter;
	
	CurrentZoom = 0.5;
	UpdateZoom();
	
}

void AFAPhotoRoom::SwapMesh(UStaticMesh* NewMesh)
{
	if (!NewMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to swap mesh with null mesh"));
		return;
	}

	//Clear frame
	UKismetRenderingLibrary::ClearRenderTarget2D(this,SceneCapture->TextureTarget, FColor::Black);

	//Removal all materials. This handles the case if the old mesh has MORE materials than the new mesh. It would stay if we didn't clear it all
	for (int i = 0; i < Mesh->GetNumMaterials(); i++)
	{
		Mesh->SetMaterial(i, nullptr);
	}
	
	Mesh->SetStaticMesh(NewMesh);
	
	for (int i = 0; i < Mesh->GetNumMaterials(); i++)
	{
		Mesh->SetMaterial(i, NewMesh->GetMaterial(i));
	}
	
	ResetMesh();
}

