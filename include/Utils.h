
namespace DeviousDevices {
    namespace Utils {
        void ForEachReferenceInRange(
            RE::TESObjectREFR* origin, float radius,
            std::function<RE::BSContainer::ForEachResult(RE::TESObjectREFR& ref)> callback);


        void ForEachActorInRange(float a_range,
                                    std::function<void(RE::Actor* a_actor)> callback);
    }  // namespace Utils
}  // namespace DeviousDevices