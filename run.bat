@echo off
g++ src\sudoku.cpp -o bin\sudoku.exe

if %errorlevel% neq 0 (
    echo ����ʧ�ܣ�
) else (
    echo ����ɹ���
)
