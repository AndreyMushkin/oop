@echo off

set PROGRAM_PATH="%~1"

rem �������� ���-�� ���������� ���������
%PROGRAM_PATH% tests\some-file.txt > %TEMP%\out.txt
if not ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\invalid-args.expect.txt
if ERRORLEVEL 1 goto err

rem �������������� ������� ����
%PROGRAM_PATH% tests\some-file.txt %TEMP%\out.txt > %TEMP%\out.txt
if not ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\invalid-input-file.expect.txt
if ERRORLEVEL 1 goto err

rem ������������ ������� ��� �������� ��������
%PROGRAM_PATH% tests\invalid-symbols.txt %TEMP%\labyrinth.txt > %TEMP%\out.txt
if not ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\invalid-symbols.expect.txt
if ERRORLEVEL 1 goto err

rem ��������� ������� A �� ������
%PROGRAM_PATH% tests\no-start-position.txt %TEMP%\labyrinth.txt > %TEMP%\out.txt
if not ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\a-or-b-not-defined.expect.txt
if ERRORLEVEL 1 goto err

rem ������� ������� B �� ������
%PROGRAM_PATH% tests\no-end-position.txt %TEMP%\labyrinth.txt > %TEMP%\out.txt
if not ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\a-or-b-not-defined.expect.txt
if ERRORLEVEL 1 goto err

rem ������ ��� ������� �������
%PROGRAM_PATH% tests\two-end-pos.txt %TEMP%\labyrinth.txt > %TEMP%\out.txt
if not ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\two-end-pos.expect.txt
if ERRORLEVEL 1 goto err

rem ������ ��� ��������� �������
%PROGRAM_PATH% tests\two-start-pos.txt %TEMP%\labyrinth.txt > %TEMP%\out.txt
if not ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\two-start-pos.expect.txt
if ERRORLEVEL 1 goto err

rem ������������ ��������
%PROGRAM_PATH% tests\no-path-labyrinth.txt %TEMP%\labyrinth.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\labyrinth.txt tests\no-path-labyrinth.expect.txt
if ERRORLEVEL 1 goto err

rem ��������� �������� 1
%PROGRAM_PATH% tests\labyrinth-1.txt %TEMP%\labyrinth.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\labyrinth.txt tests\labyrinth-1.expect.txt
if ERRORLEVEL 1 goto err

rem ��������� �������� 2
%PROGRAM_PATH% tests\labyrinth-2.txt %TEMP%\labyrinth.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\labyrinth.txt tests\labyrinth-2.expect.txt
if ERRORLEVEL 1 goto err

rem �������� ������������� ������� 1
%PROGRAM_PATH% tests\max-size-labyrinth-1.txt %TEMP%\labyrinth.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\labyrinth.txt tests\max-size-labyrinth-1.expect.txt
if ERRORLEVEL 1 goto err

rem �������� ������������� ������� 2
%PROGRAM_PATH% tests\max-size-labyrinth-2.txt %TEMP%\labyrinth.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\labyrinth.txt tests\max-size-labyrinth-2.expect.txt
if ERRORLEVEL 1 goto err

echo All tests successfully passed!
exit 0

:err
echo Testing failed
exit 1
