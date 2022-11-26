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


typedef struct {
	char* arr;
	size_t len;
	size_t capacity;
} string;


typedef struct {
	string* arr;
	size_t len;
	size_t capacity;
} string_arr;


_Bool is_num(string s) {
	for (size_t i = 0; i < strlen(s.arr); i++) {
		if (s.arr[i] >= '0' && s.arr[i] <= '9') {
			continue;
		} else {
			return 0;
		}
	}
	return 1;
}

_Bool is_word(string s, size_t size) {
	if (size > 1) {
		if ((s.arr[1] >= 'a' && s.arr[1] <= 'z') || (s.arr[1] >= 'A' && s.arr[1] <= 'Z') || s.arr[0] == '+' || s.arr[0] == '-') { 
			return 1;
		}
	}
	else {
		return 0;
	}
}

_Bool is_palindrom(string s, size_t size) {
	for (size_t i = 0; i < (size / 2); i++) {
		if (s.arr[i] != s.arr[size - 1 - i]) {
			return 0;
		}
	}
	return 1;
}

_Bool is_temp(string s) {
	if ((s.arr[0] == '+' || s.arr[0] == '-') && (s.arr[strlen(s.arr) - 1] == 'F') && \
		(s.arr[strlen(s.arr) - 2] == 't') && (s.arr[strlen(s.arr) - 3] >= '0' && (s.arr[strlen(s.arr)-3] <= '9'))) {
		if (s.arr[strlen(s.arr) - 4] != ',') {
			for (size_t i = 1; i < strlen(s.arr) - 3; i++) {
				if (s.arr[i] >= '0' && s.arr[i] <= '9') {
					continue;
				}
				else {
					return 0;
				}
			}
		} else {
			for (size_t i = 1; i < strlen(s.arr) - 5; i++) {
				if (s.arr[i] >= '0' && s.arr[i] <= '9') {
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
char** far_to_cel(string s, size_t size) {
	float far;
	char* sub = (char*)malloc((size) * sizeof(char));
	
	for (size_t i = 0; i < size; i++) {
		sub[i] = s.arr[i];
		if (s.arr[i] == ',') {
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

	s.arr = result;

	return s.arr;
}

_Bool is_oper(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/') {
		return 1;
	}
	else {
		return 0;
	}
}

_Bool is_math(string s) {
	_Bool flag = 0;
	if (strlen(s.arr) > 2) {
		for (size_t i = 0; i < strlen(s.arr); i++) {
			if (s.arr[i] >= '0' && s.arr[i] <= '9' && flag == 0) {
				return 1;
			}
			else if (s.arr[i] == '+' || s.arr[i] == '-') {
				flag = 1;
				continue;
			}
			else if (s.arr[i] >= '0' && s.arr[i] <= '9' && flag == 1) {
				continue;
			}
			else {
				return 0;
			}
		}
		return 1;
	} else {
		return 0;
	}
}

char first_el(string s) {
	return s.arr[0];
}

char** math_1(string s) {
	char op = '+';
	string first;
	string second;
	size_t n_s = 0;
	int result, fir, sec;

	first.capacity = 1;
	first.len = 0;
	first.arr = NULL;

	second.capacity = 1;
	second.len = 0;
	second.arr = NULL;

	if (first.capacity - first.len == 1) {
		first.capacity *= 2;
		first.arr = (char*)realloc(first.arr, sizeof(char) * first.capacity);
	}

	for (size_t i = 0; i < strlen(s.arr); i++) {
		if (s.arr[i] >= '0' && s.arr[i] <= '9') {
			if (first.capacity - first.len == 1) {
				first.capacity *= 2;
				first.arr = (char*)realloc(first.arr, sizeof(char) * first.capacity);
			}
			first.arr[i] = s.arr[i];
		}
		else {
			if (first.capacity - first.len == 1) {
				first.capacity *= 2;
				first.arr = (char*)realloc(first.arr, sizeof(char) * first.capacity);
			}
			first.arr[i] = '\0';
			op = s.arr[i];
			n_s = i;
			break;
		}
	}

	if (second.capacity - second.len == 1) {
		second.capacity *= 2;
		second.arr = (char*)realloc(second.arr, sizeof(char) * second.capacity);
	}
	for (size_t i = n_s+1; i < strlen(s.arr); i++) {
		if (s.arr[i] >= '0' && s.arr[i] <= '9') {
			if (second.capacity - second.len == 1) {
				second.capacity *= 2;
				second.arr = (char*)realloc(second.arr, sizeof(char) * second.capacity);
			}
			second.arr[i-n_s-1] = s.arr[i];
		} else {
			second.arr[i - n_s-1] = '\0';
		}
	}
	

	fir = atoi(first.arr);
	sec = atoi(second.arr);

	if (op == '+') {
		result = fir + sec;
	} else {
		result = fir - sec;
	}

	itoa(result, first.arr, 10);

	return first.arr;
}

char* math_2(string s1, char op, string s2) {
	int first, second, result;
	first = atoi(s1.arr);
	second = atoi(s2.arr);
	if (op == '*') {
		result = first * second;
	} else if (op == '/') {
		result = first / second;
	} else if (op == '+') {
		result = first + second;
	} else if (op == '-') {
		result = first - second;
	}

																								
	char out[30];																				
	itoa(result, s1.arr, 10);																		
	printf("^^^^^^^^%s^^^^^^^^^", s1.arr);
	return s1.arr;
}																								
																								

int main() {
	FILE* test = fopen("test.txt", "r");
										
	string s;
	s.arr = (char*)malloc(sizeof(char));
	s.len = 0;
	s.capacity = 1;

	string garbage;

	string_arr str_arr;
	str_arr.capacity = 1;
	str_arr.len = 0;
	str_arr.arr = (string*)malloc(sizeof(string)*2);

	char sym;

	while (1) {

		sym = fgetc(test);

		if (str_arr.capacity - str_arr.len == 1) {
			str_arr.arr = (string*)realloc(str_arr.arr, (str_arr.capacity * 2) * sizeof(string));
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
				str_arr.arr[str_arr.len++].arr = s.arr;
				printf("%s", str_arr.arr[str_arr.len-1].arr);
				printf("\nend of reading\n");
				break;
			}
			else {
				printf("\nreading error\n");
				exit(1);
			}
		}

		else if ((sym >= 'a' && sym <= 'z') || (sym >= 'A' && sym <= 'Z') || (sym >= '0' && sym <= '9') || sym == ',' || sym == '+' || sym == '-') {
			s.arr[s.len++] = sym;
			continue;
		} else {
			if (s.len > 0) {
				if (str_arr.capacity - str_arr.len == 1) {
					str_arr.arr = (string*)realloc(str_arr.arr, (str_arr.capacity * 2) * sizeof(string));
					nullCheck(str_arr.arr);
					str_arr.capacity *= 2;
				}

				s.arr[s.len] = '\0';
				str_arr.arr[str_arr.len++].arr = s.arr;

				printf("%s", str_arr.arr[str_arr.len - 1].arr);

				s.arr = (char*)malloc(sizeof(char));
				s.len = 0;
				s.capacity = 1;
			}

			s.arr[s.len++] = sym;
			s.arr[s.len] = '\0';


			if (str_arr.capacity - str_arr.len == 1) {
				str_arr.arr = (string*)realloc(str_arr.arr, (str_arr.capacity * 2) * sizeof(string));
				nullCheck(str_arr.arr);
				str_arr.capacity *= 2;
			}

		
			str_arr.arr[str_arr.len++].arr = s.arr;
			printf("%s ", str_arr.arr[str_arr.len-1].arr);

			s.arr = (char*)malloc(sizeof(char));
			nullCheck(s.arr);
			s.len = 0;
			s.capacity = 1;
		}
	}


	fclose(test);

	//Palindrom
	for (size_t i = 0; i < str_arr.len; i++) {
		if ( is_word(str_arr.arr[i], strlen(str_arr.arr[i].arr)) && is_palindrom(str_arr.arr[i], strlen(str_arr.arr[i].arr))) {
			s.arr = "PALINDRON";
			str_arr.arr[i] = s;

		}
		s.arr = NULL;
	}

	printf("\n\n");


	size_t index_l;
	size_t index_r;

	_Bool flag_l = 0;
	_Bool flag_r = 0;
	_Bool flag_c = 0;


	//find (..)

	while (1) {
		garbage.arr = NULL;
		garbage.len = 0;
		garbage.capacity = 1;

		for (size_t i = 0; i < str_arr.len; i++) {
			if (str_arr.arr[i].arr[0] == '(' && flag_l == 0 && flag_c == 0 && flag_r == 0) {
				flag_l = 1;
				index_l = i;

			}
			else if (flag_l == 1 && str_arr.arr[i].arr[0] != ' ' && str_arr.arr[i].arr[0] != '(' && flag_c == 0 && flag_r == 0) {
				flag_l = 0;
				flag_c = 1;

			}
			else if (str_arr.arr[i].arr[0] == ' ' && flag_c == 1 && flag_l == 0 && flag_r == 0) {
				flag_c = 0;
				flag_r = 1;

			}
			else if (str_arr.arr[i].arr[0] != ' ' && str_arr.arr[i].arr[0] != ')' && flag_c == 0 && flag_l == 0 && flag_r == 1) {
				flag_r = 0;
				index_l = 0;
				index_r = 0;

			}
			else if (str_arr.arr[i].arr[0] == ')' && flag_c == 1 && flag_l == 0 && flag_r == 0) {
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

			else if (str_arr.arr[i].arr[0] == ')' && flag_c == 0 && flag_l == 0 && flag_r == 1) {
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

		for (size_t i = 0; i < garbage.len; i++) {
			str_arr.arr[garbage.arr[i]].arr[0] = ' ';
		}

		if (garbage.len == 0) {
			break;
		}
	}


	printf("\n\n");

	//Far to cel
	for (size_t i = 0; i < str_arr.len; i++) {
		printf("str_log:\t %d", strlen(str_arr.arr[i].arr));
		if (strlen(str_arr.arr[i].arr) > 3) {
			if (is_temp(str_arr.arr[i])) {
				str_arr.arr[i].arr = far_to_cel(str_arr.arr[i], strlen(str_arr.arr[i].arr));

			}
		}
	}

	printf("\n------\n");

	FILE* file = fopen("output.txt", "w");
	char* str = NULL;


	//remove double backspace

	
	// do some math
	for (size_t i = 0; i < (str_arr.len); i++) {
		if (i < str_arr.len - 4) {
			if (is_num(str_arr.arr[i]) && is_oper(str_arr.arr[i + 2].arr[0]) && is_num(str_arr.arr[i + 4])) {
				str_arr.arr[i].arr = math_2(str_arr.arr[i], str_arr.arr[i + 2].arr[0], str_arr.arr[i + 4]);
				str_arr.arr[i + 2].arr = " ";
				str_arr.arr[i + 4].arr = " ";
				continue;
			}
		}
		if (i < str_arr.len - 3) {
			if (is_num(str_arr.arr[i]) && is_oper(str_arr.arr[i + 2].arr[0]) && is_num(str_arr.arr[i + 3])) {
				str_arr.arr[i].arr = math_2(str_arr.arr[i], str_arr.arr[i + 2].arr[0], str_arr.arr[i + 3]);
				str_arr.arr[i + 2].arr = " ";
				str_arr.arr[i + 3].arr = " ";
				continue;
			}
			if (is_num(str_arr.arr[i]) && is_oper(str_arr.arr[i + 1].arr[0]) && is_num(str_arr.arr[i + 3])) {
				str_arr.arr[i].arr = math_2(str_arr.arr[i], str_arr.arr[i + 1].arr[0], str_arr.arr[i + 3]);
				str_arr.arr[i + 1].arr = " ";
				str_arr.arr[i + 3].arr = " ";
				continue;
			}
		}
			

		if (is_math(str_arr.arr[i]) && str_arr.arr[i].arr[0] != '\0') {
			str_arr.arr[i].arr = math_1(str_arr.arr[i]);
			continue;
		}
	}


	//remove DB spaces and printf
	for (size_t i = 0; i < str_arr.len; i++) {
		if (i == 0 && str_arr.arr[i].arr[0] == ' ') {
			continue;
		}
		if (i > 0) {
			if (str_arr.arr[i - 1].arr[0] == ' ' && str_arr.arr[i].arr[0] == ' ') {
				continue;
			}
			else if ((str_arr.arr[i - 1].arr[0] == '\n' && str_arr.arr[i].arr[0] == ' ')) {
				continue;
			}
		}

		fprintf(file, "%s", str_arr.arr[i].arr);
		printf("%s %d\n", str_arr.arr[i].arr, i);
	}

	return 0;
}

