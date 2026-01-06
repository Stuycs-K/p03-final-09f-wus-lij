.PHONY: clean run compile crc crs
clean:
	@rm client
	@rm server
	@rm *.o
	@rm *~
compile: server client
	@make client
	@make server
crs: server # compile run server
	@make server
	@./server
crc: client # compile run server
	@make client
	@./client
client: client.o networking.o
	@gcc -o client client.o networking.o
server: server.o networking.o
	@gcc -o server server.o networking.o
client.o: client.c networking.h
	@gcc -Wall -c client.c
server.o: server.c networking.h
	@gcc -Wall -c server.c
networking.o: networking.c networking.h
	@gcc -Wall -c networking.c
