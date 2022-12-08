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

void str_init(string* s) {
	s->arr = (char*)malloc(sizeof(char));
	nullCheck(s->arr);
	s->len = 0;
	s->capacity = 1;
}

void str_realloc(string* s) {
	if (s->capacity - s->len == 1) {
		s->arr = (char*)realloc(s->arr, sizeof(char) * s->capacity * 2);
		nullCheck(s->arr);
		s->capacity *= 2;
	}
}

void str_arr_realloc(string_arr* s) {
	if (s->capacity - s->len == 1) {
		s->arr = (string*)realloc(s->arr, sizeof(string) * s->capacity * 2);
		nullCheck(s->arr);
		s->capacity *= 2;
	}
}

_Bool is_num(string s) {
	for (size_t i = 0; i < strlen(s.arr); i++) {
		if (!(s.arr[i] >= '0' && s.arr[i] <= '9')) {
			return 0;
		}
	}
	return 1;
}

_Bool is_word(string s, size_t len) {
	if (len > 1) {
		if ((s.arr[1] >= 'a' && s.arr[1] <= 'z') || (s.arr[1] >= 'A' && s.arr[1] <= 'Z') || s.arr[0] == '+' || s.arr[0] == '-') {
			return 1;
		}
	}
	else {
		return 0;
	}
}

_Bool is_lit(char c) {
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

_Bool is_palindrom(string s, size_t size) {
	for (size_t i = 0; i < (size / 2); i++) {
		if (s.arr[i] != s.arr[size - 1 - i] || (!(is_lit(s.arr[i])))) {
			return 0;
		}
	}
	return 1;
}

_Bool is_temp(string s) {
	size_t len = strlen(s.arr);
	if ((s.arr[0] == '+' || s.arr[0] == '-') && (s.arr[len - 1] == 'F') && \
		(s.arr[len - 2] == 't')) {
		for (size_t i = 1; i < len - 2; i++) {
			if (!(s.arr[i] >= '0' && s.arr[i] <= '9')) {
				return 0;
			}
		}
		return 1;
	}
	else {
		return 0;
	}
}

char* far_to_cel(string s, size_t size) {
	float far;
	string first;
	string second;
	string result;

	str_init(&first);
	str_init(&second);
	str_init(&result);

	for (size_t i = 0; i < size; i++) {
		if (s.arr[i] == ',') {
			s.arr[i] = '.';
		}
	}

	far = atof(s.arr);

	float cel = (far - 32) * 0.555;

	char sgn = (cel > 0) ? '+' : '-';

	int w = abs((int)cel);
	int f = abs((int)(cel * PRECISION) % PRECISION);

	sprintf(first.arr, "%d", w);
	sprintf(second.arr, "%d", f);

#ifdef DEBUG
	printf("\n-------\n");
	printf("%s %s", first.arr, second.arr);
	printf("\n-----\n");
#endif // DEBUG

	size_t len_fir = strlen(first.arr);
	result.arr[result.len++] = sgn;
	for (size_t i = 0; i < len_fir; i++) {
		result.arr[result.len++] = first.arr[i];
	}
	result.arr[result.len++] = ',';
	result.arr[result.len++] = second.arr[0];

	result.arr[result.len++] = 't';
	result.arr[result.len++] = 'C';
	result.arr[result.len] = '\0';

	return result.arr;
}

_Bool is_oper(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}


void remove_el(string_arr* ptr, size_t idx) {
	for (size_t i = idx + 1; i < ptr->len; i++) {
		ptr->arr[i - 1] = ptr->arr[i];
	}
	ptr->len -= 1;
}

void remove_all_space(string_arr* ptr) {
	while (ptr->arr[0].arr[0] == ' ') {
		remove_el(&ptr->arr, 0);
	}
	for (size_t i = 0; i < ptr->len; i++) {
		if (i == 0 && ptr->arr[i].arr[0] == ' ' && ptr->arr[i].arr[0]) {
			remove_el(&ptr->arr, i);
		}
		if (i > 1) {
			while (ptr->arr[i - 2].arr[0] == '\n' && ptr->arr[i - 1].arr[0] == '\n' && ptr->arr[i].arr[0] == '\n') {
				remove_el(&ptr->arr, i);
			}
		}
		if (i > 0) {
			while (ptr->arr[i - 1].arr[0] == '\n' && ptr->arr[i].arr[0] == ' ') {
				remove_el(&ptr->arr, i);
			}
			while (ptr->arr[i - 1].arr[0] == ' ' && ptr->arr[i].arr[0] == ' ') {
				remove_el(&ptr->arr, i);
			}
		}
	}
}

void remove_space(string_arr* ptr) {
	for (size_t i = 0; i < ptr->len; i++) {
		if (ptr->arr[i].arr[0] == ' ') {
			remove_el(&ptr->arr, i);
		}
	}
}

size_t count_of_op(string_arr* ptr) {
	size_t count = 0;
	for (size_t i = 0; i < ptr->len; i++) {
		if ((ptr->arr[i].arr[0] == '+' || ptr->arr[i].arr[0] == '-' || ptr->arr[i].arr[0] == '*' || ptr->arr[i].arr[0] == '/') && (strlen(ptr->arr[i].arr) == 1)) {
			count++;
		}
	}
	return count;
}

char* math(string* s1, char op, string* s2) {
	int first, second, result;
	first = atoi(s1->arr);
	second = atoi(s2->arr);
	if (op == '/' && second == 0) {
		return "ERROR";
	}
	if (op == '*') {
		result = first * second;
	}
	else if (op == '/') {
		result = first / second;
	}
	else if (op == '+') {
		result = first + second;
	}
	else if (op == '-') {
		result = first - second;
	}
	sprintf(s1->arr, "%d", result);

	return s1->arr;
}

_Bool is_spec_math(string* s) {
	return ((strlen(s->arr) > 1) && (s->arr[0] == '+' || s->arr[0] == '-') && s->arr[strlen(s->arr) - 1] != 'C');
}

char* spec_math(string* s1, string* s2) {
	int first, second;
	char sgn = s2->arr[0];

	for (size_t i = 1; i < strlen(s2->arr); i++) {
		s2->arr[i - 1] = s2->arr[i];
	}
	s2->arr[strlen(s2->arr) - 1] = '\0';
	first = atoi(s1->arr);
	second = atoi(s2->arr);

	sprintf(s2->arr, "%d", first - second);
	if (sgn == '+') {
		sprintf(s2->arr, "%d", first + second);
	}
	else {
		sprintf(s2->arr, "%d", first - second);
	}
	return s2->arr;
}

void end_of_string(string* str, string_arr* s_arr) {
	str_realloc(&str);
	str_arr_realloc(&s_arr);
	str->arr[str->len++] = '\0';
	s_arr->arr[s_arr->len++].arr = str->arr;
	str_realloc(&str);
	str_arr_realloc(&s_arr);
}

int main(int argc, const char** argv) {
	FILE* file_in;
	FILE* file_out;

	if (argc == 1) {
		file_in = fopen("test.txt", "r");
		file_out = fopen("output.txt", "w");
	}
	else {
		file_in = fopen(argv[1], "r");
		file_out = fopen(argv[2], "w");
	}
	string s;
	str_init(&s);

	string garbage;

	string_arr str_arr;
	str_arr.capacity = 1;
	str_arr.len = 0;
	str_arr.arr = (string*)malloc(sizeof(string) * 2);
	nullCheck(str_arr.arr);

	char sym;

	while (1) {

		sym = fgetc(file_in);

		str_arr_realloc(&str_arr);
		str_realloc(&s);

		if (sym == EOF) {
			if (feof(file_in) != 0) {
				end_of_string(&s, &str_arr);
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

		else if ((sym >= 'a' && sym <= 'z') || (sym >= 'A' && sym <= 'Z') || (sym >= '0' && sym <= '9') || (sym == '+' || sym == '-')) {
			if (s.len > 0) {
				if ((s.arr[s.len - 1] == '+' || s.arr[s.len - 1] == '-') && sym != '+' && sym != '-') {
					s.arr[s.len++] = sym;
					continue;
				}
				else if (sym == '+' || sym == '-') {
					if (s.len > 0) {
						end_of_string(&s, &str_arr);
#ifdef DEBUG
						printf("%s", str_arr.arr[str_arr.len - 1].arr);
#endif // DEBUG
						str_init(&s);
					}

					s.arr[s.len++] = sym;

					end_of_string(&s, &str_arr);
#ifdef DEBUG
					printf("%s ", str_arr.arr[str_arr.len - 1].arr);
#endif // DEBUG
					str_init(&s);
					continue;
				}
			}
			s.arr[s.len++] = sym;
			continue;
		}
		else {
			if (s.len > 0) {
				end_of_string(&s, &str_arr);
#ifdef DEBUG
				printf("%s", str_arr.arr[str_arr.len - 1].arr);
#endif // DEBUG
				str_init(&s);
			}
			end_of_string(&s, &str_arr);

			str_arr.arr[str_arr.len++].arr = s.arr;
#ifdef DEBUG
			printf("%s ", str_arr.arr[str_arr.len - 1].arr);
#endif // DEBUG
			str_init(&s);
		}
	}


	fclose(file_in);


	//Palindrom
	for (size_t i = 0; i < str_arr.len; i++) {
		if (is_word(str_arr.arr[i], strlen(str_arr.arr[i].arr)) && is_palindrom(str_arr.arr[i], strlen(str_arr.arr[i].arr))) {
			s.arr = "PALINDROM";
			str_arr.arr[i] = s;

		}
		s.arr = NULL;
	}

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
			if (str_arr.arr[i].arr[0] == '(') {
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

			else if ((str_arr.arr[i].arr[0] == ')' && flag_c == 1 && flag_l == 0 && flag_r == 0) || \
				(str_arr.arr[i].arr[0] == ')' && flag_c == 0 && flag_l == 0 && flag_r == 1)) {
				flag_l = 0;
				flag_c = 0;
				flag_r = 0;
				index_r = i;

				str_realloc(&garbage);

				garbage.arr[garbage.len++] = index_l;

				str_realloc(&garbage);

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
	

	remove_all_space(&str_arr);

	while (1) {
		for (size_t i = 0; i < str_arr.len; i++) {
			if (i < str_arr.len - 4) {
				if (is_num(str_arr.arr[i]) && is_oper(str_arr.arr[i + 2].arr[0]) && is_num(str_arr.arr[i + 4])) {
					str_arr.arr[i].arr = math(&str_arr.arr[i], str_arr.arr[i + 2].arr[0], &str_arr.arr[i + 4]);
					for (size_t j = 0; j < 4; j++) {
						remove_el(&str_arr, i + 1);
					}
				}
			}
			if (i < str_arr.len - 3) {
				if (is_num(str_arr.arr[i]) && is_oper(str_arr.arr[i + 1].arr[0]) && is_num(str_arr.arr[i + 3])) {
					str_arr.arr[i].arr = math(&str_arr.arr[i], str_arr.arr[i + 1].arr[0], &str_arr.arr[i + 3]);
					for (size_t j = 0; j < 3; j++) {
						remove_el(&str_arr, i + 1);
					}
				}
				if (is_num(str_arr.arr[i]) && is_oper(str_arr.arr[i + 2].arr[0]) && is_num(str_arr.arr[i + 3])) {
					str_arr.arr[i].arr = math(&str_arr.arr[i], str_arr.arr[i + 2].arr[0], &str_arr.arr[i + 3]);
					for (size_t j = 0; j < 3; j++) {
						remove_el(&str_arr, i + 1);
					}
				}
			}
			if (i < str_arr.len - 2) {
				if (is_num(str_arr.arr[i]) && is_oper(str_arr.arr[i + 1].arr[0]) && is_num(str_arr.arr[i + 2])) {
					str_arr.arr[i].arr = math(&str_arr.arr[i], str_arr.arr[i + 1].arr[0], &str_arr.arr[i + 2]);
					for (size_t j = 0; j < 2; j++) {
						remove_el(&str_arr, i + 1);
					}
				}
				if (is_num(str_arr.arr[i]) && is_spec_math(&str_arr.arr[i + 2])) {
					str_arr.arr[i].arr = spec_math(&str_arr.arr[i], &str_arr.arr[i + 2]);
					remove_el(&str_arr, i + 1);
					remove_el(&str_arr, i + 1);
				}
				if (is_num(str_arr.arr[i]) && is_spec_math(&str_arr.arr[i + 1])) {
					str_arr.arr[i].arr = spec_math(&str_arr.arr[i], &str_arr.arr[i + 1]);
					remove_el(&str_arr, i + 1);
				}
			}
			if (i > 0) {
				if (str_arr.arr[i - 1].arr[0] == '(' && str_arr.arr[i + 1].arr[0] == ')') {
					remove_el(&str_arr, i + 1);
					remove_el(&str_arr, i - 1);
				}
			}

		}
		if (count_of_op(&str_arr) == 0) {
			break;
		}
	}

	remove_all_space(&str_arr);

#ifdef DEBUG

	printf("\n\n");
#endif // DEBUG


	//fprintf
	for (size_t i = 0; i < str_arr.len; i++) {
		fprintf(file_out, "%s", str_arr.arr[i].arr);
#ifdef DEBUG
		printf("%s %d\n", str_arr.arr[i].arr, i);
#endif // DEBUG
	}

	for (size_t i = 0; i < str_arr.len; i++) {
#ifdef DEBUG
		printf("%s", str_arr.arr[i].arr);
#endif // DEBUG
	}

	fclose(file_out);


	return 0;
}
