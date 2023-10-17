Scriptname zadConfig extends SKI_ConfigBase Conditional

; The power of Emacs compels you.

; import/export vars
String File
int exportsettingsOID
int importsettingsOID

; Libraries
zadLibs Property libs Auto
zadBeltedAnims Property beltedAnims  Auto  

; Perks
Perk Property zad_keyCraftingEasy Auto ; Obsolete, will remove later
Perk Property zad_keyCraftingHard Auto ; Obsolete, will remove later.

; Config Variables
Int Property EscapeDifficulty = 4 Auto
Int Property CooldownDifficulty = 4 Auto
Int Property KeyDifficulty = 4 Auto
Bool Property GlobalDestroyKey = True Auto
Bool Property DisableLockJam = False Auto

int Property UnlockThreshold Auto
int thresholdDefault = 185
int Property ThresholdModifier Auto
int ThresholdModifierDefault = 0
float Property BeltRateMult = 1.5 Auto
float beltRateDefault = 1.5
float Property PlugRateMult = 3.0 Auto
float plugRateDefault = 3.0
int Property KeyCrafting Auto Conditional
int keyCraftingDefault = 1
bool Property NpcMessages = True Auto
bool npcMessagesDefault = true
bool Property PlayerMessages = True Auto
bool playerMessagesDefault = true

Float Property ArmbinderStruggleBaseChance = 5.0 Auto
Float ArmbinderStruggleBaseChanceDefault = 5.0
Int Property ArmbinderMinStruggle = 5 Auto
Int ArmbinderMinStruggleDefault = 5
Int Property YokeRemovalCostPerLevel = 200 Auto
Int YokeRemovalCostPerLevelDefault = 200

bool Property LogMessages = True Auto
bool logMessagesDefault = true
bool Property preserveAggro = True Auto
bool preserveAggroDefault = True
bool Property breastNodeManagement = false Auto
bool breastNodeManagementDefault = false
bool Property bellyNodeManagement = false Auto
bool bellyNodeManagementDefault = false

bool Property UseItemManipulation = False Auto
bool UseItemManipulationDefault = False

bool Property UseBoundCombat = True Auto
bool UseBoundCombatDefault = true
bool Property UseBoundCombatPerks = True Auto
bool UseBoundCombatPerksDefault = true

bool Property useBoundAnims =  true Auto
bool useBoundAnimsDefault = true
bool Property useAnimFilter =  true Auto
bool useAnimFilterDefault = true
bool Property useAnimFilterCreatures =  true Auto
bool useAnimFilterCreaturesDefault = true


; Blindfold
int Property blindfoldMode = 2 Auto ; 0 == DD's mode, 1 == DD's mode w/ leeches, 2 == leeches
int blindfoldModeDefault = 2
float Property blindfoldStrength = 0.5 Auto
float blindfoldStrengthDefault = 0.5
int Property darkfogStrength = 500 Auto
int Property darkfogStrength2 Auto
int darkfogStrengthDefault = 500

; HotKeys
int Property FurnitureNPCActionKey = 0xC9 Auto ; mapped to PgUp key
int FurnitureNPCActionKeyDefault = 0xC9

; Tooltips
bool Property BlindfoldTooltip Auto
bool Property GagTooltip Auto

; Events and Effects
float Property EventInterval = 1.5 Auto
float eventIntervalDefault = 1.5
int Property EffectVibrateChance = 25 Auto
int effectVibrateChanceDefault = 25
int Property EffectHealthDrainChance = 50 Auto
int effectHealthDrainChanceDefault = 50
int Property EffectManaDrainChance = 50 Auto
int EffectManaDrainChanceDefault = 50
int Property EffectStaminaDrainChance = 50 Auto
int EffectStaminaDrainChanceDefault = 50
int Property BaseMessageChance = 10 Auto
int baseMessageChanceDefault = 10
int Property BaseHornyChance = 5 Auto
int baseHornyChanceDefault = 5
int Property BaseBumpPumpChance = 17 Auto
int baseBumpPumpChanceDefault = 17
int Property numNpcs = 15 Auto Conditional
int numNpcsDefault = 15

; Sounds
float Property VolumeOrgasm = 1.0 Auto
float volumeOrgasmDefault = 1.0
float Property VolumeEdged = 1.0 Auto
float volumeEdgedDefault = 1.0
float Property VolumeVibrator = 0.5 Auto
float volumeVibratorDefault = 0.5
float Property VolumeVibratorNPC = 0.25 Auto
float volumeVibratorNPCDefault = 0.25
int Property RubberSoundMode = 0 Auto
int RubberSoundModeDefault = 0

; Quest Monitor Configuration 
bool Property ForbiddenTome = true Auto
bool ForbiddenTomeDefault = true
bool Property SergiusExperiment = true Auto
bool SergiusExperimentDefault = true
bool Property SurreptitiousStreets = false Auto
bool SurreptitiousStreetsDefault = false
bool Property RadiantMaster = false Auto
bool RadiantMasterDefault = false

; Surreptitious Streets Config
int Property ssSleepChance = 100 Auto
int ssSleepChanceDefault = 100
int Property ssTrapChance = 100 Auto
int ssTrapChanceDefault = 100
bool Property ssWarningMessages = false Auto
bool ssWarningMessagesDefault = false

; Radiant Master Configuration
float Property rmHeartbeatInterval = 2.0 Auto
float rmHeartbeatIntervalDefault = 2.0
float Property rmSummonHeartbeatInterval = 0.25 Auto
float rmSummonHeartbeatIntervalDefault = 0.25

; Devices Underneath Configuration
bool Property DevicesUnderneathEnabled = True Auto
Int Property DevicesUnderneathSlot = 12 Auto
int Property DevicesUnderneathSlotDefault = 12 Auto
bool Property UseQueueNiNode = False Auto
bool UseQueueNiNodeDefault = False

; Devious Expansion Configuration
bool Property bootsSlowdownToggle = True Auto Conditional
bool bootsSlowdownToggleDefault = True 
bool Property mittensDropToggle = True Auto Conditional
bool mittensDropToggleDefault = True 
Int Property HobbleSkirtSpeedDebuff = 50 Auto
Int HobbleSkirtSpeedDebuffDefault = 50
bool Property debugSigTerm = False Auto
bool Property debugFixDevices = False Auto
bool property lockmenuwhentied = true Auto
bool Property RegisterDevices = False Auto

;checks for OSL Aroused
Bool Property GotOSLA = False  Auto Hidden

;checks for SexLab Inflation Framework
Bool Property GotSLIF = False  Auto Hidden


; OID's
int debugFixDevicesOID
int debugSigTermOID
int thresholdOID
int beltRateOID
int plugRateOID
int keyCraftingOID
int thresholdModifierOID
int animsRegisterOID
int playerMessagesOID
int destroyKeyOID
int npcMessagesOID
int destroyKeyProbabilityOID
int destroyKeyJamChanceOID
int logMessagesOID
int eventIntervalOID
int effectVibrateChanceOID
int effectHealthDrainChanceOID
int effectManaDrainChanceOID
int effectStaminaDrainChanceOID
int baseMessageChanceOID
int baseHornyChanceOID
int baseBumpPumpChanceOID
int VolumeOrgasmOID
int VolumeEdgedOID
int VolumeVibratorOID
int VolumeVibratorNPCOID
int ForbiddenTomeOID
int SergiusExperimentOID
int SurreptitiousStreetsOID
int RadiantMasterOID
int ssSleepChanceOID
int ssTrapChanceOID
int rmHeartbeatIntervalOID
int rmSummonHeartbeatIntervalOID
int ssWarningMessagesOID
int numNpcsOID
int preserveAggroOID
int blindfoldModeOID
int blindfoldStrengthOID
int darkfogStrengthOID
int[] eventOIDs
int[] slotMaskOIDs
int DevicesUnderneathSlotOID
int UseQueueNiNodeOID
int breastNodeManagementOID
int bellyNodeManagementOID
int useBoundAnimsOID
int useAnimFilterOID
int useAnimFilterCreaturesOID
int bootsSlowdownToggleOID
int HobbleSkirtSpeedDebuffOID
int mittensDropToggleOID
int UseItemManipulationOID
int UseBoundCombatOID 
int UseBoundCombatPerksOID 
Int UseDeviceDifficultyEscapeOID
Int DeviceDifficultyCooldownOID
Int DeviceDifficultyModiferOID
Int DeviceDifficultyCatastrophicFailChanceOID
Int ArmbinderMinStruggleOID
Int ArmbinderStruggleBaseChanceOID
Int YokeRemovalCostPerLevelOID
Int EscapeDifficultyOID
Int CooldownDifficultyOID
Int KeyDifficultyOID
Int GlobalDestroyKeyOID
Int DisableLockJamOID
Int FurnitureNPCActionKeyOID
int lockmenuwhentiedOID
int RegisterDevicesOID
int RubberSoundModeOID

string[] Property EsccapeDifficultyList Auto
string[] difficultyList
string[] blindfoldList
string[] slotMasks
string[] SoundList
int[] SlotMaskValues

GlobalVariable Property zadDebugMode Auto

Function SetupBlindfolds()
	blindfoldList = new String[4]
	blindfoldList[0] = "DD blindfold"
	blindfoldList[1] = "DD blindfold w/ Leeches Effect"
	blindfoldList[2] = "Leeches Mode"
	blindfoldList[3] = "Dark Fog" ; if you change this entry, please alter the ConsoleUtil check in OnOptionMenuAccept() as well
EndFunction

Function SetupSoundDuration()
	SoundList = new String[4]
	SoundList[0] = "Never"
	SoundList[1] = "Rare"
	SoundList[2] = "Often"
	SoundList[3] = "Frequently" 
EndFunction

Function SetupEscapeDifficulties()
	; This can be extended as desired, but ALWAYS make it uneven length to centre the modifier at 0%
	EsccapeDifficultyList = new String[9]
	EsccapeDifficultyList[0] = "Born Slave [Hardest]"
	EsccapeDifficultyList[1] = "Submissive"
	EsccapeDifficultyList[2] = "Plaything"
	EsccapeDifficultyList[3] = "Handcuff Girl"
	EsccapeDifficultyList[4] = "Kinky [Default]"
	EsccapeDifficultyList[5] = "Questioning"
	EsccapeDifficultyList[6] = "Experimenting"
	EsccapeDifficultyList[7] = "First time"
	EsccapeDifficultyList[8] = "Vanilla [Easiest]"
EndFunction

Function SetupDifficulties()
	difficultyList = new String[4]
	difficultyList[0] = "Easy"
	difficultyList[1] = "Hard"
	difficultyList[2] = "Medium"
	difficultyList[3] = "Disabled"
EndFunction

Function SetupPages()
	Pages = new string[7]	
	Pages[0] = "Devices"
	pages[1] = "Animations"
	Pages[2] = "Events and Effects"
	Pages[3] = "Sounds"	
	Pages[4] = "Devices Underneath (1)"
	Pages[5] = "Devices Underneath (2)"
	Pages[6] = "Debug"
EndFunction

Function SetupSlotMasks()
	SlotMasks = new String[33]
	SlotMaskValues = new int[33]
	SlotMasks[0] = "None (Disabled) "
	int i = 1
	while i <= 32
		SlotMasks[i] = "Slot " + (30 + i - 1)
		SlotMaskValues[i] = Math.LeftShift(1, (i - 1))
		i += 1
	EndWhile
	SlotMasks[1] = "Head (30)"
	SlotMasks[2] = "Hair (31)"
	SlotMasks[3] = "Body - Full (32)"
	SlotMasks[4] = "Hands (33)"
	SlotMasks[5] = "Forearms (34)"
	SlotMasks[6] = "Amulet (35)"
	SlotMasks[7] = "Ring (36)"
	SlotMasks[8] = "Feet (37)"
	SlotMasks[9] = "Calves (38)"
	SlotMasks[10] = "Shield (39)"
	SlotMasks[11] = "Tail (40)"
	SlotMasks[12] = "Device Hider + Long Hair (41)"
	SlotMasks[13] = "Circlet (42)"
	SlotMasks[14] = "Ears (43)"
	SlotMasks[15] = "Gags (44)"
	SlotMasks[16] = "Collar (45)"
	SlotMasks[17] = "Armbinders / Yokes / Cloaks (46)"
	SlotMasks[18] = "Backpacks (47)"
	SlotMasks[19] = "Plugs (Anal) (48)"
	SlotMasks[20] = "Chastity Belt (49)"
	SlotMasks[21] = "Vaginal Piercings (50)"
	SlotMasks[22] = "Nipple Piercings (51)"
	SlotMasks[23] = "SoS (52)"
	SlotMasks[24] = "Cuffs (Legs) (53)"

	SlotMasks[26] = "Blindfold (55)"
	SlotMasks[27] = "Chastity Bra (56)"
	SlotMasks[28] = "Plug Vaginal (57)"
	SlotMasks[29] = "Harnesses / Corsets (58)"
	SlotMasks[30] = "Cuffs (Arms) / Armbinder (59)"

EndFunction

Event OnConfigInit()
	libs.Log("Building mcm menu.")
	SetupPages()
	SetupDifficulties()
	SetupEscapeDifficulties()
	SetupBlindfolds()
	SetupSoundDuration()
	CheckForSoftDepends()
	SlotMaskOIDS = new int[128]
EndEvent

Function CheckForSoftDepends()

	If Game.IsPluginInstalled("OSLAroused.esp")
		GotOSLA = True 		;OSL Aroused is here
	Else
		GotOSLA = False     ;not here
	EndIf
	
	If Game.IsPluginInstalled("SexLab Inflation Framework.esp")
		GotSLIF = True  ;SexLab Inflation Framework is here
	Else
		GotSLIF = False ;not here
	EndIf

EndFunction

int Function GetVersion()
	return 30 ; mcm menu version
EndFunction

Event OnVersionUpdate(int newVersion)
	libs.Log("OnVersionUpdate("+newVersion+"/"+CurrentVersion+")")
	if newVersion != CurrentVersion
		SlotMaskOIDS = new int[128]
		SetupPages()
		SetupDifficulties()
		SetupEscapeDifficulties()
		SetupBlindfolds()
		SetupSoundDuration()
		eventOIDs = new int[125]
		if KeyCrafting == keyCraftingDefault && !libs.PlayerRef.HasPerk(zad_keyCraftingEasy) && !libs.PlayerRef.HasPerk(zad_keyCraftingHard)
			libs.PlayerRef.AddPerk(zad_keyCraftingHard)
		EndIf
		if !darkfogStrength
			darkfogStrength = darkfogStrengthDefault
		EndIf
	EndIf	
EndEvent

bool Function isWearingRestraints()	
	If libs.PlayerRef.WornHasKeyword(libs.zad_Lockable) 
		return true
	else
		return false
	endif
endfunction

Event OnPageReset(string page)
	Libs.Log("OnPageReset("+page+")")
	if (page == "")
		int offset = 100

		int width = Utility.GetIniInt("iSize W:Display")

		if width && width >= 0
			offset = width / 20
		endIf

		LoadCustomContent("DeviousIntegrationTitle.dds", 100, 0)
		return
	else
		UnloadCustomContent()
	EndIf	
	bool restrained = isWearingRestraints()
	
	If page == "Devices"
		if restrained && lockmenuwhentied
			AddHeaderOption("This menu is locked")
			AddHeaderOption("while wearing restraints")
		else
			SetCursorFillMode(TOP_TO_BOTTOM)		
			AddHeaderOption("Device Difficulty")
			EscapeDifficultyOID = AddMenuOption("Difficulty Modifier", EsccapeDifficultyList[EscapeDifficulty])
			CooldownDifficultyOID = AddMenuOption("Cooldown Modifier", EsccapeDifficultyList[CooldownDifficulty])
			KeyDifficultyOID = AddMenuOption("Keybreak Modifier", EsccapeDifficultyList[KeyDifficulty])
			GlobalDestroyKeyOID = AddToggleOption("Consume Keys", GlobalDestroyKey)
			DisableLockJamOID = AddToggleOption("Disable Lock Jam", DisableLockJam)
			AddHeaderOption("Belt Arousal Options")
			beltRateOID = AddSliderOption("Arousal rate belt multiplier", beltRateMult, "{1}")
			plugRateOID = AddSliderOption("Arousal rate plugged multiplier", plugRateMult, "{1}")
			AddHeaderOption("Blindfold Options")
			blindfoldModeOID = AddMenuOption("Blindfold Mode", blindfoldList[blindfoldMode])
            if blindfoldMode < 3 ;all except dark fog
                blindfoldStrengthOID = AddSliderOption("Blindfold Strength", blindfoldStrength, "{2}")
                darkfogStrengthOID = AddSliderOption("Dark Fog Strength", darkfogStrength, "{0}",OPTION_FLAG_DISABLED)
            else
                blindfoldStrengthOID = AddSliderOption("Blindfold Strength", blindfoldStrength, "{2}",OPTION_FLAG_DISABLED)
                darkfogStrengthOID = AddSliderOption("Dark Fog Strength", darkfogStrength, "{0}")
            endif
			
			AddHeaderOption("Bra Options")
			if libs.PlayerRef.WornHasKeyword(libs.zad_DeviousBra)
				breastNodeManagementOID = AddToggleOption("Breast Node Management", breastNodeManagement,OPTION_FLAG_DISABLED)
			else
				breastNodeManagementOID = AddToggleOption("Breast Node Management", breastNodeManagement)
			EndIf
			AddHeaderOption("Belly Options")
			if libs.PlayerRef.WornHasKeyword(libs.zad_DeviousCorset)||libs.PlayerRef.WornHasKeyword(libs.zad_DeviousBelt)
				bellyNodeManagementOID = AddToggleOption("Belly Node Management", bellyNodeManagement,OPTION_FLAG_DISABLED)
			else
				bellyNodeManagementOID = AddToggleOption("Belly Node Management", bellyNodeManagement)
			EndIf
			SetCursorPosition(1) ; Move cursor to top right position
			lockmenuwhentiedOID = AddToggleOption("Lock this menu when tied", lockmenuwhentied)			
			bootsSlowdownToggleOID = AddToggleOption("Boots Slowdown Effect", bootsSlowdownToggle)
			mittensDropToggleOID = AddToggleOption("Hardcore Bondage Mittens", mittensDropToggle)
			HobbleSkirtSpeedDebuffOID = AddSliderOption("Hobble Skirt Debuff Strength", HobbleSkirtSpeedDebuff, "{0}")			
			FurnitureNPCActionKeyOID = AddKeyMapOption("Furniture NPC Action Key", FurnitureNPCActionKey)
			AddHeaderOption("Restraints Options")
			UseBoundCombatOID = AddToggleOption("Enable Bound Combat", UseBoundCombat)
			UseBoundCombatPerksOID = AddToggleOption("Enable Bound Combat Perks", UseBoundCombatPerks)
			UseItemManipulationOID = AddToggleOption("Enable Lock Manipulation", UseItemManipulation)
		EndIf
	ElseIf page == "Animations"
		SetCursorFillMode(TOP_TO_BOTTOM)		
		AddHeaderOption("Animation Options")
		;useAnimFilterOID = AddToggleOption("Use Animation Filter", useAnimFilter)
		preserveAggroOID = AddToggleOption("Preserve Scene Aggressiveness", preserveAggro)
		useBoundAnimsOID = AddToggleOption("Use Bound Animations", useBoundAnims)
		useAnimFilterCreaturesOID = AddToggleOption("Use Animation Filter for Creatures", useAnimFilterCreatures)
	ElseIf page == "Events and Effects"
		SetCursorFillMode(TOP_TO_BOTTOM)
		AddHeaderOption("Global Events/Effects Configuration")
		eventIntervalOID = AddSliderOption("Polling Interval", EventInterval, "{2}")		
		numNpcsOID = AddSliderOption("Number of NPC's slotted", numNpcs, "{1}")
		AddHeaderOption("Polled Events Configuration ("+libs.EventSlots.Slotted+"):")
		int i = 0
		while i < libs.EventSlots.Slotted
			eventOIDs[i] = AddSliderOption(libs.EventSlots.Slots[i].Name+" Chance", libs.EventSlots.Slots[i].Probability, "{1}")
			i += 1
		EndWhile
	ElseIf page == "Sounds"
		SetCursorFillMode(TOP_TO_BOTTOM)
		AddHeaderOption("Audio Configuration")
		VolumeOrgasmOID = AddSliderOption("Orgasm Volume", VolumeOrgasm, "{3}")
		VolumeEdgedOID = AddSliderOption("Edged Volume", VolumeEdged, "{3}")
		VolumeVibratorOID = AddSliderOption("Player Vibrator Volume ", VolumeVibrator, "{3}")	
		VolumeVibratorNPCOID = AddSliderOption("NPC Vibrator Volume ", VolumeVibratorNPC, "{3}")	
		RubberSoundModeOID = AddMenuOption("Rubber Sound Frequency", SoundList[RubberSoundMode])
	ElseIf page == "Devices Underneath (1)"
		SetupSlotMasks()
		SetCursorFillMode(TOP_TO_BOTTOM)
		DevicesUnderneathSlotOID = AddMenuOption("Item Hider Slot", SlotMasks[DevicesUnderneathSlot])
		UseQueueNiNodeOID = AddToggleOption("Use QueueNiNode", UseQueueNiNode)
		; AddMenuOption("Item Hider Slot", SlotMasks[DevicesUnderneathSlot])
		int i = 1
		while i < 16
			int index = (i - 1) * 4
			int j = 0
			AddHeaderOption(SlotMasks[i])
			while j < 4
				slotMaskOIDs[index + j] = AddMenuOption(SlotMasks[i] + " #"+j, SlotMasks[LookupSlotMask(index+j)])
				j += 1
			EndWhile
			if i == 8
				SetCursorPosition(1) ; Move cursor to top right position
			EndIf
			i += 1
		EndWhile
	ElseIf page == "Devices Underneath (2)"
		SetupSlotMasks()
		SetCursorFillMode(TOP_TO_BOTTOM)
		int i = 16
		while i < 32
			int index = (i - 1) * 4
			int j = 0
			AddHeaderOption(SlotMasks[i])
			while j < 4
				slotMaskOIDs[index + j] = AddMenuOption(SlotMasks[i] + " #"+j, SlotMasks[LookupSlotMask(index+j)])
				j += 1
			EndWhile
			if i == 23
				SetCursorPosition(1) ; Move cursor to top right position
			EndIf
			i += 1
		EndWhile	
	ElseIf page == "Debug"
		SetCursorFillMode(TOP_TO_BOTTOM)								
		SetCursorPosition(1) ; Move cursor to top right position		
		AddHeaderOption("Message Visibility Settings")
		npcMessagesOID = AddToggleOption("Show NPC Messages", NpcMessages)
		playerMessagesOID = AddToggleOption("Show Player Messages", PlayerMessages)	   		
		logMessagesOID = AddToggleOption("Enable Debug Logging", LogMessages)		
		exportsettingsOID = AddTextOption("Export Settings", "EXPORT")		
		importsettingsOID = AddTextOption("Import settings", "IMPORT")
		RegisterDevicesOID = AddTextOption("Register Devices", "Do It!")
		;debugFixDevicesOID = AddTextOption("Fix broken devices", "Do It!")
		debugSigTermOID = AddTextOption("Terminate DD quests", "Do It!")
	Endif	
EndEvent

Event OnOptionKeyMapChange(Int Option, Int keyCode, String conflictControl, String conflictName)
	Bool Continue = True
	If (keyCode == 1)
		keyCode = 0
		conflictControl = ""
	Endif
	If (conflictControl != "")
		String msg
		If conflictName != ""
			msg = "This key is already mapped to:\n'" + conflictControl + "'\n(" + conflictName + ")\n\nAre you sure you want to continue?"
		Else
			msg = "This key is already mapped to:\n'" + conflictControl + "'\n\nAre you sure you want to continue?"
		Endif
		Continue = ShowMessage(msg, True, "$Yes", "$No")
	Endif		
	If Continue
		If Option == FurnitureNPCActionKeyOID
			FurnitureNPCActionKey = keyCode			
		Endif
		SetKeymapOptionValue(Option, keyCode)
		SendModEvent("zad_RegisteredMCMKeys")		
	Endif
EndEvent

Event OnOptionMenuOpen(int option)
	if option == keyCraftingOID
		SetMenuDialogOptions(difficultyList)
		SetMenuDialogStartIndex(KeyCrafting)
		SetMenuDialogDefaultIndex(keyCraftingDefault)
	ElseIf option == blindfoldModeOID
		SetMenuDialogOptions(blindfoldList)
		SetMenuDialogStartIndex(BlindfoldMode)
		SetMenuDialogDefaultIndex(blindfoldModeDefault)
	ElseIf option == RubberSoundModeOID
		SetMenuDialogOptions(SoundList)
		SetMenuDialogStartIndex(RubberSoundMode)
		SetMenuDialogDefaultIndex(RubberSoundModeDefault)
	ElseIf option == EscapeDifficultyOID
		SetMenuDialogOptions(EsccapeDifficultyList)
		SetMenuDialogStartIndex(EscapeDifficulty)
		SetMenuDialogDefaultIndex(4)
	ElseIf option == CooldownDifficultyOID
		SetMenuDialogOptions(EsccapeDifficultyList)
		SetMenuDialogStartIndex(CooldownDifficulty)
		SetMenuDialogDefaultIndex(4)
	ElseIf option == KeyDifficultyOID
		SetMenuDialogOptions(EsccapeDifficultyList)
		SetMenuDialogStartIndex(KeyDifficulty)
		SetMenuDialogDefaultIndex(4)	
	ElseIf option == DevicesUnderneathSlotOID
		SetMenuDialogOptions(SlotMasks)
		SetMenuDialogStartIndex(DevicesUnderneathSlot)
		SetMenuDialogDefaultIndex(DevicesUnderneathSlotDefault)
	EndIf
	int i = 0
	while i < 128
		if option == slotMaskOIDs[i]
			SetMenuDialogOptions(SlotMasks)
			SetMenuDialogStartIndex(LookupSlotMask(i))
			SetMenuDialogDefaultIndex(0)
		EndIf
		i += 1
	EndWhile
EndEvent

Function CheckRemovePerk(Perk perkName)
	if libs.PlayerRef.HasPerk(perkName)
		libs.PlayerRef.RemovePerk(perkName)
	EndIf	
EndFunction

Function UpdateCraftingPerks(int index)
	if index == 0
		CheckRemovePerk(zad_keyCraftingHard)
		libs.PlayerRef.AddPerk(zad_keyCraftingEasy)
	elseif index == 1
		CheckRemovePerk(zad_keyCraftingEasy)
		libs.PlayerRef.AddPerk(zad_keyCraftingHard)
	Else
		CheckRemovePerk(zad_keyCraftingEasy)
		CheckRemovePerk(zad_keyCraftingHard)
	EndIf
EndFunction

Event OnOptionMenuAccept(int option, int index)
	if option == keyCraftingOID
		UpdateCraftingPerks(index)
		KeyCrafting = index
		SetMenuOptionValue(keyCraftingOID, difficultyList[KeyCrafting])
	ElseIf option == EscapeDifficultyOID
		EscapeDifficulty = index
		SetMenuOptionValue(EscapeDifficultyOID, EsccapeDifficultyList[EscapeDifficulty])	
	ElseIf option == CooldownDifficultyOID
		CooldownDifficulty = index
		SetMenuOptionValue(CooldownDifficultyOID, EsccapeDifficultyList[CooldownDifficulty])
	ElseIf option == KeyDifficultyOID
		KeyDifficulty = index
		SetMenuOptionValue(KeyDifficultyOID, EsccapeDifficultyList[KeyDifficulty])	
	ElseIf option == RubberSoundModeOID
		RubberSoundMode = index
		SetMenuOptionValue(RubberSoundModeOID, SoundList[RubberSoundMode])	
	ElseIf option == blindfoldModeOID
		If BlindfoldMode == 3 && index != 3 ; Old mode was Dark Fog, remove it
			if Weather.GetSkyMode() == 0
				ConsoleUtil.ExecuteCommand("ts")
			endif
			ConsoleUtil.ExecuteCommand("setfog 0 0") 
		EndIf
		If (index == 3) 
			int cotest = ConsoleUtil.GetVersion()
			if !cotest
				ShowMessage("This mode requires ConsoleUtil which doesn't seem to be installed.")
				return
			endif
		Endif
		BlindfoldMode = index		
		SetMenuOptionValue(BlindfoldModeOID, blindfoldList[blindfoldMode])
        ForcePageReset()
		game.ForceFirstPerson()
		game.ForceThirdPerson()
		libs.UpdateControls()
        SendModEvent("zadBlindfoldEffectUpdate")
	ElseIf option == DevicesUnderneathSlotOID
		DevicesUnderneathSlot = index
		libs.DevicesUnderneath.UpdateDeviceHiderSlot()
		SetMenuOptionValue(DevicesUnderneathSlotOID, SlotMasks[DevicesUnderneathSlot])
	EndIf
	int i = 0
	while i < 128
		if option == slotMaskOIDs[i]
			int value = 0
			value = Math.LeftShift(1, (index - 1))
			libs.Log("Index:" + index + " = " + value + "/" + SlotMaskValues.find(value))
			libs.DevicesUnderneath.SlotMaskFilters[i] = value
			SetMenuOptionValue(option, SlotMasks[index])
            ZadNativeFunctions.SyncSetting(libs.DevicesUnderneath.SlotMaskFilters)
		EndIf
		i += 1
	EndWhile
EndEvent

Event OnOptionSliderOpen(int option)
	;Libs.Log("OnOptionSliderOpen("+option+")")
	int i = 0;
	while i < libs.EventSlots.Slotted
		if option == eventOIDs[i]
			SetSliderDialogStartValue(libs.EventSlots.Slots[i].Probability)
			SetSliderDialogDefaultValue(libs.EventSlots.Slots[i].DefaultProbability)
			SetSliderDialogRange(0,100)
			SetSliderDialogInterval(1)			
			return
		EndIf
		i+= 1
	EndWhile
	if option == thresholdOID
		SetSliderDialogStartValue(UnlockThreshold)
		SetSliderDialogDefaultValue(thresholdDefault)
		SetSliderDialogRange(1,350)
		SetSliderDialogInterval(1)
	elseif option == thresholdModifierOID
		SetSliderDialogStartValue(ThresholdModifier)
		SetSliderDialogDefaultValue(thresholdModifierDefault)
		SetSliderDialogRange(0,100)
		SetSliderDialogInterval(1)
	elseif option == blindfoldStrengthOID
		SetSliderDialogStartValue(blindfoldStrength)
		SetSliderDialogDefaultValue(blindfoldStrengthDefault)
		SetSliderDialogRange(0.0,1.0)
		SetSliderDialogInterval(0.01)
	elseif option == darkfogStrengthOID
		SetSliderDialogStartValue(darkfogStrength)
		SetSliderDialogDefaultValue(darkfogStrengthDefault)
		SetSliderDialogRange(50,3000)
		SetSliderDialogInterval(50)
	elseif option == beltRateOID
		SetSliderDialogStartValue(BeltRateMult)
		SetSliderDialogDefaultValue(beltRateDefault)
		SetSliderDialogRange(1,5)
		SetSliderDialogInterval(0.1)	
	elseif option == plugRateOID
		SetSliderDialogStartValue(PlugRateMult)
		SetSliderDialogDefaultValue(plugRateDefault)
		SetSliderDialogRange(1,5)
		SetSliderDialogInterval(0.1)
	elseif option == eventIntervalOID
		SetSliderDialogStartValue(EventInterval)
		SetSliderDialogDefaultValue(eventIntervalDefault)
		SetSliderDialogRange(0.5, 12)
		SetSliderDialogInterval(0.05)
	elseIf option == effectVibrateChanceOID
		SetSliderDialogStartValue(EffectVibrateChance)
		SetSliderDialogDefaultValue(effectVibrateChanceDefault)
		SetSliderDialogRange(1, 100)
		SetSliderDialogInterval(1)
	elseIf option == effectHealthDrainChanceOID
		SetSliderDialogStartValue(EffectHealthDrainChance)
		SetSliderDialogDefaultValue(effectHealthDrainChanceDefault)
		SetSliderDialogRange(1, 100)
		SetSliderDialogInterval(1)
	elseIf option == effectManaDrainChanceOID
		SetSliderDialogStartValue(EffectManaDrainChance)
		SetSliderDialogDefaultValue(effectManaDrainChanceDefault)
		SetSliderDialogRange(1, 100)
		SetSliderDialogInterval(1)
	elseIf option == effectStaminaDrainChanceOID
		SetSliderDialogStartValue(EffectStaminaDrainChance)
		SetSliderDialogDefaultValue(effectStaminaDrainChanceDefault)
		SetSliderDialogRange(1, 100)
		SetSliderDialogInterval(1)
	elseIf option == baseMessageChanceOID
		SetSliderDialogStartValue(BaseMessageChance)
		SetSliderDialogDefaultValue(baseMessageChanceDefault)
		SetSliderDialogRange(1, 100)
		SetSliderDialogInterval(1)
	elseIf option == baseHornyChanceOID
		SetSliderDialogStartValue(BaseHornyChance)
		SetSliderDialogDefaultValue(baseHornyChanceDefault)
		SetSliderDialogRange(1, 100)
		SetSliderDialogInterval(1)
	elseIf option == baseBumpPumpChanceOID
		SetSliderDialogStartValue(BaseBumpPumpChance)
		SetSliderDialogDefaultValue(baseBumpPumpChanceDefault)
		SetSliderDialogRange(1, 100)
		SetSliderDialogInterval(1)
	elseIf option == VolumeOrgasmOID
		SetSliderDialogStartValue(VolumeOrgasm)
		SetSliderDialogDefaultValue(VolumeOrgasmDefault)
		SetSliderDialogRange(0, 1)
		SetSliderDialogInterval(0.01)
	elseIf option == VolumeEdgedOID
		SetSliderDialogStartValue(VolumeEdged)
		SetSliderDialogDefaultValue(VolumeEdgedDefault)
		SetSliderDialogRange(0, 1)
		SetSliderDialogInterval(0.01)
	elseIf option == VolumeVibratorOID
		SetSliderDialogStartValue(VolumeVibrator)
		SetSliderDialogDefaultValue(VolumeVibratorDefault)
		SetSliderDialogRange(0, 1)
		SetSliderDialogInterval(0.01)
	elseIf option == VolumeVibratorNPCOID
		SetSliderDialogStartValue(VolumeVibratorNPC)
		SetSliderDialogDefaultValue(VolumeVibratorNPCDefault)
		SetSliderDialogRange(0, 1)
		SetSliderDialogInterval(0.01)
	elseIf option == ssSleepChanceOID
		SetSliderDialogStartValue(ssSleepChance)
		SetSliderDialogDefaultValue(ssSleepChanceDefault)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
	elseIf option == ssTrapChanceOID
		SetSliderDialogStartValue(ssTrapChance)
		SetSliderDialogDefaultValue(ssTrapChanceDefault)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
	elseIf option == rmHeartbeatIntervalOID
		SetSliderDialogStartValue(rmHeartbeatInterval)
		SetSliderDialogDefaultValue(rmHeartbeatIntervalDefault)
		SetSliderDialogRange(0.5, 24)
		SetSliderDialogInterval(0.01)
	elseIf option == rmSummonHeartbeatIntervalOID
		SetSliderDialogStartValue(rmSummonHeartbeatInterval)
		SetSliderDialogDefaultValue(rmSummonHeartbeatIntervalDefault)
		SetSliderDialogRange(0.125, 12)
		SetSliderDialogInterval(0.01)
	elseIf option == numNpcsOID
		SetSliderDialogStartValue(numNpcs)
		SetSliderDialogDefaultValue(numNpcsDefault)
		SetSliderDialogRange(5, 20)
		SetSliderDialogInterval(1)	
	elseIf option == ArmbinderStruggleBaseChanceOID
		SetSliderDialogStartValue(ArmbinderStruggleBaseChance)
		SetSliderDialogDefaultValue(ArmbinderStruggleBaseChanceDefault)
		SetSliderDialogRange(0.0, 100.0)
		SetSliderDialogInterval(0.5)
	elseIf option == ArmbinderMinStruggleOID
		SetSliderDialogStartValue(ArmbinderMinStruggle)
		SetSliderDialogDefaultValue(ArmbinderMinStruggleDefault)
		SetSliderDialogRange(0, 50)
		SetSliderDialogInterval(1)
	elseIf option == YokeRemovalCostPerLevelOID
		SetSliderDialogStartValue(YokeRemovalCostPerLevel)
		SetSliderDialogDefaultValue(YokeRemovalCostPerLevelDefault)
		SetSliderDialogRange(0, 5000)
		SetSliderDialogInterval(50)   
	elseIf option == HobbleSkirtSpeedDebuffOID
        SetSliderDialogStartValue(HobbleSkirtSpeedDebuff)
        SetSliderDialogDefaultValue(HobbleSkirtSpeedDebuffDefault)
        SetSliderDialogRange(25, 70)
        SetSliderDialogInterval(1)
	Endif
EndEvent

Event OnOptionSelect(int option)
	;Libs.Log("OnOptionSelect("+option+")")	
	if option == animsRegisterOID
		beltedAnims.LoadAnimations()
		SetTextOptionValue(animsRegisterOID, "Done.")
	elseIf (option == lockmenuwhentiedOID)
        lockmenuwhentied = !lockmenuwhentied
        SetToggleOptionValue(lockmenuwhentiedOID, lockmenuwhentied)	
	elseif option == npcMessagesOID
		NpcMessages = !NpcMessages
		SetToggleOptionValue(npcMessagesOID, NpcMessages)
	elseif option == playerMessagesOID
		PlayerMessages = !PlayerMessages
		SetToggleOptionValue(playerMessagesOID, PlayerMessages)	
	elseif option == preserveAggroOID
		PreserveAggro = !PreserveAggro
		SetToggleOptionValue(PreserveAggroOID, PreserveAggro)
	elseif option == useBoundAnimsOID
		useBoundAnims = !useBoundAnims
		SetToggleOptionValue(useBoundAnimsOID, useBoundAnims)
	elseif option == useAnimFilterOID
		useAnimFilter = !useAnimFilter
		SetToggleOptionValue(useAnimFilterOID, useAnimFilter)		
	elseif option == useAnimFilterCreaturesOID
		useAnimFilterCreatures = !useAnimFilterCreatures
		SetToggleOptionValue(useAnimFilterCreaturesOID, useAnimFilterCreatures)
	elseif option == logMessagesOID
		 LogMessages = !LogMessages
		SetToggleOptionValue(logMessagesOID, LogMessages)	
	elseif option == ForbiddenTomeOID
		 ForbiddenTome = !ForbiddenTome
		SetToggleOptionValue(ForbiddenTomeOID, ForbiddenTome)
	elseif option == SergiusExperimentOID
		 SergiusExperiment = !SergiusExperiment
		SetToggleOptionValue(SergiusExperimentOID, SergiusExperiment)
	elseif option == SurreptitiousStreetsOID
		 SurreptitiousStreets = !SurreptitiousStreets
		SetToggleOptionValue(SurreptitiousStreetsOID, SurreptitiousStreets)
	elseif option == RadiantMasterOID
		 RadiantMaster = !RadiantMaster
		SetToggleOptionValue(RadiantMasterOID, RadiantMaster)	
	elseif option == ssWarningMessagesOID
		 ssWarningMessages = !ssWarningMessages
		SetToggleOptionValue(ssWarningMessagesOID, ssWarningMessages)
	elseif option == UseQueueNiNodeOID
		 UseQueueNiNode = !UseQueueNiNode
		SetToggleOptionValue(UseQueueNiNodeOID, UseQueueNiNode)
	elseif option == bootsSlowdownToggleOID
		 bootsSlowdownToggle = !bootsSlowdownToggle
		SetToggleOptionValue(bootsSlowdownToggleOID, bootsSlowdownToggle)
	elseif option == mittensDropToggleOID
		 mittensDropToggle = !mittensDropToggle
		SetToggleOptionValue(mittensDropToggleOID, mittensDropToggle)	
	elseif option == breastNodeManagementOID
		breastNodeManagement = !breastNodeManagement
		SetToggleOptionValue(breastNodeManagementOID, breastNodeManagement)
	elseif option == bellyNodeManagementOID
		bellyNodeManagement = !bellyNodeManagement
		SetToggleOptionValue(bellyNodeManagementOID, bellyNodeManagement)
	elseif option == UseBoundCombatOID
		UseBoundCombat = !UseBoundCombat
		SetToggleOptionValue(UseBoundCombatOID, UseBoundCombat)
	elseif option == UseItemManipulationOID
		UseItemManipulation = !UseItemManipulation		
		SetToggleOptionValue(UseItemManipulationOID, UseItemManipulation)	
	elseif option == UseBoundCombatPerksOID
		UseBoundCombatPerks = !UseBoundCombatPerks
		SetToggleOptionValue(UseBoundCombatPerksOID, UseBoundCombatPerks)	
	elseif option == GlobalDestroyKeyOID
		GlobalDestroyKey = !GlobalDestroyKey
		SetToggleOptionValue(GlobalDestroyKeyOID, GlobalDestroyKey)	
	elseif option == DisableLockJamOID
		DisableLockJam = !DisableLockJam
		SetToggleOptionValue(DisableLockJamOID, DisableLockJam)	
	elseIf (option == exportsettingsOID)
		If ShowMessage("Are you sure?")
			ExportSettings()	
			ForcePageReset()		
		Endif
	elseIf (option == importsettingsOID)
		If ShowMessage("Are you sure?")
			ImportSettings()		
			ForcePageReset()
		Endif
	elseif option == debugSigTermOID
		If ShowMessage("WARNING:\nThis function will try to remove all DD items. Wiping quest items may result in broken quest states! This feature is intended to be used for debug purposes and as a last resort only! Using it to escape DD devices is strongly discouraged.\n\nAre you sure?")
			;Utility.Wait(0.1)
			If ShowMessage("LAST WARNING:\n Using this function may result in unrecoverable, broken quest states! Do NOT use this function to escape inconvenient restraints!\n\nAre you REALLY sure you want to proceed?")
				debugSigTerm = true
				libs.UnregisterForUpdate()
				libs.RegisterForSingleUpdate(1)
				SetTextOptionValue(debugSigTermOID, "Ok! Exit Menu now!")	
			EndIf
		EndIf
	elseif option == debugFixDevicesOID
		If ShowMessage("This function will try to fix any broken devices equipped on the player. It can not be used to escape working devices.")			
			debugFixDevices = true
			libs.UnregisterForUpdate()
			libs.RegisterForSingleUpdate(1)
			SetTextOptionValue(debugFixDevicesOID, "Ok! Exit Menu now!")				
		EndIf
	elseif option == RegisterDevicesOID
		If ShowMessage("WARNING:\nThis function will activate the deprecated device database for DD expansion devices. Some legacy mods might need this database to continue working. It is NOT recommended to register devices unless required by a specific legacy mod you want to continue using. This feature will be retired in a future release of DD. Mod authors should update their mods.")			
			RegisterDevices = true
			libs.UnregisterForUpdate()
			libs.RegisterForSingleUpdate(1)
			SetTextOptionValue(RegisterDevicesOID, "Ok! Exit Menu now!")				
		EndIf
	EndIf
EndEvent

Event OnOptionDefault(int option)
	Libs.Log("OnOptionDefault("+option+")")	
	int i = 0
	while i < libs.EventSlots.Slotted
		if option == eventOIDs[i]
			libs.EventSlots.Slots[i].Probability = libs.EventSlots.Slots[i].DefaultProbability
			SetSliderOptionValue(eventOIDs[i], libs.EventSlots.Slots[i].DefaultProbability, "{1}")
			return
		EndIf
		i+= 1
	EndWhile
	if (option == thresholdOID)
		UnlockThreshold = thresholdDefault
		SetSliderOptionValue(thresholdOID, thresholdDefault, "{0}")
	elseif (option == thresholdModifierOID)
		ThresholdModifier = ThresholdModifierDefault
		SetSliderOptionValue(thresholdModifierOID, thresholdModifierDefault, "{0}")
	elseif (option == lockmenuwhentiedOID)
		lockmenuwhentied = True
		SetToggleOptionValue(lockmenuwhentiedOID, True)
	elseif (option == blindfoldStrengthOID)
		blindfoldStrength = blindfoldStrengthDefault
		SetSliderOptionValue(blindfoldStrengthOID, blindfoldStrengthDefault, "{2}")
        SendModEvent("zadBlindfoldEffectUpdate")
	elseif (option == darkfogStrengthOID)
		darkfogStrength = darkfogStrengthDefault
		SetSliderOptionValue(darkfogStrengthOID, darkfogStrengthDefault, "{0}")
        SendModEvent("zadBlindfoldEffectUpdate")
	elseIf (option == beltRateOID)
		BeltRateMult = beltRateDefault
		SetSliderOptionValue(beltRateOID, beltRateDefault, "{1}")
	elseIf (option == plugRateOID)
		PlugRateMult = plugRateDefault
		SetSliderOptionValue(plugRateOID, plugRateDefault, "{1}")
	elseIf (option == keyCraftingOID)
		UpdateCraftingPerks(keyCraftingDefault)
		KeyCrafting = keyCraftingDefault
		SetMenuOptionValue(keyCraftingOID, difficultyList[KeyCrafting])
	elseIf (option == blindfoldModeOID)
		BlindfoldMode = BlindfoldModeDefault
		SetMenuOptionValue(BlindfoldModeOID, blindfoldList[BlindfoldMode])
	elseIf (option == RubberSoundModeOID)
		RubberSoundMode = RubberSoundModeDefault
		SetMenuOptionValue(RubberSoundModeOID, SoundList[RubberSoundMode])
	elseIf (option == DevicesUnderneathSlotOID)
		DevicesUnderneathSlot = DevicesUnderneathSlotDefault
		SetMenuOptionValue(DevicesUnderneathSlotOID, SlotMasks[DevicesUnderneathSlot])
	elseIf (option == npcMessagesOID)
		NpcMessages = npcMessagesDefault
		SetToggleOptionValue(npcMessagesOID, npcMessagesDefault)
	elseIf (option == playerMessagesOID)
		PlayerMessages = playerMessagesDefault
		SetToggleOptionValue(playerMessagesOID, playerMessagesDefault)	
	elseIf (option == PreserveAggroOID)
		PreserveAggro = PreserveAggroDefault
		SetToggleOptionValue(PreserveAggroOID, PreserveAggroDefault)
	elseIf (option == useBoundAnimsOID)
		useBoundAnims = useBoundAnimsDefault
		SetToggleOptionValue(useBoundAnimsOID, useBoundAnimsDefault)
	elseIf (option == useAnimFilterOID)
		useAnimFilter = useAnimFilterDefault
		SetToggleOptionValue(useAnimFilterOID, useAnimFilterDefault)
	elseIf (option == useAnimFilterCreaturesOID)
		useAnimFilterCreatures = useAnimFilterCreaturesDefault
		SetToggleOptionValue(useAnimFilterCreaturesOID, useAnimFilterCreaturesDefault)	
	elseIf (option == logMessagesOID)
		LogMessages = logMessagesDefault
		SetToggleOptionValue(logMessagesOID, LogMessages)
	elseIf (option == eventIntervalOID)
		EventInterval = eventIntervalDefault
		SetToggleOptionValue(eventIntervalOID, eventIntervalDefault)
	elseIf (option == effectVibrateChanceOID)
		EffectVibrateChance = effectVibrateChanceDefault
		SetSliderOptionValue(effectVibrateChanceOID, effectVibrateChanceDefault, "{1}")
	elseIf (option == effectHealthDrainChanceOID)
		EffectHealthDrainChance = effectHealthDrainChanceDefault
		SetSliderOptionValue(effectHealthDrainChanceOID, effectHealthDrainChanceDefault, "{1}")
	elseIf (option == effectManaDrainChanceOID)
		EffectManaDrainChance = effectManaDrainChanceDefault
		SetSliderOptionValue(effectManaDrainChanceOID, effectManaDrainChanceDefault, "{1}")
	elseIf (option == effectStaminaDrainChanceOID)
		EffectStaminaDrainChance = effectStaminaDrainChanceDefault
		SetSliderOptionValue(effectStaminaDrainChanceOID, effectStaminaDrainChanceDefault, "{1}")
	elseIf (option == baseMessageChanceOID)
		BaseMessageChance = baseMessageChanceDefault
		SetSliderOptionValue(baseMessageChanceOID, baseMessageChanceDefault, "{1}")
	elseIf (option == baseHornyChanceOID)
		BaseHornyChance = baseHornyChanceDefault
		SetSliderOptionValue(baseHornyChanceOID, baseHornyChanceDefault, "{1}")
	elseIf (option == baseBumpPumpChanceOID)
		BaseBumpPumpChance = BaseBumpPumpChanceDefault
		SetSliderOptionValue(baseBumpPumpChanceOID, BaseBumpPumpChanceDefault, "{1}")
	elseIf (option == VolumeOrgasmOID)
		VolumeOrgasm = VolumeOrgasmDefault
		SetSliderOptionValue(VolumeOrgasmOID, VolumeOrgasmDefault, "{3}")
	elseIf (option == VolumeEdgedOID)
		VolumeEdged = VolumeEdgedDefault
		SetSliderOptionValue(VolumeEdgedOID, VolumeEdgedDefault, "{3}")
	elseIf (option == VolumeVibratorOID)
		VolumeVibrator = VolumeVibratorDefault
		SetSliderOptionValue(VolumeVibratorOID, VolumeVibratorDefault, "{3}")
	elseIf (option == VolumeVibratorNPC)
		VolumeVibratorNPC = VolumeVibratorNPCDefault
		SetSliderOptionValue(VolumeVibratorNPCOID, VolumeVibratorNPCDefault, "{3}")
	elseif option == ForbiddenTomeOID
		ForbiddenTome = ForbiddenTomeDefault
		SetToggleOptionValue(ForbiddenTomeOID, ForbiddenTome)
	elseif option == SergiusExperimentOID
		SergiusExperiment = SergiusExperimentDefault
		SetToggleOptionValue(SergiusExperimentOID, SergiusExperiment)
	elseif option == SurreptitiousStreetsOID
		SurreptitiousStreets = SurreptitiousStreetsDefault
		SetToggleOptionValue(SurreptitiousStreetsOID, SurreptitiousStreets)
	elseif option == RadiantMasterOID
		RadiantMaster = RadiantMasterDefault
		SetToggleOptionValue(RadiantMasterOID, RadiantMaster)	
	elseIf (option == ssSleepChanceOID)
		ssSleepChance = ssSleepChanceDefault
		SetSliderOptionValue(ssSleepChanceOID, ssSleepChanceDefault, "{1}")
	elseIf (option == ssTrapChanceOID)
		ssTrapChanceDefault = ssTrapChanceDefault
		SetSliderOptionValue(ssTrapChanceOID, ssTrapChanceDefault, "{1}")
	elseIf (option == rmHeartbeatIntervalOID)
		rmHeartbeatInterval = rmHeartbeatIntervalDefault
		SetSliderOptionValue(rmHeartbeatIntervalOID, rmHeartbeatIntervalDefault, "{3}")
	elseIf (option == rmSummonHeartbeatIntervalOID)
		rmSummonHeartbeatInterval = rmSummonHeartbeatIntervalDefault
		SetSliderOptionValue(rmSummonHeartbeatIntervalOID, rmSummonHeartbeatIntervalDefault, "{3}")	
	elseIf (option == ssWarningMessagesOID)
		ssWarningMessages = ssWarningMessagesDefault
		SetToggleOptionValue(ssWarningMessagesOID, ssWarningMessagesDefault)
	elseIf (option == UseQueueNiNodeOID)
		UseQueueNiNode = UseQueueNiNodeDefault
		SetToggleOptionValue(UseQueueNiNodeOID, UseQueueNiNodeDefault)
	elseIf (option == bootsSlowdownToggleOID)
		bootsSlowdownToggle = bootsSlowdownToggleDefault
		SetToggleOptionValue(bootsSlowdownToggleOID, bootsSlowdownToggleDefault)
	elseIf (option == mittensDropToggleOID)
		mittensDropToggle = mittensDropToggleDefault
		SetToggleOptionValue(mittensDropToggleOID, mittensDropToggleDefault)
	elseIf (option == numNpcsOID)
		numNpcs = numNpcsDefault
		SetSliderOptionValue(numNpcsOID, numNpcs, "{1}")	
	elseIf (option == breastNodeManagementOID)
		breastNodeManagement = breastNodeManagementDefault
		SetToggleOptionValue(breastNodeManagementOID, breastNodeManagement)
	elseIf (option == bellyNodeManagementOID)
		bellyNodeManagement = bellyNodeManagementDefault
		SetToggleOptionValue(bellyNodeManagementOID, bellyNodeManagement)
	elseIf (option == UseBoundCombatOID)
		UseBoundCombat = UseBoundCombatDefault
		SetToggleOptionValue(UseBoundCombatOID, UseBoundCombat)	
	elseIf (option == UseItemManipulationOID)
		UseItemManipulation = UseItemManipulationDefault		
		SetToggleOptionValue(UseItemManipulationOID, UseItemManipulation)			
	elseIf (option == UseBoundCombatPerksOID)
		UseBoundCombatPerks = UseBoundCombatDefault
		SetToggleOptionValue(UseBoundCombatPerksOID, UseBoundCombatPerks)	
	elseIf (option == ArmbinderStruggleBaseChanceOID)
		ArmbinderStruggleBaseChance = ArmbinderStruggleBaseChanceDefault
		SetSliderOptionValue(ArmbinderStruggleBaseChanceOID, ArmbinderStruggleBaseChance)	
	elseIf (option == ArmbinderMinStruggleOID)
		ArmbinderMinStruggle = ArmbinderMinStruggleDefault
		SetSliderOptionValue(ArmbinderMinStruggleOID, ArmbinderMinStruggle)	
	elseIf (option == YokeRemovalCostPerLevelOID)
		YokeRemovalCostPerLevel = YokeRemovalCostPerLevelDefault
		SetSliderOptionValue(YokeRemovalCostPerLevelOID, YokeRemovalCostPerLevel)
	elseIf (option == FurnitureNPCActionKeyOID)
		FurnitureNPCActionKey = FurnitureNPCActionKeyDefault
		SetSliderOptionValue(FurnitureNPCActionKeyOID, FurnitureNPCActionKey)
		SendModEvent("zad_RegisteredMCMKeys")
	endIf
EndEvent

Event OnOptionHighlight(int option)
	int i = 0
	while i < libs.EventSlots.Slotted
		if option == eventOIDs[i]
			string help = libs.EventSlots.Slots[i].help
			if help == ""
				help = "Configure the probability for a "+libs.EventSlots.Slots[i].Name +" event to occur."
			EndIf
			SetInfoText(help+"\nDefault:"+libs.EventSlots.Slots[i].DefaultProbability)
			return
		EndIf
		i+= 1
	EndWhile

	;Libs.Log("OnOptionHighlight("+option+")")			
	if (option == thresholdOID)
		SetInfoText("Base escape difficulty threshold. Higher is harder, lower is easier. At skill 100 and threshold 185, you would have a 15% chance to escape if not particularly aroused. At skill 100 and threshold 150, you would have a 50% chance to escape, and so forth. Note, that this is the base threshold, and that your actual milage will vary depending on the skill you attempt to escape with.\nDefault: "+thresholdDefault)
	elseif (option == lockmenuwhentiedOID)
		SetInfoText("Locks out access to the difficulty settings when the player character is restrained.\nThis is for players who want a more hardcore experience.")
	elseif (option == thresholdModifierOID)
		SetInfoText("The Unlock Threshold will be increased by this much every time the player successfully escapes a device.\nDefault:"+thresholdModifierDefault)
	elseif (option == blindfoldStrengthOID)
		SetInfoText("Controls the strength of the blindfold effect.\nDefault:"+blindfoldStrengthDefault)
	elseif (option == darkfogStrengthOID)
		SetInfoText("Controls the strength of the dark fog effect (requires ConsoleUtil mod to work).\nDefault:"+darkfogStrengthDefault)
	elseIf (option == beltRateOID)
		SetInfoText("Arousal exposure multiplier while belted.\nDefault: "+beltRateDefault)
	elseIf (option == plugRateOID)
		SetInfoText("Arousal exposure multiplier while belted/plugged.\nDefault: "+plugRateDefault)
	elseIf (option == keyCraftingOID)
		SetInfoText("Key crafting difficulty.\nEasy: 1 iron ingot. Medium: 1 malachite ingot. Hard: 1 ebony ingot + 1 flawless diamond.")
	elseIf (option == RubberSoundModeOID)
		SetInfoText("Determines how often rubber sounds are played when wearing latex/ebonite restraints.")
	elseIf (option == blindfoldModeOID)
		SetInfoText("Switch between the four provided blindfold modes. DD's mode is intended for First Person play. While in first person, you will be able to move freely, and one of two effects will be applied to your screen. While in third person, you will be unable to move, but will be able to see clearly. The advantage of this mode is that you will be able to clearly see yourself in scenes (Sex, animations, etc), while still being forced to endure the blindfold to advance gameplay.\nLeeche's mode applies a dof-based blindfold effect constantly, and is intended for third person play. The last mode is dark fog (requires ConsoleUtil mod to work).  Default:"+blindfoldList[blindfoldModeDefault])
	elseIf (option == DevicesUnderneathSlotOID)
		SetInfoText("Configure which slot the hidden (Device / Equipment) Hider operates on. It doesn't matter what slot is set, though a slot must be set. If you set this to the same slot as a slot that is being used by a device, bad things will happen. Don't touch this unless you know what you're doing.\nDefault: "+SlotMasks[DevicesUnderneathSlotDefault])
	elseIf (option == animsRegisterOID)
		SetInfoText("Reregister animations provided by this mod.")
	elseIf (option == npcMessagesOID)
		SetInfoText("Enable/disable device related messages for NPC's.\nDefault:"+npcMessagesDefault)
	elseIf (option == playerMessagesOID)
		SetInfoText("Enable/disable device related messages for the player. Note: Messages crucial to device functionality (Such as the menu) will display regardless of this setting. The creator of this mod recommends that you leave this option enabled, unless you really loathe his writing.\nDefault:"+playerMessagesDefault+".")
	elseIf (option == preserveAggroOID)
		SetInfoText("Toggle the preservation of a scene's aggressiveness. Disable this for more variety in animations (At the cost of seeing consensual animations in rape-scenes, etc).\nDefault:"+preserveAggroDefault)
	elseIf (option == useBoundAnimsOID)
		SetInfoText("Toggle the use of bound animations within scenes. Without this option, Yokes / Armbinders / etc will be removed until the sex act has concluded.\nDefault:"+useBoundAnimsDefault)
	elseIf (option == useAnimFilterOID)
		SetInfoText("Toggle the use of the animation filter.\nIf enabled, DD will make sure that only animations compatible with worn devices are played.\nE.g. if the character is belted, she can't have vaginal sex.\nDefault:" + useAnimFilterDefault)		
	elseIf (option == useAnimFilterCreaturesOID)
		SetInfoText("If this option is set to False, the animation filter will get completely bypassed whenever an animation includes creatures.\nOtherwise DD will try to at least hide restraints when creatures are present.\nDefault:" + useAnimFilterCreaturesDefault)		
	elseIf (option == logMessagesOID)
		SetInfoText("Toggles display of debug messages in Papyrus.0.log. You can disable this if everything is working correctly.")
	elseIf (option == eventIntervalOID)
		SetInfoText("Configure how frequently device events are polled, measured in game hours. The lower this is, the more frequent all periodic events / effects are.\nDefault: " + eventIntervalDefault)
	elseIf (option == effectVibrateChanceOID)
		SetInfoText("Controls the probability of a Vibration effect being started via event polling.\nDefault:"+EffectVibrateChanceDefault)
	elseIf (option == effectHealthDrainChanceOID)
		SetInfoText("Controls the probability of a Health Drain effect being started via event polling.\nDefault:"+EffectHealthDrainChanceDefault)
	elseIf (option == effectManaDrainChanceOID)
		SetInfoText("Controls the probability of a Mana Drain effect being started via event polling.\nDefault:"+EffectManaDrainChanceDefault)
	elseIf (option == effectStaminaDrainChanceOID)
		SetInfoText("Controls the probability of a Stamina effect being started via event polling.\nDefault:"+effectStaminaDrainChanceDefault)
	elseIf (option == baseMessageChanceOID)
		SetInfoText("Controls the base probability of a Message Event being started via event polling. This chance will vary for some messages: This is merely the base chance.\nDefault:"+baseMessageChanceDefault)
	elseIf (option == baseHornyChanceOID)
		SetInfoText("Controls the base probability of a Horny-Animation Event being started via event polling. The chance for this event is highly influenced / increased by player arousal.\nDefault:"+baseHornyChanceDefault)
	elseIf (option == baseBumpPumpChanceOID)
		SetInfoText("Controls the base probability of a Bump-Pump Event being started via event polling, or via sitting/jumping. The chance for this event varies depending on what caused it.\nDefault:"+baseBumpPumpChanceDefault)
	elseIf (option == VolumeOrgasmOID)
		SetInfoText("Controls the volume of an an actor's moans during an orgasm.\nDefault:" + volumeOrgasmDefault)
	elseIf (option == VolumeEdgedOID)
		SetInfoText("Controls the volume of an actor's moans after being edged.\nDefault:" + volumeEdgedDefault)
	elseIf (option == VolumeVibratorOID)
		SetInfoText("Controls the volume of a vibrator for a player. Note, that the stronger vibrators are inherently louder than the weaker ones. If you set this too low, you may not be able to hear the weaker ones.\nDefault:" + volumeVibratorDefault)
	elseIf (option == VolumeVibratorNPCOID)
		SetInfoText("Controls the volume of a vibrator for NPC. Note, that the stronger vibrators are inherently louder than the weaker ones. If you set this too low, you may not be able to hear the weaker ones.\nDefault:" + volumeVibratorNPCDefault)
	elseIf (option == ForbiddenTomeOID)
		SetInfoText("Enable/disable the triggers to start the Forbidden Tome quest. Hint: This quest is started in the Arcanaeum.\nDefault:"+ForbiddenTomeDefault)
	elseIf (option == SergiusExperimentOID)
		SetInfoText("Enable/disable the triggers to start Sergius's Experiment quest. Hint: This quest is started by talking to Sergius.\nDefault:"+SergiusExperimentDefault)
	elseIf (option == SurreptitiousStreetsOID)
		SetInfoText("Enable/disable the 'Catch All' triggers that start the radiant master quests. Hint: Booty-trapped containers, sleep encounters, etc.\nDefault:"+SurreptitiousStreetsDefault)
	elseIf (option == RadiantMasterOID)
		SetInfoText("Enable/disable the 'Radiant Master' quest. This is a Surreptitious Streets quest. If there are no elligible quests enabled, Surreptitious Streets will do nothing.\nDefault:"+RadiantMaster)	
	elseIf (option == ssSleepChanceOID)
		SetInfoText("Configure the probability of a sleep capture event occuring while sleeping in an unsafe area.\nDefault:"+ssSleepChanceDefault)
	elseIf (option == ssTrapChanceOID)
		SetInfoText("Configure the probability of a trapped container spawning in an elligible location.\nDefault:"+ssTrapChanceDefault)
	elseIf (option == rmHeartbeatIntervalOID)
		SetInfoText("Configure how frequently master is polled / status is checked.\nDefault:"+rmHeartbeatIntervalDefault)
	elseIf (option == rmSummonHeartbeatIntervalOID)
		SetInfoText("Configure the frequency of summon reminders.\nDefault:"+rmSummonHeartbeatIntervalDefault)	
	elseIf (option == ssWarningMessagesOID)
		SetInfoText("Enable/disable warning messages prior to Surreptitious Streets events. This option will give provide a way to avoid traps / capture events in an immersion friendly manner, without disabling them all-together.\nDefault:"+ssWarningMessagesDefault)
	elseIf (option == UseQueueNiNodeOID)
		SetInfoText("Toggles the use of QueueNiNode after Item Equip/Unequips. The advantage of QueueNiNode is that it will apply changes while you're in your inventory, and won't have an equip/unequip sound. This will work fine for some users, but for others will cause the game to lag briefly after an equip/unequip takes place.\nDefault:"+UseQueueNiNodeDefault)
	elseIf (option == bootsSlowdownToggleOID)
		SetInfoText("Toggles the slowdown effect caused by some boots.\nDefault:"+bootsSlowdownToggleDefault)
	elseIf (option == mittensDropToggleOID)
		SetInfoText("If this option is enabled, it is hard to pick up items when wearing bondage mittens.\nYou will instead drop the items to the ground (you can try to pick them up again.)\nDefault:"+mittensDropToggleDefault)
	elseIf (option == numNpcsOID)
		SetInfoText("Configure the number of NPCs (per area) that will be processed by DD's bondage features (e.g. using bound animations). Use lower settings for weaker PCs.\nDefault:"+numNpcsDefault)	
	elseIf (option == breastNodeManagementOID)
		SetInfoText("If enabled, breasts will be resized while the chastity bra is worn, to minimized HDT clipping.\nDefault: "+breastNodeManagementDefault)
	elseIf (option == bellyNodeManagementOID)
		SetInfoText("If enabled, belly will be resized while the corset is worn, to minimized HDT clipping.\nDefault: "+bellyNodeManagementDefault)
	elseIf (option == UseBoundCombatOID)
		SetInfoText("If enabled, unarmed combat (Kicking) will be enabled for the player while wrist-bound. Works in 3rd person only.\nWhen disabled, the player will not be able to defend herself with bound wrists, and likely die to any attacker.\nDefault: "+UseBoundCombatDefault)	
	elseIf (option == UseBoundCombatPerksOID)
		SetInfoText("If enabled, strength of bound combat will be influenced by which devices you are wearing, and for how long.\nUf disabled, it will make bound combat substantially weaker.\nDefault: "+UseBoundCombatPerksDefault)	
	elseIf (option == ArmbinderMinStruggleOID)
		SetInfoText("Minimum amount of times you have to struggle against your armbinder to have a chance to escape it.\nDefault: "+ArmbinderMinStruggleDefault)
	elseIf (option == ArmbinderStruggleBaseChanceOID)
		SetInfoText("Base chance to escape your armbinder after the minimum required attemts. 1% will be added to this value for every failed attemt.\nDefault: "+ArmbinderStruggleBaseChanceDefault)
	elseIf (option == YokeRemovalCostPerLevelOID)
		SetInfoText("Merchants will charge you this much gold per level for helping you out of a yoke.\nDefault: "+YokeRemovalCostPerLevelDefault)    
	elseIf (option == EscapeDifficultyOID)
		SetInfoText("This modifier will be applied to escape chance difficulties (e.g. struggle and lockpick success chances) and make it easier or harder to escape from them.\nIt applies to standard/generic devices and will not affect quest devices unless their creator enabled it.\nThe default modifier is zero.")
	elseIf (option == CooldownDifficultyOID)
		SetInfoText("This modifier will be applied to device cooldowns (e.g. unlock, escape, repair cooldown).\nIt applies to standard/generic devices and will not affect quest devices unless their creator enabled it.\nThe default modifier is zero.")
	elseIf (option == KeyDifficultyOID)
		SetInfoText("This modifier will be applied to key break and jam lock chances.\nIt applies to standard/generic devices and will not affect quest devices unless their creator enabled it.\nThe default modifier is zero.")
	elseIf (option == HobbleSkirtSpeedDebuffOID)
        SetInfoText("Sets the strength of the speed debuff caused by wearing a hobble skirt.\nThe higher the number, the slower characters wearing a hobble skirt can walk.\nNote: The animations are meant for the default value and will look off at lower values, but some people might find this speed too slow.\nDefault: " + HobbleSkirtSpeedDebuffDefault)
	elseIf (option == GlobalDestroyKeyOID)
		SetInfoText("When enabled, most keys can be used to unlock only one device, and will be consumed on use.\nThis feature will not affect custom keys unless set by the creator.")
	elseIf (option == DisableLockJamOID)
		SetInfoText("When set to true, locks can not jam when a key breaks.")
	elseIf (option == UseItemManipulationOID)
		SetInfoText("When set to true, the player can manipulate the lock of a device they voluntarily equip.\nThis will allow them escaping it without a key or passing a check.")
	elseIf (option == FurnitureNPCActionKeyOID)
		SetInfoText("Allows the player to pick a new key bind for DD Contraptions NPC Furniture Action.")		
	endIf
EndEvent


Event OnOptionSliderAccept(int option, float value)
	int i = 0;
	while i < libs.EventSlots.Slotted
		if option == eventOIDs[i]
			libs.EventSlots.Slots[i].Probability = value as int
			SetSliderOptionValue(option, value, "{1}")
			return
		EndIf
		i+= 1
	EndWhile
	;Libs.Log("OnOptionSliderAccept("+option+"/"+value+")")	
	if (option == thresholdOID)
		UnlockThreshold = value as int
		SetSliderOptionValue(option, value, "{0}")
	elseif (option == thresholdModifierOID)
		thresholdModifier = value as int
		SetSliderOptionValue(option, value, "{0}")
	elseif (option == blindfoldStrengthOID)
		blindfoldStrength = value
		SetSliderOptionValue(option, value, "{2}")
		Game.ForceFirstPerson()
		Game.ForceThirdPerson()
        SendModEvent("zadBlindfoldEffectUpdate")
	elseif (option == darkfogStrengthOID)
		darkfogStrength = value as int
		SetSliderOptionValue(option, value, "{0}")
        SendModEvent("zadBlindfoldEffectUpdate")
	elseIf (option == beltRateOID)
		BeltRateMult = value
		SetSliderOptionValue(option, value, "{1}")
	elseIf (option == plugRateOID)
		PlugRateMult = value
		SetSliderOptionValue(option, value, "{1}")
	elseIf (option == eventIntervalOID)
		EventInterval = value
		SetSliderOptionValue(option, value, "{1}")
	elseIf option == effectVibrateChanceOID
		effectVibrateChance = (value as Int)
		SetSliderOptionValue(option, value, "{1}")
	elseIf option == effectHealthDrainChanceOID
		effectHealthDrainChance = (value as Int)
		SetSliderOptionValue(option, value, "{1}")
	elseIf option == effectManaDrainChanceOID
		effectManaDrainChance = (value as Int)
		SetSliderOptionValue(option, value, "{1}")
	elseIf option == effectStaminaDrainChanceOID
		effectStaminaDrainChance = (value as Int)
		SetSliderOptionValue(option, value, "{1}")
	elseIf option == baseMessageChanceOID
		baseMessageChance = (value as Int)
		SetSliderOptionValue(option, value, "{1}")
	elseIf option == baseHornyChanceOID
		baseHornyChance = (value as Int)
		SetSliderOptionValue(option, value, "{1}")
	elseIf option == baseBumpPumpChanceOID
		BaseBumpPumpChance = (value as Int)
		SetSliderOptionValue(option, value, "{1}")
	elseIf option == VolumeOrgasmOID
		VolumeOrgasm = (value as Float)
		SetSliderOptionValue(option, value, "{3}")
	elseIf option == VolumeVibratorOID
		VolumeVibrator = (value as Float)
		SetSliderOptionValue(option, value, "{3}")
	elseIf option == VolumeVibratorNPCOID
		VolumeVibratorNPC = (value as Float)
		SetSliderOptionValue(option, value, "{3}")
	elseIf option == VolumeEdgedOID
		VolumeEdged = (value as Float)
		SetSliderOptionValue(option, value, "{3}")
	elseIf option == ssSleepChanceOID
		ssSleepChance = (value as Int)
		SetSliderOptionValue(option, value, "{1}")
	elseIf option == ssTrapChanceOID
		ssTrapChance = (value as Int)
		SetSliderOptionValue(option, value, "{1}")
	elseIf option == rmHeartbeatIntervalOID
		rmHeartbeatInterval = (value as Float)
		SetSliderOptionValue(option, value, "{3}")
	elseIf option == rmSummonHeartbeatIntervalOID
		rmSummonHeartbeatInterval = (value as Float)
		SetSliderOptionValue(option, value, "{3}")	
	elseIf option == numNpcsOID
		numNpcs = (value as Int)
		SetSliderOptionValue(option, value, "{1}")	
	elseIf option == ArmbinderStruggleBaseChanceOID
		ArmbinderStruggleBaseChance = (value as Float)
		SetSliderOptionValue(option, value, "{1}%")
	elseIf option == ArmbinderMinStruggleOID
		ArmbinderMinStruggle = (value as Int)
		SetSliderOptionValue(option, value, "{0}")
	elseIf option == YokeRemovalCostPerLevelOID
		YokeRemovalCostPerLevel = (value as Int)
		SetSliderOptionValue(option, value, "{0}/Level")	    
	elseIf (option == HobbleSkirtSpeedDebuffOID)
        HobbleSkirtSpeedDebuff = value as Int
        SetSliderOptionValue(option, value, "{0}")
	EndIf
EndEvent

int function LookupSlotMask(int i)
	int value = (libs.DevicesUnderneath.SlotMaskFilters[i])
	if value == 0
		return 0
	Else
		return SlotMaskValues.Find(value)
	EndIf
EndFunction

function ExportInt(string Name, int Value)
	JsonUtil.SetIntValue(File, Name, Value)
endFunction

int function ImportInt(string Name, int Value)
	return JsonUtil.GetIntValue(File, Name, Value)
endFunction

function ExportBool(string Name, bool Value)
	JsonUtil.SetIntValue(File, Name, Value as int)
endFunction

bool function ImportBool(string Name, bool Value)
	return JsonUtil.GetIntValue(File, Name, Value as int) as bool
endFunction

function ExportFloat(string Name, float Value)
	JsonUtil.SetFloatValue(File, Name, Value)
endFunction

float function ImportFloat(string Name, float Value)
	return JsonUtil.GetFloatValue(File, Name, Value)
endFunction

function ExportDevicesUnderneath()
	int i = 0
	while i < 128
		ExportInt("DevicesUnderneathSlot" + i,libs.DevicesUnderneath.SlotMaskFilters[i])
		i += 1
	EndWhile
endFunction

function ImportDevicesUnderneath()
	int i = 0
	while i < 128
		libs.DevicesUnderneath.SlotMaskFilters[i]=ImportInt("DevicesUnderneathSlot" + i,libs.DevicesUnderneath.SlotMaskFilters[i])
		i += 1
	EndWhile
	libs.DevicesUnderneath.RebuildSlotmask(libs.PlayerRef)
endFunction
	
function ExportEvents()
	int i = 0
	while i < libs.EventSlots.Slotted
		ExportInt("Event"+libs.EventSlots.Slots[i].Name+"Chance", libs.EventSlots.Slots[i].Probability)
		i += 1
	EndWhile
endFunction

function ImportEvents()
	int i = 0
	while i < libs.EventSlots.Slotted
		libs.EventSlots.Slots[i].Probability = ImportInt("Event" + libs.EventSlots.Slots[i].Name+"Chance", libs.EventSlots.Slots[i].Probability)
		i += 1
	EndWhile
endFunction
function ExportSettings()
	File = "../DDI/DDIConfig.json"
	JsonUtil.SetStringValue(File, "ExportLabel", Game.GetPlayer().GetLeveledActorBase().GetName()+" - "+Utility.GetCurrentRealTime() as int)
	JsonUtil.SetIntValue(File, "Version", GetVersion())
	ExportDevicesUnderneath()
	ExportEvents()
	ExportInt("EscapeDifficulty", EscapeDifficulty);EXPORTAUTOGEN
	ExportInt("CooldownDifficulty", CooldownDifficulty);EXPORTAUTOGEN
	ExportInt("KeyDifficulty", KeyDifficulty);EXPORTAUTOGEN
	ExportBool("GlobalDestroyKey", GlobalDestroyKey);EXPORTAUTOGEN
	ExportBool("DisableLockJam", DisableLockJam);EXPORTAUTOGEN
	ExportInt("UnlockThreshold", UnlockThreshold);EXPORTAUTOGEN
	ExportInt("ThresholdModifier", ThresholdModifier);EXPORTAUTOGEN
	ExportFloat("BeltRateMult", BeltRateMult);EXPORTAUTOGEN
	ExportFloat("PlugRateMult", PlugRateMult);EXPORTAUTOGEN
	ExportInt("KeyCrafting", KeyCrafting);EXPORTAUTOGEN
	ExportBool("NpcMessages", NpcMessages);EXPORTAUTOGEN
	ExportBool("PlayerMessages", PlayerMessages);EXPORTAUTOGEN
	ExportFloat("ArmbinderStruggleBaseChance", ArmbinderStruggleBaseChance);EXPORTAUTOGEN
	ExportInt("ArmbinderMinStruggle", ArmbinderMinStruggle);EXPORTAUTOGEN
	ExportInt("YokeRemovalCostPerLevel", YokeRemovalCostPerLevel);EXPORTAUTOGEN
	ExportBool("LogMessages", LogMessages);EXPORTAUTOGEN
	ExportBool("preserveAggro", preserveAggro);EXPORTAUTOGEN
	ExportBool("breastNodeManagement", breastNodeManagement);EXPORTAUTOGEN
	ExportBool("bellyNodeManagement", bellyNodeManagement);EXPORTAUTOGEN
	ExportBool("UseItemManipulation", UseItemManipulation);EXPORTAUTOGEN
	ExportBool("UseBoundCombat", UseBoundCombat);EXPORTAUTOGEN
	ExportBool("UseBoundCombatPerks", UseBoundCombatPerks);EXPORTAUTOGEN
	ExportBool("useBoundAnims", useBoundAnims);EXPORTAUTOGEN
	ExportBool("useAnimFilter", useAnimFilter);EXPORTAUTOGEN
	ExportInt("blindfoldMode", blindfoldMode);EXPORTAUTOGEN
	ExportFloat("blindfoldStrength", blindfoldStrength);EXPORTAUTOGEN
	ExportInt("darkfogStrength", darkfogStrength);EXPORTAUTOGEN
	ExportInt("darkfogStrength2", darkfogStrength2);EXPORTAUTOGEN
	ExportInt("FurnitureNPCActionKey", FurnitureNPCActionKey);EXPORTAUTOGEN
	ExportBool("BlindfoldTooltip", BlindfoldTooltip);EXPORTAUTOGEN
	ExportBool("GagTooltip", GagTooltip);EXPORTAUTOGEN
	ExportFloat("EventInterval", EventInterval);EXPORTAUTOGEN
	ExportInt("EffectVibrateChance", EffectVibrateChance);EXPORTAUTOGEN
	ExportInt("EffectHealthDrainChance", EffectHealthDrainChance);EXPORTAUTOGEN
	ExportInt("EffectManaDrainChance", EffectManaDrainChance);EXPORTAUTOGEN
	ExportInt("EffectStaminaDrainChance", EffectStaminaDrainChance);EXPORTAUTOGEN
	ExportInt("BaseMessageChance", BaseMessageChance);EXPORTAUTOGEN
	ExportInt("BaseHornyChance", BaseHornyChance);EXPORTAUTOGEN
	ExportInt("BaseBumpPumpChance", BaseBumpPumpChance);EXPORTAUTOGEN
	ExportInt("numNpcs", numNpcs);EXPORTAUTOGEN
	ExportFloat("VolumeOrgasm", VolumeOrgasm);EXPORTAUTOGEN
	ExportFloat("VolumeEdged", VolumeEdged);EXPORTAUTOGEN
	ExportFloat("VolumeVibrator", VolumeVibrator);EXPORTAUTOGEN
	ExportFloat("VolumeVibratorNPC", VolumeVibratorNPC);EXPORTAUTOGEN
	ExportBool("ForbiddenTome", ForbiddenTome);EXPORTAUTOGEN
	ExportBool("SergiusExperiment", SergiusExperiment);EXPORTAUTOGEN
	ExportBool("SurreptitiousStreets", SurreptitiousStreets);EXPORTAUTOGEN
	ExportBool("RadiantMaster", RadiantMaster);EXPORTAUTOGEN
	ExportInt("ssSleepChance", ssSleepChance);EXPORTAUTOGEN
	ExportInt("ssTrapChance", ssTrapChance);EXPORTAUTOGEN
	ExportBool("ssWarningMessages", ssWarningMessages);EXPORTAUTOGEN
	ExportFloat("rmHeartbeatInterval", rmHeartbeatInterval);EXPORTAUTOGEN
	ExportFloat("rmSummonHeartbeatInterval", rmSummonHeartbeatInterval);EXPORTAUTOGEN
	ExportBool("DevicesUnderneathEnabled", DevicesUnderneathEnabled);EXPORTAUTOGEN
	ExportInt("DevicesUnderneathSlot", DevicesUnderneathSlot);EXPORTAUTOGEN
	ExportInt("DevicesUnderneathSlotDefault", DevicesUnderneathSlotDefault);EXPORTAUTOGEN
	ExportBool("UseQueueNiNode", UseQueueNiNode);EXPORTAUTOGEN
	ExportBool("bootsSlowdownToggle", bootsSlowdownToggle);EXPORTAUTOGEN
	ExportBool("mittensDropToggle", mittensDropToggle);EXPORTAUTOGEN
	ExportInt("HobbleSkirtSpeedDebuff", HobbleSkirtSpeedDebuff);EXPORTAUTOGEN
	ExportBool("lockmenuwhentied", lockmenuwhentied);EXPORTAUTOGEN
	ExportBool("useAnimFilterCreatures", useAnimFilterCreatures)
	JsonUtil.Save(File, false)
EndFunction
function ImportSettings()
	File = "../DDI/DDIConfig.json"
	Int version = 0
	If JsonUtil.GetIntValue(File, "Version", version) != GetVersion()
		If !ShowMessage("Saved config is for another version of DDi, aborting.")
			Return
		Endif
	EndIf
	int oldBlindfoldMode = BlindfoldMode 
	ImportDevicesUnderneath()
	ImportEvents()
	EscapeDifficulty = ImportInt("EscapeDifficulty", EscapeDifficulty);IMPORTAUTOGEN
	CooldownDifficulty = ImportInt("CooldownDifficulty", CooldownDifficulty);IMPORTAUTOGEN
	KeyDifficulty = ImportInt("KeyDifficulty", KeyDifficulty);IMPORTAUTOGEN
	GlobalDestroyKey = ImportBool("GlobalDestroyKey", GlobalDestroyKey);IMPORTAUTOGEN
	DisableLockJam = ImportBool("DisableLockJam", DisableLockJam);IMPORTAUTOGEN
	UnlockThreshold = ImportInt("UnlockThreshold", UnlockThreshold);IMPORTAUTOGEN
	ThresholdModifier = ImportInt("ThresholdModifier", ThresholdModifier);IMPORTAUTOGEN
	BeltRateMult = ImportFloat("BeltRateMult", BeltRateMult);IMPORTAUTOGEN
	PlugRateMult = ImportFloat("PlugRateMult", PlugRateMult);IMPORTAUTOGEN
	KeyCrafting = ImportInt("KeyCrafting", KeyCrafting);IMPORTAUTOGEN
	NpcMessages = ImportBool("NpcMessages", NpcMessages);IMPORTAUTOGEN
	PlayerMessages = ImportBool("PlayerMessages", PlayerMessages);IMPORTAUTOGEN
	ArmbinderStruggleBaseChance = ImportFloat("ArmbinderStruggleBaseChance", ArmbinderStruggleBaseChance);IMPORTAUTOGEN
	ArmbinderMinStruggle = ImportInt("ArmbinderMinStruggle", ArmbinderMinStruggle);IMPORTAUTOGEN
	YokeRemovalCostPerLevel = ImportInt("YokeRemovalCostPerLevel", YokeRemovalCostPerLevel);IMPORTAUTOGEN
	LogMessages = ImportBool("LogMessages", LogMessages);IMPORTAUTOGEN
	preserveAggro = ImportBool("preserveAggro", preserveAggro);IMPORTAUTOGEN
	breastNodeManagement = ImportBool("breastNodeManagement", breastNodeManagement);IMPORTAUTOGEN
	bellyNodeManagement = ImportBool("bellyNodeManagement", bellyNodeManagement);IMPORTAUTOGEN
	UseItemManipulation = ImportBool("UseItemManipulation", UseItemManipulation);IMPORTAUTOGEN
	UseBoundCombat = ImportBool("UseBoundCombat", UseBoundCombat);IMPORTAUTOGEN
	UseBoundCombatPerks = ImportBool("UseBoundCombatPerks", UseBoundCombatPerks);IMPORTAUTOGEN
	useBoundAnims = ImportBool("useBoundAnims", useBoundAnims);IMPORTAUTOGEN
	useAnimFilter = ImportBool("useAnimFilter", useAnimFilter);IMPORTAUTOGEN
	blindfoldMode = ImportInt("blindfoldMode", blindfoldMode);IMPORTAUTOGEN
	blindfoldStrength = ImportFloat("blindfoldStrength", blindfoldStrength);IMPORTAUTOGEN
	darkfogStrength = ImportInt("darkfogStrength", darkfogStrength);IMPORTAUTOGEN
	darkfogStrength2 = ImportInt("darkfogStrength2", darkfogStrength2);IMPORTAUTOGEN
	FurnitureNPCActionKey = ImportInt("FurnitureNPCActionKey", FurnitureNPCActionKey);IMPORTAUTOGEN
	BlindfoldTooltip = ImportBool("BlindfoldTooltip", BlindfoldTooltip);IMPORTAUTOGEN
	GagTooltip = ImportBool("GagTooltip", GagTooltip);IMPORTAUTOGEN
	EventInterval = ImportFloat("EventInterval", EventInterval);IMPORTAUTOGEN
	EffectVibrateChance = ImportInt("EffectVibrateChance", EffectVibrateChance);IMPORTAUTOGEN
	EffectHealthDrainChance = ImportInt("EffectHealthDrainChance", EffectHealthDrainChance);IMPORTAUTOGEN
	EffectManaDrainChance = ImportInt("EffectManaDrainChance", EffectManaDrainChance);IMPORTAUTOGEN
	EffectStaminaDrainChance = ImportInt("EffectStaminaDrainChance", EffectStaminaDrainChance);IMPORTAUTOGEN
	BaseMessageChance = ImportInt("BaseMessageChance", BaseMessageChance);IMPORTAUTOGEN
	BaseHornyChance = ImportInt("BaseHornyChance", BaseHornyChance);IMPORTAUTOGEN
	BaseBumpPumpChance = ImportInt("BaseBumpPumpChance", BaseBumpPumpChance);IMPORTAUTOGEN
	numNpcs = ImportInt("numNpcs", numNpcs);IMPORTAUTOGEN
	VolumeOrgasm = ImportFloat("VolumeOrgasm", VolumeOrgasm);IMPORTAUTOGEN
	VolumeEdged = ImportFloat("VolumeEdged", VolumeEdged);IMPORTAUTOGEN
	VolumeVibrator = ImportFloat("VolumeVibrator", VolumeVibrator);IMPORTAUTOGEN
	VolumeVibratorNPC = ImportFloat("VolumeVibratorNPC", VolumeVibratorNPC);IMPORTAUTOGEN
	ForbiddenTome = ImportBool("ForbiddenTome", ForbiddenTome);IMPORTAUTOGEN
	SergiusExperiment = ImportBool("SergiusExperiment", SergiusExperiment);IMPORTAUTOGEN
	SurreptitiousStreets = ImportBool("SurreptitiousStreets", SurreptitiousStreets);IMPORTAUTOGEN
	RadiantMaster = ImportBool("RadiantMaster", RadiantMaster);IMPORTAUTOGEN
	ssSleepChance = ImportInt("ssSleepChance", ssSleepChance);IMPORTAUTOGEN
	ssTrapChance = ImportInt("ssTrapChance", ssTrapChance);IMPORTAUTOGEN
	ssWarningMessages = ImportBool("ssWarningMessages", ssWarningMessages);IMPORTAUTOGEN
	rmHeartbeatInterval = ImportFloat("rmHeartbeatInterval", rmHeartbeatInterval);IMPORTAUTOGEN
	rmSummonHeartbeatInterval = ImportFloat("rmSummonHeartbeatInterval", rmSummonHeartbeatInterval);IMPORTAUTOGEN
	DevicesUnderneathEnabled = ImportBool("DevicesUnderneathEnabled", DevicesUnderneathEnabled);IMPORTAUTOGEN
	DevicesUnderneathSlot = ImportInt("DevicesUnderneathSlot", DevicesUnderneathSlot);IMPORTAUTOGEN
	DevicesUnderneathSlotDefault = ImportInt("DevicesUnderneathSlotDefault", DevicesUnderneathSlotDefault);IMPORTAUTOGEN
	UseQueueNiNode = ImportBool("UseQueueNiNode", UseQueueNiNode);IMPORTAUTOGEN
	bootsSlowdownToggle = ImportBool("bootsSlowdownToggle", bootsSlowdownToggle);IMPORTAUTOGEN
	mittensDropToggle = ImportBool("mittensDropToggle", mittensDropToggle);IMPORTAUTOGEN
	HobbleSkirtSpeedDebuff = ImportInt("HobbleSkirtSpeedDebuff", HobbleSkirtSpeedDebuff);IMPORTAUTOGEN
	lockmenuwhentied = ImportBool("lockmenuwhentied", lockmenuwhentied);IMPORTAUTOGEN
	useAnimFilterCreatures = ImportBool("useAnimFilterCreatures", useAnimFilterCreatures)
	If BlindfoldMode == 3
		int cotest = ConsoleUtil.GetVersion()
		if !cotest
			ShowMessage("Blindfold mode Dark Fog (in import) requires ConsoleUtil which doesn't seem to be installed. Setting reverted.")
			BlindfoldMode = oldBlindfoldMode
		endif
	Endif
	If oldBlindfoldMode == 3 && BlindfoldMode != 3 ; Old mode was Dark Fog, remove it
		if Weather.GetSkyMode() == 0
			ConsoleUtil.ExecuteCommand("ts")
		endif
		ConsoleUtil.ExecuteCommand("setfog 0 0") 
	EndIf	
	game.ForceFirstPerson()
	game.ForceThirdPerson()
	libs.UpdateControls()
EndFunction
