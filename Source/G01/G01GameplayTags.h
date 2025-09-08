

#pragma once

#include "NativeGameplayTags.h"

namespace G01GameplayTags
{


	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Behavior_SurvivesDeath);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Mouse);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Stick);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Crouch);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_AutoRun);

	// actor 组件初始化状况控制
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_Spawned);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_DataAvailable);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_DataInitialized);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_GameplayReady);
};
