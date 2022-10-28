#----- Fichier genere automatiquement sous Linux ------
#----- Tue Jan 17 15:24:26 CET 2006

#-----
#options de compilation
CFLAGS = -O2 -L/usr/X11R6/include -DLINUX -g
#CFLAGS = -O2 -I. -g -I/usr/local/mesalib/include
#librairies pour l'édition des liens
LIBS = -L/usr/X11R6/lib -lGL -lGLU -lglut -lm


INCDIR=.
CCFLAGS=-W -Wall -I$(INCDIR) -D_REENTRANT
LDFLAGS=
DEPOPT=-MM
CCC=g++
#-----

#-------------  Appli  --------------

TARGET=prj

FILES=  addressUtil.c \
	creerSocket.c \
	streamOp.c \
	restartOp.c\
avatar.cpp\
camera.cpp\
client.cpp\
color.cpp\
faune.cpp\
inforeseau.cpp\
light.cpp\
main.cpp\
predateur.cpp\
proie.cpp\
reseau.cpp\
serveur.cpp\
terrain.cpp\
world.cpp\
wrapperopengl.cpp

OBJECTS=$(FILES:.c=.o)

#-------------  Appli  --------------

all: $(TARGET)

#-------------  Appli  --------------

prj : $(OBJECTS)
	$(CCC) $(OBJECTS) \
		-o prj $(LDFLAGS) $(LIBS)
#------------------------------------

.c.o :
	$(CCC) $(CCFLAGS) -c $< \
		-o $*.o
 
dep :
	@echo "======== Mise a jour des dependances : .depend ========"
	@rm -f .depend
	@for i in *.c ; do \
	echo $$i ; \
	$(CCC) $(DEPOPT) $(CCFLAGS) $$i > .tmpdepend ; \
	OBJNAME=`echo $$i | sed -e s%\\\.c%.o% ` ; \
	cat .tmpdepend | \
	sed -e s%`basename $$i .c`\\\.o%$$OBJNAME%         >> .depend ; \
	echo  >> .depend ; \
	done
	@rm -f .tmpdepend
 
CLEANING=rm -f *.o core a.out $(TARGET) .depend
CONSEIL=echo Penser a faire : make -f makefile dep
 
clear :
	@$(CLEANING)
	@echo
	@$(CONSEIL)
	@echo
clean :
	$(CLEANING)
	@echo
	@$(CONSEIL)
	@echo

sinclude .depend

