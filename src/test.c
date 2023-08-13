#include <check.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "s21_sprintf.h"
#include "s21_string.h"

#define BUF_SIZE 100
// S21_MEMCHR_TEST
START_TEST(s21_memchr_test) {
  char test1[] = "123456";
  char test2 = '4';
  char test3 = '7';
  char test4[] = "hello/\0";
  char test5[] = "h";
  char test6 = 'h';
  char test7 = ' ';
  char test8 = '/';
  char test9 = '\0';
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, test2, 6),
                    (unsigned long)memchr(test1, test2, 6));
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, test3, 6),
                    (unsigned long)memchr(test1, test3, 6));
  ck_assert_uint_eq((unsigned long)s21_memchr(test4, test6, 6),
                    (unsigned long)memchr(test4, test6, 6));
  ck_assert_uint_eq((unsigned long)s21_memchr(test5, test7, 1),
                    (unsigned long)memchr(test5, test7, 1));
  ck_assert_uint_eq((unsigned long)s21_memchr(test4, test8, 6),
                    (unsigned long)memchr(test4, test8, 6));
  ck_assert_uint_eq((unsigned long)s21_memchr(test4, test9, 6),
                    (unsigned long)memchr(test4, test9, 6));
}
END_TEST

// S21_MEMCMP_TEST
START_TEST(s21_memcmp_test) {
  char test1[] = "Apple Pay Money Day";
  char test2[] = "Apple with worm";
  char test3[] = "\0";
  char test4[] = "gud\0 job";
  char test5[] = "gud\0 job";
  ck_assert_uint_eq(s21_memcmp(test1, test2, 16) < 0,
                    memcmp(test1, test2, 16) < 0);
  ck_assert_uint_eq(s21_memcmp(test1, test3, 2) > 0,
                    memcmp(test1, test3, 2) > 0);
  ck_assert_uint_eq(s21_memcmp(test2, test3, 2) > 0,
                    memcmp(test2, test3, 2) > 0);
  ck_assert_uint_eq(s21_memcmp(test4, test1, 9) > 0,
                    memcmp(test4, test1, 9) > 0);
  ck_assert_uint_eq(s21_memcmp(test4, test5, 7) == 0,
                    memcmp(test4, test5, 7) == 0);
}
END_TEST

// S21_MEMCPY_TEST
START_TEST(s21_memcpy_test) {
  char test_1[10] = "12345";
  char test_2[] = "  ";
  char test_3[20] = "///  ";
  char test_4[] = "   ///";
  char test_5[30] = "";
  char test_6[] = "4444";
  char test_7[] = "123\0123";

  ck_assert_str_eq(s21_memcpy(test_1, test_2, 2), memcpy(test_1, test_2, 2));
  ck_assert_str_eq(s21_memcpy(test_3, test_4, 6), memcpy(test_3, test_4, 6));
  ck_assert_str_eq(s21_memcpy(test_5, test_6, 4), memcpy(test_5, test_6, 4));
  ck_assert_str_eq(s21_memcpy(test_5, test_7, 6), memcpy(test_5, test_7, 6));
}
END_TEST

// S21_MEMSET_TEST
START_TEST(s21_memset_test) {
  unsigned char test1[10] = "1234357890";
  unsigned char test2[10] = "hello";
  ck_assert_uint_eq((unsigned long)s21_memset(test1, '1', 10),
                    (unsigned long)memset(test1, '1', 10));
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, '3', 10),
                    (unsigned long)memchr(test1, '3', 10));
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, '/', 8),
                    (unsigned long)memchr(test1, '/', 8));
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, '9', 0),
                    (unsigned long)memchr(test1, '9', 0));
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, '0', 4),
                    (unsigned long)memchr(test1, '0', 4));
  ck_assert_uint_eq((unsigned long)s21_memchr(test2, '1', 3),
                    (unsigned long)memchr(test2, '1', 3));
}
END_TEST

// S21_STRNCAT_TEST
START_TEST(s21_strncat_test) {
  char dest1[100] = "Hello";
  char dest2[100] = "Hello";
  char src1[] = " World!";
  char src2[] = "";
  char src3[] = "12345";
  char src4[] = "Another String";
  char src5[] = "Goodbye";

  ck_assert_str_eq(s21_strncat(dest1, src1, 7), strncat(dest2, src1, 7));
  ck_assert_str_eq(s21_strncat(dest1, src2, 0), strncat(dest2, src2, 0));
  ck_assert_str_eq(s21_strncat(dest1, src3, 2), strncat(dest2, src3, 2));
  ck_assert_str_eq(s21_strncat(dest1, src4, 6), strncat(dest2, src4, 6));
  ck_assert_str_eq(s21_strncat(dest1, src5, 0), strncat(dest2, src5, 0));
}
END_TEST

// S21_STRCHR_TEST
START_TEST(s21_strchr_test) {
  const char str1[] = "Hello";
  const char str2[] = "Test\0String";
  const char str3[] = "1234567890";
  const char str4[] = "Lorem Ipsum";
  ck_assert_ptr_eq(s21_strchr(str1, 'H'), strchr(str1, 'H'));
  ck_assert_ptr_eq(s21_strchr(str1, 'o'), strchr(str1, 'o'));
  ck_assert_ptr_eq(s21_strchr(str2, '\0'), strchr(str2, '\0'));
  ck_assert_ptr_eq(s21_strchr(str3, '0'), strchr(str3, '0'));
  ck_assert_ptr_eq(s21_strchr(str4, 'm'), strchr(str4, 'm'));
}
END_TEST

// S21_STRCMP_TEST
START_TEST(s21_strncmp_test) {
  const char str1[] = "Hello";
  const char str2[] = "575545";
  const char str3[] = " Hello";
  const char str4[] = "\0";
  const char str5[] = "Hella";
  ck_assert_int_eq(s21_strncmp(str1, str2, 4), strncmp(str1, str2, 4));
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
  ck_assert_int_eq(s21_strncmp(str1, str3, 5), strncmp(str1, str3, 5));
  ck_assert_int_eq(s21_strncmp(str1, str4, 4), strncmp(str1, str4, 4));
  ck_assert_int_eq(s21_strncmp(str1, str5, 4), strncmp(str1, str5, 4));
}
END_TEST

// S21_STRNCPY_TEST
START_TEST(s21_strncpy_test) {
  char str1[] = "test of string";
  char dest1[15] = "";

  char str2[] = "test\0";
  char dest2[5] = "";

  char str3[] = "test ";
  char dest3[] = "crushcrush";

  char str3_test[] = "test ";
  char dest3_test[] = "crushcrush";

  ck_assert_str_eq("test ", s21_strncpy(dest1, str1, 5));
  ck_assert_str_eq("test", s21_strncpy(dest2, str2, 4));
  ck_assert_str_eq(s21_strncpy(dest3, str3, 10),
                   strncpy(dest3_test, str3_test, 10));
}
END_TEST

// S21_STRCSPN_TEST
START_TEST(s21_strcspn_test) {
  char test1[] = "0123456789";
  char test2[] = "9876";
  char test3[] = "LOST: 4-8-15-16-23-42";
  char test4[] = "1234567890";
  char test5[] = "0/";
  char test6[] = "%%\\#";
  char test7[] = " ";
  char test8[] = "1234567890";
  ck_assert_uint_eq(s21_strcspn(test1, test2), strcspn(test1, test2));
  ck_assert_uint_eq(s21_strcspn(test3, test4), strcspn(test3, test4));
  ck_assert_uint_eq(s21_strcspn(test3, test5), strcspn(test3, test5));
  ck_assert_uint_eq(s21_strcspn(test3, test6), strcspn(test3, test6));
  ck_assert_uint_eq(s21_strcspn(test3, test7), strcspn(test3, test7));
  ck_assert_uint_eq(s21_strcspn(test4, test8), strcspn(test4, test8));
  ck_assert_uint_eq(s21_strcspn(test2, test7), strcspn(test2, test7));
}
END_TEST

// S21_STRERROR_TEST
START_TEST(s21_strerror_test) {
  char *case1 = s21_strerror(0);
  char *case2 = strerror(0);
  ck_assert_uint_eq((unsigned long)*case1, (unsigned long)*case2);

  char *case9 = s21_strerror(1);
  char *case10 = strerror(1);
  ck_assert_uint_eq((unsigned long)*case9, (unsigned long)*case10);

  char *case0 = s21_strerror(106);
  char *case3 = strerror(106);
  ck_assert_uint_eq((unsigned long)*case0, (unsigned long)*case3);

  char *case7 = s21_strerror(200);
  char *case8 = strerror(200);
  ck_assert_uint_eq((unsigned long)*case7, (unsigned long)*case8);

  char *case11 = s21_strerror(-1);
  char *case12 = strerror(-1);
  ck_assert_uint_eq((unsigned long)*case11, (unsigned long)*case12);
}
END_TEST

// S21_STRLEN_TEST
START_TEST(s21_strlen_test) {
  char src1[] = " World!";
  char src2[] = "";
  char src3[] = "12345";
  ck_assert_int_eq(s21_strlen(src1), strlen(src1));
  ck_assert_int_eq(s21_strlen(src3), strlen(src3));
  ck_assert_int_eq(s21_strlen(src2), strlen(src2));
}
END_TEST

// S21_STRBRK_TEST
START_TEST(s21_strpbrk_test) {
  char str_for_strpbrk[] = "Templar Assasin";
  char str_oneof[] = "Ass";
  ck_assert_str_eq(s21_strpbrk(str_for_strpbrk, str_oneof), "Assasin");
  ck_assert_str_eq(s21_strpbrk(str_for_strpbrk, str_oneof),
                   strpbrk(str_for_strpbrk, str_oneof));
  char str_for_strpbrk2[] = "State Of New York";
  char str_oneof2[] = "Of";

  ck_assert_str_eq(s21_strpbrk(str_for_strpbrk2, str_oneof2),
                   strpbrk(str_for_strpbrk2, str_oneof2));

  char *str = "This is the road to hell";
  char *empty = "";
  char *empty2 = "T";
  char *empty3 = "l";

  ck_assert(s21_strpbrk(str, empty) == s21_NULL);
  ck_assert_uint_eq((unsigned long)s21_strpbrk(str, empty),
                    (unsigned long)strpbrk(str, empty));
  ck_assert_uint_eq((unsigned long)s21_strpbrk(str, empty2),
                    (unsigned long)strpbrk(str, empty2));
  ck_assert_uint_eq((unsigned long)s21_strpbrk(str, empty3),
                    (unsigned long)strpbrk(str, empty3));
}
END_TEST

// S21_STRRCHR_TEST
START_TEST(s21_strrchr_test) {
  char test1[] = "9876 54326 10";
  char test2[] = "a;b;c;d;e;f;g;h;i;j;h";
  char test3[] = " $ ! @ # $ ^ & * ( $ ) $ ";
  char test4[] = "$";

  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, '6'),
                    (unsigned long)strrchr(test1, '6'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, ' '),
                    (unsigned long)strrchr(test1, ' '));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, '6'),
                    (unsigned long)strrchr(test1, '6'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test2, 'h'),
                    (unsigned long)strrchr(test2, 'h'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test3, '$'),
                    (unsigned long)strrchr(test3, '$'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test2, ';'),
                    (unsigned long)strrchr(test2, ';'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test3, ' '),
                    (unsigned long)strrchr(test3, ' '));
  ck_assert_str_eq(s21_strrchr(test2, '\0'), strrchr(test2, '\0'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test4, '$'),
                    (unsigned long)strrchr(test4, '$'));
}
END_TEST

// S21_STRSTR_TEST
START_TEST(s21_strstr_test) {
  char test_1[] = "Monkey King";
  char test_2[] = "king";
  char test_3[] = "AssassinAsssasssinAsasin";
  char test_4[] = "Assassin";
  char test_5[] = "1234";
  char test_6[] = "";
  char test_7[] = "5123451234512345";
  char test_8[] = "1234";
  char test_9[] = "1";
  char test_10[] = "4";

  ck_assert_ptr_eq(s21_strstr(test_1, test_2), strstr(test_1, test_2));
  ck_assert_ptr_eq(s21_strstr(test_3, test_4), strstr(test_3, test_4));
  ck_assert_ptr_eq(s21_strstr(test_5, test_6), strstr(test_5, test_6));
  ck_assert_ptr_eq(s21_strstr(test_4, test_5), strstr(test_4, test_5));
  ck_assert_ptr_eq(s21_strstr(test_7, test_8), strstr(test_7, test_8));
  ck_assert_ptr_eq(s21_strstr(test_8, test_9), strstr(test_8, test_9));
  ck_assert_ptr_eq(s21_strstr(test_8, test_10), strstr(test_8, test_10));
}
END_TEST

// S21_STRTOK_TEST
START_TEST(s21_strtok_test) {
  char str_strtok1[] = "one/two/three(four)five";
  char delim1[] = "/()";

  char str_strtok2[] = "one/two/three(four)five";
  char delim2[] = "/()";
  char *my_strtok = s21_strtok(str_strtok1, delim1);
  char *origin_strtok = strtok(str_strtok2, delim2);
  while (my_strtok != s21_NULL) {
    ck_assert_str_eq(my_strtok, origin_strtok);
    my_strtok = s21_strtok(s21_NULL, delim1);
    origin_strtok = strtok(s21_NULL, delim2);
  }
}
END_TEST

// S21_SPRINTF_TEST

START_TEST(d_simple_int) {
  char s21_buff[100] = "";
  char buff[100] = "";
  int s21 = 5;
  int system = 5;
  s21_sprintf(s21_buff, "This is %d", s21);
  sprintf(buff, "This is %d", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(d_negative_int) {
  char s21_buff[100] = "";
  char buff[100] = "";
  int s21 = -19;
  int system = -19;
  s21_sprintf(s21_buff, "This is %d", s21);
  sprintf(buff, "This is %d", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(d_int_in_middle_of_str) {
  char s21_buff[100] = "";
  char buff[100] = "";
  int s21 = 1024;
  int system = 1024;
  s21_sprintf(s21_buff, "This is %d number", s21);
  sprintf(buff, "This is %d number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(d_zero) {
  char s21_buff[100] = "";
  char buff[100] = "";
  int s21 = 0;
  int system = 0;
  s21_sprintf(s21_buff, "This is %d number", s21);
  sprintf(buff, "This is %d number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(s_simple_test) {
  char s21_buff[100] = "";
  char buff[100] = "";
  char *s21 = "Hello str";
  char *system = "Hello str";
  s21_sprintf(s21_buff, "This is %s", s21);
  sprintf(buff, "This is %s", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(s_empty_test) {
  char s21_buff[100] = "";
  char buff[100] = "";
  char *s21 = "";
  char *system = "";
  s21_sprintf(s21_buff, "This is %s", s21);
  sprintf(buff, "This is %s", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(s_int_str_test) {
  char s21_buff[100] = "";
  char buff[100] = "";
  char *s21 = "12345";
  char *system = "12345";
  s21_sprintf(s21_buff, "This is %s", s21);
  sprintf(buff, "This is %s", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(s_str_in_middle_of_str) {
  char s21_buff[100] = "";
  char buff[100] = "";
  char *s21 = "my";
  char *system = "my";
  s21_sprintf(s21_buff, "This is %s string", s21);
  sprintf(buff, "This is %s string", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(f_simple) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 4.3;
  float system = 4.3;
  s21_sprintf(s21_buff, "This is %f number", s21);
  sprintf(buff, "This is %f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(f_simple_zero) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 0.34;
  float system = 0.34;
  s21_sprintf(s21_buff, "This is %f number", s21);
  sprintf(buff, "This is %f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(f_big_number) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 9.3425789;
  float system = 9.3425789;
  s21_sprintf(s21_buff, "This is %f number", s21);
  sprintf(buff, "This is %f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(f_big_int_part) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 10.3;
  float system = 10.3;
  s21_sprintf(s21_buff, "This is %f number", s21);
  sprintf(buff, "This is %f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(f_zero) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 0;
  float system = 0;
  s21_sprintf(s21_buff, "This is %f number", s21);
  sprintf(buff, "This is %f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(exactness_simple) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 2.322;
  float system = 2.322;
  s21_sprintf(s21_buff, "This is %.2f number", s21);
  sprintf(buff, "This is %.2f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(exactness_with_simple_rounding) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 2.3228;
  float system = 2.3228;
  s21_sprintf(s21_buff, "This is %.3f number", s21);
  sprintf(buff, "This is %.3f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(exactness_with_hard_rounding) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 2.3228;
  float system = 2.3228;
  s21_sprintf(s21_buff, "This is %.3f number", s21);
  sprintf(buff, "This is %.3f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(exactness_with_hard_rounding_minus) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = -2.3228;
  float system = -2.3228;
  s21_sprintf(s21_buff, "This is %.3f number", s21);
  sprintf(buff, "This is %.3f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(c_simple_char) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%c", 'c');
  sprintf(buff, "%c", 'c');

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(c_number_ASCII) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%c", 67);
  sprintf(buff, "%c", 67);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(c_number_char) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%c", '8');
  sprintf(buff, "%c", '8');
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(c_space_char) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%c", ' ');
  sprintf(buff, "%c", ' ');
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(flag_plus_simple_test) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%+d", 21);
  sprintf(buff, "%+d", 21);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(flag_plus_negative_number) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%+d", -250);
  sprintf(buff, "%+d", -250);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(flag_plus_zero) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "result: %+d", 0);
  sprintf(buff, "result: %+d", 0);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(flag_space_simple_test) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "result: % d", 25);
  sprintf(buff, "result: % d", 25);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(flag_space_negative_number) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "% d", -1000);
  sprintf(buff, "% d", -1000);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(sprintf_u_check) {
  char str[100] = "";
  char str2[100] = "";
  sprintf(str, "%u", (unsigned)0);
  s21_sprintf(str2, "%u", (unsigned)0);
  ck_assert_pstr_eq(str, str2);
  sprintf(str, "%2u", (unsigned int)4);
  s21_sprintf(str2, "%2u", 4);
  ck_assert_str_eq(str, str2);
  sprintf(str, "%2.5u", (unsigned int)4);
  s21_sprintf(str2, "%2.5u", 4);
  ck_assert_str_eq(str, str2);
  sprintf(str, "%-u", (unsigned int)6);
  s21_sprintf(str2, "%-u", 6);
  ck_assert_str_eq(str, str2);
}
END_TEST

START_TEST(flag_space_zero) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "% d", 0);
  sprintf(buff, "% d", 0);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  tcase_add_test(tc1_1, s21_strlen_test);
  tcase_add_test(tc1_1, s21_strncat_test);
  tcase_add_test(tc1_1, s21_strchr_test);
  tcase_add_test(tc1_1, s21_strncmp_test);
  tcase_add_test(tc1_1, s21_memchr_test);
  tcase_add_test(tc1_1, s21_memcmp_test);
  tcase_add_test(tc1_1, s21_strncpy_test);
  tcase_add_test(tc1_1, s21_strcspn_test);
  tcase_add_test(tc1_1, s21_strerror_test);
  tcase_add_test(tc1_1, s21_strpbrk_test);
  tcase_add_test(tc1_1, s21_strrchr_test);
  tcase_add_test(tc1_1, s21_strstr_test);
  tcase_add_test(tc1_1, s21_memcpy_test);
  tcase_add_test(tc1_1, s21_memset_test);
  tcase_add_test(tc1_1, s21_strtok_test);

  tcase_add_test(tc1_1, d_simple_int);
  tcase_add_test(tc1_1, d_negative_int);
  tcase_add_test(tc1_1, d_int_in_middle_of_str);

  tcase_add_test(tc1_1, s_simple_test);
  tcase_add_test(tc1_1, s_empty_test);
  tcase_add_test(tc1_1, s_int_str_test);
  tcase_add_test(tc1_1, s_str_in_middle_of_str);

  tcase_add_test(tc1_1, f_simple);
  tcase_add_test(tc1_1, f_simple_zero);
  tcase_add_test(tc1_1, f_big_number);
  tcase_add_test(tc1_1, f_big_int_part);
  tcase_add_test(tc1_1, f_zero);

  tcase_add_test(tc1_1, exactness_simple);
  tcase_add_test(tc1_1, exactness_with_simple_rounding);
  tcase_add_test(tc1_1, exactness_with_hard_rounding);
  tcase_add_test(tc1_1, exactness_with_hard_rounding_minus);

  tcase_add_test(tc1_1, c_simple_char);
  tcase_add_test(tc1_1, c_number_ASCII);
  tcase_add_test(tc1_1, c_number_char);
  tcase_add_test(tc1_1, c_space_char);

  tcase_add_test(tc1_1, flag_plus_simple_test);
  tcase_add_test(tc1_1, flag_plus_negative_number);
  tcase_add_test(tc1_1, flag_plus_zero);
  tcase_add_test(tc1_1, flag_space_simple_test);
  tcase_add_test(tc1_1, flag_space_negative_number);
  tcase_add_test(tc1_1, flag_space_zero);
  tcase_add_test(tc1_1, sprintf_u_check);
  tcase_add_test(tc1_1, d_zero);

  suite_add_tcase(s1, tc1_1);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}