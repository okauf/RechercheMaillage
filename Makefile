#declaration 
CC = g++

#CFLAGS as a typeof compiler option 
CFLAGS = -c -Wall 

compile: main 

main: main.o
	$(CC) main.o -o main 

#dependency to main.o 
main.o: main.cpp 
	$(CC) $(CFLAGS) main.cpp 

#remove not necessary files 
clean:
	rm -rf *o *txt main 


do: main
	./main 

#documentation https ://www.gnu.org/software/make/manual/make.html