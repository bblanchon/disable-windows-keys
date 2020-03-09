#define AppName        "Disable Windows Keys"

#ifndef BuildDir
#define BuildDir     "..\out\build\x64-Debug\app"
#endif

#define MainExe     "disable-windows-keys.exe"

#define Version      "1.0.0"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{194E6FB7-14A0-4244-9B23-6102C748B287}
AppName={#AppName}
AppVersion={#Version}
AppVerName={#AppName}
AppPublisher="Benoit Blanchon"
AppSupportURL="https://github.com/bblanchon/disable-windows-keys/issues"
DefaultDirName={userpf}\{#AppName}
DisableDirPage=yes
DisableProgramGroupPage=yes
DisableReadyPage=yes
OutputBaseFilename=disable-windows-keys
Compression=lzma
SolidCompression=yes
#ifdef SignTool
SignTool={#SignTool}
#endif
UninstallDisplayIcon={app}\{#MainExe}
PrivilegesRequired=lowest

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"

[Files]
Source: "{#BuildDir}\*.exe"; DestDir: "{app}"; Flags: ignoreversion signonce
Source: "{#BuildDir}\*.dll"; DestDir: "{app}"; Flags: ignoreversion signonce

[Icons]
Name: "{userprograms}\{#AppName}"; Filename: "{app}\{#MainExe}";
Name: "{userdesktop}\{#AppName}"; Filename: "{app}\{#MainExe}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MainExe}"; Description: "{cm:LaunchProgram,{#StringChange(AppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
