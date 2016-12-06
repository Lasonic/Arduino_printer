clear all
s=serial('COM4', 'BaudRate', 9600);
try
fopen(s);
catch err
    fclose(instrfind);
    error('Make sure you select the correct COM Port where the Arduino is connected.');
end
pause(1);
for i = 1:50
    fwrite(s,i, 'uint8', 'sync');
    rx(i) = fread(s, 1);
end

fclose(s);