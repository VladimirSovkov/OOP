set PROGRAM="%~1"

rem �� �������� ��������� ���������
%PROGRAM% > nul && goto err
echo Test 1 passed

rem � input ����� ����� 
%PROGRAM% "abc" > nul && goto err
echo Test 2 passed

rem ����� ����� � ������ 
%PROGRAM% "12A" > nul && goto err
echo Test 3 passed

rem ����� ����� ����������� �������� ��������
%PROGRAM% "256" > nul && goto err
echo Test 4 passed

rem ����� ����� ������ ��������� ���������
%PROGRAM% "-1" > nul && goto err
echo Test 5 passed

rem ���������� ����� 6
%PROGRAM% "6" > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\Output96.txt > nul || goto err
echo Test 6 passed

rem ���������� ����� 6
%PROGRAM% "243" > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\Output207.txt > nul || goto err
echo Test 7 passed

rem ����� ���������� ������ ��� ��������
%PROGRAM% "240" "30" > nul && goto err
echo Test 8 passed

echo ok
exit 0

:err
echo Testing failed
exit 1
