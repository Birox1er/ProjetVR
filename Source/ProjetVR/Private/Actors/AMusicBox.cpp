// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AMusicBox.h"


#include "ToolBuilderUtil.h"
#include "GameMode/AMyGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SoundManager/USoundManager.h"


// Sets default values
AAMusicBox::AAMusicBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAMusicBox::BeginPlay()
{
	Super::BeginPlay();
	
	SoundManager = NewObject<USoundManager>(this);
	SoundManager->Initialize(SoundDataTable);
	SoundManager->PlayMusic(ESoundCustomType::MusicBox);

	TArray<USceneComponent*> ChildComponents;
	GetRootComponent()->GetChildrenComponents(true, ChildComponents);

	for (USceneComponent* Component : ChildComponents)
	{
		if (USpotLightComponent* SpotLight = Cast<USpotLightComponent>(Component))
		{
			Lights.Add(SpotLight);
		}
	}
	LightsPivot = FindComponentByTag<USceneComponent>("LightsPivot");
	CrankSystemActor = nullptr;
	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("CrankSystem"), ActorsWithTag);
	if (ActorsWithTag.Num() > 0)
	{
		CrankSystemActor = ActorsWithTag[0];
	}
}

void AAMusicBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	OnTestDelegate.AddDynamic(this, &AAMusicBox::OnCrankStateUpdated);
	if (bIsPlaying)
	{
		MusicTime = FMath::Clamp(MusicTime + (maxRewind/timeToMaxRewind)*DeltaTime, 0.0f, maxRewind); ;
	
	}
	if (MusicTime <0.f and bIsPlaying)
	{
		SoundManager->PlayMusic(ESoundCustomType::MusicBox);
	}
	if (MusicTime > 0.f and MusicTime-DeltaTime < 0.f)
	{
		MusicEnded();
	}
	FRotator CurrentRotation = LightsPivot->GetComponentRotation();
	CurrentRotation.Yaw += rotationBaseSpeed*FMath::Clamp(MusicTime/timeRemainingToFallOff, 0 , 1)*DeltaTime;
	LightsPivot->SetWorldRotation(CurrentRotation);
	SoundManager->SetVolume(maxVolume*FMath::Clamp(MusicTime/timeRemainingToFallOff, 0 , 1));
	SoundManager->SetPitch(FMath::Clamp(MusicTime/timeRemainingToFallOff, 0 , 1));
	MusicTime -= DeltaTime;
	if (MusicTime < 0.0f) MusicTime = 0.0f;
	if (MusicTime>0.f) {
		for (USpotLightComponent* Light : Lights)
		{
			if (Light)
			{
				Light->Intensity = FMath::Clamp(MusicTime/timeRemainingToFallOff, 0 , 1)  * maxIntensity;
				Light->OuterConeAngle = FMath::Clamp(maxOuterAngle*FMath::Clamp(MusicTime/timeRemainingToFallOff, 0 , 1), minOuterAngle, maxOuterAngle);
				Light->MarkRenderStateDirty();
			}
		}
	}
	
}

void AAMusicBox::OnCrankStateUpdated(bool IsRunning, int CranksGrabbed)
{
	UE_LOG(LogTemp, Log, TEXT("Crank State Updated from Blueprint: IsRunning = %s, CranksGrabbed = %d"), 
		IsRunning ? TEXT("True") : TEXT("False"), CranksGrabbed);
	bIsPlaying = IsRunning;
}

void AAMusicBox::MusicEnded()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Music Stopped"));
	SoundManager->StopMusic();
}
void AAMusicBox::SetMusicTime(float Time)
{
	MusicTime = Time;
}

void AAMusicBox::AddMusicTime(float Time)
{
	MusicTime += Time;
}


