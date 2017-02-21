CXX = g++
SIZE=17
CXXFLAGS = -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS = 

main: main.o symbol.o  symbol_table.o pl_type.o gpl_assert.o
	$(CXX) $^ -o $@ $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $<

symbol.o: symbol.cpp symbol.h 
	$(CXX) $(CXXFLAGS) -c $<

symbol_table.o: symbol_table.cpp symbol_table.h
	$(CXX) $(CXXFLAGS) -c $<

gpl_type.o: gpl_type.cpp gpl_type.h
	$(CXX) $(CXXFLAGS) -c $<

gpl_assert.o: gpl_assert.cpp gpl_assert.h
	$(CXX) $(CXXFLAGS) -c $<


clean:
	rm -f *.o
