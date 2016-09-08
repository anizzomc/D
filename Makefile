INC_PATH=include/
CFLAGS=-c
TARGET=out/libd.a
TEST_BUILD=out/test
OBJ_PATH=obj/
SRC_PATH=src/
TEST_FILE=AllTest.c
TEST_FILE_OBJ=AllTest.o
TEST_FILES=$(wildcard test/src/**/*.c)
TEST_OBJ_FILES=$(TEST_FILES:.c=.o)

build: $(TARGET)

$(TARGET):
	gcc $(CFLAGS) -I$(INC_PATH) $(SRC_PATH)base/hash.c -o $(OBJ_PATH)hash.o
	ar rcs $(TARGET) $(OBJ_PATH)*.o

test: $(TEST_BUILD)
	out/test

$(TEST_FILE):
	test/search-script.sh > test/obj/$(TEST_FILE)

$(TEST_BUILD): $(TARGET) $(TEST_FILE)
	gcc $(CFLAGS) -I$(INC_PATH) test/src/base/hashTest.c -o test/obj/hashTest.o 
	gcc $(CFLAGS) -I$(INC_PATH) test/obj/$(TEST_FILE) -o test/obj/$(TEST_FILE_OBJ)
	gcc $(CFLAGS) -I$(INC_PATH) test/cutest/CuTest.c -o test/obj/CuTest.o
	gcc test/obj/*.o -Lout/ -ld -o out/test


clean:
	rm -f out/*
	rm -f obj/*
	rm -f test/obj/*