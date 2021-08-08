GCC:=gcc
BIN:=main
INC:=./include
SRC:=$(wildcard ./src/*.c)
OBJ:=./.obj
LIBS:= -lpthread

main:
	@test -d ./.obj || mkdir ./.obj
	$(GCC) -g $(SRC) -o $(BIN) -I$(INC) $(LIBS)

clean:
	rm -rf main