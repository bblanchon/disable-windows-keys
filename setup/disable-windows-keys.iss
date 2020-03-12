; Disable Windows Keys
; https://bblanchon.github.io/disable-windows-keys
; Copyright (C) 2020  Benoit Blanchon

#ifndef BuildDir
#define BuildDir     "..\build\vs2019\app\Debug"
#endif
                                                
#define MainExe     "disable-windows-keys.exe"

#define Version      GetStringFileInfo(BuildDir + "\" + MainExe, "ProductVersion")

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{194E6FB7-14A0-4244-9B23-6102C748B287}
AppName={cm:AppName}
AppVersion={#Version}
AppVerName={cm:AppName}
AppPublisher="Benoit Blanchon"
AppSupportURL="https://github.com/bblanchon/disable-windows-keys/issues"
DefaultDirName={userpf}\disable-windows-keys
DisableDirPage=yes
DisableProgramGroupPage=yes
DisableReadyPage=yes
OutputBaseFilename=disable-windows-keys-{#Version}
Compression=lzma
ShowLanguageDialog=no
SolidCompression=yes
#ifdef SignTool
SignTool={#SignTool}
#endif
UninstallDisplayIcon={app}\{#MainExe}
PrivilegesRequired=lowest

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl,Languages/English.isl"; LicenseFile: "..\LICENSE.txt"
Name: "french"; MessagesFile: "compiler:Languages/French.isl,Languages/French.isl"; LicenseFile: "Licenses/French.txt"
Name: "german"; MessagesFile: "compiler:Languages/German.isl,Languages/German.isl"; LicenseFile: "Licenses/German.txt"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"

[Files]
Source: "{#BuildDir}\*.exe"; DestDir: "{app}"; Flags: ignoreversion signonce
Source: "{#BuildDir}\*.dll"; DestDir: "{app}"; Flags: ignoreversion signonce

[Icons]
Name: "{userprograms}\{cm:AppName}"; Filename: "{app}\{#MainExe}";
Name: "{userdesktop}\{cm:AppName}"; Filename: "{app}\{#MainExe}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MainExe}"; Description: "{cm:LaunchProgram}"; Flags: nowait postinstall skipifsilent
