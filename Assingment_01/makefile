CC = gcc
CFLAGS = -I../common_wrapper -Isrc

run: ../common_wrapper/wrapper.c src/matrix.c driver/driver.c
	$(CC) $(CFLAGS) $^ -o run

clean:
	rm -f run