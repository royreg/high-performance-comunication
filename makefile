all: client server

server: kv_template.c
	gcc kv_template.c -DEX3 -libverbs -o server

client:kv_template.c
	ln -s client server
clean:
	rm -f *.o client server 