LDFLAGS = -Iinclude/
DEBUG_FLAG = -g

ifeq ($(ENV),debug)
	CFLAGS=$(DEBUG_FLAG)
endif

all: 
	$(CC) -c -o main.o main.c -Wall $(LDFLAGS) $(CFLAGS)
	$(CC) -c -o logger.o library/logger.c -Wall $(LDFLAGS) $(CFLAGS)
	$(CC) -c -o yeelight.o library/yeelight.c -Wall $(LDFLAGS) $(CFLAGS)
	$(CC) -c -o yeelight_udp.o library/yeelight_udp.c -Wall $(LDFLAGS) $(CFLAGS)
	$(CC) -o alarm-xaiomi main.o logger.o yeelight.o yeelight_udp.o $(CFLAGS)

clean:
	rm *.o alarm-xaiomi
