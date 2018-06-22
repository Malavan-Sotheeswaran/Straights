CC = g++
CFLAGS = -std=c++14

all: straights

straights: shuffle.o Player.o Table.o Card.o Command.o
	${CC} ${CFLAGS} -o $@ $^


.cpp.o: Player.h Table.h Command.h Card.h
	${CC} ${CFLAGS}  -c $<

clean:
	rm *.o straights
