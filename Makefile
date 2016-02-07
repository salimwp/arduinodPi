all: arduinod

arduinod: main.c 
	gcc -o arduinod main.c arduino.c network.c -lpthread

clean:
	rm arduinod
