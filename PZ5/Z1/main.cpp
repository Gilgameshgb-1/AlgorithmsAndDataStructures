#include <iostream>

int fib2_0(int n,int a = 0,int b = 1)
{
    if (n==0) return a;
    if (n==1) return b;// 0 i 1
    return fib2_0(n - 1, b, a + b);
}

int nzd(int x, int y)
{
    if(y==0) return x;
    else return nzd(y,x%y);
}

//neke random stvari sa predavanja

int faktorijel(int n)
{
    if(n==0) return 1;
    else {
        int ulaz = n-1;
        int s1 = faktorijel(ulaz);
        int s = n*s1;
        return s;
    }
}

int sumadon(int n)
{
    if(n==1) return 1;
    else {
        int suma = n + sumadon(n-1);
    }
}

void Hanojski_tornjevi(int n,int S,int D,int T)
{
    if(n==1) {
        std::cout<<"Preseliti disk 1 sa stapa S na stap D\n";
        return;
    }
    Hanojski_tornjevi(n-1,S,T,D);
    std::cout<<"Preseliti disk " << n<< " sa stapa S na stap T\n";
    Hanojski_tornjevi(n-1,T,D,S);
    return;
}




int main()
{
    //std::cout<<faktorijel(4);
    //std::cout<<sumadon(5);
    //Hanojski_tornjevi(3,2,2,2);
    return 0;
}
