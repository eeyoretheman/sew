#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char** argv)
{
	char* input = NULL;
	char* output = NULL;
	char* action = NULL;
	char* arguments[2] = {NULL};
	unsigned int last_argument = 0;

	for (int i = 1; i < argc; i++) {
		if (
			strcmp(argv[i], "-h") == 0 ||
			strcmp(argv[i], "--help") == 0
		) {
			fprintf(
				stderr,
				"help message.\n"
			);
			return 0;
		} else if (
			strcmp(argv[i], "-v") == 0 ||
			strcmp(argv[i], "--version") == 0
		) {
			fprintf(
				stderr,
				"sew@0.0.0\n"
				"25-12-2025\n"
				"by Yordan Todorov"
			);
			return 0;
		} else if (
			strcmp(argv[i], "-i") == 0 ||
			strcmp(argv[i], "--input") == 0
		) {
			input = argv[i+1];
		} else if (
			strcmp(argv[i], "-o") == 0 ||
			strcmp(argv[i], "--output") == 0
		) {
			output = argv[i+1];
		} else if (!action) {
			action = argv[i];
		} else {
			arguments[last_argument++] = argv[i];
		}
	}

	if (strcmp(action, "out") == 0) {
		unsigned long long slice_start = 0;
		unsigned long long slice_end = 0xffffffffffffffff;

		if (strcmp(arguments[0], "-") != 0) {
			sscanf(arguments[0], "%llx", &slice_start);
		}

		if (strcmp(arguments[1], "-") != 0) {
			sscanf(arguments[1], "%llx", &slice_end);
		}

		FILE* input_file = stdin;
		FILE* output_file = stdout;

		if (input) {
			input_file = fopen(input, "r");
		}

		if (output) {
			output_file = fopen(output, "r");
		}

		char buffer[BUFFER_SIZE];

		fseek(input_file, slice_start, SEEK_SET);

		for (int i = 0; i < ((slice_end - slice_start) / BUFFER_SIZE) + 1; i++) {
			size_t read_bytes = 0;

			if (slice_end - slice_start < BUFFER_SIZE) {
				read_bytes = fread(buffer, 1, slice_end - slice_start, input_file);
			} else {
				read_bytes = fread(buffer, 1, BUFFER_SIZE, input_file);
			}

			fwrite(buffer, 1, read_bytes, output_file);
		}
	} else if (strcmp(action, "in") == 0) {

	} else {
		fprintf(stderr, "Unknown action. Use one of 'in' or 'out'.\n");
		return 1;
	}

        return 0;
}
