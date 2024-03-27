cc: cc.cpp c.tab.cpp c.lex.cpp ast.cpp ast.cpp ast.hpp semantic.cpp
	g++ ast.cpp semantic.cpp c.tab.cpp c.lex.cpp cc.cpp -lm -ll -g -lfl -o $@

c.tab.cpp c.tab.hpp: c.y
	bison --debug -o c.tab.cpp -d c.y
	# bison -o c.tab.cpp -d c.y

c.lex.cpp: c.l c.tab.hpp
	flex -o c.lex.cpp -l c.l

clean::
	rm -f c.tab.cpp c.tab.hpp c.lex.cpp cc c.output
