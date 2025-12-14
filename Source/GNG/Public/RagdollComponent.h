#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/EngineTypes.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Math/Rotator.h"
#include "Math/Vector.h"

#include "RagdollComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GNG_API URagdollComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	USkeletalMeshComponent* Skeleton;
	UPROPERTY()
	FVector DefaultLocation;
	UPROPERTY()
	FRotator DefaultRotation;
	
	UPROPERTY()
	USceneComponent* Root;
	UPROPERTY()
	UPhysicsConstraintComponent* PhysConstraint;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		URagdollComponent();
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsRagdollEnabled = false;

	UFUNCTION(BlueprintCallable)
	void enableRagdoll();
	UFUNCTION(BlueprintCallable)
	void disableRagdoll();
};
