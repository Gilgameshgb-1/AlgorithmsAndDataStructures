#include <iostream>
#include <ctime>

int Funkcija(int n)
{
    int s=0;
    for( int i = n; i > 0; i-=2) {
        for( int j = 0; j < 2*n; j++ ) {
            for( int k = 0; k < n; k++) {
                s+=k;
            }
        }
    }
}

// n/2 * 2n * n = O(n^3)

int main()
{

    //O(n^3)
}
