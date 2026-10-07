#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *src, *dst;
	int c;

	if(argc != 3){
		fprintf(stderr, "Usage: %s <SourceFile> <DestinationFile>\n", argv[0]);
		exit(1);
	}

	src = fopen(argv[1], "r");
	if(srt == NULL){
		perror("Source file open error");
		exit(2);
	}

	dst = fopen(argv[2], "w");
	if(dst == NULL){
		perror("Destination file open error");
		fclose(src);
		exit(3);
	}

	while((c = fgetc(src)) != EOF) {
		fputc(c, dst);
	}

	fclose(src);
	fclose(dst);

	printf("File copy completed successfully.\n");
	return 0;
}
