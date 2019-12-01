CC=gcc
EXE_DIR=../out/
W_FLAGS=-Wall
LINK_LIB=-lpthread

all: test_fork test_mutex1 test_mutex2 test_mutex3 test_thread test_thread2_1 test_thread2_2 test_thread3_1 test_thread3_2 test_caractere4_1 test_caractere4_2

test_fork: test_fork.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe $(LINK_LIB)

test_mutex1: test_mutex1.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe $(LINK_LIB)
	
test_mutex2: test_mutex2.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe $(LINK_LIB)
	
test_mutex3: test_mutex3.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe $(LINK_LIB)
	
test_thread: test_thread.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe $(LINK_LIB)

test_thread2_1: test_thread2_1.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe $(LINK_LIB)
	
test_thread2_2: test_thread2_2.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe $(LINK_LIB)

test_thread3_1: test_thread3_1.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe $(LINK_LIB)
	
test_thread3_2: test_thread3_2.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe $(LINK_LIB)
	
test_caractere4_1: test_caractere4_1.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe $(LINK_LIB)
	
test_caractere4_2: test_caractere4_2.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe $(LINK_LIB)
	
clean :
	rm -f $(EXE_DIR)*.exe
