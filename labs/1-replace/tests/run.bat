@echo off

set PROGRAM_PATH="%~1"

rem �������� ���������� ����������
%PROGRAM_PATH% tests\12312312345.txt %TEMP%\out.txt > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\invalid-args.expect.txt
if ERRORLEVEL 1 goto err

%PROGRAM_PATH% tests\12312312345.txt %TEMP%\out.txt 8573 23 593 3 > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\invalid-args.expect.txt
if ERRORLEVEL 1 goto err

rem �������������� ������� ����
%PROGRAM_PATH% tests\cba.txt %TEMP%\out.txt 1 2 > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\bad-input-file.expect.txt
if ERRORLEVEL 1 goto err

rem ����������� ��������� � �������� ��������� �����
%PROGRAM_PATH% tests\brown-fox.txt %PROGRAM_PATH% fox dog > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\bad-output-file.expect.txt
if ERRORLEVEL 1 goto err

rem ������ ������ ������
%PROGRAM_PATH% tests\brown-fox.txt %TEMP%\empty-search-string.txt "" hello > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\empty-search-string.txt tests\brown-fox.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\empty-search-string.expect.txt
if ERRORLEVEL 1 goto err

rem ������ "ma" �� "mama"
%PROGRAM_PATH% tests\mama.txt %TEMP%\mama.txt ma mama
if ERRORLEVEL 1 goto err
fc %TEMP%\mama.txt tests\mama.expect.txt
if ERRORLEVEL 1 goto err

rem ������ ��������� "1231234" � ������ "12312312345"
%PROGRAM_PATH% tests\12312312345.txt %TEMP%\12312312345.txt 1231234 "works fine"
if ERRORLEVEL 1 goto err
fc %TEMP%\12312312345.txt tests\12312312345.expect.txt
if ERRORLEVEL 1 goto err

rem ������ "dog" �� "cat" � ���������.
%PROGRAM_PATH% tests\brown-fox.txt %TEMP%\brown-fox.txt dog cat
if ERRORLEVEL 1 goto err
fc %TEMP%\brown-fox.txt tests\brown-fox.expect.txt
if ERRORLEVEL 1 goto err

echo All tests successfully passed
exit 0

:err
echo Testing failed
exit 1
