// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/CharacterAttributeSet.h"
#include "GamePlayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "CharacterBase.h"
#include "ARPGCplusplusEnemyCharacter.h"
#include "ARPGCplusplusCharacter.h"
#include "Player/PlayerStateBase.h"

UCharacterAttributeSet::UCharacterAttributeSet()
{
	Health = 0.0f;
	MaxHealth = Health;
	HealthRegenRate = 0.f;
}

void UCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
}

void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute()) {
		SetMaxHealth(GetMaxHealth());
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));

		if (GetHealth() <= 0) {
			UE_LOG(LogTemp, Display, TEXT("UCharacterAttributeSet::PostGameplayEffectExecute - Health less than 0"));
			FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
			UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();

			// Get the Source actor
			AActor* SourceActor = nullptr;
			AController* SourceController = nullptr;
			ACharacterBase* SourceCharacter = nullptr;
			if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
			{
				SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
				SourceController = Source->AbilityActorInfo->PlayerController.Get();
				if (SourceController == nullptr && SourceActor != nullptr)
				{
					if (APawn* Pawn = Cast<APawn>(SourceActor))
					{
						SourceController = Pawn->GetController();
					}
				}

				// Use the controller to find the source pawn
				if (SourceController)
				{
					SourceCharacter = Cast<ACharacterBase>(SourceController->GetPawn());
				}
				else
				{
					SourceCharacter = Cast<ACharacterBase>(SourceActor);
				}

				// Set the causer actor based on context if it's set
				if (Context.GetEffectCauser())
				{
					SourceActor = Context.GetEffectCauser();
				}
			}

			float Xp = 0.f;
			if (AARPGCplusplusEnemyCharacter* Enemy = Cast< AARPGCplusplusEnemyCharacter>(Data.Target.GetAvatarActor()))
			{
				Xp = Enemy->GrantedXp;

				if (AARPGCplusplusCharacter* Player = Cast< AARPGCplusplusCharacter>(SourceCharacter))
				{
					if (APlayerStateBase* StateBase = Cast< APlayerStateBase>(Player->GetPlayerState()))
					{
						StateBase->AddXp(Xp);
					}
				}
			}

			if (ACharacterBase* AvatarCharacter = Cast<ACharacterBase>(Data.Target.GetAvatarActor()))
			{
				AvatarCharacter->OnDeath();
			}
		}
	}
}

void UCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UCharacterAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, MaxHealth, OldMaxHealth);
}

void UCharacterAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, Health, OldHealth);
}

void UCharacterAttributeSet::OnRep_HealthRegenRate(const FGameplayAttributeData& OldHealthRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, HealthRegenRate, OldHealthRegenRate);
}
