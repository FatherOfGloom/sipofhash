@echo off
setlocal enabledelayedexpansion

set SRC=main.c siphash.c
set BINARY_NAME=hash

set SRC_FILES=

for %%i in (%SRC%) do (
    set SRC_FILES=!SRC_FILES! ..\src\%%i
)

set SRC_FILES=%SRC_FILES:~1%

mkdir bin
pushd bin
gcc -o %BINARY_NAME%.exe %SRC_FILES%
popd

if %errorlevel% neq 0 exit /b %errorlevel%

echo build.bat: build success

endlocal 