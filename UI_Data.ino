char buffer[16];
#define sizeOfStringBuffer 7
String stringBuffer[sizeOfStringBuffer];
char dataInBuffer;

// Menu 0 - Main Menu
// {"Demo", "Connection Type", "Manual Control", "Settings"}
const char S_Demo[] PROGMEM = "Demo";
const char S_Connection_Type[] PROGMEM = "Connection Type";
const char S_Manual_Control[] PROGMEM = "Manual Control";
const char S_Settings[] PROGMEM = "Settings";

const char *const menus[] PROGMEM = {S_Demo, S_Connection_Type, S_Manual_Control, S_Settings};
const byte numOfMenus = 4;

// Menu 2 - Connection Type
// {"Serial", "Bluetooth", "Controller"}
const char S_Serial[] PROGMEM = "Serial";
const char S_Bluetooth[] PROGMEM = "Bluetooth";
const char S_Controller[] PROGMEM = "Controller";

const char *const typesOfConnections[] PROGMEM = {S_Serial, S_Bluetooth, S_Controller};
const byte numOfConnections = 3;


// Menu 3 - Manual Control
// {"Finger 1", "Finger 2", "Finger 3", "Finger 4", "Finger 5", "ALL"}
const char S_Finger_1[] PROGMEM = "Finger 1";
const char S_Finger_2[] PROGMEM = "Finger 2";
const char S_Finger_3[] PROGMEM = "Finger 3";
const char S_Finger_4[] PROGMEM = "Finger 4";
const char S_Finger_5[] PROGMEM = "Finger 5";
const char S_ALL[] PROGMEM = "All";

const char *const fingerList[] PROGMEM = {S_Finger_1, S_Finger_2, S_Finger_3, S_Finger_4, S_Finger_5};
const char *const fingerListAndAll[] PROGMEM = {S_Finger_1, S_Finger_2, S_Finger_3, S_Finger_4, S_Finger_5, S_ALL};


// Menu 4 - settings
// {"Configuration", "Debug"}
const char S_Configuration[] PROGMEM = "Configuration";
const char S_Debug[] PROGMEM = "Debug";

const char *const settings[] PROGMEM = {S_Configuration, S_Debug};
const byte numOfSettings = 2;

// Menu 5 - callibration
// {"Direction", "Range", "Pulses", "Hold Position",  "Save Settings", "Factory Reset"}
const char S_Direction[] PROGMEM = "Direction";
const char S_Range[] PROGMEM = "Range";
const char S_Pulses[] PROGMEM = "Pulses";
const char S_Hold_Position[] PROGMEM = "Hold Position";
const char S_Save_Settings[] PROGMEM = "Save Settings";
const char S_Factory_Reset[] PROGMEM = "Factory Reset";

const char *const callibrationOptions[] PROGMEM = {S_Direction, S_Range, S_Pulses, S_Hold_Position, S_Save_Settings, S_Factory_Reset};
const byte numOfCOptions = 6;

// Menu 7
// {"Back", "I Want To Reset"}
const char S_Back[] PROGMEM = "Back";
const char S_I_Want_To_Reset[] PROGMEM = "I Want To Reset";

const char *const confirmMenu[] PROGMEM = {S_Back, S_I_Want_To_Reset};
const byte numOfConfirm = 2;
