scriptName zadEventStruggle extends zadBaseEvent

Float EventCooldown = 0.0

bool Function HasKeywords(actor akActor)
	; don't play the animation in combat
	if akActor.IsInCombat() 
		return false
	Endif
	if Utility.GetCurrentRealTime() < Eventcooldown || akActor.IsWeaponDrawn()
		Return False
	Else	 
		; no wrist restraints for now. I will add them later! Make sure to give them priority!
		return (akActor.WornHasKeyword(libs.zad_Lockable) && !akActor.WornHasKeyword(libs.zad_DeviousHeavyBondage))
	EndIf
EndFunction

Function Execute(actor akActor)
	if libs.IsAnimating(akActor)
		return
	EndIf

	Bool has_hobble = akActor.WornHasKeyword(libs.zad_DeviousHobbleSkirt) && !akActor.WornHasKeyword(libs.zad_DeviousHobbleSkirtRelaxed)
	Bool has_heavy = akActor.WornHasKeyword(libs.zad_DeviousHeavyBondage)
	Bool has_fc = akActor.WornHasKeyword(libs.zad_DeviousCuffsFront)

	String StruggleString = ""

	If akActor.WornHasKeyword(libs.zad_DeviousGag)
		StruggleString += "ft_struggle_gag_1,"
	EndIf

	If akActor.WornHasKeyword(libs.zad_DeviousCollar) && !akActor.WornHasKeyword(libs.zad_DeviousCuffsFront)
		If has_hobble
			StruggleString += "DDCollarStruggle01_H,"
		Else
			StruggleString += "DDCollarStruggle01,"
		EndIf
	EndIf

	If akActor.WornHasKeyword(libs.zad_DeviousBlindfold)
		StruggleString += "ft_struggle_blindfold_1,"
	EndIf

	If akActor.WornHasKeyword(libs.zad_DeviousBoots)
		StruggleString += "ft_struggle_boots_1,"
	EndIf

	If (akActor.WornHasKeyword(libs.zad_DeviousGloves) || akActor.WornHasKeyword(libs.zad_DeviousSuit)) && !akActor.WornHasKeyword(libs.zad_DeviousStraitJacket)
		StruggleString += "ft_struggle_gloves_1,"
	EndIf

	If akActor.WornHasKeyword(libs.zad_DeviousHood)
		StruggleString += "ft_struggle_head_1,"
	EndIf

	If akActor.WornHasKeyword(libs.zad_DeviousBelt)
		StruggleString += "DDChastityBeltStruggle01,DDChastityBeltStruggle02,"
	EndIf

	If akActor.WornHasKeyword(libs.zad_DeviousArmbinderElbow)
		if akActor.WornHasKeyword(libs.zad_DeviousHobbleSkirt) && !akActor.WornHasKeyword(libs.zad_DeviousHobbleSkirtRelaxed)
			StruggleString += "DDHobElbStruggle01,DDHobElbStruggle02,"
		Else
			StruggleString += "DDRegElbStruggle01,DDRegElbStruggle02,DDRegElbStruggle03,DDRegElbStruggle04,DDRegElbStruggle05,"
		Endif
	EndIf

	If (akActor.WornHasKeyword(libs.zad_DeviousArmbinder) || akActor.WornHasKeyword(libs.zad_DeviousStraitJacket)) && !akActor.WornHasKeyword(libs.zad_DeviousArmbinderElbow)
		If akActor.WornHasKeyword(libs.zad_DeviousHobbleSkirt) && !akActor.WornHasKeyword(libs.zad_DeviousHobbleSkirtRelaxed)
			StruggleString += "DDHobArmbStruggle01,DDHobArmbStruggle02,"
		Else
			StruggleString += "DDRegArmbStruggle01,DDRegArmbStruggle02,DDRegArmbStruggle03,DDRegArmbStruggle04,DDRegArmbStruggle05,"
		EndIf
	Endif

	If akActor.WornHasKeyword(libs.zad_DeviousPetSuit)
		StruggleString += "DDPetSuitStruggle01,DDPetSuitStruggle02,DDPetSuitStruggle03,"
	EndIf

	If has_hobble
		If has_heavy
			If (akActor.WornHasKeyword(libs.zad_DeviousArmbinder) || akActor.WornHasKeyword(libs.zad_DeviousStraitJacket))
				StruggleString += "DDHobbleStruggle01_AH,"
			ElseIf akActor.WornHasKeyword(libs.zad_DeviousArmbinderElbow)
				StruggleString += "DDHobbleStruggle01_EH,"
			ElseIf akActor.WornHasKeyword(libs.zad_DeviousElbowTie)
				StruggleString += "DDHobbleStruggle01_TH,"
			ElseIf akActor.WornHasKeyword(libs.zad_DeviousYoke)
				StruggleString += "DDHobbleStruggle01_YH,"
			ElseIf akActor.WornHasKeyword(libs.zad_DeviousYokeBB)
				StruggleString += "DDHobbleStruggle01_BH,"
			EndIf
		ElseIf has_fc
			StruggleString += "DDHobbleStruggle01_FH,"
		Else
			StruggleString += "DDHobbleStruggle01_H,"
		EndIf
	EndIf

	If !has_heavy
		If akActor.WornHasKeyword(libs.zad_DeviousCorset)
			If has_fc
				If has_hobble
					StruggleString += "DDCorsetStruggle01_FH,"
				Else
					StruggleString += "DDCorsetStruggle01_F,"
				EndIf
			Else
				If has_hobble
					StruggleString += "DDCorsetStruggle01_H,"
				Else
					StruggleString += "DDCorsetStruggle01,"
				EndIf
			EndIf

		EndIf

		If (akActor.WornHasKeyword(libs.zad_DeviousBoots) || akActor.WornHasKeyword(libs.zad_DeviousLegCuffs)) && !has_fc
			StruggleString += "DDBootsStruggle01_H,"

		EndIf

		If akActor.WornHasKeyword(libs.zad_DeviousCollar) && !akActor.WornHasKeyword(libs.zad_DeviousCuffsFront)
			If has_hobble
				StruggleString += "DDCollarStruggle01_H,"
			Else
				StruggleString += "DDCollarStruggle01,"
			EndIf

		EndIf

		If akActor.WornHasKeyword(libs.zad_DeviousArmCuffs) || akActor.WornHasKeyword(libs.zad_DeviousGloves) || has_fc
			If has_hobble
				StruggleString += "DDArmsStruggle01_H,"
			Else
				StruggleString += "DDArmsStruggle01,"
			EndIf

		EndIf

		If akActor.WornHasKeyword(libs.zad_DeviousBra) && !has_fc
			If has_hobble
				StruggleString += "DDChestStruggle01_H,"
			Else
				StruggleString += "DDChestStruggle01,"
			EndIf

		EndIf
	EndIf
	
	; sanity check
	If StruggleString == ""
		Return
	EndIf

	String[] StruggleArray = StringUtil.Split( StruggleString, "," )

	Eventcooldown = Utility.GetCurrentRealTime() + 300.0 ; add a 5 min real time cooldown
	bool[] cameraState = libs.StartThirdPersonAnimation(akActor, StruggleArray[Utility.RandomInt( 0, StruggleArray.Length - 1) ], true)
	Utility.Wait(5)
	libs.Pant(libs.PlayerRef)
	Utility.Wait(5)
	libs.EndThirdPersonAnimation(akActor, cameraState, true)
	libs.SexlabMoan(libs.PlayerRef)
EndFunction