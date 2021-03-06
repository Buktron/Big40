/*“I [] ([]) affirm that this program is entirely my own work and that I have
neither developed my code together with any another person, nor copied any code from any other person,
nor permitted my code to be copied or otherwise used by any other person, nor have I copied, modified, or
otherwise used program code that I have found in any external source, including but not limited to, online
sources. I acknowledge that any violation of the above terms will be treated as academic dishonesty.”*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "big40.h"


char *cryptoVariableFilename; // for the filename

int seed;//to seed the RNG or not

int nFib; //control the number of Fibonacci numbers to calculate

Integer40 *cryptoVariable; // 40 digits of used to start the F[x]

Integer40 *hwConfigVariable; // 40 digits of psuedo or real
                             // randomness to start the F[x]
// Functional Prototypes

Integer40 *big40Add(Integer40 *p, Integer40 *q)
{
	int i = 0;
	int catbug = 0; // carry from resultant of most significant digits (MSD).

	if(p == NULL || q == NULL)
		return NULL;

	Integer40 *sum = malloc(sizeof(Integer40) * MAX40);
	sum->digits = calloc(MAX40, sizeof(int));

	if(sum == NULL)
		return NULL;

	for(i = 0; i < MAX40; i++)
	{
		catbug = p->digits[i] + q->digits[i];
		if(catbug <= 10)
		{
			sum->digits[i] = catbug;
			i++;
		}
		else
		{
			while(catbug > 10 && i < MAX40)
			{
				sum->digits[i] = catbug % 10;
				i++;

				if(i < MAX40)
				{
					catbug = p->digits[i] + q->digits[i] + 1;

					if(catbug < 10)
					{
						sum->digits[i] = catbug;
						i++;
					}
				}
			}
		}
		//sum->digits[i] = p->digits[i] + q->digits[i];

		// If there is a carry 
		/*if(sum->digits[i] > 9)
		{
			carry = sum->digits[i] / 9;
			sum->digits[i] %= 10;
		}
		else
		{
			carry = 0;
		}*/		
	}
	
	return sum;

}

Integer40 *big40Destroyer(Integer40 *p)
{
	if(p == NULL)
		return	NULL;
	else
		free(p);

		// free(p->digits); // This does a double free memory crash, 
		// I am unable to free both. I don't know why, 
		// please post solution to this problem.
		 
	return p; // "p" will be freed and return NULL. 
}

Integer40 *fibBig40(int n, Integer40 *first, Integer40 *second)
{
	int i =0, j = 0;
	int fibArray1[0], fibArray2[1];

	Integer40 *fib40 = malloc(sizeof(Integer40));
	fib40->digits = calloc(MAX40, sizeof(int));
	
	if(fib40 == NULL)
		return NULL;


}

void big40Rating(void)
{
	/*float difficulty = 5.0;
	float time = 35.5;
	char NID [] = "JA257871";
	big40RatingStruct *Deets = malloc(sizeof(big40RatingStruct));
	Deets->NID = malloc(sizeof(char)* 9);
	strcpy(Deets->NID, NID);
	Deets->degreeOfDifficulty = difficulty;
	Deets->duration = time;*/
	fprintf(stderr,"NID:JA257871, Rating:5.0, Difficulty:35.5\n" );

}
int convertValue(char x)
{
	if((x >= 48) && (x <= 57))
			return x - 48;

	if((x >= 65) && (x <= 78))
		return x - 55;
	
	if((x >= 97) && (x <= 102))
		return x - 87;
}

Integer40 *parseString(char *str)
{
	int i = 39, j = 0;
	int parse_length;
	Integer40 *parse = malloc(sizeof(Integer40)* MAX40 + 1);

	if(str == NULL)
	{
		return NULL; 
	}
	else if(parse == NULL)
	{
		fprintf(stderr, "ERROR: parseString failed to allocate memory.\n");
		return NULL;
	}
	
	//parse_length is the length of str
	parse_length = strlen(str);
	// Malloc space for digits
	parse->digits = calloc(MAX40, sizeof(int));
	//Parse thru the string backwards
	//for(i = parse_length - 1; i >= 0; i--)
	//{
		
		if(parse_length > MAX40)
		{
			for(j= 0; j <= MAX40; j++)
			{
				/*parse->digits[39-j] = convertValue(str[parse_length - parse_length + j]);
				if((parse_length - parse_length + j)>=39);
					break;*/
					parse->digits[j] = convertValue(str[i--]);
				if(parse_length-1-j <= 0)
					break;
			}
		}
		else if(parse_length <= MAX40)
		{
			for(j = 0; j < MAX40; j++)
			{
				parse->digits[j] = convertValue(str[parse_length-1-j]);
				if(parse_length-1-j <= 0)
					break;
			}
		}
		else if(parse_length < MAX40)
		{
			fprintf(stderr, "Under 40 digits!\n");
		}
	//}

	return parse;
}

Integer40 *loadHWConfigVariable(int doSeed)
{
	int i = 0, j = 0, randValue = 0;
	int digiArray[5];
	Integer40 *seed = malloc(sizeof(Integer40)* MAX40);
	seed->digits = calloc(40, sizeof(int)); 
	if(seed == NULL)
		return NULL;
	
	srand(time(NULL)); // random numbers generated from CPU system.

	// If false give set generated number
	if(doSeed == 0) 
	{

		for(i = 0; i < 5; i++)
		{
			randValue = rand() % 10;
			digiArray[i] = randValue;
		}
		for(j = 0; j < MAX40; j++)
		{
			seed->digits[j] = digiArray[j%5];
		}
	}

	// If true, give random number generated by system -> srand()
	else if(doSeed == 1)
	{
		for(i = 0; i < MAX40; i++)
		{
			seed->digits[i] = rand() % 16;
		}
	}
	return seed;
}

Integer40 *loadCryptoVariable(char *inputString)
{
	char *buffer[1024];
	Integer40 *crypto = malloc(sizeof(Integer40));
	crypto->digits = calloc(MAX40, sizeof(int));
	
	// If crypto memory allocation fails
	if(crypto == NULL)
		return NULL;

	FILE *ifp = fopen("cryptoVarFile", "r");

	if(fopen("cryptoVarFile", "r") == NULL)
	{
		printf("ERROR: cryptoVarFile failed to open.\n");
		return NULL;
	}
	
	if(ifp == NULL)
		return NULL;

	while(fgets(buffer, 256, ifp))
	{
		puts(buffer);
		crypto->digits = *buffer;
	}

	fclose(ifp);

	return crypto;
}
