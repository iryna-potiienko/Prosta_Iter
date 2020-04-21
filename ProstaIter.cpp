// ProstaIter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
using namespace std;
#include <Windows.h>

#define eps 0.001

struct Point{
    double x;
    double y;
};

Point system(Point point) {
    Point pointk;
    double xk, yk;
    xk = (cos(point.y) + 0.9)/3;
    yk = sin(point.x - 0.6) - 1.6;
    pointk = { xk,yk };
    return pointk;
}

double matrix_norm(double b[][2]) {
    double sum, sumi[2] = {};
    for (int j = 0; j < 2; j++) {
        sum = 0;
        for (int i = 0; i < 2; i++) {
            sum += abs(b[i][j]);
        }
        sumi[j] = sum;
    }
    double max = 0;
    for (int j = 0; j < 3; j++) {
        if (sumi[j] >= max) max = sumi[j];
    }
    return max;
}

bool convergence(Point point) {
    double yakobi[2][2];
    yakobi[0][0] = 0;
    yakobi[0][1] = -sin(point.y) / 3;
    yakobi[1][0] = cos(point.x - 0.6);
    yakobi[1][1] = 0;
    double norm = matrix_norm(yakobi);
    if (norm <= 1) return 0;
    else return 1;
}

// Умова зупинки
bool stopCheck(Point pk, Point pkp)
{
    double norm = 0;
    norm = (pk.x - pkp.x) * (pk.x - pkp.x) + (pk.y - pkp.y) * (pk.y - pkp.y);
    if (sqrt(norm) < eps) {
        return 0;
    }
    else return 1;
}

Point prostIter(Point point0) {
    Point pointK;
    Point pointK_1 = point0;
    int i = 0;
    do{
        pointK = pointK_1;
        i++;
        pointK_1 = system(pointK);
        cout << "\n " << i << ".  x = " << pointK_1.x << "   y = " << pointK_1.y;
    } while (stopCheck(pointK_1, pointK)!=0);
    return pointK_1;
}



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Point pointK;
    Point point0 = { 1.25,0 };
    printf("Задана система: \n  x = (cos y + 0.9)/3 \n  y = sin(x - 0.6) - 1.6; ");
    printf("\n\nМетод простої ітерації: ");
    if (convergence(point0)!=0)
        printf("\nМетод не збігається при початковому наближенні (%f, %f)", point0.x, point0.y);
    else {
        printf("\nМетод збіжний при заданому початковому наближенні (%f, %f)\n", point0.x, point0.y);
        pointK = prostIter(point0);
        cout << "\n\nВідповідь: x = " << pointK.x << ", y = " << pointK.y<<"\n";
    }
}
