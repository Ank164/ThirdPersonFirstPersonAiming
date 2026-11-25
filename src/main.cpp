#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

namespace
{
    constexpr auto scriptName = "ThirdPersonFirstPersonAiming";
    constexpr int noSpellDelivery = 404;

    struct CameraZoom
    {
        float target{};
        float current{};
    };

    CameraZoom thirdPersonZoom;

    RE::ThirdPersonState* GetThirdPersonState(RE::PlayerCamera& camera)
    {
        return static_cast<RE::ThirdPersonState*>(
            camera.GetRuntimeData().cameraStates[RE::CameraState::kThirdPerson].get());
    }

    bool SwitchToFirstPerson(RE::StaticFunctionTag*)
    {
        auto* camera = RE::PlayerCamera::GetSingleton();
        if (!camera) {
            return false;
        }

        if (auto* thirdPerson = GetThirdPersonState(*camera);
            thirdPerson && camera->currentState.get() == thirdPerson) {
            thirdPersonZoom = { thirdPerson->targetZoomOffset, thirdPerson->currentZoomOffset };
        }

        return camera->ForceFirstPerson();
    }

    bool SwitchToThirdPerson(RE::StaticFunctionTag*)
    {
        auto* camera = RE::PlayerCamera::GetSingleton();
        if (!camera) {
            return false;
        }

        auto* thirdPerson = GetThirdPersonState(*camera);
        const bool switched = camera->ForceThirdPerson();
        if (switched && thirdPerson) {
            thirdPerson->targetZoomOffset = thirdPersonZoom.target;
            thirdPerson->currentZoomOffset = thirdPersonZoom.current;
        }

        return switched;
    }

    int GetDeliveryTypeFromSpell(RE::StaticFunctionTag*, RE::SpellItem* spell)
    {
        return spell ? static_cast<int>(spell->data.delivery) : noSpellDelivery;
    }

    bool RegisterPapyrus(RE::BSScript::IVirtualMachine* vm)
    {
        vm->RegisterFunction("switchToFP", scriptName, SwitchToFirstPerson);
        vm->RegisterFunction("switchToTP", scriptName, SwitchToThirdPerson);
        vm->RegisterFunction("GetDeliveryTypeFromSpell", scriptName, GetDeliveryTypeFromSpell);
        SKSE::log::info("ThirdPersonFirstPersonAiming Papyrus functions registered");
        return true;
    }
}

SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
    SKSE::Init(skse);

    const auto* papyrus = SKSE::GetPapyrusInterface();
    return papyrus && papyrus->Register(RegisterPapyrus);
}
