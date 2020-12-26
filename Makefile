DEBUG = false
CPP = g++
CFLAGS = -std=c++17

ifeq ($(DEBUG), true)
CFLAGS += -g3 -O0
else
CFLAGS += -O2
endif

.PHONY : all
all : sim_cache

sim_cache : main.o cache.o row_base.o row_lfu.o row_lru.o row_wbwa.o row_wtna.o row.o
	$(CPP) -o sim_cache main.o cache.o row_base.o row_lfu.o row_lru.o row_wbwa.o row_wtna.o row.o $(CFLAGS)
main.o : main.cpp cache.h
	$(CPP) -c -o main.o main.cpp $(CFLAGS)
cache.o : cache.cpp cache.h utils.hpp
	$(CPP) -c -o cache.o cache.cpp $(CFLAGS)
row_base.o : row_base.cpp row_base.h
	$(CPP) -c -o row_base.o row_base.cpp $(CFLAGS)
row_lfu.o : row_lfu.cpp row_lfu.h
	$(CPP) -c -o row_lfu.o row_lfu.cpp $(CFLAGS)
row_lru.o : row_lru.cpp row_lru.h
	$(CPP) -c -o row_lru.o row_lru.cpp $(CFLAGS)
row_wbwa.o : row_wbwa.cpp row_wbwa.h
	$(CPP) -c -o row_wbwa.o row_wbwa.cpp $(CFLAGS)
row_wtna.o : row_wtna.cpp row_wtna.h
	$(CPP) -c -o row_wtna.o row_wtna.cpp $(CFLAGS)
row.o : row.cpp row.h row_lfu.h row_lru.h row_wbwa.h row_wtna.h
	$(CPP) -c -o row.o row.cpp $(CFLAGS)

.PHONY : clean
clean :
	-rm sim_cache main.o cache.o row_base.o row_lfu.o row_lru.o row_wbwa.o row_wtna.o row.o
