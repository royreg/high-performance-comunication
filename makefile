# All Targets
all: server client

# Tool invocations
# Executable "hello" depends on the files hello.o and run.o.
server: server.o 
	@echo 'Building target: server'
	gcc -o server  server.o
	@echo 'Finished building target: server'
	@echo ' '

# Depends on the source and header files
bin/server.o: src/server.c
	gcc -g -Wall -Weff -c -Linclude -o server.o server.c

client: client.o 
	@echo 'Building target: client'
	gcc -o client  client.o
	@echo 'Finished building target: client'
	@echo ' '

# Depends on the source and header files
bin/client.o: client.c
	gcc -g -Wall -Weff -c -Linclude -o client.o client.c


#Clean the build directory
clean: 
	rm -f server
	rm -f server.o
	rm -f client
	rm -f client.o