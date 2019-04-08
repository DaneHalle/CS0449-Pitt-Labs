//Dane Halle (dmh148)
#include <stdio.h>
#include <dlfcn.h>
#include <ctype.h>
#include <stdlib.h>

int streq_nocase(const char* a, const char*b) {
	for(; *a && *b; a++, b++) if(tolower(*a) != tolower(*b)) return 0;
	return *a == 0 && *b == 0;
}

void* lib;
unsigned long (*compressBound)(unsigned long length);
int (*compress)(void *dest, unsigned long* destLen,
		const void* source, unsigned long sourceLen);
int (*uncompress)(void *dest, unsigned long* destLen,
		const void* source, unsigned long sourceLen);

void errorChecking(int argc, char** argv)
{
	if(argc<3){
		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		printf("(You have too few arguments)\n");
		exit(1);
	}else if(!streq_nocase(argv[1], "-c") && !streq_nocase(argv[1], "-d")){
		printf("AaaaAaAAAAAaaAaaaA\n");
		printf("(Invalid first argument. Do \"-d\" or \"-c\")\n");
		exit(1);
	}

	lib = dlopen("libz.so", RTLD_NOW);
	if(lib==NULL){
		printf("aAaaaAaaaAaaaAaaaAaaa\n");
		printf("(Cannot load the library)\n");
		exit(1);
	}

	compressBound=dlsym(lib, "compressBound");
	if(compressBound==NULL){
		printf("AaaaaaAaaAaaaaaAaaAaaaa\n");
		printf("(Cannot load function compressBound)\n");
		exit(1);
	}

	compress=dlsym(lib, "compress");
	if(compress==NULL){
		printf("aaaAAaaaaaAaaaaaaAAAAAA\n");
		printf("(Cannot load function compress)\n");
		exit(1);
	}

	uncompress=dlsym(lib, "uncompress");
	if(uncompress==NULL){
		printf("AAAAAAAAaaaaaaaaa\n");
		printf("(Cannot load function uncompress)\n");
		exit(1);
	}
}

void compressFile(FILE* f)
{
	fseek(f, 0, SEEK_END);
	unsigned long length=ftell(f);
	fseek(f, 0, SEEK_SET);

	void* inputBuffer=malloc(length);
	fread(inputBuffer, sizeof(length), length, f);

	unsigned long compressLength=compressBound(length);
	void* outputBuffer=malloc(compressLength);

	compress(outputBuffer, &compressLength, inputBuffer, length);

	fwrite(&length, sizeof(length), 1, stdout);
	fwrite(&compressLength, sizeof(compressLength), 1, stdout);
	fwrite(outputBuffer, compressLength, 1, stdout);
	fclose(f);
	exit(1);
}

void decompressFile(FILE* f)
{
	unsigned long uncompressedLength;
	fread(&uncompressedLength, sizeof(unsigned long), 1 , f);
	unsigned long compressLength;
	fread(&compressLength, sizeof(unsigned long), 1, f);

	void* inputBuffer=malloc(compressLength);
	fread(inputBuffer, sizeof(compressLength), compressLength, f);

	void* outputBuffer=malloc(uncompressedLength);

	uncompress(outputBuffer, &uncompressedLength, inputBuffer, compressLength);
	fwrite(outputBuffer, uncompressedLength, 1, stdout);

	fclose(f);
	exit(1);
}

int main(int argc, char** argv)
{
	errorChecking(argc, argv);

	FILE* f=fopen(argv[2], "rb");
	if(f==NULL){
		fprintf(stderr, "AaAaAaAaAaAaAa\n");
		fprintf(stderr, "(Cannot open file)\n");
		// fclose(f);
		exit(1);
	}
	
	if(streq_nocase(argv[1], "-c")){
		compressFile(f);
	}else if(streq_nocase(argv[1], "-d")){
		decompressFile(f);
	}

	return 0;
}