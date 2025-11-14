#include "the_number_of_islands.h"
#include "../lib_DSU/DSU.h"

int field[NUMBER][NUMBER]; 

bool is_valid(int r, int c) {
	return r >= 0 && r < NUMBER && c >= 0 && c < NUMBER;
}

void field_games() {
	std::srand(std::time(0));
	for (int i = 0; i < NUMBER; i++) {
		for (int j = 0; j < NUMBER; j++) {
			int value = rand() % 2;
			field[i][j] = value;
		}
	}
}

void print_field() {
	for (int i = 0; i < NUMBER; i++) {
		for (int j = 0; j < NUMBER; j++) {
			std::cout << field[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int checking_for_islands() {
	DSU dsu(NUMBER * NUMBER);
	
	for (int i = 0; i < NUMBER; i++) {
		for (int j = 0; j < NUMBER; j++) {
			if (field[i][j] == 1) {
				int current_cell_index = i * NUMBER + j;

				if (is_valid(i, j + 1) && field[i][j + 1] == 1) {
					dsu.union_set(current_cell_index, i * NUMBER + (j + 1));
				}
				if (is_valid(i + 1, j) && field[i + 1][j] == 1) {
					dsu.union_set(current_cell_index, (i + 1) * NUMBER + j);
				}
			}
		}
	}

	int num_islands = 0;
	for (int i = 0; i < NUMBER; i++) {
		for (int j = 0; j < NUMBER; j++) {
			if (field[i][j] == 1) {
				int current_cell_index = i * NUMBER + j;
				if (dsu.find(current_cell_index) == current_cell_index) {
					num_islands++;
				}
			}
		}
	}
	return num_islands;
}