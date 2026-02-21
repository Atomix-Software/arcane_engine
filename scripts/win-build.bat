@echo off
title=Window Premake5 Build-Script
pushd ..\
call vendors\premake\premake5.exe vs2026
popd

IF %ERRORLEVEL% NEQ 0 (
	PAUSE
)