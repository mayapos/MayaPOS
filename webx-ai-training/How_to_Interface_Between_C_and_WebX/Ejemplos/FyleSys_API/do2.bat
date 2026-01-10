@set comp=mingw
@set DIR_HBBIN=d:\mio\programacion\comp\xc\hb\bin
@set DIR_CCBIN=d:\mio\programacion\comp\cc\mingw\32\9.30\bin
@set PATH=%DIR_HBBIN%;%DIR_CCBIN%;%PATH%
@hbmk2 -comp=%comp% %1 fuentes_c\cursode.c
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

