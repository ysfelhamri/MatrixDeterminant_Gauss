#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double triang(double **, int);
double det_gauss(double **, int);

void printmat(double **, int);

int main()
{

    int size, i, j, ch, rfloor, rmax, mod;
    double det, valmod;
    double **mat;
    srand(time(NULL));
    do
    {
        printf("\nEnter the size of the matrix :");
        scanf("%d", &size);
    } while (size <= 1);

    mat = (double **)malloc(size * sizeof(double *));
    if (mat == NULL)
    {
        printf("Allocation error");
        exit(33);
    }

    for (i = 0; i < size; i++)
    {
        mat[i] = (double *)malloc(size * sizeof(double));
        if (mat[i] == NULL)
        {
            printf("Allocation error");
            exit(33);
        }
    }

    do
    {
        printf("\nNormal fill/Random fill 1/0 :");
        scanf("%d", &ch);
    } while (ch != 1 && ch != 0);

    if (ch)
    {
        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                printf("Enter element [%d,%d] :", i, j);
                scanf("%lf", &mat[i][j]);
            }
            printf("\n");
        }
    }
    else
    {

        printf("\nEnter rand() floor :");
        scanf("%d", &rfloor);

        do
        {
            printf("Enter rand() max :");
            scanf("%d", &rmax);
        } while (rmax < rfloor);

        for (i = 0; i < size; i++)
            for (j = 0; j < size; j++)
                mat[i][j] = rfloor + rand() % (rmax - rfloor + 1);
    }

    printf("\nMatrix :");
    printmat(mat, size);

    do
    {
        printf("\nModify matrix ? 1/0 :");
        scanf("%d", &mod);
    } while (mod != 1 && mod != 0);
    if (mod)
    {
        while (1)
        {
            do
            {
                printf("\nEnter row position :");
                scanf("%d", &i);
            } while (i >= size);
            if (i < 0)
                break;
            do
            {
                printf("\nEnter column position :");
                scanf("%d", &j);
            } while (j >= size);
            if (j < 0)
                break;
            printf("\nEnter the value :");
            scanf("%lf", &valmod);
            mat[i][j] = valmod;
            printf("\nMatrix :");
            printmat(mat, size);
        }

        printf("\nMatrix :");
        printmat(mat, size);
    }

    printf("Determinant = %lf", det_gauss(mat, size));

    for (i = 0; i < size; i++)
        free(mat[i]);
    free(mat);

    return 0;
}

double triang(double **mat, int size)
{
    int i, j, k;
    double tmp, res = 1;

    if (mat[0][0] == 0)
        return 0;
    tmp = mat[0][0];
    for (k = 0; k < size; k++)
        mat[0][k] /= tmp;
    res *= tmp;
    for (i = 1; i < size - 1; i++)
        for (j = 0; j <= i; j++)
        {
            if (mat[i][j] == 0)
                continue;
            tmp = mat[i][j];
            for (k = 0; k < size; k++)
                mat[i][k] = (mat[i][k] / tmp) - ((j != i) ? mat[j][k] : 0);
            res *= tmp;
        }
    for (j = 0; j < size - 1; j++)
    {
        if (mat[size - 1][j] == 0)
            continue;
        tmp = mat[size - 1][j];
        for (k = 0; k < size; k++)
            mat[size - 1][k] = (mat[size - 1][k] / tmp) - mat[j][k];
        res *= tmp;
    }

    return res;
}
double det_gauss(double **mat, int size)
{
    int i;
    double res = triang(mat, size);
    if (res == 0)
        return 0;
    else
        for (i = 0; i < size; i++)
            res *= mat[i][i];
    return res;
}
void printmat(double **mat, int size)
{
    int i, j;
    printf("\n");
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
            printf("[%0.2lf]", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}
