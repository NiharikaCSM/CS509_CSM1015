CC = gcc
CFLAGS = -I../common_wrapper -I../Assingment_01/src -Isrc -Idriver -I../utils

run: ../common_wrapper/wrapper.c ../Assingment_01/src/graph.c \
      ../utils/csr_helper.c ../utils/graph_utils.c src/min_heap.c src/dsu.c src/kruskal.c src/prims.c \
     driver/kruskal_runner.c driver/prim_runner.c  driver/driver.c
	$(CC) $(CFLAGS) $^ -o run

clean:
	rm -f run
