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

_Bool is_word(char* arr, size_t size) {
	if (size > 1) {
		if ((arr[1] > 64 && arr[1] < 91) || (arr[1] > 96 && arr[1] < 123) || arr[0] == 43) {
			return 1;
		}
		
	}
	else {
		return 0;
	}
}

_Bool is_palindrom(char* arr, size_t size) {
	for (size_t i = 0; i < (size / 2); i++) {
		if (arr[i] != arr[size - 1 - i]) {
			return 0;
		}
		return 1;
	}
}

_Bool is_temp(char* arr, size_t size) {
	if ((arr[0] == '+' || arr[0] == '-') && (arr[size-1] == 'F') && (arr[size-2] == 't')) {
		return 1;
	}
	else {
		return 0;
	}
}

char* far_to_cel(char* arr, size_t size, int* retPlaceForSize) {
	float far;
	char* sub = (char*)malloc((size -3) * sizeof(char));
	for (size_t i = 0; i < size - 3; i++) {
		sub[i] = arr[i + 1];
		if (arr[i + 1] == ',') {
			sub[i] = '.';
		}

	}
	far = atol(sub);
	
	float cel;

	cel = (far - 32) * 5 / 9;
	
	gcvt(cel, 10, sub);
	char sgn;
	char* _sub = (char*)malloc((size-2) * sizeof(char));
	if (cel >= 0) {
		sgn = '+';
	}
	if (sgn == '+') {
		_sub[0] = sgn;
		for (size_t i = 1; i < size - 3; i++) {
			_sub[i] = sub[i - 1];
			if (sub[i - 1] == '.') {
				_sub[i] = ',';
			}
		}
	}
	else {
		for (size_t i = 0; i < size; i++) {
			_sub[i] = sub[i];
			if ((sub[i] == '.') && (sub[i+1] > 48 && sub[i+1] < 58)) {
				_sub[size - 4] = 't';
				_sub[size - 3] = 'C';
				retPlaceForSize--;
				return _sub;
			}
		}
	}
	retPlaceForSize--;
	_sub[size-3] = 't';
	_sub[size-2] = 'C';
	
	//printArr(_sub, size-1);
	return _sub;
}

_Bool not_in_garbage(size_t* arr, size_t len, size_t el) {
	for (size_t i = 0; i < len; i++) {
		
	}
	return 1;
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
		
		if ((sym < 91 && sym > 64) || (sym > 96 && sym < 123) || (sym > 47) && (sym < 58) || (sym == '+') || sym == '-' || sym == ',') {
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
	
	//printf("\n\n");
	//for (size_t i = 0; i < str_arr.len; i++) {
	//	printArr(str_arr.arr[i], arr_len.arr[i]);
	//	printf("\t %d\n", arr_len.arr[i]);
	//}
	
	fclose(test);

	//for (size_t i = 0; i < str_arr.len; i++) {
	//	printArr(str_arr.arr[i], arr_len.arr[i]);
	//	if (is_word(str_arr.arr[i], arr_len.arr[i]) && is_palindrom(str_arr.arr[i], arr_len.arr[i])) {
	//		printf("*");
	//		str_arr.arr[i] = "PALINDROM";
	//		arr_len.arr[i] = 9;
	//	}
	//}

	printf("\n\n");

	//for (size_t i = 0; i < str_arr.len; i++) {
	//	if (is_temp(str_arr.arr[i], arr_len.arr[i])) {
	//		
	//		str_arr.arr[i] = far_to_cel(str_arr.arr[i], arr_len.arr[i], &arr_len.arr[i]);
	//		
	//		printArr(str_arr.arr[i], arr_len.arr[i]);
	//		printf(" ");
	//	}
	//}

	struct string garbage;
	garbage.arr = NULL;
	garbage.len = 0;
	garbage.capacity = 1;

	for (size_t i = 1; i < str_arr.len + 1; i++) {
		if ((str_arr.arr[i - 1][0] == ' ' && str_arr.arr[i][0] == ' ')) {
			if (garbage.capacity - garbage.len <= 1) {
				garbage.arr = (size_t*)realloc(garbage.arr, (garbage.capacity * 2) * sizeof(size_t));
				nullCheck(garbage.arr);
				garbage.capacity *= 2;
			}
			garbage.arr[garbage.len++] = i - 1;
		}

		else if ((str_arr.arr[i - 1][0] == '\n' && str_arr.arr[i][0] == ' ')) {
			if (garbage.capacity - garbage.len <= 1) {
				garbage.arr = (size_t*)realloc(garbage.arr, (garbage.capacity * 2) * sizeof(size_t));
				nullCheck(garbage.arr);
				garbage.capacity *= 2;
			}
			garbage.arr[garbage.len++] = i - 1;
		}
		else {
			printArr(str_arr.arr[i - 1], arr_len.arr[i - 1]);
		}
	}

	size_t index_l;
	size_t index_r;
	size_t j = garbage.len;

	_Bool flag_l = 0;
	_Bool flag_r = 0;
	_Bool flag_c = 0;

	for (size_t i = 0; i < str_arr.len; i++) {
		if (str_arr.arr[i][0] == '(' && flag_l == 0 && flag_c == 0 && flag_r == 0) {
			flag_l = 1;
			index_l = i;
			
		} else if (flag_l == 1 && str_arr.arr[i] != ' ' && flag_c == 0 && flag_r == 0) {
			flag_l = 0;
			flag_c = 1;
		
	
		} else if (str_arr.arr[i][0] == ' ' && flag_c == 1 && flag_l == 0 && flag_r == 0) {
			flag_c = 0;
			flag_r = 1;
	
		}
		else if (str_arr.arr[i][0] == ')' && flag_c == 1 && flag_l == 0 && flag_r == 0){
			flag_l = 0;
			flag_c = 0;
			flag_r = 0;
			index_r = i;
	
			if (garbage.capacity - garbage.len <= 1) {
				garbage.arr = (size_t*)realloc(garbage.arr, (garbage.capacity * 2) * sizeof(size_t));
				garbage.capacity *= 2;
				nullCheck(garbage.arr);
			}
			garbage.arr[j++] = index_l;
			garbage.len++;
			if (garbage.capacity - garbage.len <= 1) {
				garbage.arr = (size_t*)realloc(garbage.arr, (garbage.capacity * 2) * sizeof(size_t));
				garbage.capacity *= 2;
				nullCheck(garbage.arr);
			}
			garbage.arr[j++] = index_r;
			garbage.len++;
		}
		else if (str_arr.arr[i][0] != ' ' && str_arr.arr[i][0] != ')' && flag_r == 1 && flag_c == 0 && flag_l == 0) {
			flag_l = 0;
			flag_c = 0;
			flag_r = 0;
			
		} else if (str_arr.arr[i][0] == ')' && flag_r == 1 && flag_l == 0 && flag_c == 0) {
			flag_l = 0;
			flag_c = 0;
			flag_r = 0;
			index_r = i;
			
			if (garbage.capacity - garbage.len <= 1) {
				garbage.arr = (size_t*)realloc(garbage.arr, (garbage.capacity * 2) * sizeof(size_t));
				nullCheck(garbage.arr);
				garbage.capacity *= 2;
			}
			garbage.arr[j++] = index_l;
			garbage.len++;
			if (garbage.capacity - garbage.len <= 1) {
				garbage.arr = (size_t*)realloc(garbage.arr, (garbage.capacity * 2) * sizeof(size_t));
				garbage.capacity *= 2;
				nullCheck(garbage.arr);
			}
			garbage.arr[j++] = index_r;
			garbage.len++;
		}
		
	}

	for (size_t i = 0; i < garbage.len; i++) {
		printf("\n%d", garbage.arr[i]);
	}

	for (size_t i = 0; i < str_arr.len; i++) {
		if (not_in_garbage(garbage.arr, garbage.len, arr_len.arr[i])) {
			printArr(str_arr.arr[i], arr_len.arr[i]);
		}
	}

	return 0;

}
