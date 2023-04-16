#include "stdlib.h"
#include "stdio.h"

int main( int argc, char** argv )
{

   char		*aStr;
   int32_t	*numbers;
   int32_t	*cars;
   int32_t	numOfNumbers;
   int32_t	numOfCars;
   size_t	stringSize = 32;

   if( (aStr = (char*) calloc(stringSize, sizeof(char))) != NULL )
   {
      snprintf(aStr,(stringSize-1),"I am the aStr string\n");
      numOfNumbers = 100;
      if( (numbers = (int32_t*) calloc( numOfNumbers,sizeof(int32_t) )) != NULL )
         for( int32_t i = 0; i < numOfNumbers; ++i )
            numbers[i] = 123 * (i+1);

      numOfCars = 8;
      if( (cars = (int32_t*) calloc( numOfCars, sizeof(int32_t) )) != NULL )
      {
         for( int32_t i = 0; i < numOfCars; ++i )
            cars[i] = numbers[i] * 4;
      }
   }
   else  // Error case
   {
      perror("Unable to allocate a string");
   }

   return( 0 );
}
