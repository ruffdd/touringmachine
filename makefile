CC:=g++ -g -std=c++17
CFLAGS:= 
LIBS:= 
build: bin out bin/touring

clean:
	rm -r out

clear:
	rm -r bin
	rm -r out

bin:
	mkdir bin

out:
	mkdir out

bin/touring: out/main.o out/tm.o 
	$(CC) $^ -o $@ $(LIBS)

out/tm.o: tm.cpp tm.h
	$(CC) -c tm.cpp -o $@ $(CFLAGS)

out/main.o: main.cpp tm.h
	$(CC) -c main.cpp -o $@ $(CFLAGS)