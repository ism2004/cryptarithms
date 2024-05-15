#include <stdio.h>
#include <math.h>

#define MAXLEN 20

char word1[MAXLEN] = {0};
char word2[MAXLEN] = {0};
char word3[MAXLEN] = {0};

int num1[MAXLEN] = {-1};
int num2[MAXLEN] = {-1};
int num3[MAXLEN] = {-1};

int map[MAXLEN] = {-1};

char letters[MAXLEN] = {0};
int numbers[MAXLEN] = {-1};

//filling massives
void fillfirstly()
{
    for (int i = 0; i < MAXLEN; i++)
    {
        word1[i] = 0;
        word2[i] = 0;
        word3[i] = 0;
        num1[i] = -1;
        num2[i] = -1;
        num3[i] = -1;
        map[i] = -1;
        letters[i] = 0;
        numbers[i] = -1;
    }
}

//real number of chars in a massive
int len(char x[])
{
    int i;
    for (i = 0; x[i] != '\0'; i++);
    return i;
}

//turning backwards
void towords(char w1[], char w2[], char w3[])
{
    int i = len(w2) - 1;
    for (int j = 0; i >= 0; i--, j++)
    {
        word1[j] = w2[i];
    }

    i = len(w3) - 1;
    for (int j = 0; i >= 0; i--, j++)
    {
        word2[j] = w3[i];
    }

    i = len(w1) - 1;
    for (int j = 0; i >= 0; i--, j++)
    {
        word3[j] = w1[i];
    }
}

//radix of a number
void makeamap()
{
    int m = len(word3);
    for (int i = 0; i < m; i++)
    {
        map[i] = pow(10,i);
    }
}

int isinthere(char x)
{
    for (int i = 0; i < len(letters); i++)
    {
        if (letters[i] == x) return 0;
    }
    return 1;
}

//all letters in order we need
void alletters()
{
    int j = 0;
    for (int i = 0; i < len(word3); i++)
    {
        if ((word1[i] != '\0') && (isinthere(word1[i])))
        {
            letters[j] = word1[i];
            j++;
        }
        if ((word2[i] != '\0') && (isinthere(word2[i])))
        {
            letters[j] = word2[i];
            j++;
        }
        if ((word3[i] != '\0') && (isinthere(word3[i])))
        {
            letters[j] = word3[i];
            j++;
        }
    }
}

//putting number of a letter in all words at the same time
void put(char let, int num)
{
    for (int i = 0; i < len(word1); i++)
    {
        if (word1[i] == let) num1[i] = num;
    }

    for (int i = 0; i < len(word2); i++)
    {
        if (word2[i] == let) num2[i] = num;
    }

    for (int i = 0; i < len(word3); i++)
    {
        if (word3[i] == let) num3[i] = num;
    }

    for (int i = 0; i < len(letters); i++)
    {
        if (letters[i] == let) numbers[i] = num;
    }
}

//checking if it already has a number
int checknum(int num)
{
    for (int i = 0; i < len(word1); i++)
    {
        if (num1[i] == num) return 0;
    }
    for (int i = 0; i < len(word2); i++)
    {
        if (num2[i] == num) return 0;
    }
    for (int i = 0; i < len(word3); i++)
    {
        if (num3[i] == num) return 0;
    }
    return 1;
}

//a number of radixes which are already there
int rasr()
{
    int r1 = -1;
    int r2 = -1;
    int r3 = -1;
    for (int i = 0; i < len(word1); i++)
    {
        if (num1[i] > -1) r1 = i;
        else break;
    }
    for (int i = 0; i < len(word2); i++)
    {
        if (num2[i] > -1) r2 = i;
        else break;
    }
    for (int i = 0; i < len(word3); i++)
    {
        if (num3[i] > -1) r3 = i;
        else break;
    }
    if ((r1 == (len(word1)-1)) && (r2 == (len(word2)-1)) && (r3 == (len(word3)-1))) return r3;
    if ((r1 <= r2) && (r1 <= r3)) return r1;
    if ((r2 <= r1) && (r2 <= r3)) return r2;
    if ((r3 <= r2) && (r3 <= r1)) return r3;
}

//checking if the solution is right
int checksumm()
{
    int summ1 = 0;
    int summ2 = 0;
    int summ3 = 0;
    int ras = rasr();
    if (ras != -1)
    {
        for (int i = 0; i <= ras; i++)
        {
            if (num1[i] != -1) summ1 += (num1[i]*map[i]);
            if (num2[i] != -1) summ2 += (num2[i]*map[i]);
            summ3 += (num3[i]*map[i]);
        }
        if ((summ1 + summ2 == summ3) || ((ras < len(word3)-1) && (summ1 + summ2 == (summ3 + map[ras+1])))) return 1;
        else return 0;
    }
    else return -1;
}

int zerocheck(char let)
{
    if ((word1[len(word1)-1] == let) || (word2[len(word2)-1] == let) || (word3[len(word3)-1] == let)) return 0;
    else return 1;
}

//minumal number we can put
int minnum(int bef, char let)
{
    for (int i = 0; i < 10; i++)
    {
        if ((i > bef) && (checknum(i)) && ((i != 0) || (zerocheck(let)))) return i;
    }
    return -1;
}

void try(int n)
{
    int mn;
    if ((n < len(letters)) && (n != -1))
    {
        mn = minnum(numbers[n],letters[n]);
        put(letters[n], mn);
        if (mn == -1)
        {
            try(n-1);
        }
        else
        {
            if ((checksumm() == 1) || (checksumm() == -1)) try(n+1);
            else try(n);
        }
    }
}

void printanswer()
{
    if (checksumm())
    {
        for (int i = len(word3)-1; i >= 0; i--) printf("%d",num3[i]);
        printf(" - ");
        for (int i = len(word1)-1; i >= 0; i--) printf("%d",num1[i]);
        printf(" = ");
        for (int i = len(word2)-1; i >= 0; i--) printf("%d",num2[i]);
        printf("\n");
    }
    else
    {
        printf("Solution does not exist\n");
    }
}

int main()
{
    char w1[MAXLEN];
    char w2[MAXLEN];
    char w3[MAXLEN];
    printf("Type the first word: ");
    scanf("%s",&w1);
    printf("Type the second word: ");
    scanf("%s",&w2);
    printf("Type the third word: ");
    scanf("%s",&w3);
    fillfirstly();
    towords(w1,w2,w3);
    makeamap();
    alletters();
    if ((len(word3) < len(word1)) || (len(word3) < len(word2)))
    {
        printf("Solution does not exist\n");
    }
    else
    {
        try(0);
        if ((num1[0] == -1) || (num2[0] == -1) || (num3[0] == -1))
        {
            printf("Solution does not exist\n");
        }
        else
        {
            printf("Answer: \n");
            printanswer();
        }
    }

    return 0;
}
