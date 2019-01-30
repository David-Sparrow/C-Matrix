#ifndef matrix_h
#define matrix_h

#include <cstdlib>
#include <cstdio>
#include <string.h>

/*Rozwiazanie ukladu rownan (6x6) przez odwracanie macierzy Ax=b => x=A^-1 * b
*/

int CreateMatrix(double ***pTab, int nSize); //0 = error, 1  = ok
void DeleteMatrix(double ***pTab, int nSize);
void PrintMatrix( double ** pTab, int nSize );//wypisz macierz na ekran
void TransMatrix( double**pTab, int nSize );//transponowanie macierzy
double Det( double**pTab, int nSize );// rozw wzgl 0-go wiersza
void InverseMatrix(double **pInv, double**pTab, int nSize, double det); //pTab - wejscie, pInv - wyjscie, det - wyznacznik, nSize - rozmiar tablicy
void LayoutEqu(double **pInv, double*pB, double *pRes, int nSize);//Obliczanie wektora wynikowego - pRes

#endif