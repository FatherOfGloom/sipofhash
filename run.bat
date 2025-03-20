@echo off

call build.bat

if %errorlevel% neq 0 exit /b %errorlevel%

pushd bin
hash.exe
popd