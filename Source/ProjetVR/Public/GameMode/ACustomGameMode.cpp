#include "ACustomGameMode.h"
#include "SoundManager/USoundManager.h"

ACustomGameMode::ACustomGameMode()
{
	// Set default values
}

void ACustomGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Create and initialize the SoundManager
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Init Sound Manager !"));	
	SoundManager = NewObject<USoundManager>(this);
	SoundManager->Initialize(SoundDataTable);

	// Start playing background music
	SoundManager->PlayMusic(ESoundCustomType::Music);
}

void ACustomGameMode::ChangeBackgroundMusic(ESoundCustomType NewMusicType)
{
	if (SoundManager)
	{
		SoundManager->StopMusic();
		SoundManager->PlayMusic(NewMusicType);
	}
}