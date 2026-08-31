#pragma once

class Settings : public REX::TSingleton<Settings>
{
public:
	enum class DoNotDispel : std::uint32_t
	{
		kDisabled = 0,
		kOnActivate,
		kOnAll
	};

	enum class DetectionState : std::uint32_t
	{
		kDisabled = 0,
		kOnlyPlayer,
		kEveryone
	};

	void LoadSettings();

	[[nodiscard]] bool GetAllowRefractionFix() const { return invisibility.fixRefraction; }
	[[nodiscard]] bool GetAllowRefractBlood() const { return invisibility.refractBlood; }
	[[nodiscard]] bool GetAllowRefractArrows() const { return invisibility.refractAttachedArrows; }
	[[nodiscard]] bool GetAllowAlphaBlendFix() const { return invisibility.fixArmorAlphaBlend; }

	[[nodiscard]] const DoNotDispel GetInvisState() const { return static_cast<DoNotDispel>(invisibility.state.GetValue()); }
	[[nodiscard]] const DoNotDispel GetEtherealState() const { return static_cast<DoNotDispel>(etherealForm.state.GetValue()); }

	[[nodiscard]] const DetectionState GetInvisDetection() const { return static_cast<DetectionState>(invisibility.detectState.GetValue()); }
	[[nodiscard]] const DetectionState GetEtherealDetection() const { return static_cast<DetectionState>(etherealForm.detectState.GetValue()); }

	[[nodiscard]] bool ShouldMakeSuperInvisible(RE::Actor* a_target) const;

private:
	static constexpr auto path = R"(Data\SKSE\Plugins\po3_EnhancedInvisibility.ini)"sv;

	static constexpr auto section = "Invisibility"sv;
	static constexpr auto etherealSection = "Ethereal Form"sv;

	struct Invisibility
	{
		REX::TIniSetting<bool> fixRefraction{ section, "bRefractionShaderFix", true };
		REX::TIniSetting<bool> refractBlood{ section, "bDynamicBloodRefraction", true };
		REX::TIniSetting<bool> refractAttachedArrows{ section, "bDynamicAttachedArrowRefraction", true };
		REX::TIniSetting<bool> fixArmorAlphaBlend{ section, "bArmorAlphaBlendFix", true };

		REX::TIniSetting<std::uint32_t> state{ section, "iUninterruptedActions", std::to_underlying(DoNotDispel::kOnActivate) };
		REX::TIniSetting<std::uint32_t> detectState{ section, "iMakeUndetectable", std::to_underlying(DetectionState::kDisabled) };
	};

	struct EtherealForm
	{
		REX::TIniSetting<std::uint32_t> state{ etherealSection, "iUninterruptedActions", std::to_underlying(DoNotDispel::kOnActivate) };
		REX::TIniSetting<std::uint32_t> detectState{ etherealSection, "iMakeUndetectable", std::to_underlying(DetectionState::kDisabled) };
	};

	// members
	Invisibility invisibility{};
	EtherealForm etherealForm{};
};
