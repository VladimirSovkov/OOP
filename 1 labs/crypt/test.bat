set PROGRAM="%~1"

rem Не переданы аргументы программе
%PROGRAM% > nul && goto err
echo Test 1 passed

rem Первый аргумент записан не верно 
%PROGRAM% test testData\emptyInput.txt testData\emptyOutput.txt 1 && goto err
echo Test 2 passed

rem Не хватает одного аргумента 
%PROGRAM%  crypt testData\emptyInput.txt testData\emptyOutput.txt  && goto err
echo Test 3 passed

rem key > 255
%PROGRAM%  crypt testData\emptyInput.txt "%TEMP%\output.txt" 256 && goto err
echo Test 4 passed

rem key < 0
%PROGRAM%  crypt testData\emptyInput.txt "%TEMP%\output.txt" -1 && goto err
echo Test 5 passed

rem key - пустая строка
%PROGRAM%  crypt testData\emptyInput.txt "%TEMP%\output.txt" "" && goto err
echo Test 6 passed

rem шифровка файла с одной строкой "Hello world!!" key = 255 
%PROGRAM% crypt testData\inputWithOneLine.txt "%TEMP%\output.txt" 255 || goto err
fc.exe "%TEMP%\output.txt" testData\outputWithOneLine.txt > nul || goto err
echo Test 7 passed

rem расшифровка файла с одной строкой "Hello Wrold!!" key = 255
%PROGRAM% decrypt testData\outputWithOneLine.txt "%TEMP%\output.txt" 255 || goto err
fc.exe "%TEMP%\output.txt" testData\inputWithOneLine.txt  > nul || goto err
echo Test 8 passed

rem передан пустой файл 
%PROGRAM% crypt testData\emptyInput.txt "%TEMP%\output.txt" 1 || goto err
fc.exe "%TEMP%\output.txt" testData\emptyOutput.txt > nul || goto err
echo Test 9 passed

rem шифровка объемного файла с key = 15
%PROGRAM% crypt testData\inputWithText.txt "%TEMP%\output.txt" 15 || goto err
fc.exe "%TEMP%\output.txt" testData\outputWithText.txt > nul || goto err
echo Test 10 passed

rem расшифровка объемного файла с key = 15
%PROGRAM% decrypt testData\outputWithText.txt "%TEMP%\output.txt" 15 || goto err
fc.exe "%TEMP%\output.txt" testData\inputWithText.txt > nul || goto err
echo Test 11 passed

echo ok
exit 0

:err
echo Testing failed
exit 1
