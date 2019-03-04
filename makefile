TARGETS = myShell

all: $(TARGETS)

%o: %.c
	gcc -g -c -o  $@ $<
myShell: clock.o cd.o echo.o pwd.o pinfo.o ls.o main.o remindme.o sighandler.o othcommands.o env.o overkill.o jobs.o kjob.o fg.o bg.o execCTRL_C.o execCTRL_Z.o
	gcc -o myShell clock.o cd.o echo.o pwd.o pinfo.o ls.o main.o remindme.o sighandler.o othcommands.o env.o overkill.o jobs.o kjob.o fg.o bg.o execCTRL_C.o execCTRL_Z.o

.PHONY: clean
clean:
	rm -f $(TARGETS) *.o