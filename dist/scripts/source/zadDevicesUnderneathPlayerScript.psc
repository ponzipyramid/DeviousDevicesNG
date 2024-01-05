Scriptname zadDevicesUnderneathPlayerScript extends ReferenceAlias

zadLibs Property libs Auto
import zadNativeFunctions

Bool Property Working Auto

Event OnPlayerLoadGame()
    libs.DevicesUnderneath.Maintenance()
    libs.PlayerRef.RemoveItem(libs.DevicesUnderneath.zad_DeviceHider, 999, true)
EndEvent

Function OnUpdate()
EndFunction