#include <iostream>
#include <ctime>

int SumaFaktorijela(int n)
{
    int s=0;
    int fact=1;
    for(int i = 1; i <= n; i++) {
        fact = 1;
        for (int j = 1; j <= n; j++) {
            fact = fact * j;
        }
        s+=fact;
    }
    return s;
}

//O(n^2) kompleksnost

int main()
{
    
}
