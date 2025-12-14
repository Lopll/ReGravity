#pragma once

#include "Engine/Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Math/Rotator.h"
#include "Math/Vector.h"
#include "Math/Quat.h"
#include "Math/RotationMatrix.h"
#include "Math/UnrealMathUtility.h"

#include "OrientationComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GNG_API UOrientationComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	USceneComponent* OwnerRoot;
	UPROPERTY()
	USkeletalMeshComponent* Mesh;
	UPROPERTY()
	USpringArmComponent* SpringArm;
	UPROPERTY()
	UCameraComponent* Camera;
	
	UPROPERTY()
	bool bIsModifyingView = false;
	float targetFOV;
	float targetArmLength;
	    
protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "View")
	float MinPitch = -70;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "View")
	float MaxPitch = 70;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")
	bool bFreeCam = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "View")
	float FOV = 103;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "View")
	float ChangedFOV = 120;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "View")
	float ArmLength = 300;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "View")
	float ChangedArmLength = 320;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")
	float ViewInterpSpeed = 1;

	UOrientationComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void AddRotation(FRotator Rot);
	
	UFUNCTION(BlueprintCallable)
	void AdjustSpringArmRotationToGravity(FVector DefaultGravityDir, FVector NewGravityDir);
	
	UFUNCTION(BlueprintCallable)
	void ModifyView(float newFOV, float newArmLength);
};
