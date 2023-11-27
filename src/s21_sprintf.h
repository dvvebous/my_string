#ifndef STRINGS
#define STRINGS
#include <math.h>
#include <stdarg.h>

#include "s21_string.h"

#define S21_NAN 0.0 / 0.0
#define S21_INF_POS +1.0 / 0.0
#define S21_INF_NEG -1.0 / 0.0

#define S21_IS_NAN(x) (x != x)
#define S21_IS_INF(x) (x == S21_INF_NEG || x == S21_INF_POS)
#define S21_IS_POS_INF(x) (x == S21_INF_POS)
#define S21_IS_NEG_INF(x) (x == S21_INF_NEG)

#define s21_sprintf_NULL (void *)0
#define avail_char_spec "01234567890lh.cdfsu%"

typedef struct {
  int plus;
  int space;
  int minus;
  int with;
  int precision;
  int dot;
  char expansion;
} info;

int s21_sprintf(char *str, const char *format, ...);
void Parse(va_list ptr, char *str, const char *format);
char *SetSpec(info *spec, const char *format);  
char *find_flags(info *spec, const char *format);
char *find_with(int *spec_field, const char *format);
void insert_in_str(info *spec, const char *format, char *str, va_list argumets);
void insert_d(info *spec, char *str, va_list argumets);
void insert_c(info *spec, char *str, va_list argumets);
void insert_f(info *spec, char *str, va_list argumets);
void insert_s(info *spec, char *str, va_list argumets);
void insert_u(info *spec, char *str, va_list argumets);
void add_space(info *spec, char *str, char *result, char *str_num, int size_str,
               int size_num);
void sprintf_not_number(info *spec, char *str, double x);
int check_null_numb(double x);
#endif