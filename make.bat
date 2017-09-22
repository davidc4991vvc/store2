@if exist scripts\minimaws\minimaws.sqlite3 del scripts\minimaws\minimaws.sqlite3
del mamearcade.sym
:start
@if exist mamearcade.exe del mamearcade.exe
@if exist mamearcade.exe goto start
make32 -j4 %1 %2 %3
