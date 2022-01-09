#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool o_flag = false;
char *out_name;

char *input_files[1024];
int num_input_files = 0;

static void usage(void)
{
	printf("\nger - A German programming language\n\n");
	printf("Usage:\n");
	printf("	./ger [input files]\n");
	printf("Flags:\n");
	printf("	-o [output file]		Specify a filename for the output file\n");
	exit(0);
}

static void parse_args(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		char *current = argv[i];

		if (strlen(current) != 0) {
			if (current[0] == '-') {
				switch (current[1]) {
					case 'o':
						o_flag = true;
						if (strlen(current) == 2) {
							if (i + 1 >= argc) {
								fprintf(stderr, "Error: No output filename given\n");
								exit(3);
							}
							out_name = malloc(strlen(argv[i+1]) + 1);
							memcpy(out_name, argv[i+1], strlen(argv[i+1]) + 1);
							i++;
						} else {
							out_name = malloc(strlen(current) - 1);
							memcpy(out_name, &current[2], strlen(&current[2]));
						}
						break;

					default:
						fprintf(stderr, "Error: Unexpected -%c in argument %d\n", current[1], i);
						exit(1);
				}
			} else {
				input_files[num_input_files] = malloc(strlen(current) + 1);
				memcpy(input_files[num_input_files], current, strlen(current) + 1);
				num_input_files++;
			}
		} else {
			fprintf(stderr, "Error: Invalid argument number %d\n", i);
			exit(2);
		}
	}
	
}

static void interpret(void)
{
	char *filename = input_files[0];
	FILE *file = fopen(filename, "r");
	int filesize;
	char *content;

	// TODO: Move file reading to separate function

	fseek(file, 0, SEEK_END);
	filesize = ftell(file);
	rewind(file);

	content = malloc(filesize);
	fread(content, filesize, 1, file);
	
	// TODO: Define keywords to interpret

	free(content);
	fclose(file);
}

int main(int argc, char **argv)
{
	if (argc == 1) usage();
	
	parse_args(argc, argv);

	if (num_input_files == 0) {
		fprintf(stderr, "Error: No input file specified\n");
		exit(4);
	}

	for (int i = 0; i < num_input_files; i++) {
		interpret();
	}
}