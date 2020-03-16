set PROGRAM="%~1"

rem Не переданы аргументы программе
%PROGRAM% > nul && goto err
echo Test 1 passed

rem тестирование с пустым входным файлом
%PROGRAM% testData\InputEmptyFile.txt && goto err
fc.exe "%TEMP%\output.txt" testData\OutputEmptyFile.txt > nul && goto err
echo Test 2 passed

rem	тестирование с целыми числами, на выходе имеют целые числа
%PROGRAM% testData\InputWholeArray.txt > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" testData\OutputWholeArray.txt > nul || goto err
echo Test 3 passed

rem тестрование с дробными числами
%PROGRAM% testData\InputDoubleNumber.txt > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" testData\OutputDoubleNumber.txt > nul || goto err
echo Test 4 passed

rem на вход передана матрица с буквенными символами
%PROGRAM% testData\InputMatrixOfLetters.txt > "%TEMP%\output.txt" && goto err
echo Test 5 passed

rem на вход передана незаполненная матрица
%PROGRAM% testData\InputUnfilledArray.txt > "%TEMP%\output.txt" && goto err
echo Test 6 passed

echo ok
exit 0

:err
echo Testing failed
exit 1