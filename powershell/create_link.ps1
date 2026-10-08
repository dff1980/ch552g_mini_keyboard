$lnk = (New-Object -ComObject WScript.Shell).CreateShortcut("$env:USERPROFILE\Desktop\mic-mute.lnk")
$lnk.Hotkey           = "CTRL+ALT+SHIFT+F20" 
$lnk.TargetPath       = "$env:SystemRoot\System32\WindowsPowerShell\v1.0\powershell.exe"
$lnk.Arguments        = "-WindowStyle Hidden -ExecutionPolicy Bypass -File $env:USERPROFILE\git\mic-mute.ps1"
$lnk.WorkingDirectory = "$env:USERPROFILE\git\"
$lnk.WindowStyle      = 7          # 7 = minimized
$lnk.IconLocation     = "$env:SystemRoot\System32\WindowsPowerShell\v1.0\powershell.exe,0"
$lnk.Save()