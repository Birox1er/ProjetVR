
#include "USoundManager.h"
#include "Kismet/GameplayStatics.h"
#include "FSoundCustomData.h"
#include "Components/AudioComponent.h"

void USoundManager::Initialize(UDataTable* InSoundDataTable)
{
    SoundDataTable = InSoundDataTable;
}

FSoundCustomData* USoundManager::GetRandomSoundData(ESoundCustomType SoundType)
{
    if (!SoundDataTable) return nullptr;

    TArray<FSoundCustomData*> SoundArray;
    SoundDataTable->GetAllRows<FSoundCustomData>("", SoundArray);

    TArray<FSoundCustomData*> FilteredSounds;
    for (FSoundCustomData* SoundData : SoundArray)
    {
        if (SoundData && SoundData->SoundType == SoundType)
        {
            FilteredSounds.Add(SoundData);
        }
    }

    if (FilteredSounds.Num() > 0)
    {
        int32 RandomIndex = FMath::RandRange(0, FilteredSounds.Num() - 1);
        return FilteredSounds[RandomIndex];
    }

    return nullptr;
}

void USoundManager::PlayRandomSound(ESoundCustomType SoundType, const FVector& Location)
{
    FSoundCustomData* SoundData = GetRandomSoundData(SoundType);
    if (SoundData && SoundData->SoundCue)
    {
        UGameplayStatics::PlaySoundAtLocation(
            this,
            SoundData->SoundCue,
            Location,
            FRotator::ZeroRotator,
            SoundData->Volume,
            SoundData->PitchMultiplier
        );
    }
}

void USoundManager::PlayUISound(ESoundCustomType SoundType)
{
    FSoundCustomData* SoundData = GetRandomSoundData(SoundType);
    if (SoundData && SoundData->SoundCue)
    {
        UGameplayStatics::PlaySound2D(
            this,
            SoundData->SoundCue,
            SoundData->Volume,
            SoundData->PitchMultiplier
        );
    }
}

void USoundManager::PlayMusic(ESoundCustomType SoundType)
{
    StopMusic();

    FSoundCustomData* SoundData = GetRandomSoundData(SoundType);
    if (SoundData && SoundData->SoundCue)
    {
        CurrentMusicComponent = UGameplayStatics::CreateSound2D(
            this,
            SoundData->SoundCue,
            SoundData->Volume,
            SoundData->PitchMultiplier
        );
        if (CurrentMusicComponent)
        {
            CurrentMusicComponent->Play();
        }
    }
}

void USoundManager::StopMusic()
{
    if (CurrentMusicComponent)
    {
        CurrentMusicComponent->Stop();
        CurrentMusicComponent = nullptr;
    }
}