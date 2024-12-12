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
	UFUNCTION(BlueprintCallable)
	void PlayRandomSound(ESoundCustomType SoundType, const FVector& Location);
	UFUNCTION(BlueprintCallable)
	void PlayUISound(ESoundCustomType SoundType);
	UFUNCTION(BlueprintCallable)
	void PlayMusic(ESoundCustomType SoundType);
	UFUNCTION(BlueprintCallable)
	void StopMusic();
	UFUNCTION(BlueprintCallable)
	void SetVolume(float Volume);
	void SetPitch(float Pitch);

private:
	UPROPERTY()
	UDataTable* SoundDataTable;

	UPROPERTY()
	UAudioComponent* CurrentMusicComponent;

	FSoundCustomData* GetRandomSoundData(ESoundCustomType SoundType);
};

