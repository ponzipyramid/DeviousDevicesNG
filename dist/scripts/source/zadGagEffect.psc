ScriptName zadGagEffect extends ActiveMagicEffect

; Libraries
zadLibs Property Libs Auto
SexLabFramework Property Sexlab Auto

;reworked ClearMFG to prevent expression loss
Function ClearMFG(actor ActorRef)
    libs.RemoveGagEffect(ActorRef)
EndFunction

Event OnEffectFinish(Actor akTarget, Actor akCaster)
    Utility.Wait(0.2) ; Wait for menus to close
    ClearMFG(akTarget)
EndEvent