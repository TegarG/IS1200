/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

int is_prime(int n){
  int t = 1;  //Vi antar att n är ett primtal och ändrar till 0 ifall det inte är det //Tegar
  int i = 2;
  while(i < n) //Kollar inte om n är delbart med n för då kommer t = 0 trots att n är ett primtal //Tegar
  {
    if(n % i == 0) //Delar n med i och om resten är 0 betyder att det är ett sammansatt tal //Henrietta
    {
      t = 0;  //Tegar
    }
    i++; //Henrietta
  }
  return t; //Henrietta
}

int print_number(int n){ 
  static int line = 1; // Deklarerar första gången men inte dem andra gångerna vilket gör att vi kan stega upp den varje gågn den kallas
  printf("%10d", n); //Tegar & Henrietta
  if(line == COLUMNS) //när line = 6 hoppar vi ner en rad //Tegar
  {
    printf("\n"); //Henrietta
    line = 0; //Tegar
  }
  line++; 
}

void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS
  for(int j = 2; j < n; j++) //Henrietta
  {
    if(is_prime(j) == 1) //Tegar
    {
    print_number(j); //Tegar & Henrietta 
    }
  }
  printf("\n");
}


// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
