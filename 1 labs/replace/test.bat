set PROGRAM="%~1"

rem Не переданы аргументы программе
%PROGRAM% > nul && goto err
echo Test 1 passed

rem тестирование с пустым входным файлом
%PROGRAM% testData\InputEmptyFile.txt "%TEMP%\output.txt" text 1 || goto err
fc.exe "%TEMP%\output.txt" testData\OutputEmptyFile.txt > nul || goto err
echo Test 2 passed

rem тестирование с одним из отсутсвующих параметров
%PROGRAM% testData\InputEmptyFile.txt "%TEMP%\output.txt" test && goto err
echo Test 3 passed

rem тестирование на зацикливание (подстрока повторяется в строке несколько раз)
%PROGRAM% testData\InputStringWithThreeSubstrings.txt "%TEMP%\output.txt" check 1 || goto err 
fc.exe "%TEMP%\output.txt" testData\OutputStringWithThreeSubstrings.txt > nul || goto err
echo Test 4 passed

rem тестирование с обычным текстом из 3 строчек 
%PROGRAM% testData\OutputLinesWithText.txt "%TEMP%\output.txt" text 1 || goto err
fc.exe "%TEMP%\output.txt" testData\OutputLinesWithText.txt > nul || goto err
echo Test 5 passed

rem искомая строка является подстрокой  
%PROGRAM% testData\InputWithNumbers.txt "%TEMP%\output.txt" 1231234 test || goto err
fc.exe "%TEMP%\output.txt" testData\OutputWithNumbers.txt > nul || goto err
echo Test 6 passed

rem тестирование с отсутствующем входным файлом   
%PROGRAM% testData\NoName.txt "%TEMP%\output.txt" text 1 && goto err
echo Test 7 passed

echo ok
exit 0

:err
echo Testing failed
exit 1
