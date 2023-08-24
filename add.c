#include <stdio.h>

/**
 * main - entry point
 * description: adding two given numbers
 * Return: 0 always
 *
 */
int main(void)
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
