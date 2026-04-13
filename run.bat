@echo off
C:\msys64\ucrt64\bin\g++.exe -g src/main.cpp -o IntergalacticBattles -IC:\msys64\ucrt64\include -LC:\msys64\ucrt64\lib -lsfml-graphics -lsfml-window -lsfml-system
if %errorlevel% == 0 (

    IntergalacticBattles.exe
) else (
    echo Error compiling
)