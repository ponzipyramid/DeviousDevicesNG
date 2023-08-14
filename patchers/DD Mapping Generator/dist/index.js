
registerPatcher({
    info: info,
    gameModes: [xelib.gmSSE],
    settings: {
        label: 'Devious Devices Mapping Gen',
        hide: true,
    },
    requiredFiles: [],
    getFilesToPatch: function() {
        return [...['Devious Devices - Integration', 'Devious Devices - Expansion'].map(str => str + '.esm')];
    },
    execute: (patchFile, helpers, settings, locals) => ({
        initialize: function() {
            locals.data = []
            locals.getRecordFormData = (record) => {
                const editorId = xelib.GetValue(record, 'EDID')

                const hexId = xelib.GetHexFormID(record)
                const modIndex = parseInt(hexId.slice(0, 2))

                const mod = xelib.FileByLoadOrder(modIndex)
                const espName = xelib.GetFileName(mod)

                const formId = Number('0x' + hexId.slice(2))

                return {editorId, formId, espName}
            }

            locals.setPropertyFormInfo = (script, propertyName, invData, fieldName) => {
                let property = xelib.GetScriptProperty(script, propertyName)

                if (property) {
                    
                    const formId = xelib.GetUIntValue(property, "Value\\Object Union\\Object v2\\FormID")

                    if (formId) {
                        const rendered = xelib.GetRecord(0, formId)
                        invData[fieldName] = locals.getRecordFormData(rendered)
                    } else {
                        invData[fieldName] = {invalid: true}
                    }
                    

                } else {
                    helpers.logMessage(`could not find property ${propertyName}`)
                }
            }
        },
        process: [{
            load: {
                signature: 'ARMO',
                filter: function(record) {
                    return xelib.HasKeyword(record, "zad_InventoryDevice")
                }
            },
            patch: function(record) {

                const edid = xelib.GetValue(record, 'EDID')
                
                helpers.logMessage(`Patching inventory device: ${edid}`);

                const invData = {...locals.getRecordFormData(record)}
                const scriptName = xelib.GetValue(record, "VMAD\\Scripts\\[0]\\scriptName")

                helpers.logMessage(`Found script name ${scriptName}`)

                const script = xelib.GetScript(record, scriptName)
                if (script) {
                    
                    locals.setPropertyFormInfo(script, 'deviceRendered', invData, 'rendered')

                    locals.setPropertyFormInfo(script, 'zad_DeviceMsg', invData, 'equipMenu')
                    locals.setPropertyFormInfo(script, 'zad_DeviousDevice', invData, 'kwd')

                    /*
                    locals.setPropertyFormInfo(script, 'EquipConflictingDevices', invData, 'equipConflictingDeviceKwds')
                    locals.setPropertyFormInfo(script, 'EquipRequiredDevices', invData, 'requiredDeviceKwds')
                    locals.setPropertyFormInfo(script, 'UnEquipConflictingDevices', invData, 'unequipConflictingDeviceKwds')
                    */

                    let property = xelib.GetScriptProperty(script, 'EquipConflictingDevices')

                    if (property) {
                        helpers.logMessage("Found property")
                    }
                } else {
                    helpers.logMessage('could not find script')
                }
                
                locals.data.push(invData)
            }
        }],
        finalize: function() {
            fh.saveJsonFile('./devices.json', JSON.stringify(locals.data)) // will create file in root directory of z-edit installation
        }
    })
});