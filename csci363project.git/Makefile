#TCPLIB = .
#CC     = gcc -std=c99 #g++
CC     = gcc
CFLAGS = -I ./include --std=gnu99 -Wall 
CFLAGS_B = -I ./include --std=gnu99 #Used for source files we did not write, to ignore warning messages
LIB    = #-lsocket -lnsl  # uncomment the line if solaris
G      = -g
DBLIB  = -lgdbm #-lgdbm_compat

INC = ./include
SRC = ./src
OBJ = ./obj

vpath %.h ./include
vpath %.c ./src

#STRLIB = $(OBJ)/stringwrapper.o $(OBJ)/stringlist.o
TESTO  = $(OBJ)/extraction.o $(OBJ)/htmllinks.o $(OBJ)/stringutil.o $(OBJ)/list.o $(OBJ)/url.o $(OBJ)/http.o $(OBJ)/tcplib.o $(OBJ)/stringlist.o $(OBJ)/stringwrapper.o $(OBJ)/htmlparse.o $(OBJ)/queueADT.o $(OBJ)/dbtools.o $(OBJ)/crawler.o $(OBJ)/crawlerutils.o

SCRAWL  = $(OBJ)/extraction.o $(OBJ)/htmllinks.o $(OBJ)/stringutil.o $(OBJ)/list.o $(OBJ)/url.o $(OBJ)/http.o $(OBJ)/tcplib.o $(OBJ)/stringlist.o $(OBJ)/stringwrapper.o $(OBJ)/htmlparse.o $(OBJ)/dbtools.o $(OBJ)/crawlerutils.o $(OBJ)/queueADT.o $(OBJ)/specialcrawler.o

SEARCH = $(OBJ)/searchserver.o $(OBJ)/tcplib.o $(OBJ)/stringlist.o $(OBJ)/stringwrapper.o $(OBJ)/dbtools.o 
EXE    = crawler searchserver specialcrawler
all: $(EXE)

# The '@' in front of a command causes the command to not print to STDOUT
# Since we did not write these files, we don't need to worry about their
# warning messages

$(OBJ)/list.o: list.c list.h
	@$(CC) $(CFLAGS_B) $G -c $(SRC)/list.c -o $(OBJ)/list.o
$(OBJ)/stringutil.o: stringutil.c stringutil.h
	@$(CC) $(CFLAGS_B) $G -c $(SRC)/stringutil.c -o $(OBJ)/stringutil.o
$(OBJ)/htmllinks.o: htmllinks.c htmllinks.h
	@$(CC) $(CFLAGS_B) $G -c $(SRC)/htmllinks.c -o $(OBJ)/htmllinks.o
$(OBJ)/url.o: url.c url.h
	@$(CC) $(CFLAGS_B) $G -c $(SRC)/url.c -o $(OBJ)/url.o
$(OBJ)/http.o: http.c http.h stringutil.h
	@$(CC) $(CFLAGS_B) $G -c $(SRC)/http.c -o $(OBJ)/http.o
$(OBJ)/tcplib.o: tcplib.c
	@$(CC) $(CFLAGS_B) $G -c $(SRC)/tcplib.c -o $(OBJ)/tcplib.o


$(OBJ)/stringwrapper.o: stringwrapper.c  stringwrapper.h
	$(CC) $(CFLAGS) $G -c $(SRC)/stringwrapper.c -o $(OBJ)/stringwrapper.o
$(OBJ)/stringlist.o: stringlist.c stringlist.h stringwrapper.h
	$(CC) $(CFLAGS) $G -c $(SRC)/stringlist.c -o $(OBJ)/stringlist.o
$(OBJ)/queueADT.o: stringwrapper.h stringlist.h queueADT.h queueADT.c
	$(CC) $(CFLAGS) $G -c $(SRC)/queueADT.c -o $(OBJ)/queueADT.o

$(OBJ)/htmlparse.o: stringlist.h stringwrapper.h htmlparse.h htmlparse.c
	$(CC) $(CFLAGS) $G -c $(SRC)/htmlparse.c -o $(OBJ)/htmlparse.o


$(OBJ)/extraction.o: extraction.c extraction.h tcplib.h stringwrapper.h stringlist.h htmlparse.h
	$(CC) $(CFLAGS) $G -c $(SRC)/extraction.c -o $(OBJ)/extraction.o

$(OBJ)/dbtools.o: dbtools.c dbtools.h stringwrapper.h stringlist.h
	$(CC) $(CFLAGS) $G -c $(SRC)/dbtools.c -o $(OBJ)/dbtools.o $(DBLIB)

$(OBJ)/crawlerutils.o: crawlerutils.c crawlerutils.h extraction.h stringwrapper.h stringlist.h dbtools.h queueADT.h
	$(CC) $(CFLAGS) $G -c $(SRC)/crawlerutils.c -o $(OBJ)/crawlerutils.o $(DBLIB)

$(OBJ)/crawler.o: crawler.c extraction.h stringwrapper.h stringlist.h dbtools.h queueADT.h crawlerutils.h
	$(CC) $(CFLAGS) $G -c $(SRC)/crawler.c -o $(OBJ)/crawler.o  $(DBLIB)

$(OBJ)/searchserver.o: searchserver.c  stringwrapper.h stringlist.h dbtools.h
	$(CC) $(CFLAGS) $G -c $(SRC)/searchserver.c -o $(OBJ)/searchserver.o $(DBLIB)

$(OBJ)/specialcrawler.o: specialcrawler.c extraction.h stringwrapper.h stringlist.h dbtools.h crawlerutils.h queueADT.h
	$(CC) $(CFLAGS) $G -c $(SRC)/specialcrawler.c -o $(OBJ)/specialcrawler.o $(DBLIB)

#Unless there is a linker error, we don't need to see results
searchserver: $(SEARCH)
	@$(CC) $(CFLAGS_B) $(SEARCH) -o searchserver $(DBLIB)
crawler: $(TESTO)
	@$(CC) $(CFLAGS_B) $(TESTO) -o crawler $(DBLIB)

specialcrawler: $(SCRAWL)
	$(CC) $(CFLAGS_B) $(SCRAWL) -o specialcrawler $(DBLIB)


#I hardcoded the clean because I am afraid I might inadvertantly recursively remove all files in my filesystem.
#Like I did last time
.PHONY: clean
clean:
	/bin/rm -f $(TESTO) $(SEARCH) $(SCRAWL)
	/bin/rm -f crawler
	/bin/rm -f searchserver
	/bin/rm -f specialcrawler


