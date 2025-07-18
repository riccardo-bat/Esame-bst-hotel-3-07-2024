CC = gcc 
CFLAGS = -Wall

#Regole

#Generazione exe
esame: compito.o hotel.o bst.o
	$(CC) $(CFLAGS) -o esame $^


#generazione file oggetto
compito.o: compito.c hotel.h bst.h 
	$(CC) $(CFLAGS) -c $^

hotel.o: hotel.c hotel.h 
	$(CC) $(CFLAGS) -c $^

bst.o: bst.c hotel.h bst.h 
	$(CC) $(CFLAGS) -c $^