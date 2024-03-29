#include "matrix.h"

void Complement( double**pTab0, double**pTab1, int nRow, int nCol, int nSize ); //wycina podany wiersz i kolumne; pTab0 - wyjscie, pTab1 - wejscie;
void ComplementMatrix( double**pTabD, double **pTab, int nSize ); //oblicza macierz dopelnien

int CreateMatrix( double *** pTab, int nSize )
{
	double ** p = *pTab = (double **)malloc( nSize * sizeof( double* ) );
	if (!p)
	{
		perror( "ERROR: CreateMatrix!" );
		return 0;
	}
	memset( p, 0, nSize * sizeof( double* ) );

	for (int i = 0; i < nSize; i++)
	{
		*p = (double *)malloc( nSize * sizeof( double ) );
		if (!*p)
		{
			perror( "ERROR: CreateMatrix!" );
			return 0;
		}
		memset( *p++, 0, nSize * sizeof( double ) );
	}
	return 1;
}
//-------------------
void DeleteMatrix( double *** pTab, int nSize )
{
	double ** v = *pTab;
	for (int i = 0; i < nSize; i++)
	{
		free( *v++ );
	}
	free( *pTab );
	*pTab = NULL;
}
//-------------------
void PrintMatrix( double ** pTab, int nSize )
{
	for (int i = 0; i < nSize; i++)
	{
		double * p = *pTab++;
		for (int j = 0; j < nSize; j++)
		{
			printf( "%.2lf\t", *p++ );
		}
		printf( "\n" );
	}
}
//-------------------
void Complement( double** pTab0, double** pTab1, int nRow, int nCol, int nSize )
{
	for (int r = 0; r < nSize; r++)
	{
		double* v1 = *pTab0;
		double* v = *pTab1++;
		if (r == nRow) continue;

		for (int c = 0; c < nSize; c++, v++)
		{
			if (c == nCol) continue;
			*v1++ = *v;
		}
		pTab0++;
	}
}
//-------------------
void ComplementMatrix( double** pTabD, double** pTab, int nSize )
{
	double** pCompl = NULL;
	if (!CreateMatrix( &pCompl, nSize - 1 )) exit(3);
	for (int nRow = 0; nRow < nSize; nRow++)
	{
		double coef = (nRow % 2) ? -1 : 1;
		double* v = *pTabD++;
		for (int nCol = 0; nCol < nSize; nCol++)
		{
			Complement( pCompl, pTab, nRow, nCol, nSize );
			*v++ = coef * Det( pCompl, nSize - 1 );
			coef = -coef;
		}
	}
	DeleteMatrix( &pCompl, nSize - 1 );
}
//-------------------
void TransMatrix( double ** pTab, int nSize )
{
	double tmp;
	double ** p = pTab;
	for (int i = 0; i < nSize-1; i++)
	{
		double *v = *p++ + i + 1;
		for (int j = i + 1; j < nSize; j++, v++)
		{
			tmp = *v;
			*v = pTab[j][i];
			pTab[j][i] = tmp;
		}
	}
}
//-------------------
double Det( double**pTab, int nSize )
{
	if (nSize == 1) return **pTab;
	else if (nSize == 2) return **pTab * pTab[1][1] - pTab[0][1] * pTab[1][0];

	double res = 0;
	double** pT = NULL;
	
	if (!CreateMatrix( &pT, nSize - 1 )) exit(3);

	int coef = 1;
	double* p = *pTab;
	for (int nCol = 0; nCol < nSize; nCol++)
	{

		Complement( pT, pTab, 0, nCol, nSize );

		res += coef * *p++ * Det( pT, nSize - 1 );
		coef = -coef;
	}
	DeleteMatrix( &pT, nSize - 1 );
	return res;
}
//-------------------
void InverseMatrix( double** pInv, double** pTab, int nSize, double det )
{
	ComplementMatrix( pInv, pTab, nSize );
	TransMatrix( pInv, nSize );

	for (int r = 0; r < nSize; r++)
	{
		double* v = *pInv++;
		for (int c = 0; c < nSize; c++, v++)
		{
			*v /= det;
		}
	}
}
//-------------------
void LayoutEqu( double **pInv, double*pB, double *pRes, int nSize )
{
	for (int i = 0; i < nSize; i++)
	{
		double * wolne = pB;
		double * v = *pInv++;
		for (int j = 0; j < nSize; j++)
		{
			*pRes += (*v++) * (*wolne++);
		}
		pRes++;
	}
}