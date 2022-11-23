#include <stdio.h>
#include <stdlib.h>
#define PRECISION 10
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

_Bool is_num(char c) {
	if (c >= '0' && c <= '9') { //? ''
		return 1;
	}
	else {
		return 0;
	}
}

_Bool is_word(char* arr, size_t size) {
	if (size > 1) {
		if ((arr[1] >= 'a' && arr[1] <= 'z') || (arr[1] >= 'A' && arr[1] <= 'Z') || arr[0] == '+' || arr[0] == '-') { 
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
	}
	return 1;
}

_Bool is_temp(char* arr) {
	if ((arr[0] == '+' || arr[0] == '-') && (arr[strlen(arr) - 1] == 'F') && (arr[strlen(arr) - 2] == 't') && is_num(arr[strlen(arr) - 3])) {
		if (arr[strlen(arr) - 4] != ',') {
			for (size_t i = 1; i < strlen(arr) - 3; i++) {
				if (is_num(arr[i])) {
					continue;
				}
				else {
					return 0;
				}
			}
		} else {
			for (size_t i = 1; i < strlen(arr) - 5; i++) {
				if (is_num(arr[i])) {
					continue;
				}
				else {
					return 0;
				}
			}
		}
		return 1;
	}
	else {
		return 0;
	}
}


//? use string type
char* far_to_cel(char* arr, size_t size) {
	float far;
	char* sub = (char*)malloc((size) * sizeof(char));
	
	for (size_t i = 0; i < size; i++) {
		sub[i] = arr[i];
		if (arr[i] == ',') {
			sub[i] = '.';
		}
	}

	far = atof(sub);

	float cel = (far - 32) * 5 / 9;;

	char sgn;

	if (cel > 0) {
		sgn = '+';
	}
	else {
		sgn = '-';
	}

	int w = abs((int)cel);
	int f = abs((int)(cel * PRECISION) % PRECISION);


	char* first = (char*)malloc(10 * sizeof(char));
	char* second = (char*)malloc(10 * sizeof(char));

	itoa(w, first, 10);
	printf("\n-------\n");
	printf("%s", first);
	printf("\n-----\n");
	itoa(f, second, 10);

	char* result = (char*)malloc(23 * sizeof(char));

	size_t n_s = 0;
	result[n_s++] = sgn;

	for (size_t i = 0; i < (strlen(first)); i++) {
		result[n_s++] = first[i];
	}

	size_t o_s = n_s + 1;
	result[n_s++] = ',';


	for (size_t i = o_s; i < o_s + strlen(second); i++) {
		result[n_s++] = first[i - o_s];

	}

	result[n_s++] = 't';
	result[n_s++] = 'C';
	result[n_s] = '\0';

	//printf("----- "); //? ifdef
	//printf("%s", result);
	//printf("-----\n");

	return result;
}

_Bool is_oper(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/') {
		return 1;
	}
	else {
		return 0;
	}
}

char* algebra(char* first, char op, char* second) {
	int result, f, s;
	f = atoi(first);
	s = atoi(second);

	if (s == 0 && op == '/') {
		return "error";
	}

	switch (op) {
	case '+': result = f + s;
		break;
	case '-': result = f - s;
		break;
	case '*': result = f * s;
		break;
	case '/': result = f / s;
	}

	char out[20];
	itoa(result, out, 10);

	return out;
}


int main() {
	FILE* test = fopen("test.txt", "r");
											 //? combine dym_arr & string_arr into array of string	

	struct string_arr str_arr;
	str_arr.arr = NULL;
	str_arr.len = 0;
	str_arr.capacity = 1;

	struct string s;
	s.arr = NULL;
	s.len = 0;
	s.capacity = 1;

	char sym;
	while (1) {

		sym = fgetc(test);

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
				s.arr[s.len] = '\0';
				str_arr.arr[str_arr.len++] = s.arr;
				printf("%s", str_arr.arr[str_arr.len-1]);
				printf("\nend of reading\n");
				break;
			}
			else {
				printf("\nreading error\n");
				exit(1);
			}
		}

		else if ((sym >= 'a' && sym <= 'z') || (sym >= 'A' && sym <= 'Z') || (sym >= '0' && sym <= '9') || (sym == '+') || sym == '-' || sym == ',') {
			s.arr[s.len++] = sym;
		}
		else {
			if (s.len > 0) {
				if (str_arr.capacity - str_arr.len == 1) {
					str_arr.arr = (char**)realloc(str_arr.arr, (str_arr.capacity * 2) * sizeof(char*));
					nullCheck(str_arr.arr);
					str_arr.capacity *= 2;
				}

				s.arr[s.len] = '\0';
				str_arr.arr[str_arr.len++] = s.arr;

				printf("%s", str_arr.arr[str_arr.len - 1]);

				s.arr = (char*)malloc(sizeof(char));
				s.len = 0;
				s.capacity = 1;
			}

			s.arr[s.len++] = sym;
			s.arr[s.len] = '\0';


			if (str_arr.capacity - str_arr.len == 1) {
				str_arr.arr = (char**)realloc(str_arr.arr, (str_arr.capacity * 2) * sizeof(char*));
				nullCheck(str_arr.arr);
				str_arr.capacity *= 2;
			}

		
			str_arr.arr[str_arr.len++] = s.arr;
			printf("%s ", str_arr.arr[str_arr.len-1]);

			s.arr = (char*)malloc(sizeof(char));
			nullCheck(s.arr);
			s.len = 0;
			s.capacity = 1;
		}
	}


	fclose(test);

	//Palindrom
	for (size_t i = 0; i < str_arr.len; i++) {
		if ( is_word(str_arr.arr[i], strlen(str_arr.arr[i])) && is_palindrom(str_arr.arr[i], strlen(str_arr.arr[i]))) {
			str_arr.arr[i] = "PALINDROM";
		}

	}

	printf("\n\n");


	struct string garbage;
	garbage.arr = NULL;
	garbage.len = 0;
	garbage.capacity = 1;


	size_t index_l;
	size_t index_r;

	_Bool flag_l = 0;
	_Bool flag_r = 0;
	_Bool flag_c = 0;


	//find (..)
	for (size_t i = 0; i < str_arr.len; i++) {
		if (str_arr.arr[i][0] == '(' && flag_l == 0 && flag_c == 0 && flag_r == 0) {
			flag_l = 1;
			index_l = i;

		}
		else if (flag_l == 1 && str_arr.arr[i][0] != ' ' && flag_c == 0 && flag_r == 0) {
			flag_l = 0;
			flag_c = 1;

		}
		else if (str_arr.arr[i][0] == ' ' && flag_c == 1 && flag_l == 0 && flag_r == 0) {
			flag_c = 0;
			flag_r = 1;

		}
		else if (str_arr.arr[i][0] != ' ' && str_arr.arr[i][0] != ')' && flag_c == 0 && flag_l == 0 && flag_r == 1) {
			flag_r = 0;
			index_l = 0;
			index_r = 0;

		}
		else if (str_arr.arr[i][0] == ')' && flag_c == 1 && flag_l == 0 && flag_r == 0) {
			index_r = i;
			flag_c = 0;
			flag_l == 0;
			flag_r == 0;

			if (garbage.capacity - garbage.len <= 1) {
				garbage.arr = (char*)realloc(garbage.arr, (garbage.capacity * 2) * sizeof(char));
				garbage.capacity *= 2;
				nullCheck(garbage.arr);
			}

			garbage.arr[garbage.len++] = index_l;

			if (garbage.capacity - garbage.len <= 1) {
				garbage.arr = (char*)realloc(garbage.arr, (garbage.capacity * 2) * sizeof(char));
				garbage.capacity *= 2;
				nullCheck(garbage.arr);
			}

			garbage.arr[garbage.len++] = index_r;


		}

		else if (str_arr.arr[i][0] == ')' && flag_c == 0 && flag_l == 0 && flag_r == 1) {
			flag_l = 0;
			flag_c = 0;
			flag_r = 0;
			index_r = i;

			if (garbage.capacity - garbage.len <= 1) {
				garbage.arr = (char*)realloc(garbage.arr, (garbage.capacity * 2) * sizeof(char));
				garbage.capacity *= 2;
				nullCheck(garbage.arr);
			}

			garbage.arr[garbage.len++] = index_l;

			if (garbage.capacity - garbage.len <= 1) {
				garbage.arr = (char*)realloc(garbage.arr, (garbage.capacity * 2) * sizeof(char));
				garbage.capacity *= 2;
				nullCheck(garbage.arr);
			}

			garbage.arr[garbage.len++] = index_r;


		}
	}

	printf("\n\n");

	//Far to cel
	for (size_t i = 0; i < str_arr.len; i++) {
		printf("str_log:\t %d", strlen(str_arr.arr[i]));
		if (is_temp(str_arr.arr[i])) {
			str_arr.arr[i] = far_to_cel(str_arr.arr[i], strlen(str_arr.arr[i]));
			
		}
	}

	//Do some math
	if (str_arr.len > 4) {
		for (size_t i = 0; i < str_arr.len - 4; i++) {
			if (is_num(str_arr.arr[i][0]) && is_oper(str_arr.arr[i + 2][0]) && is_num(str_arr.arr[i + 4][0])) {
				if (str_arr.arr[i + 2][0] == '/' && str_arr.arr[i + 4][0] == '0') {
					str_arr.arr[i][0] = ' ';
					str_arr.arr[i + 4][0] = ' ';
					str_arr.arr[i + 2] = "ERROR";
					continue;
				}

				str_arr.arr[i + 2] = algebra(str_arr.arr[i], str_arr.arr[i + 2][0], str_arr.arr[i + 4]);
				//arr_len.arr[i + 2] = strlen(str_arr.arr[i + 2]);
				str_arr.arr[i][0] = ' ';
				str_arr.arr[i + 4][0] = ' ';
			}
		}
	}

	//Remove double backspace
	for (size_t i = 0; i < garbage.len; i++) {
		printf("%d ", garbage.arr[i]);
		str_arr.arr[garbage.arr[i]][0] = ' ';
	}


	FILE* file = fopen("output.txt", "w");
	char* str = NULL;

	for (size_t i = 0; i < (str_arr.len); i++) {
		if (i == 0 && str_arr.arr[i][0] == ' ') {
			continue;
		}


		if (i > 0) {
			if (str_arr.arr[i - 1][0] == ' ' && str_arr.arr[i][0] == ' ') {
				continue;
			}
			else if ((str_arr.arr[i - 1][0] == '\n' && str_arr.arr[i][0] == ' ')) {
				continue;
			}
		}

		for (size_t j = 0; j < strlen(str_arr.arr[i]); j++) {
			fputc(str_arr.arr[i][j], file);
		}

	}
	printf("\n------\n");

	for (size_t i = 0; i < str_arr.len; i++) {
		printf("%s", str_arr.arr[i]);
	}


	return 0;
}

