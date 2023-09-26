scriptName zadNativeFunctions Hidden

Form Function FindMatchingDevice(Actor akActor, Keyword kwd)  global native
bool Function FormHasKeywordString(form theForm, string kwd)  global native
bool Function Print(string msg) global native

; Apply expression from aaExpression to actor akActor
; aiControl & 0x01 -> Apply phonems     (0-15)
; aiControl & 0x02 -> Apply modifiers   (16-29)
float[] Function ApplyExpression(Actor akActor,float[] aaExpression, int aiControl = 0x2) global native

; Returns phonems and modifiers expression
float[] Function GetExpression(Actor akActor) global native

; Reset expression
; abPhonems = true -> phonems will be reset
; abModifiers = true -> modifiers will be reset
Function ResetExpression(Actor akActor, bool abPhonems = true, bool abModifiers = true) global native

; Converts faction array to float array based on faction rank
; aaFactions - array of faction
; aaDefaults - default numbers used instead of faction if actor is either rank -1 or not in faction
float[] Function FactionsToPreset(Actor akActor, Faction[] aaFactions, Int[] aaDefaults) global native

; Edits passed expression aaExpression (you can get it with GetExpression), and edits its phonems based on faction ranks and default values
; Note that this was mainly created to make proccessing of gag expressions in Devious Devices faster.. But can be technically used for other things too
float[] Function ApplyPhonemsFaction(Actor akActor, float[] aaExpression, Faction[] aaFactions, Int[] aaDefaults) global native


;Rebuild hider slots
Int[]   Function RebuildSlotMask(Actor akActor, Int[] aaSlotFilter)                 global native
Int     Function FilterMask     (Actor akActor, int aiSlotMask)                     global native

;Node hider
        Function HideWeapons    (Actor akActor)                                     global native
        Function ShowWeapons    (Actor akActor)                                     global native

; === Device database
; return render device based on passed inventory device
Armor    Function GetRenderDevice(Armor akInvDevice)                                global native
; return inventory device based on passed render device
Armor    Function GetInventoryDevice(Armor akRendDevice)                            global native
; return render device based on passed inventory device name - note that if there are multiple devices with same name, only first found will be returned
; I do not recommend using this, as when the device name will be edited, this function will stop returning intended device
Armor    Function GetDeviceByName(String asName)                                    global native
;return array of all mods which edit passed device
;array is ordered, where first element is original mod, and last element is the last editing mod
String[] Function GetEditingMods(Armor akInvDevice)                                 global native


; === device property reader
; These functions returns properties from passed inventory devices
;   if aiMode == 0 -> Property is read from LAST iteration of device after device is overwritten by other mods
;   if aiMode != 0 -> Property is read from FIRST iteretion of device before it gets overwritten by other mods (original value)
Form        Function GetPropertyForm        (Armor akInvDevice, String asPropertyName, int aiMode = 0)  global native
Int         Function GetPropertyInt         (Armor akInvDevice, String asPropertyName, int aiMode = 0)  global native
Float       Function GetPropertyFloat       (Armor akInvDevice, String asPropertyName, int aiMode = 0)  global native
Bool        Function GetPropertyBool        (Armor akInvDevice, String asPropertyName, int aiMode = 0)  global native
String      Function GetPropertyString      (Armor akInvDevice, String asPropertyName, int aiMode = 0)  global native
Form[]      Function GetPropertyFormArray   (Armor akInvDevice, String asPropertyName, int aiMode = 0)  global native
Int[]       Function GetPropertyIntArray    (Armor akInvDevice, String asPropertyName, int aiMode = 0)  global native
Float[]     Function GetPropertyFloatArray  (Armor akInvDevice, String asPropertyName, int aiMode = 0)  global native
Bool[]      Function GetPropertyBoolArray   (Armor akInvDevice, String asPropertyName, int aiMode = 0)  global native
String[]    Function GetPropertyStringArray (Armor akInvDevice, String asPropertyName, int aiMode = 0)  global native


; === equip rework
        Function SetManipulated (Actor akActor, Armor akInvDevice, bool abManip)    global native
bool    Function GetManipulated (Actor akActor, Armor akInvDevice)                  global native

; === Lib functions
; Return all devices
; aiMode - What type of device should be returned
;   aiMode = 0 -> Return all inventory devices
;   aiMode = 1 -> Return all render devices
; abWorn - If only worn devices should be returned
;   abWorn = False -> All devices will be returned
;   abWorn = True  -> Only worn devices will be returned
Armor[]  Function GetDevices(Actor akActor, int aiMode = 0, bool abWorn = False)    global native

; Return worn device based on passed main keyword (set on equip script)
Armor    Function GetWornDevice(Actor akActor, Keyword akKeyword)                   global native