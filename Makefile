INC=-I/home/tntech.edu/zonik42/gmp/gmp_install/include
LIB=-L/home/tntech.edu/zonik42/gmp/gmp_install/lib -lgmp

build:
	g++ parallel_modular_exponentiation.cpp -std=c++11 $(INC) $(LIB) -fopenmp

clean:
	rm a.out