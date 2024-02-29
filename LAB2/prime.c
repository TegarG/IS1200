/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/



#include <stdio.h>

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

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
