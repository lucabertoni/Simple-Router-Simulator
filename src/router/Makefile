# Il compilatore utilizzato per compilare i sorgenti è gcc
CC=gcc

# -c serve per compilare e assemblare il codice senza però linkare i file
# -Wall serve per mostrare tutti gli warning in fase di compilazione
CFLAGS=-c -Wall

# Percorso nel quale salvare i file compilati (*.o)
BUILDDIR=build

# Percorso delle librerie condivise
LIB=../lib/

# Nome eseguibile finale
EXE=router

# File compilati che compongono l'eseguibile
OBJECTS=$(BUILDDIR)/netlib.o $(BUILDDIR)/common.o $(BUILDDIR)/router.o $(BUILDDIR)/main.o 

# Punto di partenza della compilazione
all: router

router: printstartmessage netlib.o common.o router.o main.o
	$(info Generazione eseguibile router...)
	@$(CC) $(OBJECTS) -o $(EXE)
	$(info Eseguibile creato nella cartella corrente con il nome di $(EXE))

# Libreria di supporto per le funzioni di rete
netlib.o:
	$(info Compilazione $(LIB)netlib.c ...)
	@$(CC) -c $(LIB)netlib.c -o $(BUILDDIR)/netlib.o
	$(info netlib.c compilato)

# Libreria che controlla l'intero router
router.o:
	$(info Compilazione router.c ...)
	@$(CC) -c router.c -o $(BUILDDIR)/router.o
	$(info router.c compilato)

# Main che avvia il router
main.o:
	$(info Compilazione main.c ...)
	@$(CC) -c main.c -o $(BUILDDIR)/main.o
	$(info main.c compilato)

# Funzioni comuni
common.o:
	$(info Compilazione common.c ...)
	@$(CC) -c $(LIB)common.c -o $(BUILDDIR)/common.o
	$(info common.c compilato)

# Pulisce dal disco i file *.o e l'eseguibile router
clean:
	$(info Elimino file compilati ed eseguibile ...)
	@rm -f $(BUILDDIR)/*.o
	@rm -f router
	$(info File eliminati)

printstartmessage:
	$(info Inizio compilazione dei sorgenti del router)
	$(info I file compilati vengono salvati in $(BUILDDIR)/)