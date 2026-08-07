CC = gcc
CFLAGS = -I../common_wrapper -I../Assingment_01/src -Isrc -Idriver -I../utils

run: ../common_wrapper/wrapper.c ../Assingment_01/src/graph.c src/bellman_ford.c src/floyd_warshall.c \
    ../utils/csr_helper.c driver/bf_runner.c driver/fw_runner.c driver/driver.c
	$(CC) $(CFLAGS) $^ -o run

clean:
	rm -f run