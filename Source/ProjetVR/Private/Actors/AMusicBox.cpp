// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AMusicBox.h"


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
	Light = FindComponentByClass<UPointLightComponent>();
	
	CrankSystemActor = nullptr;
	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("CrankSystem"), ActorsWithTag);
	if (ActorsWithTag.Num() > 0)
	{
		CrankSystemActor = ActorsWithTag[0];
	}
}

// Called every frame
void AAMusicBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OnTestDelegate.AddDynamic(this, &AAMusicBox::OnCrankStateUpdated);
	if (bIsPlaying)
	{
		MusicTime = FMath::Clamp(MusicTime + (timeToMaxRewind/DeltaTime)*maxRewind, 0.0f, maxRewind); ;
	}
	if (MusicTime > 0.f and MusicTime-DeltaTime < 0.f)
	{
		MusicEnded();
	}
	MusicTime -= DeltaTime;
	if (MusicTime < 0.0f) MusicTime = 0.0f;
	if (MusicTime>0.f) {
		Light->Intensity = FMath::Clamp(MusicTime/(maxRewind/3), 0 , 1)  * maxIntensity;
		Light->MarkRenderStateDirty();
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


