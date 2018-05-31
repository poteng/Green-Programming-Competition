/*
 ============================================================================
 Name        : GreenProjectC.c
 Author      : Po-Teng Tseng
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

//cscan is better than cin
//



#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

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


const int size_pool = 80000;
struct node table[80000];

//http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

void initial()
{

}



static int partition( struct node* table,  int start,  int end) {
	//int value_pivot = table[(start + end)/2].freq;
	int value_pivot;
	int temp_index_pivot = start;
	int i = start; //index of left side elements
	int j = start; //index of current element
	struct node node_tmp;


	//median of first, middle and last element
	if (end - start >= 3){
		value_pivot = max(min(table[start].freq,table[end].freq),
			min(max(table[start].freq,table[end].freq),table[(start + end)/2].freq));
	} else {
		value_pivot = table[start].freq;
	}

	//heuristic value for pivot
	if (value_pivot == 0) value_pivot = 1;


	for (j = start; j <= end; j++) {
		if (table[j].freq >= value_pivot) {
			//move the bigger element to left
			node_tmp = table[j];
			table[j] = table[i];
			table[i] = node_tmp;
			if (table[i].freq == value_pivot) temp_index_pivot = i;
			i++;
		}
	}

	//move the pivot to the middle (i - 1)
	node_tmp = table[i - 1];
	table[i - 1] = table[temp_index_pivot];
	table[temp_index_pivot] = node_tmp;



	//swap(table, i + 1, end);
	/*
	node_tmp = table[i + 1];
	table[i + 1] = table[end];
	table[end] = node_tmp;
	*/


//	printf("%d %d %d partition pivot: %d start: %d end: %d return: %d\n", table[start].freq,table[(start + end)/2].freq, table[end].freq, value_pivot, start, end, i - 1);




	//when all empty terms are at right side
	if (i == start && value_pivot ==1) return -1;

	return i - 1;
}


void quick_select(struct node* table,  int start,  int end, int num_start, int num_end){
	int pivot;

	if (start >= end) return;

	if (start > num_end) {
		//printf("~~smart return. start %d > num_end %d \n" , start, num_end);
		return;
	} else if (end < num_start) {
		//printf("~~smart return. end %d < num_start %d \n" , end, num_start);
		return;
	}

	if (end - start == 1 && table[start].freq >= table[end].freq) {
		//printf("~~smart return. only 2 value. table[start]:%d > table[end]:%d \n" , table[start].freq, table[end].freq);
		return;
	}

	pivot = partition(table, start, end);



	if (pivot == -1) return;
/*
	if (pivot >= num_end - 1){
		printf("[quick_select] pivot = %d start %d end %d %d~%d(first\n", pivot, start, end, num_start, num_end);
		quick_select(table, start, pivot - 1,  num_start, num_end);		//first half
	} else if (pivot <= num_start - 1){
		printf("[quick_select] pivot = %d start %d end %d %d~%d(second\n", pivot, start, end, num_start, num_end);
		quick_select(table, pivot + 1, end, num_start, num_end);		//first half
	} else { //not done
		printf("[quick_select] pivot = %d start %d end %d %d~%d(double\n", pivot, start, end, num_start, num_end);
		quick_select(table, start, pivot - 1,  num_start, num_end);		//first half
		quick_select(table, pivot + 1, end, num_start, num_end); 	//second half
	}*/

//	printf("[quick_select] pivot = %d start %d end %d %d~%d(double\n", pivot, start, end, num_start, num_end);
	quick_select(table, start, pivot - 1,  num_start, num_end);		//first half

	quick_select(table, pivot + 1, end, num_start, num_end); 	//second half


	return;
}



int main(void) {

	char buff_line[1200];
	char* pt_buff_line;
	char buff[110];
	int num_test;
	int num_line;
	int num_start;
	int num_end;
	unsigned int index;
	int num_parsed = 0;
	struct node node_tmp;

	int i;
	int j;
	int k;
	int l;

	setbuf(stdout, NULL);




	FILE *file1;
	file1 = fopen( "test3.in", "r");
	if (file1 == NULL)
	{
		printf("\nFile open failed.\n");
		return 17;
	}

	fscanf(file1, "%s", buff);
	num_test = strtol (buff, NULL, 10);

	for (l = 1; l <= num_test; l++){

		printf("\nTestcase #%d\n", l);

		for (i = 0; i < size_pool; i++){
			strcpy(table[i].name, "");
			table[i].freq = 0;
		}

		fscanf(file1, "%s", buff);
		num_line = strtol (buff, NULL, 10);
		fscanf(file1, "%s", buff);
		num_start = strtol (buff, NULL, 10);
		fscanf(file1, "%s", buff);
		num_end = strtol (buff, NULL, 10);
//		printf("%d %d %d %d\n", num_test, num_line, num_start, num_end);

		fgets(buff_line, 1200, file1);

		//read and assign words to array
		for (j = 0; j < num_line; j++){
		//while (fscanf(file1, "%s%c", buff, &aaa) >= 0 ){
			//fscanf(file1, "%s", buff);

			pt_buff_line = fgets(buff_line, 1200, file1);
			//printf("%s", buff_line);
			while (sscanf(pt_buff_line, "%s %n", buff, &num_parsed) == 1)
			{
				//if (j % 249 == 0) printf("%s ", buff);
				pt_buff_line += num_parsed;
				index = hash(buff)%size_pool;
				k = 1;
				while (strcmp(table[index].name, "") != 0 && strcmp(table[index].name, buff) != 0){
					//printf("Conflict occurred at %d. ", index);
					//index = k * (hash(buff) + k)%size_pool;
					index = (index + k*k)%size_pool;
					//printf("New index : %d\n", index);
					if (k >= size_pool - 100) printf("%s New index : %d %s\n", buff, index, table[index].name);
					k++;
				}
				strcpy(table[index].name, buff);
				table[index].freq++;
				/*
				if (strcmp(table[index].name, "") == 0 || strcmp(table[index].name, buff) == 0){
					strcpy(table[index].name, buff);
					table[index].freq++;
				} else {
					//printf("#######Duplicated hash values######\n");
				}*/

				//printf("%s  %lu   i = %d, [%s]\n", buff, hash(buff)%size_pool, i, table[index].name);
			}
			//if (j % 249 == 0) printf("\n");
		}


		quick_select(table, 0, size_pool - 1, num_start, num_end);


		//while to increase range
		int up = num_start - 1;	//min: 0
		int down = num_end - 1;
		while (up >= 1 && table[up].freq == table[up - 1].freq){
			up--;
		}
		while (table[down].freq == table[down + 1].freq){
			down++;
		}
		//printf("up %d   down %d\n", up, down);
		int s_down = up;

		//up is upper bound, s_down is lower bound for each chunk
		while (up <= down){
			while (table[s_down].freq == table[s_down + 1].freq){
				s_down++;
			}
//			printf("up %d   s_down %d\n", up, s_down);
			for (i = up; i <= s_down; i++){
				node_tmp = table[i];
				j = i - 1;
				while (j >= 0 && j >= up && strcmp(node_tmp.name, table[j].name) < 0){

	//				printf("i = %d j = %d  %s < %s \n", i, j, node_tmp.name, table[j].name);
					table[j + 1] = table[j];
					j--;
				}
				table[j + 1] = node_tmp;
			}
			//go to next chunk
			s_down++;
			up = s_down;
		}

//		printf("%d %s %s\n", strcmp(table[29].name, table[30].name), table[29].name, table[30].name);
//		printf("%d %s %s\n", strcmp(table[30].name, table[31].name), table[30].name, table[31].name);


		for (i = num_start - 1; i < num_end; i++)
		{
			if (table[i].freq != 0 || table[i].freq == 0)
			{
				printf("%d %s:%d\n", i, table[i].name, table[i].freq);
			}
		}
		while (table[i].freq == table[i - 1].freq){
			//printf("extra %d %s:%d\n", i, table[i].name, table[i].freq);
			i++;
		}



/*
		j = 0;
		for (i = 0; i < size_pool; i++)
		{
			if (table[i].freq != 0)
			{
				j++;
			}
		}
		printf("Total %d words.\n", j);*/

	}


	fclose(file1);


	return EXIT_SUCCESS;
}
