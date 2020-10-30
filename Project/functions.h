//
// Created by 陆彦青 on 2020/10/30.
//

#ifndef PROJECT_FUNCTIONS_H
#define PROJECT_FUNCTIONS_H

struct matrix{
    matrix(int r, int c) {
        row = r;
        column = c;
        data = new float [r*c]();
    }
    matrix() = default;;
    int row{};
    int column{};
    float *data{};
};

void matrixCompute(matrix &m1, matrix &m2, matrix &m3);
float vectorCompute(float * v1, float * v2, size_t n);

#endif //PROJECT_FUNCTIONS_H
