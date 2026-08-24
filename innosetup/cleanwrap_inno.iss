; ==========================================================
; CleanWrap Installer
; Version: 1.0
; Author: Ettisaf Rup
; ==========================================================

#define CleanWrapName "CleanWrap"
#ifndef CleanWrapVersion
#define CleanWrapVersion "0.0.0"
#endif
#define CleanWrapPublisher "XtendArena"
#define CleanWrapURL "https://ettisafxrup.github.io/CleanWrap"

[Setup]
AppId={{F82485E8-1EDB-4B19-8C10-D3A558513B5D}
AppName={#CleanWrapName}
AppVersion={#CleanWrapVersion}
AppPublisher={#CleanWrapPublisher}
AppPublisherURL={#CleanWrapURL}
AppSupportURL={#CleanWrapURL}
AppUpdatesURL={#CleanWrapURL}

DefaultDirName={autopf}\{#CleanWrapName}
DefaultGroupName={#CleanWrapName}

UninstallDisplayIcon={app}\{#CleanWrapName}_v{#CleanWrapVersion}_Setup

ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible

Compression=lzma2
SolidCompression=yes

WizardStyle=modern

DisableProgramGroupPage=no

OutputDir=D:\Codes\CleanWrap\release
OutputBaseFilename={#CleanWrapName}_v{#CleanWrapVersion}_Setup

SetupIconFile=D:\Codes\CleanWrap\assets\cleanwrap.ico

LicenseFile=D:\Codes\CleanWrap\LICENSE

InfoBeforeFile=D:\Codes\CleanWrap\docs\.txt\GREETING.txt
InfoAfterFile=D:\Codes\CleanWrap\docs\.txt\THANK_YOU.txt

WizardImageFile=D:\Codes\CleanWrap\assets\installer_banner.bmp
WizardSmallImageFile=D:\Codes\CleanWrap\assets\installer_icon.bmp

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

;=============================================================
; Optional Tasks
;=============================================================

[Tasks]

Name: "contextmenu"; \
Description: "Add ""🧹 Organize with CleanWrap"" to your Mouse Left-Click Optionbox for Instant File Organizer!"; \
GroupDescription: "Additional Tasks:"; \
Flags: checkedonce

Name: "startup"; \
Description: "Automatically organize your Downloads folder when Windows starts."; \
GroupDescription: "Additional Tasks:"; \
Flags: checkedonce

Name: "desktopstartup"; \
Description: "Automatically organize your Desktop when Windows starts."; \
GroupDescription: "Additional Tasks:"; \
Flags: unchecked

;=============================================================
; Files
;=============================================================

[Files]

Source: "D:\Codes\CleanWrap\CleanWrap.exe"; DestDir: "{app}"; Flags: ignoreversion

Source: "D:\Codes\CleanWrap\docs\.txt\CleanWrap_User_Manual_v1.0.txt"; DestDir: "{app}"; Flags: ignoreversion

Source: "D:\Codes\CleanWrap\LICENSE"; DestDir: "{app}"; Flags: ignoreversion

Source: "D:\Codes\CleanWrap\docs\.txt\README.txt"; DestDir: "{app}"; Flags: ignoreversion

;=============================================================
; Shortcuts
;=============================================================

[Icons]

Name: "{group}\CleanWrap"; Filename: "{app}\{#CleanWrapName}"

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
ValueData: "{app}\{#CleanWrapName}.exe"; \
Tasks: contextmenu

Root: HKCR; \
Subkey: "Directory\Background\shell\CleanWrap\command"; \
ValueType: string; \
ValueData: """{app}\{#CleanWrapName}.exe"" ""%V"""; \
Tasks: contextmenu; \
Flags: uninsdeletekey

;=============================================================
; Startup Option (Runs after every Machine boot)
;=============================================================

Root: HKLM; \
Subkey: "Software\Microsoft\Windows\CurrentVersion\Run"; \
ValueType: string; \
ValueName: "CleanWrap"; \
ValueData: """{app}\{#CleanWrapName}"""; \
Tasks: startup; \
Flags: uninsdeletevalue

Root: HKCU; \
Subkey: "Software\Microsoft\Windows\CurrentVersion\Run"; \
ValueType: string; \
ValueName: "CleanWrapDesktop"; \
ValueData: """{app}\{#CleanWrapName}"" ""{userdesktop}"""; \
Tasks: desktopstartup; \
Flags: uninsdeletevalue

;=============================================================
; Run After Installation (I DONT NEED IT HERE)
;=============================================================

[Run]

; Filename: "{app}\{#CleanWrapName}_v{#CleanWrapVersion}_Setup"; \
; Description: "Launch CleanWrap"; \
; Flags: nowait postinstall skipifsilent