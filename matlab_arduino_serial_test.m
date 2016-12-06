clear all
clc

answer = 1; % this is where we'll store the user's answer
arduino = serial('COM5','BaudRate',115200); % create serial communication object on port COM5
answer_2 = 1;

m=instrfind;
fclose(m)

fopen(arduino); % initiate arduino communication
 
while answer
    disp('0=EXIT PROGRAM, 1=PRESSURE, 2=VOLTAGE, 3=MOTOR_SPEED, 4=SETPOINT_HEAD, 5=SETPOINT_RING)');
    answer=input('Enter variable to be changed '); 
    fprintf(arduino,'%s',double(answer)); % send answer variable content to arduino   
    x = fscanf(arduino,'%s')
        

end
 
fclose(arduino); % end communication with arduino
