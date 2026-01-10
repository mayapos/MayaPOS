@set comp=mingw64
@set DIR_HBBIN=u:\desarrollo\comp\xc\hb\bin
@set DIR_CCBIN=u:\desarrollo\comp\cc\mingw\64\9.30\bin
@set PATH=%DIR_HBBIN%;%DIR_CCBIN%;%PATH%
@hbmk2 -comp=%comp% %1 fuentes_c\cursode.c -l-hbvm -lhbvm_dbg
@pause
@if %errorlevel% neq 0 goto bld_error
@cls
%1
goto fin_exec
:bld_error
@echo -----------------------------------
@echo    Hay errores en la compilacion
@echo -----------------------------------
pause
:fin_exec
