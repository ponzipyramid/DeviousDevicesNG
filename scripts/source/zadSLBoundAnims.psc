Scriptname zadSLBoundAnims extends sslAnimationFactory

SexlabFramework Property Sexlab Auto
zadLibs Property libs Auto
zadBQ00 Property filterQuest Auto

;This sets up bound animations for private use.
;They will not populate the general sexlab list and must be called specifically.

;Define animation prefixes for each actor (must correspond to names in FNIS), add more if necessary

function LoadAnimations()
	libs.log("Devious Devices is now creating bound animations.")
	SexLab = SexLabUtil.GetAPI()
	If SexLab == None
		libs.Error("Animation registration failed: SexLab is none.")
	EndIf
	if filterQuest == None
		libs.Error("Animation registration failed: FilterQuest is none.")
	EndIf

	;--------------------
	;ARMBINDER ANIMATIONS
	;--------------------
	;blowjob
	SexLab.GetSetAnimationObject("DD_SH_armbBJ1", "CreateDD_SH_armbBJ1", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_ADogFF", "CreateDD_B_ADogFF", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_AHogFF", "CreateDD_B_AHogFF", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_AKneelFF", "CreateDD_B_AKneelFF", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_LayAFF", "CreateDD_B_LayAFF", filterQuest)
	;vaginal
	SexLab.GetSetAnimationObject("DDZapArmbDoggy01Both", "CreateDDZapArmbDoggy01Both", filterQuest)
	SexLab.GetSetAnimationObject("DD_SH_armbMiss1", "CreateDD_SH_armbMiss1", filterQuest)
	SexLab.GetSetAnimationObject("DD_SH_armbCowg1", "CreateDD_SH_armbCowg1", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_ACG", "CreateDD_B_ACG", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_AHold", "CreateDD_B_AHold", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_ASide", "CreateDD_B_ASide", filterQuest)
	;anal
	SexLab.GetSetAnimationObject("DD_ArmbA", "CreateDD_ArmbA", filterQuest)
	;lesbian
	SexLab.GetSetAnimationObject("DDZapArmbLesbian01Both", "CreateDDZapArmbLesbian01Both", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_LACunnKnl", "CreateDD_B_LACunnKnl", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_LAFaceSit1", "CreateDD_B_LAFaceSit1", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_LAFingSit", "CreateDD_B_LAFingSit", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_LAFingStand", "CreateDD_B_LAFingStand", filterQuest)
	;other
	SexLab.GetSetAnimationObject("DDZapArmbKissing01", "CreateDDZapArmbKissing01", filterQuest)

	;----------------------
	;ELBOWBINDER ANIMATIONS
	;----------------------
	;blowjob
	Sexlab.GetSetAnimationObject("DD_SH_elbBJ1", "CreateDD_SH_elbBJ1", filterQuest)
	;vaginal
	SexLab.GetSetAnimationObject("DD_SH_elbMiss1", "CreateDD_SH_elbMiss1", filterQuest)
	SexLab.GetSetAnimationObject("DD_SH_elbCowg1", "CreateDD_SH_elbCowg1", filterQuest)
	;anal
	SexLab.GetSetAnimationObject("DD_ElbndAn", "CreateDD_ElbndAn", filterQuest)
	;lesbian
	SexLab.GetSetAnimationObject("DD_ElbL", "CreateDD_ElbL", filterQuest)

	;---------------
	;YOKE ANIMATIONS
	;---------------
	;blowjob
	SexLab.GetSetAnimationObject("DD_SH_yokeBJ1", "CreateDD_SH_yokeBJ1", filterQuest)
	SexLab.GetSetAnimationObject("DD_Billyy_YokeFaceFuck", "CreateDD_Billyy_YokeFaceFuck", filterQuest)
	SexLab.GetSetAnimationObject("DD_Billyy_Yoke69", "CreateDD_Billyy_Yoke69", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_Y692", "CreateDD_B_Y692", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_YKneelFF", "CreateDD_B_YKneelFF", filterQuest)
	;vaginal
	SexLab.GetSetAnimationObject("DD_SH_yokeMiss1", "CreateDD_SH_yokeMiss1", filterQuest)
	SexLab.GetSetAnimationObject("DD_Billyy_YokeCowgirl", "CreateDD_Billyy_YokeCowgirl", filterQuest)
	SexLab.GetSetAnimationObject("DD_Billyy_YokeDoggy", "CreateDD_Billyy_YokeDoggy", filterQuest)
	SexLab.GetSetAnimationObject("DD_Billyy_YokeMissionary", "CreateDD_Billyy_YokeMissionary", filterQuest)
	SexLab.GetSetAnimationObject("DD_Billyy_YokeStanding", "CreateDD_Billyy_YokeStanding", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_YCG", "CreateDD_B_YCG", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_YHold", "CreateDD_B_YHold", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_YMiss", "CreateDD_B_YMiss", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_YStand", "CreateDD_B_YStand", filterQuest)
	SexLab.GetSetAnimationObject("DD_Babo_SneakYokeStandingFuck", "CreateDD_Babo_SneakYokeStandingFuck", filterQuest)
	;anal
	SexLab.GetSetAnimationObject("DD_Billyy_YokeRevCowgirlAnal", "CreateDD_Billyy_YokeRevCowgirlAnal", filterQuest)
	SexLab.GetSetAnimationObject("DD_Billyy_YokeLayingAnal", "CreateDD_Billyy_YokeLayingAnal", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_YDogA", "CreateDD_B_YDogA", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_YStandA", "CreateDD_B_YStandA", filterQuest)
	;lesbian
	SexLab.GetSetAnimationObject("DDZapYokeLesbian01Both", "CreateDDZapYokeLesbian01Both", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_LYCunnKnl", "CreateDD_B_LYCunnKnl", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_LYFaceSit1", "CreateDD_B_LYFaceSit1", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_LYFingSit", "CreateDD_B_LYFingSit", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_LYFingStand", "CreateDD_B_LYFingStand", filterQuest)
	;other
	SexLab.GetSetAnimationObject("DDZapYokeKissing01", "CreateDDZapYokeKissing01", filterQuest)

	;-----------------------
	;BREAST YOKE ANIMATIONS
	;-----------------------
	;blowjob
	SexLab.GetSetAnimationObject("DD_SH_bbYokeBJ1", "CreateDD_SH_bbYokeBJ1", filterQuest)
	;vaginal
	SexLab.GetSetAnimationObject("DD_SH_bbYokeMiss1", "CreateDD_SH_bbYokeMiss1", filterQuest)
	;anal
	SexLab.GetSetAnimationObject("DD_BBYoA", "CreateDD_BBYoA", filterQuest)
	;lesbian


	;-----------------
	;CUFFED ANIMATIONS
	;-----------------
	;blowjob
	SexLab.GetSetAnimationObject("DD_SH_cuffsFrontBJ1", "CreateDD_SH_cuffsFrontBJ1", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_C69", "CreateDD_B_C69", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_CDogFF", "CreateDD_B_CDogFF", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_CHogFF", "CreateDD_B_CHogFF", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_KneelCFF", "CreateDD_B_KneelCFF", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_LayCFF", "CreateDD_B_LayCFF", filterQuest)
	;vaginal
	SexLab.GetSetAnimationObject("DD_SH_cuffsFrontMiss1", "CreateDD_SH_cuffsFrontMiss1", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_CCG", "CreateDD_B_CCG", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_CDog", "CreateDD_B_CDog", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_CHold", "CreateDD_B_CHold", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_CMiss", "CreateDD_B_CMiss", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_CSide", "CreateDD_B_CSide", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_CStand", "CreateDD_B_CStand", filterQuest)
	;anal
	SexLab.GetSetAnimationObject("DD_B_CDogA", "CreateDD_B_CDogA", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_CLayBA", "CreateDD_B_CLayBA", filterQuest)
	;lesbian
	SexLab.GetSetAnimationObject("DD_B_LCCunnKnl", "CreateDD_B_LCCunnKnl", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_LCFaceSit1", "CreateDD_B_LCFaceSit1", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_LCFingSit", "CreateDD_B_LCFingSit", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_LCFingStand", "CreateDD_B_LCFingStand", filterQuest)
	;other
	SexLab.GetSetAnimationObject("DD_B_CHJ", "CreateDD_B_CHJ", filterQuest)

	;-------------------
	;PET SUIT ANIMATIONS
	;-------------------
	;blowjob
	SexLab.GetSetAnimationObject("DD_B_PS_DT", "CreateDD_B_PS_DT", filterQuest)
	;vaginal
	SexLab.GetSetAnimationObject("DD_B_PS_Doggy", "CreateDD_B_PS_Doggy", filterQuest)
	SexLab.GetSetAnimationObject("DD_B_PS_Miss", "CreateDD_B_PS_Miss", filterQuest)
	;anal
	SexLab.GetSetAnimationObject("DD_B_PS_DoggyA", "CreateDD_B_PS_DoggyA", filterQuest)
	;lesbian


	;----------------
	;OTHER ANIMATIONS
	;----------------
	SexLab.GetSetAnimationObject("DDZapMixLesbian01ArmbYoke", "CreateDDZapMixLesbian01ArmbYoke", filterQuest)
	SexLab.GetSetAnimationObject("DDZapMixLesbian01YokeArmb", "CreateDDZapMixLesbian01YokeArmb", filterQuest)

EndFunction

;Defining animations:
;========================
;ARMBINDER
;========================

;animations from ZaZ Animation Pack

Function CreateDDZapArmbDoggy01Both(int id)
	String asAnim1 = "DD_ZapArmbDoggy01"

	libs.Log("Creating DDZapArmbDoggy01Both")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DDZapArmbDoggy01Both")
	if Anim != none && Anim.Name != "DDZapArmbDoggy01Both"
		Anim.Name = "DDZapArmbDoggy01Both"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Anal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", -100, sos = 5)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", -100, sos = 5)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", -100, sos = 7)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", -100, sos = 5)

		Anim.AddTag("Doggystyle")
		Anim.AddTag("Anal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("SubSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
	EndIf
endFunction

Function CreateDDZapArmbLesbian01Both(int id)
	String asAnim1 = "DD_ZapArmbLesbian01"

	libs.Log("Creating DDZapArmbLesbian01Both")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DDZapArmbLesbian01Both")
	if Anim != none && Anim.Name != "DDZapArmbLesbian01Both"
		Anim.Name = "DDZapArmbLesbian01Both"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", 0, silent = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", 0, silent = False)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", 0, silent = False, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", 0, silent = False, openMouth = True)

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", -110, silent = True)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", -105, silent = True, openMouth = True)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", -100, silent = False, openMouth = True)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", -100, silent = False, openMouth = True)
		
		Anim.SetStageTimer(4, 10.0)

		Anim.AddTag("Arrok")
		Anim.AddTag("Oral")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Laying")
		Anim.AddTag("Loving")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		
		Anim.AddTag("SubSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
	EndIf
endFunction

Function CreateDDZapArmbKissing01(int id)
	String asAnim1 = "DD_ZapArmbKissing01"
	String asAnim2 = "DD_ZapKissing01"

	libs.Log("Creating DDZapArmbKissing01")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DDZapArmbKissing01")
	if Anim != none && Anim.Name != "DDZapArmbKissing01"
		Anim.Name = "DDZapArmbKissing01"
		Anim.SetContent(Foreplay)
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", silent = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", silent = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", silent = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim2 + "_A2_S1", strapon = False, silent = True)
		Anim.AddPositionStage(a2, asAnim2 + "_A2_S2", strapon = False, silent = True)
		Anim.AddPositionStage(a2, asAnim2 + "_A2_S3", strapon = False, silent = True)

		; Anim.SetStageTimer(1, 1.8)
		; Anim.SetStageTimer(2, 15.0)
		Anim.SetStageTimer(3, 0.7)

		Anim.AddTag("Leito")
		Anim.AddTag("Kissing")
		Anim.AddTag("Standing")
		Anim.AddTag("Loving")

		Anim.AddTag("Foreplay")
		Anim.AddTag("MF")
	
		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
	EndIf
endFunction

;animations by SpaceHamster

Function CreateDD_SH_armbBJ1(int id)
	String asAnim1 = "DD_SH_armbBJ1"

	libs.Log("Creating DD_SH_armbBJ1")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_SH_armbBJ1")
	if Anim != none && Anim.Name != "DD_SH_armbBJ1"
		Anim.Name = "DD_SH_armbBJ1"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", silent = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", silent = True, openMouth = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", silent = True, openMouth = False)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.SetStageSoundFX(1, None)

		Anim.AddTag("Blowjob")
		Anim.AddTag("Oral")		

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ArmbinderBlowjob = PapyrusUtil.PushString(filterQuest.ArmbinderBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_SH_armbCowg1(int id)
	String asAnim1 = "DD_SH_armbCowg1"

	libs.Log("Creating DD_SH_armbCowg1")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_SH_armbCowg1")
	if Anim != none && Anim.Name != "DD_SH_armbCowg1"
		Anim.Name = "DD_SH_armbCowg1"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Cowgirl")
		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ArmbinderVaginal = PapyrusUtil.PushString(filterQuest.ArmbinderVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_SH_armbMiss1(int id)
	String asAnim1 = "DD_SH_armbMiss1"

	libs.Log("Creating DD_SH_armbMiss1")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_SH_armbMiss1")
	if Anim != none && Anim.Name != "DD_SH_armbMiss1"
		Anim.Name = "DD_SH_armbMiss1"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S6")

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S6")

		Anim.AddTag("Missionary")
		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ArmbinderVaginal = PapyrusUtil.PushString(filterQuest.ArmbinderVaginal, Anim.Name)
	EndIf
endFunction

;animations by Billyy

Function CreateDD_B_ADogFF(int id)
	String asAnim1 = "DD_B_ADogFF"

	libs.Log("Creating DD_B_ADogFF")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_ADogFF")
	if Anim != none && Anim.Name != "DD_B_ADogFF"
		Anim.Name = "DD_B_ADogFF"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = 2)

		Anim.AddTag("Doggy")
		Anim.AddTag("Oral")
		Anim.AddTag("Blowjob")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ArmbinderBlowjob = PapyrusUtil.PushString(filterQuest.ArmbinderBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_AHogFF(int id)
	String asAnim1 = "DD_B_AHogFF"

	libs.Log("Creating DD_B_AHogFF")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_AHogFF")
	if Anim != none && Anim.Name != "DD_B_AHogFF"
		Anim.Name = "DD_B_AHogFF"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 5)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = -1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = -1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = -2)

		Anim.AddTag("Hogtied")
		Anim.AddTag("Laying")
		Anim.AddTag("Oral")
		Anim.AddTag("Blowjob")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ArmbinderBlowjob = PapyrusUtil.PushString(filterQuest.ArmbinderBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_AKneelFF(int id)
	String asAnim1 = "DD_B_AKneelFF"

	libs.Log("Creating DD_B_AKneelFF")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_AKneelFF")
	if Anim != none && Anim.Name != "DD_B_AKneelFF"
		Anim.Name = "DD_B_AKneelFF"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 7)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Kneeling")
		Anim.AddTag("Oral")
		Anim.AddTag("Blowjob")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ArmbinderBlowjob = PapyrusUtil.PushString(filterQuest.ArmbinderBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_LayAFF(int id)
	String asAnim1 = "DD_B_LayAFF"

	libs.Log("Creating DD_B_LayAFF")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_LayAFF")
	if Anim != none && Anim.Name != "DD_B_LayAFF"
		Anim.Name = "DD_B_LayAFF"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = -2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = 1)

		Anim.AddTag("Laying")
		Anim.AddTag("Oral")
		Anim.AddTag("Blowjob")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ArmbinderBlowjob = PapyrusUtil.PushString(filterQuest.ArmbinderBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_ACG(int id)
	String asAnim1 = "DD_B_ACG"

	libs.Log("Creating DD_B_ACG")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_ACG")
	if Anim != none && Anim.Name != "DD_B_ACG"
		Anim.Name = "DD_B_ACG"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Cowgirl")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ArmbinderVaginal = PapyrusUtil.PushString(filterQuest.ArmbinderVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_AHold(int id)
	String asAnim1 = "DD_B_AHold"

	libs.Log("Creating DD_B_AHold")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_AHold")
	if Anim != none && Anim.Name != "DD_B_AHold"
		Anim.Name = "DD_B_AHold"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 5)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 5)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 7)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = 8)

		Anim.AddTag("Holding")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ArmbinderVaginal = PapyrusUtil.PushString(filterQuest.ArmbinderVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_ASide(int id)
	String asAnim1 = "DD_B_ASide"

	libs.Log("Creating DD_B_ASide")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_ASide")
	if Anim != none && Anim.Name != "DD_B_ASide"
		Anim.Name = "DD_B_ASide"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 7)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = 4)

		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ArmbinderVaginal = PapyrusUtil.PushString(filterQuest.ArmbinderVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_LACunnKnl(int id)
	String asAnim1 = "DD_B_LACunnKnl"

	libs.Log("Creating DD_B_LACunnKnl")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_LACunnKnl")
	if Anim != none && Anim.Name != "DD_B_LACunnKnl"
		Anim.Name = "DD_B_LACunnKnl"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Kneeling")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Cunnilingus")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		Anim.AddTag("Lesbian")

		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ArmbinderLesbian = PapyrusUtil.PushString(filterQuest.ArmbinderLesbian, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_LAFaceSit1(int id)
	String asAnim1 = "DD_B_LAFaceSit1"

	libs.Log("Creating DD_B_LAFaceSit1")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_LAFaceSit1")
	if Anim != none && Anim.Name != "DD_B_LAFaceSit1"
		Anim.Name = "DD_B_LAFaceSit1"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Cunnilingus")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		Anim.AddTag("Lesbian")

		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ArmbinderLesbian = PapyrusUtil.PushString(filterQuest.ArmbinderLesbian, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_LAFingSit(int id)
	String asAnim1 = "DD_B_LAFingSit"

	libs.Log("Creating DD_B_LAFingSit")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_LAFingSit")
	if Anim != none && Anim.Name != "DD_B_LAFingSit"
		Anim.Name = "DD_B_LAFingSit"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Kneeling")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Fingering")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		Anim.AddTag("Lesbian")

		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ArmbinderLesbian = PapyrusUtil.PushString(filterQuest.ArmbinderLesbian, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_LAFingStand(int id)
	String asAnim1 = "DD_B_LAFingStand"

	libs.Log("Creating DD_B_LAFingSit")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_LAFingStand")
	if Anim != none && Anim.Name != "DD_B_LAFingStand"
		Anim.Name = "DD_B_LAFingStand"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Standing")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Fingering")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		Anim.AddTag("Lesbian")

		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ArmbinderLesbian = PapyrusUtil.PushString(filterQuest.ArmbinderLesbian, Anim.Name)
	EndIf
endFunction

;animations edited by krzp

Function CreateDD_ArmbA(int id)
	String asAnim1 = "DD_ArmbA"

	libs.Log("Creating DD_ArmbA")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_ArmbA")
	if Anim != none && Anim.Name != "DD_ArmbA"
		Anim.Name = "DD_ArmbA"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Anal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", forward = -8.5)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", forward = -8.5)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", forward = -26.5)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", forward = -30.0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Cowgirl")
		Anim.AddTag("Laying")
		Anim.AddTag("Anal")		
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ArmbinderAnal = PapyrusUtil.PushString(filterQuest.ArmbinderAnal, Anim.Name)
	EndIf
endFunction

;========================
;ELBOWBINDER
;========================

;animations by SpaceHamster

Function CreateDD_SH_elbBJ1(int id)
	String asAnim1 = "DD_SH_elbBJ1"

	libs.Log("Creating DD_SH_elbBJ1")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_SH_elbBJ1")
	if Anim != none && Anim.Name != "DD_SH_elbBJ1"
		Anim.Name = "DD_SH_elbBJ1"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", silent = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", silent = True, openMouth = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", silent = True, openMouth = False)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.SetStageSoundFX(1, None)

		Anim.AddTag("Kneeling")
		Anim.AddTag("Blowjob")
		Anim.AddTag("Oral")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Elbowbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ElbowbinderBlowjob = PapyrusUtil.PushString(filterQuest.ElbowbinderBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_SH_elbMiss1(int id)
	String asAnim1 = "DD_SH_elbMiss1"

	libs.Log("Creating DD_SH_elbMiss1")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_SH_elbMiss1")
	if Anim != none && Anim.Name != "DD_SH_elbMiss1"
		Anim.Name = "DD_SH_elbMiss1"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S6")

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S6")

		Anim.AddTag("Missionary")
		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Elbowbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ElbowbinderVaginal = PapyrusUtil.PushString(filterQuest.ElbowbinderVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_SH_elbCowg1(int id)
	String asAnim1 = "DD_SH_elbCowg1"

	libs.Log("Creating DD_SH_elbCowg1")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_SH_elbCowg1")
	if Anim != none && Anim.Name != "DD_SH_elbCowg1"
		Anim.Name = "DD_SH_elbCowg1"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Cowgirl")
		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Elbowbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ElbowbinderVaginal = PapyrusUtil.PushString(filterQuest.ElbowbinderVaginal, Anim.Name)
	EndIf
endFunction

;animations edited by krzp

Function CreateDD_ElbndAn(int id)
	String asAnim1 = "DD_ElbndAn"

	libs.Log("Creating DD_ElbndAn")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_ElbndAn")
	if Anim != none && Anim.Name != "DD_ElbndAn"
		Anim.Name = "DD_ElbndAn"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Anal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", forward = -8.5)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", forward = -8.5)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", forward = -26.5)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", forward = -30.0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", forward = -20.5)
		
		Anim.AddTag("Cowgirl")
		Anim.AddTag("Laying")
		Anim.AddTag("Anal")		
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Elbowbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ElbowbinderAnal = PapyrusUtil.PushString(filterQuest.ElbowbinderAnal, Anim.Name)
	EndIf
endFunction

Function CreateDD_ElbL(int id)
	String asAnim1 = "DD_ElbL"

	libs.Log("Creating DD_ElbL")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_ElbL")
	if Anim != none && Anim.Name != "DD_ElbL"
		Anim.Name = "DD_ElbL"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Standing")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Fingering")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		Anim.AddTag("Lesbian")

		Anim.AddTag("DomSub")
		Anim.AddTag("Elbowbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.ElbowbinderLesbian = PapyrusUtil.PushString(filterQuest.ElbowbinderLesbian, Anim.Name)
	EndIf
endFunction

;========================
;YOKE
;========================

;animations from ZaZ Animation Pack

Function CreateDDZapYokeLesbian01Both(int id)
	String asAnim1 = "DD_ZapYokeLesbian01"

	libs.Log("Creating DDZapYokeLesbian01Both")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DDZapYokeLesbian01Both")
	if Anim != none && Anim.Name != "DDZapYokeLesbian01Both"
		Anim.Name = "DDZapYokeLesbian01Both"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", 0, silent = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", 0, silent = False)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", 0, silent = False, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", 0, silent = False, openMouth = True)

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", -110, silent = True)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", -105, silent = True, openMouth = True)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", -100, silent = False, openMouth = True)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", -100, silent = False, openMouth = True)
		
		Anim.SetStageTimer(4, 10.0)

		Anim.AddTag("Arrok")
		Anim.AddTag("Oral")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Laying")
		Anim.AddTag("Loving")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		
		Anim.AddTag("SubSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
	EndIf
endFunction

Function CreateDDZapYokeKissing01(int id)
	String asAnim1 = "DD_ZapYokeKissing01"
	String asAnim2 = "DD_ZapKissing01"

	libs.Log("Creating DDZapYokeKissing01")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DDZapYokeKissing01")
	if Anim != none && Anim.Name != "DDZapYokeKissing01"
		Anim.Name = "DDZapYokeKissing01"
		Anim.SetContent(Foreplay)
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", silent = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", silent = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", silent = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim2 + "_A2_S1", strapon = False, silent = True)
		Anim.AddPositionStage(a2, asAnim2 + "_A2_S2", strapon = False, silent = True)
		Anim.AddPositionStage(a2, asAnim2 + "_A2_S3", strapon = False, silent = True)

		; Anim.SetStageTimer(1, 1.8)
		; Anim.SetStageTimer(2, 15.0)
		Anim.SetStageTimer(3, 0.7)

		Anim.AddTag("Leito")
		Anim.AddTag("Kissing")
		Anim.AddTag("Standing")
		Anim.AddTag("Loving")

		Anim.AddTag("Foreplay")
		Anim.AddTag("MF")
	
		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
	EndIf
endFunction

Function CreateDD_SH_yokeBJ1(int id)
	String asAnim1 = "DD_SH_yokeBJ1"

	libs.Log("Creating DD_SH_yokeBJ1")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_SH_yokeBJ1")
	if Anim != none && Anim.Name != "DD_SH_yokeBJ1"
		Anim.Name = "DD_SH_yokeBJ1"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", silent = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", silent = True, openMouth = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", silent = True, openMouth = False)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.SetStageSoundFX(1, None)

		Anim.AddTag("Blowjob")
		Anim.AddTag("Oral")		

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeBlowjob = PapyrusUtil.PushString(filterQuest.YokeBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_SH_yokeMiss1(int id)
	String asAnim1 = "DD_SH_yokeMiss1"

	libs.Log("Creating DD_SH_yokeMiss1")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_SH_yokeMiss1")
	if Anim != none && Anim.Name != "DD_SH_yokeMiss1"
		Anim.Name = "DD_SH_yokeMiss1"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S6")

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S6")

		Anim.AddTag("Missionary")
		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeVaginal = PapyrusUtil.PushString(filterQuest.YokeVaginal, Anim.Name)
	EndIf
endFunction

;animations by Billyy

Function CreateDD_Billyy_YokeCowgirl(int id)
	String asAnim1 = "DD_Billyy_YokeCowgirl"

	libs.Log("Creating DD_Billyy_YokeCowgirl")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_Billyy_YokeCowgirl")
	if Anim != none && Anim.Name != "DD_Billyy_YokeCowgirl"
		Anim.Name = "DD_Billyy_YokeCowgirl"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = 5)
		
		Anim.AddTag("Cowgirl")
		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeVaginal = PapyrusUtil.PushString(filterQuest.YokeVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_Billyy_YokeDoggy(int id)
	String asAnim1 = "DD_Billyy_YokeDoggy"

	libs.Log("Creating DD_Billyy_YokeDoggy")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_Billyy_YokeDoggy")
	if Anim != none && Anim.Name != "DD_Billyy_YokeDoggy"
		Anim.Name = "DD_Billyy_YokeDoggy"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Doggy")
		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeVaginal = PapyrusUtil.PushString(filterQuest.YokeVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_Billyy_YokeMissionary(int id)
	String asAnim1 = "DD_Billyy_YokeMissionary"

	libs.Log("Creating DD_Billyy_YokeMissionary")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_Billyy_YokeMissionary")
	if Anim != none && Anim.Name != "DD_Billyy_YokeMissionary"
		Anim.Name = "DD_Billyy_YokeMissionary"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Missionary")
		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeVaginal = PapyrusUtil.PushString(filterQuest.YokeVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_Billyy_YokeStanding(int id)
	String asAnim1 = "DD_Billyy_YokeStanding"

	libs.Log("Creating DD_Billyy_YokeStanding")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_Billyy_YokeStanding")
	if Anim != none && Anim.Name != "DD_Billyy_YokeStanding"
		Anim.Name = "DD_Billyy_YokeStanding"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Standing")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeVaginal = PapyrusUtil.PushString(filterQuest.YokeVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_Billyy_YokeFaceFuck(int id)
	String asAnim1 = "DD_Billyy_YokeFaceFuck"

	libs.Log("Creating DD_Billyy_YokeFaceFuck")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_Billyy_YokeFaceFuck")
	if Anim != none && Anim.Name != "DD_Billyy_YokeFaceFuck"
		Anim.Name = "DD_Billyy_YokeFaceFuck"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", 0, silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", 0, silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", 0, silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", 0, silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", 0, silent = True, openMouth = True)
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Kneeling")
		Anim.AddTag("Blowjob")
		Anim.AddTag("Oral")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeBlowjob = PapyrusUtil.PushString(filterQuest.YokeBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_Billyy_Yoke69(int id)
	String asAnim1 = "DD_Billyy_Yoke69"

	libs.Log("Creating DD_Billyy_Yoke69")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_Billyy_Yoke69")
	if Anim != none && Anim.Name != "DD_Billyy_Yoke69"
		Anim.Name = "DD_Billyy_Yoke69"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Laying")
		Anim.AddTag("Blowjob")
		Anim.AddTag("69")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeBlowjob = PapyrusUtil.PushString(filterQuest.YokeBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_Billyy_YokeRevCowgirlAnal(int id)
	String asAnim1 = "DD_Billyy_YokeRevCowgirlAnal"

	libs.Log("Creating DD_Billyy_YokeRevCowgirlAnal")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_Billyy_YokeRevCowgirlAnal")
	if Anim != none && Anim.Name != "DD_Billyy_YokeRevCowgirlAnal"
		Anim.Name = "DD_Billyy_YokeRevCowgirlAnal"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Anal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Laying")
		Anim.AddTag("Anal")
		Anim.AddTag("Cowgirl")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeAnal = PapyrusUtil.PushString(filterQuest.YokeAnal, Anim.Name)
	EndIf
endFunction

Function CreateDD_Billyy_YokeLayingAnal(int id)
	String asAnim1 = "DD_Billyy_YokeLayingAnal"

	libs.Log("Creating DD_Billyy_YokeLayingAnal")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_Billyy_YokeLayingAnal")
	if Anim != none && Anim.Name != "DD_Billyy_YokeLayingAnal"
		Anim.Name = "DD_Billyy_YokeLayingAnal"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Anal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Laying")
		Anim.AddTag("Anal")		
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeAnal = PapyrusUtil.PushString(filterQuest.YokeAnal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_Y692(int id)	
	String asAnim1 = "DD_B_Y692"

	libs.Log("Creating DD_B_Y692")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_Y692")
	if Anim != none && Anim.Name != "DD_B_Y692"
		Anim.Name = "DD_B_Y692"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", openMouth = True)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", openMouth = True)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", openMouth = True)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", openMouth = True)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", openMouth = True)
		
		Anim.AddTag("Laying")
		Anim.AddTag("Blowjob")
		Anim.AddTag("69")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeBlowjob = PapyrusUtil.PushString(filterQuest.YokeBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_YKneelFF(int id)	
	String asAnim1 = "DD_B_YKneelFF"

	libs.Log("Creating DD_B_YKneelFF")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_YKneelFF")
	if Anim != none && Anim.Name != "DD_B_YKneelFF"
		Anim.Name = "DD_B_YKneelFF"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", silent = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 7)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Kneeling")
		Anim.AddTag("Blowjob")
		Anim.AddTag("Oral")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeBlowjob = PapyrusUtil.PushString(filterQuest.YokeBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_YCG(int id)	
	String asAnim1 = "DD_B_YCG"

	libs.Log("Creating DD_B_YCG")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_YCG")
	if Anim != none && Anim.Name != "DD_B_YCG"
		Anim.Name = "DD_B_YCG"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Cowgirl")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeVaginal = PapyrusUtil.PushString(filterQuest.YokeVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_YHold(int id)	
	String asAnim1 = "DD_B_YHold"

	libs.Log("Creating DD_B_YHold")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_YHold")
	if Anim != none && Anim.Name != "DD_B_YHold"
		Anim.Name = "DD_B_YHold"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 5)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 5)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 7)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = 8)
		
		Anim.AddTag("Holding")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeVaginal = PapyrusUtil.PushString(filterQuest.YokeVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_YMiss(int id)	
	String asAnim1 = "DD_B_YMiss"

	libs.Log("Creating DD_B_YMiss")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_YMiss")
	if Anim != none && Anim.Name != "DD_B_YMiss"
		Anim.Name = "DD_B_YMiss"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 3)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = -1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = 0)
		
		Anim.AddTag("Missionary")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeVaginal = PapyrusUtil.PushString(filterQuest.YokeVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_YStand(int id)	
	String asAnim1 = "DD_B_YStand"

	libs.Log("Creating DD_B_YStand")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_YStand")
	if Anim != none && Anim.Name != "DD_B_YStand"
		Anim.Name = "DD_B_YStand"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Standing")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeVaginal = PapyrusUtil.PushString(filterQuest.YokeVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_YDogA(int id)	
	String asAnim1 = "DD_B_YDogA"

	libs.Log("Creating DD_B_YDogA")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_YDogA")
	if Anim != none && Anim.Name != "DD_B_YDogA"
		Anim.Name = "DD_B_YDogA"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Anal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Doggy")
		Anim.AddTag("Laying")
		Anim.AddTag("Anal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeAnal = PapyrusUtil.PushString(filterQuest.YokeAnal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_YStandA(int id)	
	String asAnim1 = "DD_B_YStandA"

	libs.Log("Creating DD_B_YStandA")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_YStandA")
	if Anim != none && Anim.Name != "DD_B_YStandA"
		Anim.Name = "DD_B_YStandA"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Anal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Standing")
		Anim.AddTag("Anal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeAnal = PapyrusUtil.PushString(filterQuest.YokeAnal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_LYCunnKnl(int id)
	String asAnim1 = "DD_B_LYCunnKnl"

	libs.Log("Creating DD_B_LYCunnKnl")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_LYCunnKnl")
	if Anim != none && Anim.Name != "DD_B_LYCunnKnl"
		Anim.Name = "DD_B_LYCunnKnl"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Kneeling")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Cunnilingus")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		Anim.AddTag("Lesbian")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeLesbian = PapyrusUtil.PushString(filterQuest.YokeLesbian, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_LYFaceSit1(int id)
	String asAnim1 = "DD_B_LYFaceSit1"

	libs.Log("Creating DD_B_LYFaceSit1")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_LYFaceSit1")
	if Anim != none && Anim.Name != "DD_B_LYFaceSit1"
		Anim.Name = "DD_B_LYFaceSit1"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Cunnilingus")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		Anim.AddTag("Lesbian")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeLesbian = PapyrusUtil.PushString(filterQuest.YokeLesbian, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_LYFingSit(int id)
	String asAnim1 = "DD_B_LYFingSit"

	libs.Log("Creating DD_B_LYFingSit")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_LYFingSit")
	if Anim != none && Anim.Name != "DD_B_LYFingSit"
		Anim.Name = "DD_B_LYFingSit"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Kneeling")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Fingering")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		Anim.AddTag("Lesbian")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeLesbian = PapyrusUtil.PushString(filterQuest.YokeLesbian, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_LYFingStand(int id)
	String asAnim1 = "DD_B_LYFingStand"

	libs.Log("Creating DD_B_LYFingSit")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_LYFingStand")
	if Anim != none && Anim.Name != "DD_B_LYFingStand"
		Anim.Name = "DD_B_LYFingStand"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Standing")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Fingering")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		Anim.AddTag("Lesbian")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeLesbian = PapyrusUtil.PushString(filterQuest.YokeLesbian, Anim.Name)
	EndIf
endFunction

Function CreateDD_Babo_SneakYokeStandingFuck(int id)	
	String asAnim1 = "DD_Babo_SneakYokeStandingFuck"

	libs.Log("Creating DD_Babo_SneakYokeStandingFuck")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_Babo_SneakYokeStandingFuck")
	if Anim != none && Anim.Name != "DD_Babo_SneakYokeStandingFuck"
		Anim.Name = "DD_Babo_SneakYokeStandingFuck"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 3)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 6)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = 6)
		
		Anim.AddTag("Standing")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.YokeVaginal = PapyrusUtil.PushString(filterQuest.YokeVaginal, Anim.Name)
	EndIf
endFunction

;========================
;BREAST YOKE
;========================

;animations by SpaceHamster

Function CreateDD_SH_bbyokeBJ1(int id)
	String asAnim1 = "DD_SH_bbyokeBJ1"

	libs.Log("Creating DD_SH_bbyokeBJ1")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_SH_bbyokeBJ1")
	if Anim != none && Anim.Name != "DD_SH_bbyokeBJ1"
		Anim.Name = "DD_SH_bbyokeBJ1"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", silent = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", silent = True, openMouth = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", silent = True, openMouth = False)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.SetStageSoundFX(1, None)

		Anim.AddTag("Blowjob")
		Anim.AddTag("Oral")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("BBYoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.BBYokeBlowjob = PapyrusUtil.PushString(filterQuest.BBYokeBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_SH_bbyokeMiss1(int id)
	String asAnim1 = "DD_SH_bbyokeMiss1"

	libs.Log("Creating DD_SH_bbyokeMiss1")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_SH_bbyokeMiss1")
	if Anim != none && Anim.Name != "DD_SH_bbyokeMiss1"
		Anim.Name = "DD_SH_bbyokeMiss1"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S6")

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S6")

		Anim.AddTag("Missionary")
		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("BBYoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.BBYokeVaginal = PapyrusUtil.PushString(filterQuest.BBYokeVaginal, Anim.Name)
	EndIf
endFunction

;animatons edited by krzp

Function CreateDD_BBYoA(int id)
	String asAnim1 = "DD_BBYoA"

	libs.Log("Creating DD_BBYoA")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_BBYoA")
	if Anim != none && Anim.Name != "DD_BBYoA"
		Anim.Name = "DD_BBYoA"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Anal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Standing")
		Anim.AddTag("Anal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("BBYoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.BBYokeAnal = PapyrusUtil.PushString(filterQuest.BBYokeAnal, Anim.Name)
	EndIf
endFunction

;========================
;CUFFED
;========================

;animations by SpaceHamster

Function CreateDD_SH_cuffsFrontBJ1(int id)
	String asAnim1 = "DD_SH_cuffsFrontBJ1"

	libs.Log("Creating DD_SH_cuffsFrontBJ1")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_SH_cuffsFrontBJ1")
	if Anim != none && Anim.Name != "DD_SH_cuffsFrontBJ1"
		Anim.Name = "DD_SH_cuffsFrontBJ1"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", silent = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", silent = True, openMouth = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", silent = True, openMouth = False)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.SetStageSoundFX(1, None)

		Anim.AddTag("Blowjob")
		Anim.AddTag("Oral")		

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedBlowjob = PapyrusUtil.PushString(filterQuest.CuffedBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_SH_cuffsFrontMiss1(int id)
	String asAnim1 = "DD_SH_cuffsFrontMiss1"

	libs.Log("Creating DD_SH_cuffsFrontMiss1")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_SH_cuffsFrontMiss1")
	if Anim != none && Anim.Name != "DD_SH_cuffsFrontMiss1"
		Anim.Name = "DD_SH_cuffsFrontMiss1"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S6")

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S6")

		Anim.AddTag("Missionary")
		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedVaginal = PapyrusUtil.PushString(filterQuest.CuffedVaginal, Anim.Name)
	EndIf
endFunction

;animations by Billyy

Function CreateDD_B_C69(int id)	
	String asAnim1 = "DD_B_C69"

	libs.Log("Creating DD_B_C69")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_C69")
	if Anim != none && Anim.Name != "DD_B_C69"
		Anim.Name = "DD_B_C69"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", openMouth = True)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", openMouth = True)

		Anim.SetStageSoundFX(1, None)

		Anim.AddTag("Laying")
		Anim.AddTag("Blowjob")
		Anim.AddTag("Oral")
		Anim.AddTag("69")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedBlowjob = PapyrusUtil.PushString(filterQuest.CuffedBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_CDogFF(int id)	
	String asAnim1 = "DD_B_CDogFF"

	libs.Log("Creating DD_B_CDogFF")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_CDogFF")
	if Anim != none && Anim.Name != "DD_B_CDogFF"
		Anim.Name = "DD_B_CDogFF"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = 2)

		Anim.SetStageSoundFX(1, None)

		Anim.AddTag("Doggy")
		Anim.AddTag("Blowjob")
		Anim.AddTag("Oral")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedBlowjob = PapyrusUtil.PushString(filterQuest.CuffedBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_CHogFF(int id)	
	String asAnim1 = "DD_B_CHogFF"

	libs.Log("Creating DD_B_CHogFF")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_CHogFF")
	if Anim != none && Anim.Name != "DD_B_CHogFF"
		Anim.Name = "DD_B_CHogFF"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = -1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = -1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = -2)

		Anim.SetStageSoundFX(1, None)

		Anim.AddTag("Laying")
		Anim.AddTag("Blowjob")
		Anim.AddTag("Oral")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedBlowjob = PapyrusUtil.PushString(filterQuest.CuffedBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_KneelCFF(int id)	
	String asAnim1 = "DD_B_KneelCFF"

	libs.Log("Creating DD_B_KneelCFF")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_KneelCFF")
	if Anim != none && Anim.Name != "DD_B_KneelCFF"
		Anim.Name = "DD_B_KneelCFF"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 7)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.SetStageSoundFX(1, None)

		Anim.AddTag("Kneeling")
		Anim.AddTag("Blowjob")
		Anim.AddTag("Oral")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedBlowjob = PapyrusUtil.PushString(filterQuest.CuffedBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_LayCFF(int id)	
	String asAnim1 = "DD_B_LayCFF"

	libs.Log("Creating DD_B_LayCFF")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_LayCFF")
	if Anim != none && Anim.Name != "DD_B_LayCFF"
		Anim.Name = "DD_B_LayCFF"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)

		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = -2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = 1)

		Anim.SetStageSoundFX(1, None)

		Anim.AddTag("Laying")
		Anim.AddTag("Blowjob")
		Anim.AddTag("Oral")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedBlowjob = PapyrusUtil.PushString(filterQuest.CuffedBlowjob, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_CCG(int id)	
	String asAnim1 = "DD_B_CCG"

	libs.Log("Creating DD_B_CCG")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_CCG")
	if Anim != none && Anim.Name != "DD_B_CCG"
		Anim.Name = "DD_B_CCG"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Cowgirl")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedVaginal = PapyrusUtil.PushString(filterQuest.CuffedVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_CDog(int id)	
	String asAnim1 = "DD_B_CDog"

	libs.Log("Creating DD_B_CDog")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_CDog")
	if Anim != none && Anim.Name != "DD_B_CDog"
		Anim.Name = "DD_B_CDog"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = 1)
		
		Anim.AddTag("Doggy")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedVaginal = PapyrusUtil.PushString(filterQuest.CuffedVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_CHold(int id)	
	String asAnim1 = "DD_B_CHold"

	libs.Log("Creating DD_B_CHold")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_CHold")
	if Anim != none && Anim.Name != "DD_B_CHold"
		Anim.Name = "DD_B_CHold"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 5)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 5)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 7)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = 8)
		
		Anim.AddTag("Holding")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedVaginal = PapyrusUtil.PushString(filterQuest.CuffedVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_CMiss(int id)	
	String asAnim1 = "DD_B_CMiss"

	libs.Log("Creating DD_B_CMiss")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_CMiss")
	if Anim != none && Anim.Name != "DD_B_CMiss"
		Anim.Name = "DD_B_CMiss"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 3)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = -1)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = 0)
		
		Anim.AddTag("Missionary")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedVaginal = PapyrusUtil.PushString(filterQuest.CuffedVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_CSide(int id)	
	String asAnim1 = "DD_B_CSide"

	libs.Log("Creating DD_B_CSide")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_CSide")
	if Anim != none && Anim.Name != "DD_B_CSide"
		Anim.Name = "DD_B_CSide"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 6)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4", sos = 0)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5", sos = 4)
		
		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedVaginal = PapyrusUtil.PushString(filterQuest.CuffedVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_CStand(int id)	
	String asAnim1 = "DD_B_CStand"

	libs.Log("Creating DD_B_CStand")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_CStand")
	if Anim != none && Anim.Name != "DD_B_CStand"
		Anim.Name = "DD_B_CStand"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Standing")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedVaginal = PapyrusUtil.PushString(filterQuest.CuffedVaginal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_CDogA(int id)	
	String asAnim1 = "DD_B_CDogA"

	libs.Log("Creating DD_B_CDogA")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_CDogA")
	if Anim != none && Anim.Name != "DD_B_CDogA"
		Anim.Name = "DD_B_CDogA"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Anal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Doggy")
		Anim.AddTag("Laying")
		Anim.AddTag("Anal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedAnal = PapyrusUtil.PushString(filterQuest.CuffedAnal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_CStandA(int id)	
	String asAnim1 = "DD_B_CStandA"

	libs.Log("Creating DD_B_CStandA")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_CStandA")
	if Anim != none && Anim.Name != "DD_B_CStandA"
		Anim.Name = "DD_B_CStandA"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Anal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Standing")
		Anim.AddTag("Anal")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedAnal = PapyrusUtil.PushString(filterQuest.CuffedAnal, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_LCCunnKnl(int id)
	String asAnim1 = "DD_B_LCCunnKnl"

	libs.Log("Creating DD_B_LCCunnKnl")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_LCCunnKnl")
	if Anim != none && Anim.Name != "DD_B_LCCunnKnl"
		Anim.Name = "DD_B_LCCunnKnl"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Kneeling")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Cunnilingus")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		Anim.AddTag("Lesbian")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedLesbian = PapyrusUtil.PushString(filterQuest.CuffedLesbian, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_LCFaceSit1(int id)
	String asAnim1 = "DD_B_LCFaceSit1"

	libs.Log("Creating DD_B_LCFaceSit1")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_LCFaceSit1")
	if Anim != none && Anim.Name != "DD_B_LCFaceSit1"
		Anim.Name = "DD_B_LCFaceSit1"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", openMouth = True)

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Cunnilingus")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		Anim.AddTag("Lesbian")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedLesbian = PapyrusUtil.PushString(filterQuest.CuffedLesbian, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_LCFingSit(int id)
	String asAnim1 = "DD_B_LCFingSit"

	libs.Log("Creating DD_B_LCFingSit")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_LCFingSit")
	if Anim != none && Anim.Name != "DD_B_LCFingSit"
		Anim.Name = "DD_B_LCFingSit"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Kneeling")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Fingering")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		Anim.AddTag("Lesbian")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedLesbian = PapyrusUtil.PushString(filterQuest.CuffedLesbian, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_LCFingStand(int id)
	String asAnim1 = "DD_B_LCFingStand"

	libs.Log("Creating DD_B_LCFingSit")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_LCFingStand")
	if Anim != none && Anim.Name != "DD_B_LCFingStand"
		Anim.Name = "DD_B_LCFingStand"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Standing")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Fingering")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		Anim.AddTag("Lesbian")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedLesbian = PapyrusUtil.PushString(filterQuest.CuffedLesbian, Anim.Name)
	EndIf
endFunction

Function CreateDD_B_CHJ(int id)
	String asAnim1 = "DD_B_CHJ"

	libs.Log("Creating DD_B_CHJ")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_CHJ")
	if Anim != none && Anim.Name != "DD_B_CHJ"
		Anim.Name = "DD_B_CHJ"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, AddCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1", sos = 2)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2", sos = 4)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")

		Anim.AddTag("Kneeling")
		Anim.AddTag("Handjob")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.CuffedOther = PapyrusUtil.PushString(filterQuest.CuffedOther, Anim.Name)
	EndIf
endFunction


;========================
;PET SUIT
;========================

;animations by Billyy

Function CreateDD_B_PS_Doggy(int id)
	String asAnim1 = "DD_B_PS_Doggy"

	libs.Log("Creating DD_B_PS_Doggy")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_PS_Doggy")
	if Anim != none && Anim.Name != "DD_B_PS_Doggy"
		Anim.Name = "DD_B_PS_Doggy"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")		
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("PetSuit")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.PetsuitVaginal = PapyrusUtil.PushString(filterQuest.PetsuitVaginal, Anim.Name)
	EndIf
EndFunction

Function CreateDD_B_PS_DoggyA(int id)
	String asAnim1 = "DD_B_PS_DoggyA"

	libs.Log("Creating DD_B_PS_DoggyA")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_PS_DoggyA")
	if Anim != none && Anim.Name != "DD_B_PS_DoggyA"
		Anim.Name = "DD_B_PS_DoggyA"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Anal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Laying")
		Anim.AddTag("Anal")	
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("PetSuit")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.PetSuitAnal = PapyrusUtil.PushString(filterQuest.PetSuitAnal, Anim.Name)
	EndIf
EndFunction

Function CreateDD_B_PS_DT(int id)
	String asAnim1 = "DD_B_PS_DT"

	libs.Log("Creating DD_B_PS_DT")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_PS_DT")
	if Anim != none && Anim.Name != "DD_B_PS_DT"
		Anim.Name = "DD_B_PS_DT"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female, addCum = Oral)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", silent = True, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5", silent = True, openMouth = True)
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.SetStageSoundFX(1, None)
		
		Anim.AddTag("Laying")
		Anim.AddTag("Blowjob")	
		Anim.AddTag("Oral")
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("PetSuit")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.PetSuitBlowjob = PapyrusUtil.PushString(filterQuest.PetSuitBlowjob, Anim.Name)
	EndIf
EndFunction

Function CreateDD_B_PS_Miss(int id)
	String asAnim1 = "DD_B_PS_Miss"

	libs.Log("Creating DD_B_PS_Miss")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DD_B_PS_Miss")
	if Anim != none && Anim.Name != "DD_B_PS_Miss"
		Anim.Name = "DD_B_PS_Miss"
		Anim.SoundFX = Squishing

		Int a1 = Anim.AddPosition(Female, addCum = Vaginal)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4")
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S5")
		
		Int a2 = Anim.AddPosition(Male)
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S1")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S2")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S3")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S4")
		Anim.AddPositionStage(a2, asAnim1 + "_A2_S5")
		
		Anim.AddTag("Laying")
		Anim.AddTag("Vaginal")		
		Anim.AddTag("Aggressive")

		Anim.AddTag("Sex")
		Anim.AddTag("MF")

		Anim.AddTag("DomSub")
		Anim.AddTag("PetSuit")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
		filterQuest.PetSuitVaginal = PapyrusUtil.PushString(filterQuest.PetSuitVaginal, Anim.Name)
	EndIf
EndFunction

;========================
;OTHER/MIXED
;========================

;animations from ZaZ Animation Pack

Function CreateDDZapMixLesbian01ArmbYoke(int id)
	; Source = ZAP, a1(F) = armbinder, a2(F) = yoke
	; Define animation prefixes for each actor (must correspond to names in FNIS), add more if necessary
	String asAnim1 = "DD_ZapArmbLesbian01"
	String asAnim2 = "DD_ZapYokeLesbian01"

	libs.Log("Creating DDZapMixLesbian01ArmbYoke")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DDZapMixLesbian01ArmbYoke")
	if Anim != none && Anim.Name != "DDZapMixLesbian01ArmbYoke"
		Anim.Name = "DDZapMixLesbian01ArmbYoke"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", silent = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", silent = False)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", silent = False, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", silent = False, openMouth = True)

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim2 + "_A2_S1", -110, silent = True)
		Anim.AddPositionStage(a2, asAnim2 + "_A2_S2", -105, silent = True, openMouth = True)
		Anim.AddPositionStage(a2, asAnim2 + "_A2_S3", -100, silent = False, openMouth = True)
		Anim.AddPositionStage(a2, asAnim2 + "_A2_S4", -100, silent = False, openMouth = True)
		
		Anim.SetStageTimer(4, 10.0)

		Anim.AddTag("Arrok")
		Anim.AddTag("Oral")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Laying")
		Anim.AddTag("Loving")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		
		Anim.AddTag("SubSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
	EndIf
endFunction

Function CreateDDZapMixLesbian01YokeArmb(int id)
	String asAnim1 = "DD_ZapYokeLesbian01"
	String asAnim2 = "DD_ZapArmbLesbian01"

	libs.Log("Creating DDZapMixLesbian01YokeArmb")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DDZapMixLesbian01YokeArmb")
	if Anim != none && Anim.Name != "DDZapMixLesbian01YokeArmb"
		Anim.Name = "DDZapMixLesbian01YokeArmb"
		Anim.SoundFX = Sucking

		Int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S1", 0, silent = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S2", 0, silent = False)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S3", 0, silent = False, openMouth = True)
		Anim.AddPositionStage(a1, asAnim1 + "_A1_S4", 0, silent = False, openMouth = True)

		Int a2 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a2, asAnim2 + "_A2_S1", -110, silent = True)
		Anim.AddPositionStage(a2, asAnim2 + "_A2_S2", -105, silent = True, openMouth = True)
		Anim.AddPositionStage(a2, asAnim2 + "_A2_S3", -100, silent = False, openMouth = True)
		Anim.AddPositionStage(a2, asAnim2 + "_A2_S4", -100, silent = False, openMouth = True)
		
		Anim.SetStageTimer(4, 10.0)

		Anim.AddTag("Arrok")
		Anim.AddTag("Oral")
		Anim.AddTag("Vaginal")
		Anim.AddTag("Laying")
		Anim.AddTag("Loving")

		Anim.AddTag("Sex")
		Anim.AddTag("FF")
		
		Anim.AddTag("SubSub")
		Anim.AddTag("Yoke")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")

		Anim.Save(-1)
	EndIf
endFunction
