 // Dane Halle (dmh148)
 #include <stdio.h>
 int main()
 {
     int x = 10;
	printf("sizeof(x) = %d\n", (int)sizeof(x));
	printf("sizeof(int) = %d\n", (int)sizeof(int));
	printf("sizeof(char) = %d\n", (int)sizeof(char));
	printf("sizeof(unsigned int) = %d\n", (int)sizeof(unsigned int));
    printf("sizeof(short) = %d\n", (int)sizeof(short));
	printf("sizeof(long) = %d\n", (int)sizeof(long));
	printf("sizeof(long long) = %d\n", (int)sizeof(long long));
	printf("sizeof(float) = %d\n", (int)sizeof(float));
	printf("sizeof(double) = %d\n", (int)sizeof(double));
	printf("sizeof(int*) = %d\n", (int)sizeof(int*));
	printf("sizeof(&x) = %d\n", (int)sizeof(&x));
	printf("sizeof(int**) = %d\n", (int)sizeof(int**));
	printf("sizeof(double**) = %d\n", (int)sizeof(double**));
	printf("sizeof(char**) = %d\n", (int)sizeof(char**));

	char a[10];
        int b[10];
        int* c = b;
	printf("sizeof(a) = %d\n", (int)sizeof(a));
	printf("sizeof(b) = %d\n", (int)sizeof(b));
	printf("sizeof(c) = %d\n", (int)sizeof(c));
	printf("sizeof(&a) = %d\n", (int)sizeof(&a));
	printf("sizeof(&b) = %d\n", (int)sizeof(&b)); 
}
