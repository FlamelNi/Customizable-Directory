@echo off
for /f "tokens=2 delims==" %%a in ('wmic OS Get localdatetime /value') do set "dt=%%a"
set "YY=%dt:~2,2%" & set "YYYY=%dt:~0,4%" & set "MM=%dt:~4,2%" & set "DD=%dt:~6,2%"
set "HH=%dt:~8,2%" & set "Min=%dt:~10,2%" & set "Sec=%dt:~12,2%"

@REM set "datestamp=%YYYY%%MM%%DD%" & set "timestamp=%HH%%Min%%Sec%"
@REM set "fullstamp=%YYYY%-%MM%-%DD%_%HH%-%Min%-%Sec%"
@REM echo datestamp: "%datestamp%"
@REM echo timestamp: "%timestamp%"
@REM echo fullstamp: "%fullstamp%"
@REM pause

copy directory.csv "./backup/directory_%YYYY%-%MM%-%DD%_%HH%-%Min%-%Sec%.csv"

START /WAIT renewHtml.exe
powershell Compress-Archive -Path index.html,style.css,background.jpg -DestinationPath directory.zip -Update

