CC := gcc

CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra  -pedantic -Wfloat-equal -Wfloat-conversion 
MODE_FILE := ./.$(mode)

OBJECTS := out/main.o out/rw_sudent.o out/sort_std.o out/check_str.o 

# for WSL: -lcheck -lsubunit -lrt -lm -lpthread
# for Server: -lcheck -lpthread -lrt 

UNIT_TEST_LINKS := -lcheck -lsubunit -lrt -lm -lpthread
UNIT_FILES := $(wildcard ./unit_tests/*.c)
UNIT_OBJECTS := out/filter.o out/mysort.o

SRCS := $(wildcard ./src/*.c)


ifeq ($(mode), debug)
	CFLAGS += -g3
endif
 
ifeq ($(mode), release)
	CFLAGS += -O3 -g0 -DNDEBUG
endif
 
ifeq ($(mode), gcov)
	CFLAGS += --coverage -O0
	COVERAGE_LINK_ARGS = -lgcov
endif
 
 
ifeq ("$(wildcard ./.$(MODE_FILE))", "")
	CLEAN_OPT = clean
endif


app.exe : $(OBJECTS)
 
	$(CC) $(OBJECTS) -o $@ $(COVERAGE_LINK_ARGS)
	touch ./.$(mode)


./out/%.o : ./src/%.c ./inc/*.h ./out
	$(CC) $(CFLAGS) -c $< -o $@


unit_tests.exe: $(UNIT_OBJECTS) $(UNIT_FILES)
	$(CC) -I inc -g $^ -o $@ $(UNIT_TEST_LINKS)


.PHONY : clean outfolder func collect_coverage unit

./out: 
	@mkdir ./out

clean :
	$(RM) out/*.o *.exe  src/*.d unit_tests/*.d out/*.gcno out/*.gcda  out/*.c.gcov func_tests/data/temp* out/*temp*
	rm -f ./.release ./.debug ./.gcov

func : ./app.exe
	./func_tests/scripts/func_tests.sh

collect_coverage : ./.gcov 
	mv ./out/*.gcno ./src/
	./func_tests/scripts/func_tests.sh
	mv ./out/*.gcda ./src/
	gcov ./src/*.c
	mv ./*.gcov ./out/
	mv ./src/*.gcda ./out/
	mv ./src/*.gcno ./out/


unit : ./unit_tests.exe
	./unit_tests.exe


