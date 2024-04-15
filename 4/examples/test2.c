int printf(char const *format, ...);

int factorial(int n)
{
	if (n <= 0){
		return 1;
	}
	else{
		return n*factorial(n-1);
	}
}

int fibonacci(int a, int b, int n)
{
	if (n <= 0)
		return a;

	while (n > 0) {
		int t;
		t = b;
		b = a+b;
		a = t;
		n = n-1;
	}
	return b;
}

int main()
{
	// int f1 = factorial(1);
	// int f3 = factorial(3);
	// int f5 = factorial(5);
	// int f6 = factorial(6);

	// printf("%d %d %d %d\n", f1, f3, f5, f6);
	
  return fibonacci(factorial(1), factorial(2), factorial(5));
}
