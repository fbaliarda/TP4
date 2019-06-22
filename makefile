server:
	gcc Server/server.c -o server Challenges/challenges.c TP4Challenges/TP4Challenges.c

client:
	gcc Client/client.c -o client

all:
	make server && make client
