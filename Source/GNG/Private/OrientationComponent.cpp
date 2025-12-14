#include "OrientationComponent.h"

UOrientationComponent::UOrientationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UOrientationComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerRoot = GetOwner()->GetRootComponent();
	Mesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	SpringArm = GetOwner()->FindComponentByClass<USpringArmComponent>();
	Camera = GetOwner()->FindComponentByClass<UCameraComponent>();

	ensureMsgf(OwnerRoot, TEXT("Root component not found!"));
	ensureMsgf(Mesh, TEXT("Mesh component not found!"));
	ensureMsgf(SpringArm, TEXT("SpringArm component not found!"));
	ensureMsgf(Camera, TEXT("Camera component not found!"));
}


void UOrientationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (bIsModifyingView)
	{
		float newFOV = FMath::FInterpTo(Camera->FieldOfView, targetFOV, DeltaTime, ViewInterpSpeed);
		Camera->SetFieldOfView(newFOV);
		
		float newArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, targetArmLength, DeltaTime, ViewInterpSpeed);
		SpringArm->TargetArmLength = newArmLength;
		
		if (FMath::IsNearlyEqual(Camera->FieldOfView, targetFOV, 0.1f))
        {
            bIsModifyingView = false;
        }
	}	
}

void UOrientationComponent::AddRotation(FRotator Rot)
{
	FRotator currentRot = SpringArm->GetRelativeRotation();
	FQuat newQuat = currentRot.Quaternion();
	
	newQuat *= FQuat(FVector::UpVector, FMath::DegreesToRadians(Rot.Yaw));
	
	float desiredPitch = currentRot.Pitch + Rot.Pitch;
	if (bFreeCam or (desiredPitch > MinPitch && desiredPitch < MaxPitch))
	{
		newQuat *= FQuat(FVector::RightVector, FMath::DegreesToRadians(-Rot.Pitch));
	}
	
	if (bFreeCam)
	{
		SpringArm->SetRelativeRotation(newQuat.Rotator());
	}
	else
	{
		FRotator newRot = newQuat.Rotator();
		SpringArm->SetRelativeRotation(FRotator(newRot.Pitch, newRot.Yaw, currentRot.Roll));
	}
}

void UOrientationComponent::AdjustSpringArmRotationToGravity(FVector DefaultGravityDir, FVector NewGravityDir)
{
	FRotator currentRot = SpringArm->GetRelativeRotation();
	SpringArm->SetRelativeRotation(FRotator(currentRot.Pitch, currentRot.Yaw, 0));
}

void UOrientationComponent::ModifyView(float newFOV, float newArmLength)
{
	bIsModifyingView = true;
	targetFOV = newFOV;
	targetArmLength = newArmLength;
}
