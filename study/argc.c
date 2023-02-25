#include <stdio.h>

long long	func()
{
	int a = 3;
	long long	b = 2;
	return (a - b);
}

int main(int argc, char **argv)
{
	printf("%lld\n", func());
}