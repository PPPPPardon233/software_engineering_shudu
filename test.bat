@echo off
g++ test\test.cpp -o  test\test.exe

if %errorlevel% neq 0 (
    echo ����ʧ�ܣ�
) else (
    echo ����ɹ���
)

test\test.exe > test\test.txt

if %errorlevel% neq 0 (
    echo �����test\text.txtʧ�ܣ�
) else (
    echo �����test\text.txt�ɹ���
)
