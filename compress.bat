START /WAIT renewHtml.exe
powershell Compress-Archive -Path index.html,style.css,background.jpg -DestinationPath directory.zip -Update

