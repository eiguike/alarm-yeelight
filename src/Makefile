LDFLAGS = -Iinclude/ -Ivendors/logger-c/include/
DEBUG_FLAG = -g

ifeq ($(ENV),debug)
	CFLAGS=$(DEBUG_FLAG)
endif

all: 
	$(CC) -c -o main.o main.c -Wall $(LDFLAGS) $(CFLAGS)
	$(CC) -c -o logger.o vendors/logger-c/library/logger.c -Wall $(LDFLAGS) $(CFLAGS)
	$(CC) -c -o yeelight_lamp.o library/yeelight_lamp.c -Wall $(LDFLAGS) $(CFLAGS)
	$(CC) -c -o yeelight_integration.o library/yeelight_integration.c -Wall $(LDFLAGS) $(CFLAGS)
	$(CC) -o alarm-xaiomi main.o logger.o yeelight_lamp.o yeelight_integration.o $(CFLAGS)

clean:
	rm *.o alarm-xaiomi
