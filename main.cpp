#include "check.h"

#include <stdlib.h>

int main() {
	test_init();
	test_assignment();
	test_ij();
	test_cout();
	test_arithmetic();
	test_capacity();
	test_alloc();

	system("pause");
	return 0;
}