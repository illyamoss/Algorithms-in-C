#include <stdio.h>
#include <stdlib.h>

const int MATRIX_ROWS = 5;
const int MATRIX_COLS = 4;


void printMatrix(int matrix[MATRIX_ROWS][MATRIX_COLS])
{
    for (int row = 0; row < MATRIX_ROWS; ++row) {
        printf("%d:\t", row);

        for (int col = 0; col < MATRIX_COLS; ++col) {
            printf("%x ", matrix[row][col]);
        }

        printf("\n");
    }
}


int main(int argc, char **argv)
{
    int matrix[MATRIX_ROWS][MATRIX_COLS];

    for (int row = 0; row < MATRIX_ROWS; ++row) {
        for (int col = 0; col < MATRIX_COLS; ++col) {
            matrix[row][col] = (row << 16) | col;
        }
    }

    printf("%lu\n", sizeof(matrix));
    printMatrix(matrix);

    return 0;
}
