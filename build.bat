setlocal

: remove MinGW from PATH
@set PATH=%PATH:C:\MinGW\bin;=%
@set CONFIGURATION=Release
@set SOURCE_DIR=%~dp0
@set BUILD_DIR=%~dp0build\staging
@set SETUP_DIR=%BUILD_DIR%\setup\%CONFIGURATION%

: call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat" || goto :ERROR

mkdir "%BUILD_DIR%"
pushd "%BUILD_DIR%"
  cmake -G "Visual Studio 16 2019" -A Win32 %SOURCE_DIR% || goto :ERROR
  cmake --build . --config %CONFIGURATION% -t setup || goto :ERROR
popd

move "%SETUP_DIR%\*.exe" .

exit /b 0

:ERROR
pause
exit /b 1