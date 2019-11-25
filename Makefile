all:
	$(CC) -shared -o libnss_hostlog.so hostlog.c

clean:
	rm libnss_hostlog.so
