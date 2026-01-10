@rem ---------------------------------------------------------------------------
@rem Archivo por lotes para consruir librerias
@rem Para adaptarlo a tu sistema cambiar las variables:
@rem COMP compilador de C para windows puedes usar mingw, mingw64, clang, 
@rem      clang64, msvc, msvc64, clang-cl, clang-cl64, watcom, icc, icc64, 
@rem      iccia64, msvcia64, bcc, bcc64, pocc, pocc64
@rem DIR_HBBIN  directorio bin de Harbour
@rem DIR_CCBIN  directorio bin del compilador de C
@rem ---------------------------------------------------------------------------
@set COMP=mingw64
@set DIR_HBBIN=u:\desarrollo\comp\xc\hb\bin
@set DIR_CCBIN=u:\desarrollo\comp\cc\mingw\64\9.30\bin
@set PATHOLD=%PATH%
@set PATH=%DIR_HBBIN%;%DIR_CCBIN%;%PATH%
@hbmk2 -comp=%COMP% cursodec.hbp
@pause
@if %errorlevel% neq 0 goto bld_error
goto fin_exec
:bld_error
@echo -----------------------------------
@echo    Hay errores en la compilacion
@echo -----------------------------------
@pause
:fin_exec
@set PATH=%PATHOLD%
