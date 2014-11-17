#include <stdio.h>
#include <stdlib.h>

int main(){
  //printf("%d", 5%2);
  printf("%d\n", multThreeFive());
  printf("%d\n", fibNum());
  printf("%d\n", sumSquareDiff());
}
//Problem 1
int multThreeFive(){
  int counter = 0;
  int sum = 0;
  while (counter < 1000){
    if ((counter % 3) == 0 || (counter%5) == 0){
      sum = sum + counter;
      counter++;
    }
    else {
      counter++;
    }
  }
  return sum;
}

//Problem 2
int fibNum(){
  int counter = 1;
  int counter2 = 2;
  int sum = 2;
  while (counter <= 4000000){
    counter = counter + counter2; 
    counter2 = counter2 + counter;
    if (counter%2 == 0){
      sum = sum+counter;
	}
    if (counter2%2 == 0){
      sum = sum+counter2;
	}
  }
  return sum;
    }

//Problem 6
int sumSquareDiff(){
  int counter = 1;
  int sumSquare = 0;//sum of squares
  int squareSum = 0;//square of sums
  while (counter <= 100){
    sumSquare = sumSquare + counter*counter;
    squareSum = squareSum + counter;
    counter++;
  }
  squareSum = squareSum * squareSum;
  int diff = sumSquare - squareSum;
  return diff;
}
