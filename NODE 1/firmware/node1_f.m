% UTA Rover team | Nabeel Nayyar | Jetson TX2 firmware
% 
%
clear all;
clc;


serialInit();
fprintf("Main\n");


function [nodea, nodeb] = serialInit() %#codegen
coder.gpu.kernelfun();
nodea = 0;
nodeb = 0;
nodea_buad = 115200;
nodeb_buad = 115200;
collectD_A = ["", ""];
while(1)
ports = serialportlist();
    if isempty(ports) == 1
        fprintf("[!] NO SERIAL PORTS DETECTED\n");
        break;
    else
        p_count = numel(ports);
        fprintf("[!] %d Serial device(s) discovered. \n", p_count);
        
        % Starting to identify nodes.
        if p_count == 1
            nodea = ports(1);
            fprintf("Node A has been assigned %s \n", ports(1));
            nodeb = 0;
            fprintf("Node B was NOT discovered \n");

        else
            nodea_TMserial = serialport(ports(1), nodea_buad);
            nodeb_TMserial = serialport(port(1), nodeb_buad);
            collectD_A(1) = readline(nodea_TMserial);
            collectD_A(2) = readline(nodeb_TMserial);
            
            if collectD_A(1) == "[!]RSD-MEGA 2560 Armed"
                nodea = port(1);
                fprintf("Node A has been assigned %s \n", ports(1));
                nodeb = ports(2);
                fprintf("Node B has been assigned %s \n", ports(2));

            else
                nodea = ports(2);
                fprintf("Node A has been assigned %s \n", ports(2));
                nodeb = ports(1);
                fprintf("Node B has been assigned %s \n", ports(1));

            end
        end
        break;
    end
end
end