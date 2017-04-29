#include <stdio.h>
void main()
{
  FILE *fp;
  fp = fopen("24c04.bin","wb");
  fwrite("123456",1,6,fp);
  fclose(fp);
}