#include <stdio.h>

int main(int argc, char const *argv[]){
	int n, i, j;
	unsigned char zero = 0;
	unsigned char um = 1;

	scanf("%d", &n);

	printf("%d 1 1 %d %d\n", n, 2, 1);

	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(i == 0 || i == n-1 || j == 0 || j == n-1){
				if(j == n-1) printf("%hhu\n", um);
				else printf("%hhu ", um);
			}
			else printf("%hhu ", zero);
		}
	}
	return 0;
}