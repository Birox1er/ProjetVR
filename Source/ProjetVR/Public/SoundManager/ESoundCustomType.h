#pragma once

class USoundCue;


UENUM(BlueprintType)
enum class ESoundCustomType : uint8
{
	Ambient,
	Music,
	PlayerAction,
	EnemyAction,
	UI,
	Cinematic,
	MusicBox,
};