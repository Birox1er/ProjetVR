#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FSoundCustomData.generated.h"

class USoundCue;
enum class ESoundCustomType : uint8;

USTRUCT(BlueprintType)
struct FSoundCustomData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESoundCustomType SoundType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* SoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Volume = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PitchMultiplier = 1.0f;
};
