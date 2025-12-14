#include "RagdollComponent.h"

URagdollComponent::URagdollComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void URagdollComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Skeleton = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();	
	ensureMsgf(Skeleton, TEXT("Skeletal mesh component not found!"));
	DefaultLocation = Skeleton->GetRelativeLocation();
	DefaultRotation = Skeleton->GetRelativeRotation();
	
	PhysConstraint = GetOwner()->FindComponentByClass<UPhysicsConstraintComponent>();
	ensureMsgf(PhysConstraint, TEXT("Physics constraint component not found!"));
	
	Root = GetOwner()->GetRootComponent();
}


void URagdollComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(bIsRagdollEnabled)
	{
		Skeleton->SetWorldLocation(GetOwner()->GetActorLocation(), false, nullptr, ETeleportType::ResetPhysics);
	}
}

void URagdollComponent::enableRagdoll()
{	
	bIsRagdollEnabled = true;
	Skeleton->SetSimulatePhysics(true);
	Skeleton->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PhysConstraint->SetConstrainedComponents((UPrimitiveComponent*)Root, NAME_None, Skeleton, FName(TEXT("spine_05")));
}

void URagdollComponent::disableRagdoll()
{
	bIsRagdollEnabled = false;
	Skeleton->SetSimulatePhysics(false);
	Skeleton->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
	Skeleton->SetRelativeRotation(DefaultRotation);
	Skeleton->SetRelativeLocation(DefaultLocation);
}