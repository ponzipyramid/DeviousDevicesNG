Scriptname zadxUpdater extends Quest  

zadxlibs Property xlibs auto
float currentVersion = 0.0
bool initDone = false 
Event OnInit()
    RegisterForSingleUpdate(5.0)
EndEvent

Event OnUpdate()
	If !initDone
		initDone = true
		Maintenance()
	EndIf
EndEvent

Function Maintenance()
	If xlibs.GetVersion() > currentVersion
		xlibs.Stop()
		Utility.Wait(1.0)
		xlibs.Start()
		xlibs.VersionUpdate()
		xlibs.log("Updated to " + xlibs.GetVersion() + " from " + currentVersion + ".")
		currentVersion = xlibs.GetVersion()
	EndIf
	xlibs.RegisterEvents()
EndFunction
