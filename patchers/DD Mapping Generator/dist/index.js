
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
            locals.data = {
                'mapping': []
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
                const getRecordFormData = (record) => {
                    const editorId = xelib.GetValue(record, 'EDID')

                    const hexId = xelib.GetHexFormID(record)
                    const modIndex = parseInt(hexId.slice(0, 2))

                    const mod = xelib.FileByLoadOrder(modIndex)
                    const espName = xelib.GetFileName(mod)

                    const formId = Number('0x' + hexId.slice(2))
    
                    return {editorId, formId, espName}
                }

                const edid = xelib.GetValue(record, 'EDID')
                
                helpers.logMessage(`Patching inventory device: ${edid}`);

                const invData = {...getRecordFormData(record)}
                const scriptName = xelib.GetValue(record, "VMAD\\Scripts\\[0]\\scriptName")

                helpers.logMessage(`Found script name ${scriptName}`)

                const script = xelib.GetScript(record, scriptName)
                if (script) {
                    const property = xelib.GetScriptProperty(script, 'deviceRendered')

                    if (property) {
                        
                        const formId = xelib.GetUIntValue(property, "Value\\Object Union\\Object v2\\FormID")
                        const rendered = xelib.GetRecord(0, formId)
                        
                        invData['rendered'] = getRecordFormData(rendered)

                    } else {
                        helpers.logMessage('could not find property')
                    }
                } else {
                    helpers.logMessage('could not find script')
                }
                
                locals.data['mapping'].push(invData)
            }
        }],
        finalize: function() {
            fh.saveJsonFile('./devices.json', JSON.stringify(locals.data)) // will create file in root directory of z-edit installation
        }
    })
});

