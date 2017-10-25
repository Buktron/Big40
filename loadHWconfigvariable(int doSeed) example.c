Integer40 *loadHWConfigVariable(int doSeed)
{
    Integer40 *temp = malloc(sizeof(Integer40) *MAX40);
    temp->digits = calloc (MAX40, sizeof(int));
    int i,j;
    if (doSeed == 0) {
        int randValue =0;
        int tmpArr[5];
        srand(time(NULL));
        
        for (i = 0; i < 5; i++)
        {
            randValue = rand() % 10;
            tmpArr[i] = randValue;
        }
        
        for(j = 0; j<MAX40 ; j++)
        {
            
            temp->digits[j] = tmpArr[j%5];
            
        }
    }
    
    
    else if(doSeed == 1)
    {
        srand(time(NULL));
        for (i=0; i<MAX40; i++) {
            temp->digits[i] = rand()%16;
        }
    }
    
    
    return temp;
}

void big40Print(Integer40 *p)
{
    int i;
    
    if (p == NULL)
    {
        printf("(null pointer)\n");
        return;
    }
    
    for (i = MAX40 - 1; i >= 0; i--)
        printf("%x", p->digits[i]);
    printf("\n");
}

Integer40* big40Destroyer(Integer40* p)
{

    free (p);
    
    return NULL;
}



int main(){
    
    Integer40 *p;
    
    big40Print(p = loadHWConfigVariable(0));
    big40Destroyer(p);
    big40Print(p = loadHWConfigVariable(1));
    big40Destroyer(p);
    
}
