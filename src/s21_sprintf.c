#include "s21_sprintf.h"

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

int s21_sprintf(char *str, const char *format, ...) {
  va_list ptr;
  str[0] = '\0';
  va_start(ptr, format);
  Parse(ptr, str, format);
  va_end(ptr);
  return (int)s21_strlen(str);
}

void Parse(va_list ptr, char *str, const char *format) {
  const char *specificators = "csdfu%";
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      info spec = {0};
      format = SetSpec(&spec, format);
      if (s21_strchr(specificators, *format) == NULL) {
        fprintf(stderr, "golovka");
        return;
      }
      insert_in_str(&spec, format, str, ptr);
    } else {
      s21_strncat(str, format, 1);
    }
    format++;
  }
}

char *SetSpec(info *spec, const char *format)
{
  char *result = NULL;
  format = find_flags(spec, format);
  format = (format != s21_NULL ? find_with(&(spec->with), format) : NULL);
  if (format) {
    if (*format == '.') {
      spec->dot = 1;
      format++;
      format = find_with(&(spec->precision), format);
    } else if (*format == 'l')
      spec->expansion = 'l';
    else if (*format == 'h')
      spec->expansion = 'h';
    if (spec->expansion != 0) format++;
    result = (char *)format;
  }
  return result;
}

char *find_flags(info *spec, const char *format) {
  while (format) {
    if (*format == '-')
      spec->minus = 1;
    else if (*format == ' ')
      spec->space = 1;
    else if (*format == '+')
      spec->plus = 1;
    else {
      if (!s21_strchr(avail_char_spec, *format)) format = s21_NULL;
      break;
    }
    format++;
  }
  spec->space = (spec->space != 0 && spec->plus == 0);
  return (char *)format;
}

char *find_with(int *spec_field, const char *format) {
  *spec_field = 0;
  while ('0' <= *format && *format <= '9') {
    *spec_field *= 10;
    *spec_field += *format - '0';
    format++;
  }
  return (char *)format;
}

void insert_in_str(info *spec, const char *format, char *str,
                   va_list argumets) {
  if (*format == 'd') {
    insert_d(spec, str, argumets);
  } else if (*format == 'c') {
    insert_c(spec, str, argumets);
  } else if (*format == 'f') {
    insert_f(spec, str, argumets);
  } else if (*format == 's') {
    insert_s(spec, str, argumets);
  } else if (*format == 'u') {
    insert_u(spec, str, argumets);
  } else if (*format == '%') {
    s21_strncat(str, "%", 2);
  }
}

void insert_c(info *spec, char *str, va_list argumets) {
  char ch = va_arg(argumets, int);
  int size = MAX(1, spec->with);
  char result[size + 1];
  if (spec->minus) {
    int index = 1;
    result[0] = ch;
    for (; index < size; index++) result[index] = ' ';
  } else {
    int index = 0;
    for (; index < size; index++) {
      result[index] = ' ';
    }
    result[size - 1] = (char)ch;
  }
  result[size] = '\0';
  s21_strncat(str, result, s21_strlen(result));
}

void insert_d(info *spec, char *str, va_list argumets) {
  int place = 0;
  long long num;
  if (spec->expansion == 'l')
    num = va_arg(argumets, long int);
  else
    num = va_arg(argumets, int);
  int is_null = (num == 0) ? 1 : 0;
  long long x = (num > 0) ? num : -num;
  while (x > 0) {
    x = x / 10;
    place++;
  }
  int is_plus_space = spec->plus || spec->space || num < 0;
  int size = MAX(place, spec->precision) + is_plus_space + is_null;
  char str_num[size + 1];
  if (num < 0)
    str_num[0] = '-';
  else if (spec->plus)
    str_num[0] = '+';
  else if (spec->space)
    str_num[0] = ' ';
  else
    str_num[0] = '0';
  for (int i = 1; i < size; i++) {
    str_num[i] = '0';
  }
  x = (num > 0) ? num : -num;
  for (int i = size - 1; i > size - 1 - place; i--) {
    str_num[i] = (char)('0' + x % 10);
    x /= 10;
  }
  if (num < 0) str_num[0] = '-';
  str_num[size] = '\0';

  int res_size = MAX(size, spec->with) + 1;
  char result[res_size];
  if (spec->minus) {
    int index = 0;
    for (index = 0; index < size; index++) result[index] = str_num[index];
    for (; index < res_size; index++) result[index] = ' ';
  } else {
    int index = 0;
    for (; index < res_size - size - 1; index++) {
      result[index] = ' ';
    }
    int tmp = index;
    for (; index < res_size; index++) {
      result[index] = str_num[index - tmp];
    }
  }
  result[res_size - 1] = '\0';
  s21_strncat(str, result, s21_strlen(result));
}
void insert_f(info *spec, char *str, va_list argumets) {
  long double num = va_arg(argumets, double);
  int precision = spec->precision;
  if (S21_IS_NAN(num) || S21_IS_INF(num)) {
    sprintf_not_number(spec, str, num);
  } else {
    if (spec->dot == 1 && spec->precision == 0) {
      precision = 0;
    } else if (spec->precision == 0)
      precision = 6;
    int place = ((long long)num == 0) ? 1 : 0;
    int is_pos = (num >= 0) ? 0 : 1;
    int is_minus_null = check_null_numb(num);
    num = fabsl(num);
    long long num_without_dot = (long long)num;
    while (num_without_dot > 0) {
      place++;
      num_without_dot /= 10;
    }
    long double left = 0;
    long double right = modfl(num, &left);
    for (int i = precision; i != 0; i--) right *= 10;
    right = roundl(right);
    int size_num = precision > 0
                       ? place + precision + is_minus_null + is_pos + 1
                       : place + precision + is_minus_null + is_pos;
    char str_num[size_num + 1];
    for (int i = size_num - 1; i >= 0; i--) {
      if (i == place + is_pos + is_minus_null && precision != 0)
        str_num[i] = '.';
      else if (i > place + is_pos + is_minus_null) {
        str_num[i] = (char)('0' + fmodl(right, 10));
        right /= 10;
      } else {
        str_num[i] = (char)('0' + fmodl(left, 10));
        left /= 10;
      }
    }
    if (is_pos == 1 || is_minus_null) str_num[0] = '-';
    str_num[size_num] = '\0';
    int size_str = MAX(spec->with, size_num);
    char result[size_str + 1];
    result[size_str] = '\0';
    add_space(spec, str, result, str_num, size_str + 1, size_num);
  }
}

void add_space(info *spec, char *str, char *result, char *str_num, int size_str,
               int size_num) {
  if (spec->minus) {
    for (int i = 0; i < size_num + 1; i++) {
      result[i] = str_num[i];
    }
    for (int i = size_num; i < size_str - 1; i++) result[i] = ' ';
  } else {
    int index = 0;
    for (; index < size_str - size_num - 1; index++) result[index] = ' ';
    int tmp = index;
    for (; index < size_str + 2; index++) result[index] = str_num[index - tmp];
  }
  result[size_str] = '\0';
  s21_strncat(str, result, s21_strlen(result));
}

void sprintf_not_number(info *spec, char *str, double x) {
  int size_chars = 0;
  char chars[6] = {0};
  if (S21_IS_NEG_INF(x)) {
    size_chars = 4;
    s21_strncat(chars, "-inf", s21_strlen("-inf") + 1);
  } else if (S21_IS_POS_INF(x)) {
    size_chars = 3;
    s21_strncat(chars, "inf", s21_strlen("inf") + 1);
  } else {
    size_chars = 4;
    s21_strncat(chars, "-nan", s21_strlen("-nan") + 1);
  }
  int size_str = MAX(spec->with, size_chars);
  char result[size_str + 1];
  result[size_str] = '\0';
  add_space(spec, str, result, chars, size_str + 1, size_chars);
}

int check_null_numb(double x) {
  int result = 0;
  if (x == 0.0) {
    double a = 1;
    if (a != copysign(a, x)) result = 1;
  }
  return result;
}
void insert_u(info *spec, char *str, va_list argumets) {
  insert_d(spec, str, argumets);
}

void insert_s(info *spec, char *str, va_list argumets) {
  if (spec->space || spec->plus) {
    fprintf(stderr,
            "Attempt to treat a string as if it were a signed number\n");
    return;
  }
  char *tmp = va_arg(argumets, char *);
  int line_size = MAX(spec->precision, (int)s21_strlen(tmp));
  char line[line_size + 1];
  line[0] = '\0';
  line[line_size] = '\0';
  s21_strncat(line, tmp, line_size);
  int real_size = MAX(line_size, spec->with);
  char result[real_size + 1];
  result[real_size] = '\0';
  for (int i = 0; i < real_size; i++) {
    result[i] = ' ';
  }
  if (spec->minus) {
    for (int i = 0; i < line_size; i++) {
      result[i] = line[i];
    }
  } else {
    int index = real_size - 1;
    for (int i = real_size - 1; i > real_size - line_size - 1; i--) {
      result[i] = line[line_size - (index - i) - 1];
    }
  }
  s21_strncat(str, result, s21_strlen(result));
}
