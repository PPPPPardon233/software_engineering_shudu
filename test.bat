@echo off
g++ test\test.cpp -o  test\test.exe

if %errorlevel% neq 0 (
    echo ±àÒëÊ§°Ü£¡
) else (
    echo ±àÒë³É¹¦£¡
)

test\test.exe > test\test.txt

if %errorlevel% neq 0 (
    echo Êä³öµ½test\text.txtÊ§°Ü£¡
) else (
    echo Êä³öµ½test\text.txt³É¹¦£¡
)
