Scriptname zadNPCGagUpdater extends Quest

zadexpressionlibs   Property zadExp                         auto ;required to update gag expression of actor
Quest               Property zadNPCGagSlots                 auto ;Quest which slots all nearby NPCs for Gag update
Int                 Property zadNPCGagUpdateTime    = 5     auto ;update time, should be configurable in future with MCM

; Change updater state
; Can be used to disabled this script 
Bool                        _Disabled               = false
Bool                Property Disabled Hidden
    Bool Function Get()
        return _Disabled
    EndFunction
    Function Set(Bool akVal)
        _Disabled = akVal
        if _Disabled
            GoToState("Disabled")   ;disable script
        else
            GoToState("")           ;enable script
        endif
    EndFunction
EndProperty

;init
Event OnInit()
    ;Utility.wait(1.0)
    ;;wait minute before starting update loop. Should be Ok unless actor tried to gag the actor directly as first thing after starting new game
    ;RegisterForSingleUpdate(60)
EndEvent

;main update loop
Event OnUpdate()
    ;Evaluate()
    ;RegisterForSingleUpdate(zadNPCGagUpdateTime)
EndEvent

Function Evaluate()
    ;;update slots, so only closests actors are stored
    ;zadNPCGagSlots.Stop()
    ;Utility.wait(0.25) ;wait little time for quest to fully stop
    ;zadNPCGagSlots.Start()
    ;Utility.wait(0.25) ;wait little time for quest to fully start
    ;
    ;Int loc_index       = 0
    ;Int loc_aliasNum    = zadNPCGagSlots.GetNumAliases()
    ;
    ;while loc_index < loc_aliasNum
    ;    ReferenceAlias  loc_ref     = (zadNPCGagSlots.GetNthAlias(loc_index) as ReferenceAlias)
    ;    Actor           loc_actor   = loc_ref.GetReference() as Actor
    ;    if loc_actor
    ;        loc_ref.clear()
    ;        zadExp.ApplyGagEffect(loc_actor)
    ;        loc_index += 1
    ;    else
    ;        ;no more actors found, end the loop
    ;        loc_index = loc_aliasNum
    ;    endif
    ;    Utility.wait(0.01) ;wait for menu to close before continuing
    ;endwhile
EndFunction

;disabled state
State Disabled
    Event OnUpdate()
        RegisterForSingleUpdate(30)
    EndEvent
    Function Evaluate()
    EndFunction
EndState