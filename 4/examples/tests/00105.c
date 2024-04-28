int printf(const char *format, ...);

int
main()
{
	int i;

	for(i = 0; i < 10; i++){
		if (!i){
			printf("%d\n", i);
			continue;
		}
	}
	
	return 0;
}

// int main(){
// 	int i = 0;
// 	int j = i++;
// 	printf("%d\n", j);
// }