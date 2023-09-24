//===========================================================
// Preprocessor switches for disabling/toggling some features
//===========================================================

//allows to call papyrus functions without waiting for frame, making calls much faster
#define DD_ALLOWFASTPAPYRUSCALL_S       1U

//prints content of database to log file after database is loaded
//printing the content only takes time, and users don't care about it
//so this feature should be only used for debugging/development
#define DD_PRINTDB                      0U

//logging is enabled
#define DD_LOGENABLED                   1U

// equip rework enabled
#define DD_EQREWORKON                   0U