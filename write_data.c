#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fp;
	if((fp=fopen("write_txt.txt","wb"))==NULL)
	{
		printf("\nopen file Fail,close!");
		getchar();
		exit(1);
	}
	fputs("Hello world123",fp);
	fclose(fp);	
	
	return 0;
}
