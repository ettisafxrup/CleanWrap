; ==========================================================
; CleanWrap Installer
; Version: 1.0
; Author: Ettisaf Rup
; ==========================================================

#define MyAppName "CleanWrap"
#define MyAppVersion "1.0.1"
#define MyAppPublisher "XtendArena"
#define MyAppURL "https://ettisafxrup.github.io/CleanWrap"

[Setup]
AppId={{F82485E8-1EDB-4B19-8C10-D3A558513B5D}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}

DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}

UninstallDisplayIcon={app}\{#MyAppName}_v{#MyAppVersion}_Setup

ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible

Compression=lzma2
SolidCompression=yes

WizardStyle=modern

DisableProgramGroupPage=no

OutputDir=D:\Codes\CleanWrap\release
OutputBaseFilename={#MyAppName}_v{#MyAppVersion}_Setup

SetupIconFile=D:\Codes\CleanWrap\assets\cleanwrap.ico

LicenseFile=D:\Codes\CleanWrap\LICENSE

InfoBeforeFile=D:\Codes\CleanWrap\docs\GREETING.txt
InfoAfterFile=D:\Codes\CleanWrap\docs\THANK_YOU.txt

WizardImageFile=D:\Codes\CleanWrap\assets\installer_banner.bmp
WizardSmallImageFile=D:\Codes\CleanWrap\assets\installer_icon.bmp

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

;=============================================================
; Optional Tasks
;=============================================================

[Tasks]

Name: "contextmenu"; \
Description: "Add ""🧹 Organize with CleanWrap"" to Explorer Context Menu"; \
GroupDescription: "Additional Tasks:"; \
Flags: checkedonce

Name: "startup"; \
Description: "Automatically organize your Downloads folder when Windows starts."; \
GroupDescription: "Additional Tasks:"; \
Flags: checkedonce

;=============================================================
; Files
;=============================================================

[Files]

Source: "D:\Codes\CleanWrap\CleanWrap.exe"; DestDir: "{app}"; Flags: ignoreversion

Source: "D:\Codes\CleanWrap\docs\CleanWrap_User_Manual_v1.0.txt"; DestDir: "{app}"; Flags: ignoreversion

Source: "D:\Codes\CleanWrap\LICENSE"; DestDir: "{app}"; Flags: ignoreversion

Source: "D:\Codes\CleanWrap\docs\README.txt"; DestDir: "{app}"; Flags: ignoreversion

;=============================================================
; Shortcuts
;=============================================================

[Icons]

Name: "{group}\CleanWrap"; Filename: "{app}\{#MyAppName}"

Name: "{group}\README"; Filename: "{app}\Userfiles\README.txt"

Name: "{group}\User Manual"; Filename: "{app}\Userfiles\CleanWrap_User_Manual_v1.0.txt"

Name: "{group}\Uninstall CleanWrap"; Filename: "{uninstallexe}"

;=============================================================
; Explorer Context Menu
;=============================================================

[Registry]

Root: HKCR; \
Subkey: "Directory\Background\shell\CleanWrap"; \
ValueType: string; \
ValueData: "🧹 Organize with CleanWrap"; \
Tasks: contextmenu; \
Flags: uninsdeletekey

Root: HKCR; \
Subkey: "Directory\Background\shell\CleanWrap"; \
ValueType: string; \
ValueName: "Icon"; \
ValueData: "{app}\{#MyAppName}.exe"; \
Tasks: contextmenu

Root: HKCR; \
Subkey: "Directory\Background\shell\CleanWrap\command"; \
ValueType: string; \
ValueData: """{app}\{#MyAppName}.exe"" ""%V"""; \
Tasks: contextmenu; \
Flags: uninsdeletekey

;=============================================================
; Startup Option
;=============================================================

Root: HKLM; \
Subkey: "Software\Microsoft\Windows\CurrentVersion\Run"; \
ValueType: string; \
ValueName: "CleanWrap"; \
ValueData: """{app}\{#MyAppName}"""; \
Tasks: startup; \
Flags: uninsdeletevalue

;=============================================================
; Run After Installation (I DONT NEED IT HERE)
;=============================================================

[Run]

; Filename: "{app}\{#MyAppName}_v{#MyAppVersion}_Setup"; \
; Description: "Launch CleanWrap"; \
; Flags: nowait postinstall skipifsilent