#pragma once

#include "Settings.h"

namespace EnhancedInvisibility
{
	using DoNotDispel = Settings::DoNotDispel;
	using DetectionState = Settings::DetectionState;

	namespace MakeUninterrupted
	{
		struct detail
		{
			static void dispel_invisibility(RE::Actor* a_actor, RE::EffectArchetype a_archetype);
			static void dispel_ethereal_form(RE::Actor* a_actor, RE::EffectArchetype a_archetype);
		};
	}

	void Install();
}
