all: dynconf_demo libconfig.so

dynconf_demo: main.o
	$(CC) $< -o $@ -ldl

main.o: main.c
	$(CC) $< -o $@ -c

libconfig.so: config.o
	$(CC) $< -o $@ -shared

config.o: config.c
	$(CC) $< -o $@ -c -fPIC

clean:
	$(RM) dynconf_demo libconfig.so main.o config.o

.PHONY: all clean
