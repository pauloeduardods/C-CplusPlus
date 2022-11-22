//Faça um programa que ao ser executado cria um arquivo com o nome dados.txt contendo na primeira linha qualquer coisa e na segunda um numero

#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fp;
  fp = fopen("dados.txt", "w");
  char text[] = "Ola caraio mano \n1\n";
  for (int i = 0; i < sizeof(text); i++) {
    fputc(text[i], fp); // Put character
  }
  fputs(text, fp); // Put string
  fclose(fp);
  return 0;
}