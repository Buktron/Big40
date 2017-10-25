// Code for seeding and parsing thru them 
// Implement this code in big40.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int value = 0;
    int i,j;  
    int randValue =0; 
    int tmpArray[5]; 
    int finalArray[40]; 
    srand(time(NULL)); 

        for (i = 0; i < 5; i++)
        {
            randValue = rand() % 10; // This gets numbers from 0 thru 9
            tmpArray[i] = randValue; // Because it's in a for loop of 5, 
            						 // this will only hold the first 5 digits
            printf("%d", tmpArray[i]);
        }
        printf("\n");

     	// This for loop with populate the finalArray of 40 elements of space
        for(j = 0; j < 40 ; j++)
        {
            
            // This takes in only the first 5 digits of tmpArray until of 40 elements
            // of finalArray are filled.
            finalArray[j] = tmpArray[j%5]; 
            printf("%d", finalArray[j]);
            
        }
        printf("\n");
    
    
    return 0; 
}

/*fgets(buffer, MAX40 + 1, fp); 
	for (i = 0; i < 40; i++)
	{
		tempArray->digits[39 - i] = conversion(buffer[i]);
	}
*/
