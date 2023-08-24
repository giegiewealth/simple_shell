#include <stdio.h>

int alternative_main(void)
{
	int a;
	int b;
	int sum;

	printf("Enter the first number\n");
	scanf("%d", &a);
	printf("Enter the second number\n");
	scanf("%d", &b);

	sum = a + b;
	printf("The sum of %d and %d is %d\n", a, b, sum);

	return (0);
}
