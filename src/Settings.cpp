#include "Settings.h"

void Settings::LoadSettings()
{
	const auto store = REX::FIniSettingStore::GetSingleton();
	store->Init(path.data(), "");

	store->Load();
	store->Save();
}

bool Settings::ShouldMakeSuperInvisible(RE::Actor* a_target) const
{
	constexpr auto hasEffectWithArchetype = [](RE::Actor* a_target, RE::EffectArchetype a_type)
	{
		auto effects = a_target->GetActiveEffectList();
		if (!effects) {
			return false;
		}

		RE::EffectSetting* setting = nullptr;
		for (auto& effect : *effects) {
			setting = effect ? effect->GetBaseObject() : nullptr;
			if (setting && setting->HasArchetype(a_type) && effect->flags.none(RE::ActiveEffect::Flag::kInactive) && effect->flags.none(RE::ActiveEffect::Flag::kDispelled)) {
				return true;
			}
		}
		return false;
	};

	if (hasEffectWithArchetype(a_target, RE::EffectArchetype::kInvisibility)) {
		const auto state = GetInvisDetection();
		return state == DetectionState::kEveryone || state == DetectionState::kOnlyPlayer && a_target->IsPlayerRef();
	}
	if (hasEffectWithArchetype(a_target, RE::EffectArchetype::kEtherealize)) {
		const auto state = GetEtherealDetection();
		return state == DetectionState::kEveryone || state == DetectionState::kOnlyPlayer && a_target->IsPlayerRef();
	}

	return false;
}
