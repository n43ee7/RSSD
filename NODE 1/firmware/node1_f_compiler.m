% UTA Rover team | Nabeel Nayyar | Jetson TX2 firmware compiler
% 
% Network Operation. Flash OTA or Locally
%

NEST_IP = input("IP of JETSON module :");

Jetsonobj = jetson(NEST_IP,'ubuntu','ubuntu');

% Enviorment verification
envCfg = coder.gpuEnvConfig('jetson');
envCfg.BasicCodegen = 1;
envCfg.Quiet = 1;
envCfg.HardwareObject = Jetsonobj;
coder.checkGpuInstall(envCfg);