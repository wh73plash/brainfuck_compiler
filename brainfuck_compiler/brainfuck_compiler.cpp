#pragma once
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <windows.h>

using namespace std;

std::vector<char> source_read(FILE* source) {
	try {
		char buffer;
		std::vector<char> ret;
		while ((buffer = std::fgetc(source)) != EOF) {
			ret.push_back(buffer);
		}
		return ret;
	} catch (exception ex) {
		std::cout << ex.what( ) << std::endl;
		system("pause");
	}
}

void run_program(std::vector<char> source) {
	try {
		int memory_ptr = 0, code = 0;
		std::vector<char> memory(4096, 0);
		int loop = 0;
		while (code < source.size( )) {
			char i = source.at(code);
			if (i == '>')
				memory_ptr++;
			else if (i == '<')
				memory_ptr--;
			else if (i == '+')
				memory.at(memory_ptr)++;
			else if (i == '-')
				memory.at(memory_ptr)--;
			else if (i == '.')
				std::cout << memory.at(memory_ptr);
			else if (i == ',')
				std::cin >> memory.at(memory_ptr);
			else if (i == '[' && memory.at(memory_ptr) != 0)
				loop = code;
			else if (i == ']' && loop != 0 && memory.at(memory_ptr))
				code = loop - 1;
			code++;
		}
		return;
	} catch (exception ex) {
		std::cout << ex.what( ) << std::endl;
		system("pause");
	}
}

int32_t main(const int argc, const char** argv, const char** env) {
	try {
		if (argc != 2) {
			std::cout << "Usage : brain fuck File" << std::endl;
			system("pause");
			return EXIT_FAILURE;
		}
		FILE* source = NULL;
		source = std::fopen(argv[1], "r");
		if (source == NULL) {
			std::cout << "Error : Could not open brain fuck source file" << std::endl;
			system("pause");
			return EXIT_FAILURE;
		}
		std::vector<char> contents(source_read(source));
		if (contents.empty( )) {
			std::cout << "Error : Reading source file failure" << std::endl;
			system("pause");
			return EXIT_FAILURE;
		} else {
			if (contents.size( ) >= 4096) {
				std::cout << "File size is too big !" << std::endl;
				system("pause");
				return EXIT_FAILURE;
			} else {
				run_program(contents);
			}
		}
		std::cout << "\n\n" << std::endl;
	} catch (exception ex) {
		std::cout << ex.what( ) << std::endl;
	}

	system("pause");
	return EXIT_SUCCESS;
}
