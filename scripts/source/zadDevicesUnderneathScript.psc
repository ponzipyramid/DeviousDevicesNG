scriptname zadDevicesUnderneathScript extends Quest

zadLibs Property libs Auto
import zadNativeFunctions
Armor Property zad_DeviceHider Auto
ArmorAddon Property zad_DeviceHiderAA Auto

int[] Property SlotMaskFilters Auto
int[] Property SlotMaskUsage Auto
int[] Property ShiftCache Auto

int Property SlotMask Auto ; Avoid repeated lookups


;; [30]: 0x00000001
;; [31]: 0x00000002
;; [32]: 0x00000004
;; [33]: 0x00000008
;; [34]: 0x00000010
;; [35]: 0x00000020
;; [36]: 0x00000040
;; [37]: 0x00000080
;; [38]: 0x00000100
;; [39]: 0x00000200
;; [40]: 0x00000400
;; [41]: 0x00000800
;; [42]: 0x00001000
;; [43]: 0x00002000
;; [44]: 0x00004000
;; [45]: 0x00008000
;; [46]: 0x00010000
;; [47]: 0x00020000
;; [48]: 0x00040000
;; [49]: 0x00080000
;; [50]: 0x00100000
;; [51]: 0x00200000
;; [52]: 0x00400000
;; [53]: 0x00800000
;; [54]: 0x01000000
;; [55]: 0x02000000
;; [56]: 0x04000000
;; [57]: 0x08000000
;; [58]: 0x10000000
;; [59]: 0x20000000

; Event OnInit()
; 	Maintenance()
; EndEvent


Function SetDefaultSlotMasks()
    SlotMaskFilters = new int[128]
    ShiftCache = new int [33]
    int i = 0
    while i <= 32
        ShiftCache[i] = Math.LeftShift(1, i)
        i += 1
    EndWhile
    ; SlotMaskFilters[2*4] = Math.LeftShift(1,26) ; For slot 32, hide slot 56.
    HideEquipment(32, 51) ; When slot 32 is equipped, hide slot 51 (Nipple Piercings).
    HideEquipment(32, 56) ; When slot 32 is equipped, hide slot 56 (Chastity Bra's).
    HideEquipment(32, 58) ; When slot 32 is equipped, hide slot 58 (Corsets).
    HideEquipment(32, 49) ; When slot 32 is equipped, hide slot 49 (Belts).
    
    ZadNativeFunctions.SyncSetting(SlotMaskFilters)
EndFunction


Function HideEquipment(int slot1, int slot2)
    if slot1 < 30 || slot1 > 61 || slot2 < 30 || slot2 > 61
        libs.Error("HideEquipment received out of bound slot number.")
    else
        int index = ((slot1 - 30) * 4)
        int i = 0
        while i < 4
            if SlotMaskFilters[index+i] == 0
                SlotMaskFilters[index+i] = ShiftCache[slot2 - 30]
                libs.Log("DevicesUnderneath Registered(" + index+i + ":" + (slot2 - 30)+")")
                return
            EndIf
            i += 1
        EndWhile
        libs.Error("Maximum number of equipment slots reached for slot "+ slot1 + " while trying to hide slot "+ slot2)
    EndIf
EndFunction


Function Maintenance()
    ZadNativeFunctions.SyncSetting(SlotMaskFilters)
    ;libs.Log("DevicesUnderneath::Maintenance()")
    ;zad_DeviceHiderAA = zad_DeviceHider.GetNthArmorAddon(0)
    ;if SlotMaskFilters.length <= 0 || ShiftCache.Length <= 0
    ;    SetDefaultSlotMasks()
    ;EndIf
    ;UpdateDeviceHiderSlot()
    
    ;TODO - Call here to native, and also add it in MCM
EndFunction

Function ApplySlotmask(Actor akActor)
    ;akActor.EquipItem(zad_DeviceHider, true, true)
    ;Int loc_slot = ZadNativeFunctions.FilterMask(akActor, SlotMask)
    ;if loc_slot != zad_DeviceHiderAA.GetSlotMask()
    ;    if loc_slot < 0
    ;        loc_slot = 0
    ;    EndIf
    ;    zad_DeviceHiderAA.SetSlotMask(loc_slot)
    ;    akActor.UnEquipItem(zad_DeviceHider, false, true)
    ;    akActor.EquipItem(zad_DeviceHider, true, true)
    ;EndIf
EndFunction

Function RebuildSlotmask(actor akActor)
    ;SlotMaskUsage = ZadNativeFunctions.RebuildSlotMask(akActor,SlotMaskFilters)
    ;SlotMask = SlotMaskUsage[128]
    ;ApplySlotMask(akActor)
EndFunction

Bool _HiderMutex = False
Function StartHiderMutex()
    if _HiderMutex ;destroy thread, no need to do the action multiple times
        return
    endif
    _HiderMutex = True
EndFunction

Function EndHiderMutex()
    _HiderMutex = False
EndFunction

Function UpdateDeviceHiderSlot()
    ;StartHiderMutex()
    ;int slot = libs.Config.DevicesUnderneathSlot - 1
    ;zad_DeviceHider.SetSlotMask(Math.LeftShift(1, slot))
    ;RebuildSlotMask(libs.PlayerRef)
    ;EndHiderMutex()
EndFunction
