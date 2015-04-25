#LIBS=libs/index-handler libs/parser-handler libs/data-packets libs/data-structs libs/xmlshark libs/formatting libs/porter2-stemmer
#LIBS=$(wildcard libs/*)
LIBS=libs/xmlshark libs/porter2-stemmer libs/parser-handler libs/index-handler libs/query-engine libs/user-interface
INCLUDE_PATH=libs/
EXE=search

$(EXE): libraries
	g++ -std=c++0x -O3 cli/test.cc $(wildcard libraries/*) -I$(INCLUDE_PATH) -o $(EXE)

libraries:
	mkdir libraries/
	for dir in $(LIBS); do \
		cd $$dir; \
		g++ -std=c++0x -c -O3 *.cc -I../; \
		mv *.o ../../libraries; \
		cd -; \
	done

clean:
	rm -rf libraries/ $(EXE).tar $(EXE)

tar: $(EXE)
	tar cfv $(EXE).tar cli libs $(EXE) 