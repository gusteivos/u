@echo off

SET v=0

:begin

if "%1" == "-f" goto :begin-end
if "%1" == "-v" (
    SET v=1
    goto :begin-end
)

if "%1" == "" goto :end
if exist "%1" (
    del "%1"
    if "%v%"=="1" echo removed: '%1'
)

:begin-end
shift
goto :begin
:end
