## Do not change this file

TARGETS=parser_tester test_env

COMMON_FILES=thsh.h parse.c builtin.c jobs.c

LAB_FILES=$(COMMON_FILES) parser_tester.c test_env.c

CFLAGS= -Wall -Werror -g

.PHONY: all update clean

all: $(TARGETS)

parser_tester: parser_tester.c $(COMMON_FILES)
	gcc $(CFLAGS) parser_tester.c $(COMMON_FILES) -o parser_tester

test_env: test_env.c $(COMMON_FILES)
	gcc $(CFLAGS) test_env.c $(COMMON_FILES) -o test_env

update:
	git pull https://github.com/comp530-f20/thsh.git lab0


clean:
	rm -f $(TARGETS)
