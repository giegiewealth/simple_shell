#include <stdio.h>

/**
 * main - enter two numbers
 *
 * Description: adding two given numbers
 * Return: 0
 */

int main(void)
{
	int a;
	int b;
	int sum;

	printf("Enter two numbers\n");
	scanf("%d", &a);
	scanf("%d", &b);
	sum = a + b;
	printf("The sum of %d and %d is %d\n", a, b, sum);

	return (0);
}
