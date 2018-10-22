/*
 ============================================================================
 Name        : optimized.c
 Author      : Po-Teng Tseng
 Description : The optimization related to algorithm design, parallel programing, and knowledge about ideal size of hash table.
 ============================================================================
 */



#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <omp.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

struct node
{
	char name[110];
	int freq;
};


//This good hash function was found on http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}


int cmpfunc(const void * a, const void * b){
	struct node *orderA = (struct node *)a;
	struct node *orderB = (struct node *)b;
	return ( orderB->freq - orderA->freq);
}


int main(void) {

	char buff_line[1200];
	char* pt_buff_line;
	char buff[110];
	int num_test;
	int num_line;
	int num_start;
	int num_end;
	int num_start_a[40];
	int num_end_a[40];
	unsigned int index;
	int num_parsed = 0;
	struct node node_tmp;

	int i;
	int j;
	int k;
	int l;

	const int size_pool = 60000;	//60,000 is the optimized size for the hash table for this question
	
	//it's struct node table[40][40000];
	struct node** table;
	table = malloc(sizeof(struct node*) * 40);
	for (i = 0; i < 40; i++){
		table[i] = malloc(sizeof(struct node) * 60000);
	}


	

	FILE *file1;
	file1 = fopen( "test.in", "r");
	if (file1 == NULL)
	{
		printf("\nFile open failed.\n");
		return 17;
	}

	fscanf(file1, "%s", buff);
	num_test = strtol (buff, NULL, 10);

	for (l = 0; l < num_test; l++){

		for (i = 0; i < size_pool; i++){
			strcpy(table[l][i].name, "");
			table[l][i].freq = 0;
		}

		fscanf(file1, "%s", buff);
		num_line = strtol (buff, NULL, 10);
		fscanf(file1, "%s", buff);
		num_start = strtol (buff, NULL, 10);
		num_start_a[l] = num_start;
		fscanf(file1, "%s", buff);
		num_end = strtol (buff, NULL, 10);
		num_end_a[l] = num_end;

		fgets(buff_line, 1200, file1);

		//read and assign words to array
		for (j = 0; j < num_line; j++){
			pt_buff_line = fgets(buff_line, 1200, file1);
			while (sscanf(pt_buff_line, "%s %n", buff, &num_parsed) == 1)
			{
				pt_buff_line += num_parsed;
				index = hash(buff)%size_pool;
				k = 1;
				while (strcmp(table[l][index].name, "") != 0 && strcmp(table[l][index].name, buff) != 0){
					index = (index + k + k*k)%size_pool;
					if (k >= size_pool - 100) printf("%s New index : %d %s\n", buff, index, table[l][index].name);
					k++;
				}
				strcpy(table[l][index].name, buff);
				table[l][index].freq++;
			}
		}
	}


	#pragma omp parallel for num_threads(5)
	for (l = 0; l < num_test; l++){
		qsort(table[l], size_pool, sizeof(struct node), cmpfunc);
	}

	for (l = 0; l < num_test; l++){
		//while to increase range
		int up = num_start_a[l] - 1;	//min: 0
		int down = num_end_a[l] - 1;
		while (up >= 1 && table[l][up].freq == table[l][up - 1].freq){
			up--;
		}
		while (table[l][down].freq == table[l][down + 1].freq){
			down++;
		}
		int s_down = up;

		//up is upper bound, s_down is lower bound for each chunk
		while (up <= down){
			while (table[l][s_down].freq == table[l][s_down + 1].freq){
				s_down++;
			}
			for (i = up; i <= s_down; i++){
				node_tmp = table[l][i];
				j = i - 1;
				while (j >= 0 && j >= up && strcmp(node_tmp.name, table[l][j].name) < 0){
					table[l][j + 1] = table[l][j];
					j--;
				}
				table[l][j + 1] = node_tmp;
			}
			//go to next chunk
			s_down++;
			up = s_down;
		}

		printf("\nTestcase #%d\n", l + 1);
		for (i = num_start_a[l] - 1; i < num_end_a[l]; i++)
		{
			if (table[l][i].freq != 0 || table[l][i].freq == 0)
			{
				printf("%s:%d\n", table[l][i].name, table[l][i].freq);
			}
		}
	}
	
	fclose(file1);
	free(table);

	return EXIT_SUCCESS;
}
