@echo off
setlocal enabledelayedexpansion

set "folders= Build Logs Output"
set "script_dir=%~dp0"

for %%f in (%folders%) do (
    if exist "%script_dir%%%f" (
        echo Deleting folder: [ %%f ]
        rd /s /q "%script_dir%%%f"
        echo Folder [ %%f ] deleted.
    ) else (
        echo Folder [ %%f ] does not exist
    )
)