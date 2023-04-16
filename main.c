#include "stdlib.h"
#include "stdio.h"

#define bool32_t int32_t
#ifndef TRUE
   #define TRUE  (bool32_t)(1)
   #define FALSE (bool32_t)(0)
#endif

// Function prototypes
bool32_t allocateTheArray( int32_t numItems, int32_t **arrayToAllocate );
void freeTheArray( int32_t **arrayToFree );
bool32_t allocateNumbers( int32_t  numNums, int32_t **numbersArray );
bool32_t allocateCars( int32_t  numCars, int32_t **carsArray, int32_t *numbersArray );
void freeTheNumbers( int32_t **numbersArray );
void freeTheCars( int32_t **carsArray );
bool32_t doNumbersAndCars( void );
bool32_t doNumbers( int32_t numNums, int32_t **numbersArray );
bool32_t doCars( int32_t numCars, int32_t **carsArray, int32_t *numbersArray );

// Function bodies
bool32_t allocateTheArray( int32_t numItems, int32_t **arrayToAllocate )
{
   return( (*arrayToAllocate = (int32_t*) calloc( numItems,sizeof(int32_t) )) != NULL );
}

void freeTheArray( int32_t **arrayToFree )
{
   if( arrayToFree != NULL )
      if( *arrayToFree != NULL )
      {
         free( *arrayToFree );
         *arrayToFree = NULL;
      }
   return;
}

bool32_t allocateNumbers( int32_t  numNums, int32_t **numbersArray )
{
   bool32_t  returnStatus = FALSE;
   if( numbersArray != NULL )
      if( (returnStatus = allocateTheArray( numNums, numbersArray )) )
         for( int32_t i = 0; i < numNums; ++i )
            (*numbersArray)[i] = 123 * (i+1);
      else
         perror("Unable to allocate the numbersArray!");
   else
      perror("Invalid numbersArray - NULL pointer!");
   return( returnStatus );
}

bool32_t allocateCars( int32_t  numCars, int32_t **carsArray, int32_t *numbersArray )
{
   bool32_t  returnStatus = FALSE;
   if( carsArray != NULL )
      if( (returnStatus = allocateTheArray( numCars, carsArray )) )
         if( numbersArray != NULL )
            for( int32_t i = 0; i < numCars; ++i )
               (*carsArray)[i] = numbersArray[i] * 4;
         else
            for( int32_t i = 0; i < numCars; ++i )
               (*carsArray)[i] = 456 * (i+1);
      else
         perror("Unable to allocate the carsArray!");
   else
      perror("Invalid carsArray - NULL pointer!");
   return( returnStatus );
}

void freeTheNumbers( int32_t **numbersArray )
{
   freeTheArray( numbersArray );
   return;
}

void freeTheCars( int32_t **carsArray )
{
   freeTheArray( carsArray );
   return;
}

bool32_t doNumbers( int32_t numNums, int32_t **numbersArray )
{
   bool32_t    returnStatus = FALSE;
   if( allocateNumbers(numNums, numbersArray ) )
   {
      for( int32_t i = 0; i < numNums; ++i )
         fprintf(stdout,"numbersArray[%2.2d] = %d\n",i,(*numbersArray)[i]);
      returnStatus = TRUE;
   }
   return( returnStatus );
}

bool32_t doCars( int32_t numCars, int32_t **carsArray, int32_t *numbersArray )
{
   bool32_t    returnStatus = FALSE;
   if( numbersArray != NULL && allocateCars(numCars, carsArray, numbersArray) )
   {
      for( int32_t i = 0; i < numCars; ++i )
         fprintf(stdout,"carsArray[%2.2d] = %d\n",i,(*carsArray)[i]);
      freeTheCars( carsArray );
      returnStatus = TRUE;
   }
   return( returnStatus );
}

bool32_t doNumbersAndCars( void )
{
   bool32_t     returnStatus = FALSE;
   int32_t	*numbers     = NULL;
   int32_t	*cars        = NULL;
   int32_t	numOfNumbers = 100;
   int32_t	numOfCars    = 8;

   if( doNumbers(numOfNumbers, &numbers) )
   {
      returnStatus = (doCars(numOfCars, &cars, numbers) ? TRUE : returnStatus);
      freeTheNumbers( &numbers );
   }
   return( returnStatus );
}

int main( int argc, char** argv )
{
   int          rc = -99;
   char		*aStr;
   size_t	stringSize = 32;

   if( (aStr = (char*) calloc(stringSize, sizeof(char))) != NULL )
   {
      snprintf(aStr,(stringSize-1),"I am the aStr string\n");
   }
   else  // Error case - string
      perror("Unable to allocate a string");

   return( doNumbersAndCars() ? 0 : rc );
}
