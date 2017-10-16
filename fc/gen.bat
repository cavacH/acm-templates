@echo off  
:loop  
    rand.exe > in.txt
    test.exe < in.txt > testout.txt
    std.exe < in.txt > stdout.txt
    fc testout.txt stdout.txt
if not errorlevel 1 goto loop  
pause
goto loop