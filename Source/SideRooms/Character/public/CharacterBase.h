// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterBase.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay();

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
//==== Movement / Input =============================== 
public:
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
		virtual void EnableMovement();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
		virtual void DisableMovement();

	UFUNCTION(Server, Reliable)
		void ServerRPCEnableMovement();		

	UFUNCTION(Server, Reliable)
		void ServerRPCDisableMovement();

protected:
	/** Called for movement input */
	virtual void Move(const FInputActionValue& Value);

	virtual void Sprint(const FInputActionValue& Value);

	virtual void StopSprint(const FInputActionValue& Value);

	virtual void Die();

//====CharacterStat, CharacterState============
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool GetIsSprinting() { return bIsSprinting; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetCurrentHP() { return CharacterCurrHP; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetMaxHP() { return CharacterMaxHP; }

protected:
	/** Character Max HP **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Stat")
		int32 CharacterMaxHP;

	/** Character Sprint speed */
	UPROPERTY(EditAnywhere, Category = "Gameplay|Stat")
		float SprintMultipleVal;

	/** Character Curr HP */
	int32 CharacterCurrHP;

	/** Character  */
	bool bIsSprinting = false;

///====Init Widget================
protected:
	//Init Widget & Input mode
	UFUNCTION(BlueprintImplementableEvent)
		void InitWidget();
};