Проверено на Windows 11
lnk должен создаваться в Desktop иначе неработает вызов по комбинации клавиш.
Назначается  ctrl+alt+shift+F20 Windows такое отображает некорректно.
```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\mic-mute.ps1 toggle
powershell -NoProfile -ExecutionPolicy Bypass -File .\mic-mute.ps1 -Action mute
```