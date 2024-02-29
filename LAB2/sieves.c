
//#include "print-primes.c"
#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

int print_number(int n){ 
  static int line = 1;
  printf("%10d", n); //Tegar & Henrietta
  if(line == COLUMNS) //Tegar
    {
      printf("\n"); //Henrietta
      line = 0; //Tegar
    }
  line++;
}

void print_sieves(int n){

  // kopierar in alla värden från 2 upp till n in i en array, lämna platserna med index 0 & 1 tomma
  int arr[n];
  for(int i = 2; i < n; i++)
  {
    arr[i] = i;
  }
  
  for(int i = 2; i < n; i++)
  {
    int j = arr[i]*arr[i]; //j = i^2, vi behöver inte titta på tidigiare multiplar av i då vi redan har gjort det.
    if(arr[i] != 0) // 0 = sammansatt tal
    {   
      print_number(i);
      //sätter alla multiplar av i som 0 = sammansatt tal
      while(j < n)
      {
      arr[j] = 0;  //alla multiplar/sammansatta tal sätter vi som 0
      j+=i;  //går till nästa multipel av i
      }
    }
  }
  int count = 0;
  int k;
  for(int i = 2; i < n; i++)
  {
    if(arr[i] != 0)
    {
      k = i + 1;
      while(k < i+5)
      {
        if(arr[k] != 0)
        {
          if(arr[k] - arr[i] == 4)
          {
            count++;  
          }
          break;
        }
        k++;
      }
    }
  }
  //0 0 2 3 0 5 0 7 0 0 0 11 0 13 0 0 0 17 0 19 0 0 0 23*/
  printf("\n");
  printf("Number of times there is a distance of 4:%2d",count);
  printf("\n");
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

//Kan inte lagra för stora värden då den inte alokerar data för det.