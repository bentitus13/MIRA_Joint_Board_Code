# invoke SourceDir generated makefile for config.pem4f
config.pem4f: .libraries,config.pem4f
.libraries,config.pem4f: package/cfg/config_pem4f.xdl
	$(MAKE) -f C:\Users\Ben\Documents\MQP_Code\MIRA_Joint_Board_Code\MIRA_Joint_Code/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\Ben\Documents\MQP_Code\MIRA_Joint_Board_Code\MIRA_Joint_Code/src/makefile.libs clean

