#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SoundManager/ESoundCustomType.h"
#include "AMyGameMode.generated.h"

class USoundManager;
class UDataTable;

UCLASS()
class PROJETVR_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameMode();

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void ChangeBackgroundMusic(ESoundCustomType NewMusicType);

private:
	UPROPERTY()
	USoundManager* SoundManager;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	UDataTable* SoundDataTable;
};
