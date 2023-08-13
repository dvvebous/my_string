CC=gcc
CFLAGS=-Wall -Wextra -Werror
LDFLAGS= `pkg-config --cflags --libs check`
GCOVFLAGS=-fprofile-arcs -ftest-coverage
TEST_LIBS = -lcheck -lm -lpthread

.PHONY: all clean

all: s21_string.a test gcov_report

s21_string.a:
	$(CC) $(CFLAGS) -c s21_string.c s21_sprintf.c
	ar rc s21_string.a *.o
	ranlib s21_string.a
	
clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.info *.out *.cfg *.txt test gcov_main gcov_report

test:
	$(CC) $(CFLAGS) s21_sprintf.c s21_string.c test.c -o test $(LDFLAGS)

gcov_report:
	$(CC) $(CFLAGS)  $(GCOVFLAGS) s21_string.c s21_sprintf.c test.c -o gcov_main $(LDFLAGS)
	./gcov_main
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	open gcov_report/index.html
	
	
style_check:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h
	rm .clang-format
	
style:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h
	rm .clang-format
