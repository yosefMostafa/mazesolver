#include<iostream>
#include"program.h"

using namespace std;

int main() {
	program* PG = new program();

	while (true) {
		PG->RunProgram();
	}
	return 0;
}