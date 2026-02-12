#define LABIRINT_H
#ifdef LABIRINT_H
#include <iostream>
#include "../lib_DSU/DSU.h"
#include <ctime>

Matrix<bool> generate(int X, int Y, int N, int M) {
	DSU dsu(M * N);


}

void print(Matrix<bool> labirint, int N, int M){
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (i == 0) {
				std::cout << "+------------------" << std::endl;


			}
		}
	}
}



#endif