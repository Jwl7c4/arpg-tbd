
#include "Player/PlayerStateBase.h"
#include "Abilities/CharacterAttributeSet.h"
#include "Character/ARPGCplusplusCharacter.h"
#include "Player/ARPGCplusplusPlayerController.h"
#include "Game/ARPGGameInstance.h"
#include "Kismet/GameplayStatics.h"

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

	CurrentLevel = 1;
	CurrentXp = 0.f;
	x = .07f;
	y = 2.f;
	NextLevelXpNeeded = NewLevelXpToGain(CurrentLevel);

	SaveGameIndex = -1;
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

void APlayerStateBase::AddXp(float AddXpAmount)
{
	CurrentXp += AddXpAmount;

	int preLevel = CurrentLevel;
	LevelUp();

	if (preLevel < CurrentLevel)
	{
		// todo - gameplay ability with effect/cue
		FGameplayTag GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.LevelUp"));
		AbilitySystemComponent->ExecuteGameplayCue(GameplayCueTag);
	}

	UARPGGameInstance* GameInstance = Cast<UARPGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	AARPGCplusplusCharacter* Character = Cast<AARPGCplusplusCharacter>(UGameplayStatics::GetPlayerController(this, 0)->GetCharacter());
	GameInstance->SaveCharacter(this, Character);

	OnXpUpdated.Broadcast();
}

void APlayerStateBase::LevelUp()
{
	if (CurrentXp >= NextLevelXpNeeded)
	{
		// increment level
		CurrentLevel++;

		// reset current xp + add any overcapped
		float OverLevelCapXp = CurrentXp - NextLevelXpNeeded;
		CurrentXp = 0;
		CurrentXp += OverLevelCapXp;

		// get new xp needed
		NextLevelXpNeeded = NewLevelXpToGain(CurrentLevel);

		if (CurrentXp > NextLevelXpNeeded)
		{
			// recursive call to get to next level
			LevelUp();
		}
	}
}

float APlayerStateBase::NewLevelXpToGain(float NewCharacterLevel)
{
	return pow(NewCharacterLevel / x, y);
}
