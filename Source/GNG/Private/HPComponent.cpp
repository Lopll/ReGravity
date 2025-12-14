#include "HPComponent.h"

UHPComponent::UHPComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UHPComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHPComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UHPComponent::SetHP(int newHP)
{
	HP = FMath::Clamp(newHP, 0, MAX_HP);
	return HP > 0;
}

int UHPComponent::CalcDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	int dmgResult = dmgResult = (int) Damage;;
	if(DamageType->IsA(UDT_Environmental::StaticClass()))
	{
		if(DamageCauser == DamagedActor)
		{
			dmgResult = FMath::Clamp((int)Damage, 0, FallDamageLimit);
		}
	}
	return dmgResult;
}