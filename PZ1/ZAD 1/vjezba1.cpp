#include <iostream>
#include <ctime>

bool DaLiJePrirodan(int x)
{
    for(int i = 2; i <= x/2; i++) {
        if(x%i==0) return false;
    }
    return true;
}

void Goldbach(int n,int& p,int& q)
{
    if(n%2!=0 || (n%2==0 && n<=2)) throw std::domain_error("Netacan unos n-a");
    for(int i = 2; i<=n; i++) {
        if(DaLiJePrirodan(n%i)==true) {
            int z = i;
            int y = n-z;
            if(DaLiJePrirodan(z) && DaLiJePrirodan(y)) {
                p=z;
                q=y;
                return;
            }
        }

    }
    return;
}

int main()
{

    int n,p = 0,q = 0;
    clock_t vrijeme1 = clock();
    std::cout<<"\nUnesite neko n: ";
    std::cin>>n;

    try {
        Goldbach(n,p,q);
        std::cout<<"\np = "<<p;
        std::cout<<"\nq = "<<q;
    } catch(std::domain_error e) {
        std::cout<<e.what();
    }
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "\nVrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
    return 0;
}