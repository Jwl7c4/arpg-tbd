
#include "Player/PlayerStateBase.h"
#include "Abilities/CharacterAttributeSet.h"
#include <ARPGCplusplusCharacter.h>
#include <ARPGCplusplusPlayerController.h>

APlayerStateBase::APlayerStateBase()
{
	// If the NetUpdateFrequency is too low, there will be a delay on Ability activation / Effect application on the client.
	NetUpdateFrequency = 60.0f;

	// Create the Ability System Component sub-object.
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("Ability System Component");

	// Explicitly set the Ability System Component to replicate.
	AbilitySystemComponent->SetIsReplicated(true);

	// Sets the Ability System Component to use Full replication mode. This will replicate Gameplay Effects to everyone.
	AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Mixed;

	// Non Ability attributes
	CharacterAttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("CharacterAttributeSet"));
}

UAbilitySystemComponent* APlayerStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

float APlayerStateBase::GetHealth() const
{
	return CharacterAttributeSet->GetHealth();
}

float APlayerStateBase::GetMaxHealth() const
{
	return CharacterAttributeSet->GetMaxHealth();
}

float APlayerStateBase::GetHealthRegenRate() const
{
	return CharacterAttributeSet->GetHealthRegenRate();
}
