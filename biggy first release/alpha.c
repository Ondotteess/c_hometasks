#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
#pragma warning(disable:4996)

void nullCheck(arr) {
	if (arr == NULL) {
		printf("out of memory");
		exit(0);
	}
}

struct string_arr {
	char** arr;
	size_t len;
	size_t capacity;
};

struct string {
	char* arr;
	size_t len;
	size_t capacity;
};

struct dym_arr {
	size_t* arr;
	size_t len;
	size_t capacity;
	size_t counter;
};

int check = 0;

void printArr(char* arr, size_t len) {
	for (size_t i = 0; i < len; i++) {
		printf("%c", arr[i]);
	}
}

void printArr2(char* arr, size_t len) {
	for (size_t i = 0; i < len; i++) {
		printf("%s", arr[i]);
	}
}


int main() {
	FILE* test = fopen("test.txt", "r");

	struct dym_arr arr_len;
	arr_len.arr = NULL;
	arr_len.len = 0;
	arr_len.capacity = 1;
	arr_len.counter = 0;

	struct string_arr str_arr;
	str_arr.arr = NULL;
	str_arr.len = 0;
	str_arr.capacity = 1;

	struct string s;
	s.arr = NULL;
	s.len = 0;
	s.capacity = 1;

	char sym;
	while (1)
	{
		sym = fgetc(test);

		if (arr_len.capacity - arr_len.len == 1) {
			arr_len.arr = (size_t*)realloc(arr_len.arr, (arr_len.capacity * 2) * sizeof(size_t));
			nullCheck(arr_len.arr);
			arr_len.capacity *= 2;
		}

		if (str_arr.capacity - str_arr.len == 1) {
			str_arr.arr = (char**)realloc(str_arr.arr, (str_arr.capacity * 2) * sizeof(char*));
			nullCheck(str_arr.arr);
			str_arr.capacity *= 2;
		}

		if (s.capacity - s.len == 1) {
			s.arr = (char*)realloc(s.arr, (s.capacity * 2) * sizeof(char));
			nullCheck(s.arr);
			s.capacity *= 2;
		}
		
		if (sym == EOF) {
			if (feof(test) != 0) {
				str_arr.arr[str_arr.len++] = s.arr;
				printArr(str_arr.arr[str_arr.len - 1], s.len);
				arr_len.arr[arr_len.len++] = arr_len.counter;
				arr_len.counter = 0;
				printf("\nend of reading\n");
				break;
			}
			else {
				printf("\nreading error\n");
				exit(1);
			}
		}
		
		if ((sym < 91 && sym > 64) || (sym > 96 && sym < 123) || (sym > 47) && (sym < 58)) {
			s.arr[s.len++] = sym;
			arr_len.counter++;
		} else {
			if (s.len > 0) {
				if (str_arr.capacity - str_arr.len == 1) {
					str_arr.arr = (char**)realloc(str_arr.arr, (str_arr.capacity * 2) * sizeof(char*));
					nullCheck(str_arr.arr);
					str_arr.capacity *= 2;
				}

				str_arr.arr[str_arr.len++] = s.arr;
								
				printArr(str_arr.arr[(str_arr.len)-1], s.len);
				arr_len.arr[arr_len.len++] = arr_len.counter;
				arr_len.counter = 0;
		
				s.arr = (char*)malloc(sizeof(char));
				s.len = 0;
				s.capacity = 1;				
			}
			s.arr[s.len++] = sym;

			if (str_arr.capacity - str_arr.len == 1) {
				str_arr.arr = (char**)realloc(str_arr.arr, (str_arr.capacity * 2) * sizeof(char*));
				nullCheck(str_arr.arr);
				str_arr.capacity *= 2;
			}

			str_arr.arr[str_arr.len++] = s.arr;
			arr_len.arr[arr_len.len++] = 1;
			arr_len.counter = 0;
			printArr(s.arr, s.len);

			s.arr = (char*)malloc(sizeof(char));
			nullCheck(s.arr);
			s.len = 0;
			s.capacity = 1;
		} 
	}



	printf("\n\n");
	for (size_t i = 0; i < str_arr.len; i++) {
		printArr(str_arr.arr[i], arr_len.arr[i]);
		printf("\t %d\n", arr_len.arr[i]);
	}

	fclose(test);

	return 0;

}
