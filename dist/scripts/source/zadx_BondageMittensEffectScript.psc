Scriptname zadx_BondageMittensEffectScript extends activemagiceffect  

zadlibs Property libs  Auto

Armor Property zad_DeviceHider Auto
bool Function isDeviousDevice(Form device)
    if device.HasKeyword(libs.zad_InventoryDevice) || device.HasKeyword(libs.zad_Lockable) 
        return true
    endif
    return false
EndFunction

bool Function isValidItem(Form item)
    ; the device hider is not tagged with a DD keyword, so we need to explicitly rule it out.
    If item.GetName() && (item.GetType() == 41 || (item.GetType() == 26 && !isDeviousDevice(Item)) || item.GetType() == 45)
        return true
    EndIf
    return false
EndFunction

Event OnEffectStart(Actor akTarget, Actor akCaster)
    if akTarget != libs.playerRef
        return
    EndIf
    while libs.hasAnyWeaponEquipped(akTarget)
        libs.stripweapons(akTarget)
    EndWhile
EndEvent