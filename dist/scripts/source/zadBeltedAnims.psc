scriptname zadBeltedAnims extends sslAnimationFactory
zadLibs Property libs Auto
SexlabFramework Property Sexlab Auto
zadBQ00 Property filterQuest Auto

function LoadAnimations()
	libs.log("Devious Devices is now creating animations.")
	SexLab = SexLabUtil.GetAPI()
	If SexLab == None
		libs.Error("Animation registration failed: SexLab is none.")
	EndIf
	if filterQuest == None
		libs.Error("Animation registration failed: FilterQuest is none.")
	EndIf
	SexLab.GetSetAnimationObject("DDBeltedSolo", "CreateDDBeltedSolo", filterQuest)
	SexLab.GetSetAnimationObject("DDArmbinderSolo", "CreateDDArmbinderSolo", filterQuest)
	SexLab.GetSetAnimationObject("DDYokeSolo", "CreateDDYokeSolo", filterQuest)
	SexLab.GetSetAnimationObject("DDElbowbinderSolo", "CreateDDElbowinderSolo", filterQuest)
	SexLab.GetSetAnimationObject("DDBBYokeSolo", "CreateDDBBYokeSolo", filterQuest)
	SexLab.GetSetAnimationObject("DDFrontCuffsSolo", "CreateDDFrontCuffsSolo", filterQuest)
	SexLab.GetSetAnimationObject("DDElbowTieSolo", "CreateDDElbowTieSolo", filterQuest)
EndFunction

Function CreateDDBeltedSolo(int id)
	libs.Log("Creating DDBeltedSolo")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DDBeltedSolo")
	if Anim != none && Anim.Name != "DDBeltedSolo"
		Anim.Name = "DDBeltedSolo"

		int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, "DDBeltedSolo")
		
		Anim.AddTag("Solo")
		Anim.AddTag("F")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")
		
		Anim.Save(-1)
	EndIf
EndFunction

Function CreateDDArmbinderSolo(int id)
	libs.Log("Creating DDArmbinderSolo")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DDArmbinderSolo")
	if Anim != none && Anim.Name != "DDArmbinderSolo"
		Anim.Name = "DDArmbinderSolo"

		int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, "ft_horny_armbinder_7")
		
		Anim.AddTag("Solo")
		Anim.AddTag("F")
		Anim.AddTag("Armbinder")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")
		
		Anim.Save(-1)
		filterQuest.BoundMasturbation = PapyrusUtil.PushString(filterQuest.BoundMasturbation, Anim.Name)
	EndIf
EndFunction

Function CreateDDYokeSolo(int id)
	libs.Log("Creating CreateDDYokeSolo")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DDYokeSolo")
	if Anim != none && Anim.Name != "DDYokeSolo"
		Anim.Name = "DDyokeSolo"

		int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, "ft_horny_yoke_7")
		
		Anim.AddTag("Solo")
		Anim.AddTag("F")
		Anim.AddTag("Yoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")
		
		Anim.Save(-1)
		filterQuest.BoundMasturbation = PapyrusUtil.PushString(filterQuest.BoundMasturbation, Anim.Name)
	EndIf
EndFunction

Function CreateDDElbowinderSolo(int id)
	libs.Log("Creating DDElbowbinderSolo")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DDElbowbinderSolo")
	if Anim != none && Anim.Name != "DDElbowbinderSolo"
		Anim.Name = "DDElbowbinderSolo"

		int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, "ft_horny_elbowbinder_7")
		
		Anim.AddTag("Solo")
		Anim.AddTag("F")
		Anim.AddTag("DDElbowbinderSolo")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")
		
		Anim.Save(-1)
		filterQuest.BoundMasturbation = PapyrusUtil.PushString(filterQuest.BoundMasturbation, Anim.Name)
	EndIf
EndFunction

Function CreateDDBBYokeSolo(int id)
	libs.Log("Creating CreateDDBBYokeSolo")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DDBBYokeSolo")
	if Anim != none && Anim.Name != "DDBBYokeSolo"
		Anim.Name = "DDBBYokeSolo"

		int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, "ft_horny_bbyoke_7")
		
		Anim.AddTag("Solo")
		Anim.AddTag("F")
		Anim.AddTag("BBYoke")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")
		
		Anim.Save(-1)
		filterQuest.BoundMasturbation = PapyrusUtil.PushString(filterQuest.BoundMasturbation, Anim.Name)
	EndIf
EndFunction

Function CreateDDFrontCuffsSolo(int id)
	libs.Log("Creating CreateDDFrontCuffsSolo")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DDFrontCuffsSolo")
	if Anim != none && Anim.Name != "DDFrontCuffsSolo"
		Anim.Name = "DDFrontCuffsSolo"

		int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, "ft_horny_frontcuffs_7")
		
		Anim.AddTag("Solo")
		Anim.AddTag("F")
		Anim.AddTag("FrontCuffs")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")
		
		Anim.Save(-1)
		filterQuest.BoundMasturbation = PapyrusUtil.PushString(filterQuest.BoundMasturbation, Anim.Name)
	EndIf
EndFunction

Function CreateDDElbowTieSolo(int id)
	libs.Log("Creating CreateDDElbowTieSolo")
	sslBaseAnimation Anim = SexLab.GetAnimationObject("DDElbowTieSolo")
	if Anim != none && Anim.Name != "DDElbowTieSolo"
		Anim.Name = "DDElbowTieSolo"

		int a1 = Anim.AddPosition(Female)
		Anim.AddPositionStage(a1, "DDElbowTie_hornytwo")
		
		Anim.AddTag("Solo")
		Anim.AddTag("F")
		Anim.AddTag("ElbowTie")
		Anim.AddTag("DeviousDevice")
		Anim.AddTag("NoSwap")
		
		Anim.Save(-1)
		filterQuest.BoundMasturbation = PapyrusUtil.PushString(filterQuest.BoundMasturbation, Anim.Name)
	EndIf
EndFunction