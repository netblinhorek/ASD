#pragma once
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

const int NUMBER = 5; // Предполагаемый размер поля
extern int field[NUMBER][NUMBER]; // Объявляем field как внешний массив

// Объявляем вспомогательные функции
bool is_valid(int r, int c);
void field_games();
void print_field();
int checking_for_islands();
