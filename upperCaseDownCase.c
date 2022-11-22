// Faça um programa que leia uma frase de 300 caracteres e seja impressa a quantidade de letras maiúsculas e minúsculas nessa frase. Utilize a mascara de leitura “%[^\n]”. Considere os valores decimais da tabela ASCII A=65, Z=90,a= 97 e z=122.

#include <stdio.h>
#include <stdlib.h>

int main() {
  int upper_case = 0, down_case = 0, unknown = 0;
  char phrase[300] = "";
  scanf("%[^\n]", phrase);
  for (int i = 0; i < sizeof(phrase); i++) {
    if (phrase[i] >= 65 && phrase[i] <= 90) {
      upper_case++;
    }
    if (phrase[i] >= 97 && phrase[i] <= 122) {
      down_case++;
    }
    else {
      unknown++;
    }
  }
  printf("UpperCase: %d DownCase: %d Unknown: %d", upper_case, down_case, unknown);
}