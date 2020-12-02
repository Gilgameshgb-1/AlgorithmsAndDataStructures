#include <iostream>

bool DaLiJeProst(int n)
{
    int c = 0;
    for(int i = 2; i<=n/2; i++) {
        if(n%i==0) c=1;
    }
    if(c==1) return false;
    return true;
}

void ProstiBrojevi(int n)
{
    for(int i = 2; i<=n; i++) {
        if(DaLiJeProst(i)==true) std::cout<<"\nProst broj: "<< i;
    }
}
// n * n/2 = O(n^2) kompleksnost?, moguce imati O(n^3/2) kompleknost

bool DaLiJeProstBolji(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

void ProstiBrojeviBolji(int n){
    for(int i = 2;i<=n;i++){
        if(DaLiJeProstBolji(i)) std::cout<<"\nOvo je prost broj: "<<i;
    }
}

//Vremenska kompleksnost ovog rjesenja je n^(3/2) jer ide n puta kroz petlju a unutar petlje ide sqrt(n) => sqrt(n)*n = n^(3/2)

int main()
{
    //ProstiBrojevi(100);
    ProstiBrojeviBolji(100);
    return 0;
}
