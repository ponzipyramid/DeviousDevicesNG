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
Int[]   Function RebuildSlotMask(Actor akActor, Int[] aaSlotFilter)         global native
Int     Function FilterMask     (Actor akActor, int aiSlotMask)             global native

;Node hider
        Function HideWeapons    (Actor akActor)                             global native
        Function ShowWeapons    (Actor akActor)                             global native