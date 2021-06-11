##################################################################################
CODECLIENT = cliente.c
CODESERVER = servidor.c
CONFIGFILE = /home/tiempo.conf
FLAGS = -Wall -g

all : cliente.elf servidor.elf config

config :
	@echo "Generando fichero de configuración..."
	@echo 10 >> $(CONFIGFILE)

uninstall : clean
	@echo "Desinstalando demonio..."
	-rm $(CONFIGFILE)
	@echo "Desinstalación completa"

cliente.elf : $(CODECLIENT) 
	@echo "Compilando..."
	gcc $^ $(FLAGS) -o $@

servidor.elf : $(CODESERVER) 
	@echo "Compilando..."
	gcc $^ $(FLAGS) -o $@
    
clean : 
	@echo "Borrando archivos antiguos..."
	-rm *.elf
	-rm $(CONFIGFILE)

.PHONY: all clean install uninstall
##################################################################################
