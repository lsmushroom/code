SRCFILE=$(shell ls ./*.c)
OBJFILE=$(SRCFILE .c:=.o)

.PHONY:all

all:$(OBJFILE)
	gcc -g -o tree $(SRCFILE)
#$(OBJFILE):$(SRCFILE)
#	gcc -c $@ -o $<
	
.PHONY:depend
depend:
	gcc -M ./* > .depend


clean:
	rm -f ./*.o tree



