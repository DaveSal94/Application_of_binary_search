#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************
Erwin Dave Salinas
1000-785-308
****************************/

void ranksbyBinary(int *firstLine, int *a, int *b, int *rank);
void readFile();

/***********************************
Function: readFile
Inputs: None
Outputs: None
Processing: Read file
*************************************/
void readFile()
{
	int *firstLine, *a, *b, *rank;
	int i, m, n, p;
	char* filename;
	FILE *fp;

	filename = (char*)malloc(20 * sizeof(int) + 1);

	printf("Type input file:\n");
	scanf("%s", filename);
	printf("\n");
	fp = fopen(filename, "r");

	firstLine = (int*)malloc(3 * sizeof(int) + 1);
	for (i = 0; i<3; i++) {
		fscanf(fp, "%d", &firstLine[i]); /* reads the first line in the file which consist of number of elements for array a and b,
										 and number of ranks to look for */
	}

	m = firstLine[0]; /* size of array a */
	n = firstLine[1]; /* size of array b */
	p = firstLine[2]; /* size of array rank */

	a = (int*)malloc((m + 1)*sizeof(int) + 1); /* Allocate memory for array a, b and rank based on the amount read by firstLine array */
	b = (int*)malloc((n + 1)*sizeof(int) + 1);
	rank = (int*)malloc((p + 1)*sizeof(int) + 1);

	/* Default values for first and last elements for array a and b */
	a[0] = -99999999;
	b[0] = -99999999;
	a[m + 1] = 99999999;
	b[n + 1] = 99999999;


	/* Read array a, b and rank */
	for (i = 1; i<(m + 1); i++) {
		fscanf(fp, "%d", &a[i]);
	}
	for (i = 1; i<(n + 1); i++) {
		fscanf(fp, "%d", &b[i]);
	}
	for (i = 0; i<(p + 1); i++){
		fscanf(fp, "%d", &rank[i]);
	}


	/* Call ranksbyBinary to rank elements from both arrays */
	ranksbyBinary(firstLine, a, b, rank);

}


/**************************************************************
Function: ranksbyBinary
Inputs: Takes int firstLine[], int a[], int b[], int rank[]
Outputs: Prints the rank of the element, the range high and
low in which the element is found and the element
it was found either i and j.
Processing: Binary Search
***************************************************************/

void ranksbyBinary(int *firstLine, int *a, int *b, int *rank)
{

	int each, m, n, p, high, low, amid, bmid, i, j;
	m = firstLine[0]; /* m is the size of array a */
	n = firstLine[1]; /* n is the size of array b */
	p = firstLine[2]; /* p is the size of array rank */

	/* For each rank input, check for 3 conditions that will satisfy that the element is array a and b.
	Prints the rank based on the location of the element */
	for (each = 0; each<p; each++)
	{
		if (rank[each] < (m + 1)){ /* if rank is less than the size of array a + 1 */
			low = 0;
			high = rank[each];
			while (low <= high){
				amid = (low + high) / 2;
				bmid = rank[each] - amid;
				i = amid;
				j = bmid;
				printf("low %d high %d i %d j %d a[%d] = %d b[%d] = %d\n", low, high, i, j, i, a[i], j, b[j]);
				if (i + j == rank[each]) /* 1st condition for both array a and b */
				{
					if (a[i] <= b[j + 1]) /* 3rd condition for array a */
					{
						if (a[i] > b[j])/* 2nd condition for array a */{
							printf("a[%d] = %d has rank %d\n", i, a[i], rank[each]);
							break;
						}
						else if (a[i] <= b[j])/* executed if 2nd condition for array a is not met */{
							if (a[i + 1] > b[j])/* 3rd condition for array b */{
								printf("b[%d] = %d has rank %d\n", j, b[j], rank[each]);
								break;
							}
							else if (a[i + 1] <= b[j])/* executed if 3rd condition for array b is not met */{
								low = amid + 1;
							}
						}
					}
					else if (a[i] > b[j + 1]){ /* executed if 3rd condition for array a is not met */
						high = amid - 1;
					}
				}
			}
		}
		else if (rank[each] >= m + 1){ /* if rank is equal or more than the size of array a + 1 */
			high = m;
			low = rank[each] - (n);
			while (low <= high){
				amid = (low + high) / 2;
				bmid = rank[each] - amid;
				i = amid;
				j = bmid;
				printf("low %d high %d i %d j %d a[%d] = %d b[%d] = %d\n", low, high, i, j, i, a[i], j, b[j]);
				if (i + j == rank[each]) /* 1st condition for both array a and b */
				{
					if (a[i] <= b[j + 1]) /* 3rd condition for array a */
					{
						if (a[i] > b[j]){ /* 2nd condition for array a */
							printf("a[%d] = %d has rank %d\n", i, a[i], rank[each]);
							break;
						}
						else if (a[i] <= b[j]){ /* executed if 2nd condition for array a is not met */
							if (a[i + 1] > b[j]){  /* 3rd condition for array b */
								printf("b[%d] = %d has rank %d\n", j, b[j], rank[each]);
								break;
							}
							else if (a[i + 1] <= b[j]){ /* executed if 3rd condition for array b is not met */
								low = amid + 1;
							}
						}
					}
					else if (a[i] > b[j + 1]){ /* executed if 3rd condition for array a is not met */
						high = amid - 1;
					}
				}
			}
		}
	}
}
int main()
{
	readFile();
	return 0;
}

