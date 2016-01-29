@echo off
echo "Installing Steam files"
mkdir "C:\Program Files (x86)\Steam\steamapps\common\Grand Theft Auto V\GTALua"
for %%a in ("build\GTALua.asi" "build\*.dll") do (xcopy /s /q /y "%%~a" "C:\Program Files (x86)\Steam\steamapps\common\Grand Theft Auto V\")
for %%a in ("build\GTALua") do (xcopy /s /q /y "%%~a" "C:\Program Files (x86)\Steam\steamapps\common\Grand Theft Auto V\GTALua\")
