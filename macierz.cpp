#include "matrix.h"

#define DEBUG

void ReadDate( FILE * pl, double ** pTab, double * pB, int nSize );
//-------------------
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		perror("\nUzyj: macierz <input_file>");
		return 1;
	}

	FILE* plik = NULL;

	if ((plik = fopen( argv[1],"r") ) == NULL) 
	{
		perror( "Blad otwarcia pliku!!\n" );
		return 2;
	}

	double ** pMacierz = NULL;
	int nRozmiar;
	fscanf( plik, "%d\n", &nRozmiar );

	if (!CreateMatrix( &pMacierz, nRozmiar )) return 3;

	double * B = (double *)malloc( nRozmiar * sizeof( double ) );//Wektor wyrazów wolnych
	if (!B) return 3;
	memset( B, 0, nRozmiar * sizeof( double ) );

	ReadDate( plik, pMacierz, B, nRozmiar );
	fclose( plik );

	double det = Det( pMacierz, nRozmiar );

#ifdef DEBUG
	printf( "\nWczytana macierz:\n" );
	PrintMatrix( pMacierz, nRozmiar );
	printf( "\n\nWektor wyrazow wolnych:" );
	double * cpyB = B;
	for (int i = 0; i < nRozmiar; i++)
	{
		printf( "\n%.2lf", *cpyB++ );
	}
	printf( "\n\nDet = %.2lf\n\n", det );
#endif

	if (fabs(det) > 1e-14)
	{
		double ** pOdwr = NULL;
		if (!CreateMatrix( &pOdwr, nRozmiar )) return 3;
		InverseMatrix( pOdwr, pMacierz, nRozmiar, det );
#ifdef DEBUG
		printf( "\nMacierz odwrotna:\n" );
		PrintMatrix( pOdwr, nRozmiar );
#endif
		double * x = (double*)malloc( nRozmiar * sizeof( double ) ); //Wektor niewiadomych
		if (!x) return 3;
		memset( x, 0, nRozmiar * sizeof( double ) );

		LayoutEqu( pOdwr, B, x, nRozmiar );

		printf( "\nWYNIKI:\n" );
		double * cpyX = x;
		for (int i = 1; i <= nRozmiar; i++)
		{
			printf( "\nX%d = %.2lf", i, *cpyX++ );
		}

		free( x );
		DeleteMatrix( &pOdwr, nRozmiar );
	}

	free( B );
	DeleteMatrix( &pMacierz, nRozmiar );

	return 0;

}
//-------------------
void ReadDate( FILE * pl, double ** pTab, double * pB, int nSize )
{
	for (int i = 0; i < nSize; i++)
	{
		double * v = *pTab++;
		for (int j = 0; j < nSize; j++)
		{
			fscanf( pl, "%lf ", v++ );
		}
		fscanf( pl, " %lf\n", pB++ );
	}
}
