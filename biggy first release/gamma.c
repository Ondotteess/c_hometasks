#include <stdio.h>
#include <stdlib.h>
//#define DEBUG
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


void str_realloc(string* s) {
	s->arr = (char*)realloc(s->arr, sizeof(char) * s->capacity * 2);
	nullCheck(s->arr);
	s->capacity *= 2;
}

void str_arr_realloc(string_arr* s) {
	s->arr = (string*)realloc(s->arr, sizeof(string) * s->capacity * 2);
	nullCheck(s->arr);
	s->capacity *= 2;
}

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

	for (size_t i = 0; i < size; i++) {
		if (s.arr[i] == ',') {
			s.arr[i] = '.';
		}
	}

	far = atof(s.arr);

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
	itoa(f, second, 10);
	#ifdef DEBUG
	printf("\n-------\n");
	printf("%s %s", first, second);
	printf("\n-----\n");
	#endif // DEBUG

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
		str_realloc(&first);
	}

	for (size_t i = 0; i < strlen(s.arr); i++) {
		if (s.arr[i] >= '0' && s.arr[i] <= '9') {
			if (first.capacity - first.len == 1) {
				str_realloc(&first);
			}
			first.arr[i] = s.arr[i];
		}
		else {
			if (first.capacity - first.len == 1) {
				str_realloc(&first);
			}
			first.arr[i] = '\0';
			op = s.arr[i];
			n_s = i;
			break;
		}
	}

	if (second.capacity - second.len == 1) {
		str_realloc(&second);
	}
	for (size_t i = n_s+1; i < strlen(s.arr); i++) {
		if (s.arr[i] >= '0' && s.arr[i] <= '9') {
			if (second.capacity - second.len == 1) {
				str_realloc(&second);
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
			str_arr_realloc(&str_arr);
		}

		if (s.capacity - s.len == 1) {
			str_realloc(&s);
		}

		if (sym == EOF) {
			if (feof(test) != 0) {
				s.arr[s.len] = '\0';
				str_arr.arr[str_arr.len++].arr = s.arr;
				#ifdef DEBUG
				printf("%s", str_arr.arr[str_arr.len - 1].arr);
				printf("\nend of reading\n");
				#endif // DEBUG
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
					str_arr_realloc(&str_arr);
				}

				s.arr[s.len] = '\0';
				str_arr.arr[str_arr.len++].arr = s.arr;
				#ifdef DEBUG
				printf("%s", str_arr.arr[str_arr.len - 1].arr);
				#endif // DEBUG

				s.arr = (char*)malloc(sizeof(char));
				s.len = 0;
				s.capacity = 1;
			}

			s.arr[s.len++] = sym;
			s.arr[s.len] = '\0';


			if (str_arr.capacity - str_arr.len == 1) {
				str_arr_realloc(&str_arr);
			}
		
			str_arr.arr[str_arr.len++].arr = s.arr;
			#ifdef DEBUG
			printf("%s ", str_arr.arr[str_arr.len - 1].arr);
			#endif // DEBUG

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

	#ifdef DEBUG
	printf("\n\n");
	#endif // DEBUG



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
					str_realloc(&garbage);
				}

				garbage.arr[garbage.len++] = index_l;

				if (garbage.capacity - garbage.len <= 1) {
					str_arr_realloc(&garbage);
				}

				garbage.arr[garbage.len++] = index_r;


			}

			else if (str_arr.arr[i].arr[0] == ')' && flag_c == 0 && flag_l == 0 && flag_r == 1) {
				flag_l = 0;
				flag_c = 0;
				flag_r = 0;
				index_r = i;

				if (garbage.capacity - garbage.len <= 1) {
					str_realloc(&garbage);
				}

				garbage.arr[garbage.len++] = index_l;

				if (garbage.capacity - garbage.len <= 1) {
					str_realloc(&garbage);
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

	#ifdef DEBUG

	printf("\n\n");
	#endif // DEBUG

	//Far to cel
	for (size_t i = 0; i < str_arr.len; i++) {
	#ifdef DEBUG
		printf("str_log:\t %d", strlen(str_arr.arr[i].arr));
	#endif // DEBUG


		if (strlen(str_arr.arr[i].arr) > 3) {
			if (is_temp(str_arr.arr[i])) {
				str_arr.arr[i].arr = far_to_cel(str_arr.arr[i], strlen(str_arr.arr[i].arr));
			}
		}
	}


	FILE* file = fopen("output.txt", "w");
	char* str = NULL;

	string_arr out;
	out.capacity = 1;
	out.len = 0;
	out.arr = (string*)malloc(sizeof(string) * 2 * out.capacity);

	for (size_t i = 0; i < str_arr.len; i++) {
		if (i == 0 && str_arr.arr[i].arr[0] == ' ') {
			continue;
		} else if (i > 0) {
			if (str_arr.arr[i - 1].arr[0] == ' ' && str_arr.arr[i].arr[0] == ' ') {
				continue;
			}
			else if ((str_arr.arr[i - 1].arr[0] == '\n' && str_arr.arr[i].arr[0] == ' ')) {
				continue;
			}
		}
		if (out.capacity - out.len == 1) {
			str_arr_realloc(&out);
		}
		out.arr[out.len++].arr = str_arr.arr[i].arr;
		#ifdef DEBUG
		printf("%s", out.arr[out.len - 1].arr);
		#endif // DEBUG
	}
	
	// do some math
		for (size_t i = 0; i < (out.len); i++) {
			if (i < out.len - 4) {
				if (is_num(out.arr[i]) && is_oper(out.arr[i + 2].arr[0]) && is_num(out.arr[i + 4])) {
					out.arr[i].arr = math_2(out.arr[i], out.arr[i + 2].arr[0], out.arr[i + 4]);
					out.arr[i + 2].arr = " ";
					out.arr[i + 4].arr = " ";

					continue;
				}
			}
			if (i < out.len - 3) {
				if (is_num(out.arr[i]) && is_oper(out.arr[i + 2].arr[0]) && is_num(out.arr[i + 3])) {
					out.arr[i].arr = math_2(out.arr[i], out.arr[i + 2].arr[0], out.arr[i + 3]);
					out.arr[i + 2].arr = " ";
					out.arr[i + 3].arr = " ";
					continue;
				}
				if (is_num(out.arr[i]) && is_oper(out.arr[i + 1].arr[0]) && is_num(out.arr[i + 3])) {
					out.arr[i].arr = math_2(out.arr[i], out.arr[i + 1].arr[0], out.arr[i + 3]);
					out.arr[i + 1].arr = " ";
					out.arr[i + 3].arr = " ";
					continue;
				}
			}
			if (is_math(out.arr[i]) && out.arr[i].arr[0] != '\0') {
				out.arr[i].arr = math_1(out.arr[i]);
				continue;
			}
		}

	//fprintf
	for (size_t i = 0; i < out.len; i++) {
		if (i > 0) {
			if (out.arr[i-1].arr[0] == ' ' && out.arr[i].arr[0] == ' ') {
				continue;
			}
		} 
		fprintf(file, "%s", out.arr[i].arr);
		#ifdef DEBUG
		printf("%s %d\n", out.arr[i].arr, i);
		#endif // DEBUG
	}

	return 0;
}

