// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "AMusicBox.generated.h"

class USoundManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(OnCrankStateUpdate, bool, IsRunning, int, CranksGrabbed);
UCLASS()
class PROJETVR_API AAMusicBox : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AAMusicBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame	
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void OnCrankStateUpdated(bool IsRunning, int CranksGrabbed);
	void MusicEnded();
	UPROPERTY(BlueprintAssignable, Category = "Test")
	OnCrankStateUpdate OnTestDelegate;
	UFUNCTION(BlueprintCallable)
	void SetMusicTime (float Time);
	UFUNCTION(BlueprintCallable)
	void AddMusicTime (float Time);
	float MusicTime = 0.0f;
	UPointLightComponent* Light;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	UDataTable* SoundDataTable;

	UPROPERTY(EditAnywhere, Category = "Sound")
	float maxIntensity = 0.f;
	UPROPERTY(EditAnywhere, Category = "Sound")
	float maxRewind = 0.f;
	UPROPERTY(EditAnywhere, Category = "Sound")
	float timeToMaxRewind = 0.f;

	UPROPERTY()
	bool bIsPlaying = false;
	
private:
	UPROPERTY()	
	USoundManager* SoundManager;
	UPROPERTY()	
	AActor* CrankSystemActor;
	
};