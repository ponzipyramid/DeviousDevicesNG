
namespace DeviousDevices {
    namespace Utils {
        void ForEachReferenceInRange(
            RE::TESObjectREFR* origin, float radius,
            std::function<RE::BSContainer::ForEachResult(RE::TESObjectREFR& ref)> callback);
    }  // namespace Utils
}  // namespace DeviousDevices