CXX = g++
CXX_FLAGS = -std=c++17 -Wextra -Wall -Werror
TARGET = SmartCalc_v2
TEST_DIR = ./Tests
TEST = ./Tests/test
TEST_SRC := $(shell find $(TEST_DIR) -name "*.cc" | sed -e 's/\.\///')
TEST_OBJS := $(TEST_SRC:%.c=$(BUILD_TEST_DIR)/%.o)
COV_FLAGS = -fprofile-arcs -ftest-coverage --coverage -O0
TEST_FLAGS =-lgtest -lgcov

all: clean test

install:
	mkdir build
	cd ./build/ && qmake ../SmartCalc_v2.pro && make && mv SmartCalc_v2 SmartCalc_v2.app
	mkdir ../SmartCalc
	cp -rf ./build ../SmartCalc/
	@-rm -rf ./build/

uninstall:
	rm -rf ../SmartCalc ./build

dvi: $(TARGET).pdf
	open $(TARGET).pdf

$(TARGET).pdf: Info/$(TARGET).tex
	texi2pdf -q -c Info/$(TARGET).tex -o $(TARGET).pdf

dist:
	tar -czf $(TARGET).tar.gz ./Controller ./Model ./View main.cpp SmartCalc_v2.pro

test: clean $(TEST_DIR)/*.cc $(TEST_DIR)/test.h ./Model/model.h ./Model/model.cpp
	$(CXX) $(CXX_FLAGS) $(TEST_DIR)/*.cc $(TEST_DIR)/test.h ./Model/model.h ./Model/model.cpp $(TEST_FLAGS) -o $(TEST)
	$(TEST)

gcov_report: clean
	$(CXX) $(CXX_FLAGS) $(COV_FLAGS) $(TEST_OBJS) $(SRC) $(TEST_FLAGS) ./Model/model.h ./Model/model.cpp -o $(TEST)
	$(TEST)
	rm -rf $(TEST_DIR)/*.gcno $(TEST_DIR)/*.gcda
	gcovr -r . -s --html --html-details -o ./coverage_report.html
	rm -rf *.gcno *.gcda *.o
	open ./coverage_report.html

style_check:
	@find . \( -name '*.h' -o -name '*.cpp' \) -print0 | xargs -0 clang-format -n -style=Google

style_fix:
	@find . \( -name '*.h' -o -name '*.cpp' \) -print0 | xargs -0 clang-format -i -style=Google

leaks_check: clean test
ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes --log-file=RESULT_VALGRIND.txt $(TEST)
endif

cppcheck:
	cppcheck . 2> cppcheck.log

clean:
	@rm -rf *.o *.a coverage* report RESULT_VALGRIND.txt $(TEST) cppcheck.log *.gcda *.gcno *.pdf
