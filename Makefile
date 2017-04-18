CC=gcc
CFLAGS=-std=c11 -Wall -lsystemd

all: sdbus-server sdbus-client

sdbus-server: sdbus-server.c
	$(CC) $(CFLAGS) -o $@ $<

sdbus-client: sdbus-client.c
	$(CC) $(CFLAGS) -o $@ $<

