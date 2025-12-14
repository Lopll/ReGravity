#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Actor.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Controller.h"
#include "DT_Environmental.h"
#include "DT_Actor.h"
#include "Engine/Engine.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/ConstructorHelpers.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Math/Vector.h"
#include "GameFramework/Character.h"

#include "HPComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GNG_API UHPComponent : public UActorComponent
{
	GENERATED_BODY()

private:	

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int MAX_HP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int HP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int FallDamageLimit = 60;
	
	UHPComponent();	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// if HP is not 0, returns true
	UFUNCTION(BlueprintCallable)
	bool SetHP(int newHP);
	
	UFUNCTION(BlueprintCallable)
	int CalcDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
