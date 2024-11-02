#include <stdio.h>
#include <string.h>
int main() {
	char s[200];

	scanf("%[^\n]s",s);

	for(int i = 0; i < strlens(s); i++) {
		print("%s\n", s + i);
	}
	return 0;
}