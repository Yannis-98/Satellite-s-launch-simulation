CC = gcc
CFLAGS = -pedantic
SRC = affichage.c initialisation.c Projet.c Question_EDO_erreur.c Question_II_2.c \
Question_II_3.c Question_II_4_5.c Question_II_6.c Question1.c Question2.c \
Question3.c Question4.c Question5.c 
OBJ = $(SRC:.c=.o)
LDLIBS = -lm

all: Projet_MONTREUIL

Projet_MONTREUIL : $(OBJ)
	$(CC) $^ -o $@ $(LDLIBS)

%.o :%.c
	$(CC) $(CFLAGS)  -c $< -o $@ $(LDLIBS)

Projet.o : Projet.c

Question3.o : Question2.h

Question_EDO_erreur.o Question_II_4_5.o Question1.o : initialisation.h

Question_II_3.o Question_II_6.o Question_II_4_5.o : Question_II_2.h

%.o: types.h

clean:
	rm -f Projet_MONTREUIL $(OBJ)

.PHONY : clean
