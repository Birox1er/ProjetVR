#pragma once
#include "CoreMinimal.h"
#include "FSoundCustomData.h"
#include "USoundManager.generated.h"

class UDataTable;

UCLASS()
class PROJETVR_API USoundManager : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(UDataTable* SoundDataTable);
    
	void PlayRandomSound(ESoundCustomType SoundType, const FVector& Location);
	void PlayUISound(ESoundCustomType SoundType);
	void PlayMusic(ESoundCustomType SoundType);
	void StopMusic();
	void SetVolume(float Volume);
	void SetPitch(float Pitch);

private:
	UPROPERTY()
	UDataTable* SoundDataTable;

	UPROPERTY()
	UAudioComponent* CurrentMusicComponent;

	FSoundCustomData* GetRandomSoundData(ESoundCustomType SoundType);
};

