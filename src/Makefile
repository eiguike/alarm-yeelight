LDFLAGS = -Iinclude/

all: 
	$(CC) -c -o main.o main.c -Wall $(LDFLAGS)
	$(CC) -c -o logger.o library/logger.c -Wall $(LDFLAGS)
	$(CC) -c -o yeelight.o library/yeelight.c -Wall $(LDFLAGS)
	$(CC) -c -o yeelight_udp.o library/yeelight_udp.c -Wall $(LDFLAGS)
	$(CC) -o alarm_xaiomi main.o logger.o yeelight.o yeelight_udp.o

clean:
	rm *.o alarm_xaiomi
