@setlocal enabledelayedexpansion
@echo off
@set ROOT_DIR=%~dp0


@set ENV_FILE=%ROOT_DIR%BuildEnv.ini

@for /F "tokens=1,2* delims==" %%i in (%ENV_FILE%) do (
     @set VAR=%%i
     @set VAL=%%j
     @set !VAR!=!VAL!
)

@call "%VSVARSALL_BAT%" x86

@set SLNList=%ROOT_DIR%BuildSLN.ini
@for /F "tokens=1,2* delims=:" %%i in (%SLNList%) do (
	@set SLNName=%%i
	@if exist !SLNName! (
		call "!VSDEVENV_EXE!" !SLNName! /Rebuild Debug
		call "!VSDEVENV_EXE!" !SLNName! /Rebuild Release
	)
	@echo !SLNName!
)

@if exist !LibDebug! mkdir !LibDebug!
@if exist !LibRelease! mkdir !LibRelease!

@set CopyList=%ROOT_DIR%BuildCopy.ini
@for /F "tokens=1,2* delims=:" %%i in (%CopyList%) do (
	@set CopyDir=%%i
	@if exist !CopyDir! (
		xcopy /Y !CopyDir!*.lib  !LibRelease!
	)
	@echo !SLNName!
)

@set CopyList=%ROOT_DIR%BuildCopyDebug.ini
@for /F "tokens=1,2* delims=:" %%i in (%CopyList%) do (
	@set CopyDir=%%i
	@if exist !CopyDir! (
		xcopy /Y !CopyDir!*.lib  !LibDebug!
	)
	@echo !SLNName!
)







@cmd
