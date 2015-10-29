#
# Makefile -- for user threads library with synchronization
#
 
CC = gcc
INCLUDE_PATH=.
#-fno-stack-protector -zexecstack
CFLAGS1 = -O1 -g -I$(INCLUDE_PATH)
CFLAGS = -g -I$(INCLUDE_PATH)
 
TESTS = hello helloa hellob helloc hellod helloe hello3 trigger genpage
 
all: $(TESTS)

%.o: %.c
	$(CC) $(CFLAGS1) -c -o $@ $<

hello: hello.o
	$(CC) $(CFLAGS1) -o $@ $^

helloa: hello.c
	$(CC) $(CFLAGS1) -o $@ $<
#	execstack -s $@

hellob: hello.c
	$(CC) $(CFLAGS1) -o $@ $<
#	execstack -s $@

helloc: hello.c
	$(CC) $(CFLAGS1) -o $@ $<

hellod: hello.c
	$(CC) $(CFLAGS) -o $@ $<

helloe: hello.c
	$(CC) $(CFLAGS) -o $@ $<

hello3: align.o readString.o align2.o hello3.o align3.o sandbox.o 
	$(CC) $(CFLAGS1) -o $@ $^

trigger: trigger.o
	$(CC) $(CFLAGS1) -o $@ $^

genpage: genpage.o
	$(CC) $(CFLAGS1) -o $@ $^

align.c: genpage
	./genpage 1 4096 > $@

align2.c: genpage
	./genpage 2 4096 > $@

align3.c: genpage
	./genpage 3 4096 > $@

clean:
	$(RM) align* $(TESTS) a.out core *.o *.BAK *.CKP *~ #*
