set PROGRAM="%~1"

rem �� �������� ��������� ���������
%PROGRAM% > nul && goto err
echo Test 1 passed

rem ������������ � ������ ������� ������
%PROGRAM% testData\InputEmptyFile.txt && goto err
fc.exe "%TEMP%\output.txt" testData\OutputEmptyFile.txt > nul && goto err
echo Test 2 passed

rem	������������ � ������ �������, �� ������ ����� ����� �����
%PROGRAM% testData\InputWholeArray.txt > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" testData\OutputWholeArray.txt > nul || goto err
echo Test 3 passed

rem ����������� � �������� �������
%PROGRAM% testData\InputDoubleNumber.txt > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" testData\OutputDoubleNumber.txt > nul || goto err
echo Test 4 passed

rem �� ���� �������� ������� � ���������� ���������
%PROGRAM% testData\InputMatrixOfLetters.txt > "%TEMP%\output.txt" && goto err
echo Test 5 passed

rem �� ���� �������� ������������� �������
%PROGRAM% testData\InputUnfilledArray.txt > "%TEMP%\output.txt" && goto err
echo Test 6 passed

echo ok
exit 0

:err
echo Testing failed
exit 1