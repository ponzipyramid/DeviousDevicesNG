scriptName zadEventHorny extends zadBaseEvent

Bool Function Filter(actor akActor, int chanceMod=0)
	if akActor == libs.playerref && libs.playerref.IsInCombat() 
		return False
	Endif
	int arousal = libs.Aroused.GetActorExposure(akActor)
	float CombatModifier = 1
	if akActor.GetCombatState() == 1
		CombatModifier = 0.5
	EndIf
	if arousal >= libs.ArousalThreshold("Desperate")
		chanceMod += 20
	ElseIf arousal >= libs.ArousalThreshold("Horny")
		chanceMod += 10
	EndIf
	 return (arousal >= libs.ArousalThreshold("Desire")) && Parent.Filter(akActor, (chanceMod * combatModifier) as Int)
EndFunction

bool Function HasKeywords(actor akActor)
	If !libs.AllowGenericEvents(akActor, libs.zad_DeviousBelt)
		return false
	Elseif !libs.AllowGenericEvents(akActor, libs.zad_DeviousHarness)
		return false
	Else
		return (akActor.WornHasKeyword(libs.zad_DeviousBelt) || akActor.WornHasKeyword(libs.zad_DeviousHarness))
	EndIf
EndFunction

Function Execute(actor akActor)
	if akActor == libs.PlayerRef
		libs.NotifyPlayer("You absent-mindedly allow your hands to wander...")
	EndIf
	; don't play the animation in combat
	If akActor == libs.playerref && libs.playerref.IsInCombat() 
		return 
	Endif
	libs.PlayThirdPersonAnimation(akActor, libs.AnimSwitchKeyword(akActor, "Horny"), Utility.RandomInt(5,10), permitRestrictive=true)
EndFunction
