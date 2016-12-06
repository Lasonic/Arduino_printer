global temp1;
global temp2;
global hv;
global pressure;
global temp1state;
global temp2state;
global hvstate;
global pressurestate; 
value = '25';
flag=1;
i=1;

%% Create and connect serial object for Arduino %%
s=serial('COM4', 'BaudRate', 9600); % change COM port as needed
try
    fopen(s);
catch err
    fclose(instrfind);
    error('Make sure you select the correct COM Port where the Arduino is connected or restart the program.');
end

while flag>0
   if pressurestate==1 
       pause(1);
       fprintf(s,'%c', value);
       rx = fscanf(s);
   end
flag=flag-1;
end
fclose(s);

   
   
%     if temp1state==1 
%         if 0>temp1<120 
%         fprintf(arduino, '%s', char('temp1 ' temp1));
%         else
%             display('Error: Enter a temperature between 0 and 120 degrees celcius');
%         end 
%     fclose(arduino);
    
    
    

