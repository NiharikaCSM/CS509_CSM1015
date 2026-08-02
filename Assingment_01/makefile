CC = gcc
CFLAGS = -I../common_wrapper -Isrc -Idriver

run: ../common_wrapper/wrapper.c src/matrix.c src/graph.c \
     driver/gemm_runner.c driver/csr_runner.c driver/driver.c
	$(CC) $(CFLAGS) $^ -o run

clean:
	rm -f run