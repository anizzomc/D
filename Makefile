INC_PATH=include/
CFLAGS=-c -Wall -m64
OUT_PATH=out/
TARGET=$(OUT_PATH)libd.a
TEST_BUILD=$(OUT_PATH)test
OBJ_PATH=obj/
SRC_PATH=src/
TEST_FILE=AllTest.c
TEST_FILE_OBJ=AllTest.o
TEST_FILES=$(wildcard test/src/**/*.c)
TEST_OBJ_FILES=$(TEST_FILES:.c=.o)

all: $(TARGET)

build: $(TARGET)

$(TARGET):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OUT_PATH)
	gcc $(CFLAGS) -I$(INC_PATH) $(SRC_PATH)base/stack.c -o $(OBJ_PATH)stack.o
	gcc $(CFLAGS) -I$(INC_PATH) $(SRC_PATH)base/clist.c -o $(OBJ_PATH)clist.o
	gcc $(CFLAGS) -I$(INC_PATH) $(SRC_PATH)base/d_malloc.c -o $(OBJ_PATH)d_malloc.o
	gcc $(CFLAGS) -I$(INC_PATH) $(SRC_PATH)base/hash.c -o $(OBJ_PATH)hash.o
	gcc $(CFLAGS) -I$(INC_PATH) $(SRC_PATH)base/util.c -o $(OBJ_PATH)util.o
	gcc $(CFLAGS) -I$(INC_PATH) $(SRC_PATH)mm.c -o $(OBJ_PATH)mm.o
	gcc $(CFLAGS) -I$(INC_PATH) $(SRC_PATH)mm_pool.c -o $(OBJ_PATH)mm_pool.o
	ar rcs $(TARGET) $(OBJ_PATH)*.o

test: $(TEST_BUILD)
	$(OUT_PATH)test

$(TEST_FILE):
	mkdir -p test/obj/
	test/search-script.sh > test/obj/$(TEST_FILE)

$(TEST_BUILD): $(TARGET) $(TEST_FILE)
	mkdir -p test/obj/
	gcc $(CFLAGS) -I$(INC_PATH) test/src/mm.c -o test/obj/mm.o 
	gcc $(CFLAGS) -I$(INC_PATH) test/src/mm_pool.c -o test/obj/mm_pool.o 
	gcc $(CFLAGS) -I$(INC_PATH) test/src/base/stackTest.c -o test/obj/stackTest.o 
	gcc $(CFLAGS) -I$(INC_PATH) test/src/base/hashTest.c -o test/obj/hashTest.o 
	gcc $(CFLAGS) -I$(INC_PATH) test/src/base/clistTest.c -o test/obj/clistTest.o 
	gcc $(CFLAGS) -I$(INC_PATH) test/obj/$(TEST_FILE) -o test/obj/$(TEST_FILE_OBJ)
	gcc $(CFLAGS) -I$(INC_PATH) test/cutest/CuTest.c -o test/obj/CuTest.o
	gcc test/obj/*.o -Lout/ -ld -o out/test

clean:
	rm -rf out/*
	rm -rf obj/*
	rm -rf test/obj/*