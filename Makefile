#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2020/2021
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = main testunitaires_2 testunitaires_3


#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
geom2d.o : geom2d.c geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geom"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

contour_image.o : contour_image.c contour_image.h image.h types_macros.h eps.h simplification.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contour_image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

image.o : image.c image.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

eps.o : eps.c eps.h image.h contour_image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

main.o : main.c image.h image.h types_macros.h eps.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module main"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

testunitaires_2.o : testunitaires_2.c image.h image.h types_macros.h eps.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module main"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

testunitaires_3.o : testunitaires_3.c image.h image.h types_macros.h eps.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module main"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplification.o : simplification.c simplification.h image.h geom2d.h types_macros.h contour_image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module main"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
		
########################################################
# regles explicites de creation des executables

main : main.o image.o contour_image.o geom2d.o eps.o simplification.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

testunitaires_2 : testunitaires_2.o image.o contour_image.o geom2d.o eps.o simplification.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

testunitaires_3 : testunitaires_3.o image.o contour_image.o geom2d.o eps.o simplification.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@


# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
