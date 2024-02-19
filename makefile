FLAGS = -Wall -g

.PHONY: all clean

all: StrList

# Generating library:
StrListlib.o: StrList.c StrList.h
	gcc ${FLAGS} -fPIC -c StrList.c -o StrListlib.o

StrListlib.a: StrListlib.o
	ar -rcs StrListlib.a StrListlib.o
	ranlib StrListlib.a

# Generating main:
main.o: main.c StrList.h
	gcc ${FLAGS} -c main.c -o main.o

StrList: main.o StrListlib.a
	gcc ${FLAGS} main.o StrListlib.a -o StrList

# Cleaning:
clean:
	rm -f StrList *.a *.o