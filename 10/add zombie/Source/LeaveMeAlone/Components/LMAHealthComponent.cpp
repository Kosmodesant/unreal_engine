// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "LMAHealthComponent.h"

// Sets default values for this component's properties
ULMAHealthComponent::ULMAHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool ULMAHealthComponent::IsDead() const
{
	return Health <= 0.0f;
}

bool ULMAHealthComponent::AddHealth(float NewHealth)
{
	if (IsDead() || IsHealthFull())
		return false;

	Health = FMath::Clamp(Health + NewHealth, 0.0f, MaxHealth);
	return true;
}

bool ULMAHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}


// Called when the game starts
void ULMAHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
	AActor* OwnerComponent = GetOwner();
	if (OwnerComponent)
	{
		OwnerComponent->OnTakeAnyDamage.AddDynamic(this, &ULMAHealthComponent::OnTakeAnyDamage);
	}
}

void ULMAHealthComponent::OnTakeAnyDamage(
	AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsDead()) return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}
