#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int DajMaximum(std::vector<int> &a){
    int max = a[0];
    for(int i = 0;i<a.size();i++){
        if(a[i]>max) max = a[i];
    }
    return max;
}

void radixSort(std::vector<int> &a){
    int max = DajMaximum(a);
    int brojanje[10]{0};
    std::vector<int> kante;
    int expo = 1;
    
    kante.resize(a.size());

    while(max/expo > 0){
        //resetujemo brojanje
        for(int i = 0;i<10;i++){
            brojanje[i] = 0;
        }
        for(int i = 0;i<a.size();i++){
            int k = (a[i]/expo)%10; //izvlacimo cifre
            brojanje[k]++;
        }
        for(int i = 1;i<10;i++){
            brojanje[i] += brojanje[i-1];//ocuvanje pravih pozicija
        }
        for(int i = a.size()-1;i>=0;i--){
            int k = (a[i]/expo)%10;
            kante[brojanje[k]-1] = a[i];
            brojanje[k]--;
        }
        for(int i = 0;i<a.size();i++){
            a[i] = kante[i];
        }
        expo*=10;
    }
}

int LijevoDijete(int i){
    return 2*i+1;
}

int DesnoDijete(int i){
    return 2*i+2;
}

bool Je_li_list(int i,int vel){
    return (!(i>=vel/2) && (i<vel));
}

int Roditelj(int i){
    return (i-1)/2;
}

void Popravi_gore(vector<int> &a,int i){
    while((i!=0) && (a[i]>a[Roditelj(i)])){
        int temp = a[i];
        a[i] = a[Roditelj(i)];
        a[Roditelj(i)] = temp;
        i = Roditelj(i);
    }
}

void Popravi_dolje(vector<int> &a,int i,int vel){
    while(Je_li_list(i,vel)){
        int veci = LijevoDijete(i);
        int dd = DesnoDijete(i);
        if(dd<vel && a[dd] > a[veci]) veci = dd;
        if(a[i] > a[veci]) return;
        int temp = a[i];
        a[i] = a[veci];
        a[veci] = temp;
        i = veci;
    }
}

void umetniUGomilu(vector<int> &a, int umetnuti, int &velicina){
    if(velicina+1 > a.size()){
        a.resize(a.size()+1);
    }
    a[velicina] = umetnuti;
    velicina++;
    Popravi_gore(a,velicina-1);
}

int IzbaciPrvi(vector<int> &a){
    if(a.size()==0) throw;
    int temp = a[0];
    int vel = a.size();
    a[0] = a[--vel];
    a[--vel] = temp;
    a.resize(a.size()-1);
    if(a.size() != 0){
        Popravi_dolje(a,0,a.size());
    }
    return a[a.size()];
}


void stvoriGomilu(vector<int> &a){
    for(int i = a.size();i>=0;i--){
        Popravi_dolje(a,i,a.size());
    }
}

void gomilaSort(vector<int> &a){
    stvoriGomilu(a);
    int k = 1;
    for(int i = a.size() - 1;i>=1;i--){
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        int vel = a.size() - k++;
        Popravi_dolje(a,0,vel);
    }
}

int izbaciPrvi(vector<int> &a,int &velicina){
    if(velicina == 0) throw "Gomila je prazna!";
    int temp = a[0];
    a[0] = a[--velicina];
    a[velicina] = temp;
    if(velicina!=0){
        Popravi_dolje(a,0,velicina);
    }
    return a[velicina];
}

int main() {

    return 0;
}


/*


void Popravi_dolje(std::vector<int> &a,int i){
    int velicina = a.size() - 1;
    while(Je_li_list(a,i) != true){
        int veci = LijevoDijete(i);
        int dd = DesnoDijete(i);
        if(dd < velicina && a[dd]>a[veci]){
            veci = dd;
        }
        if(a[i]>a[veci]) return;
        int temp = a[i];
        a[i] = a[veci];
        a[veci] = temp;
        i = veci;
    }
}

void stvoriGomilu(vector<int> &a){
    for(int i = a.size()/2;i>=0;i--){
        Popravi_dolje(a,i);
    }
}







int izbaciPrvi(vector<int> &a, int &velicina){
    if(velicina == 0) cout<<"Gomila je prazna!";
    int temp = a[0];
    int vel = velicina -1;
    a[0] = a[vel];
    a[vel] = temp;
    if(vel !=0){
        Popravi_dolje(a,0);
    }
    return a[vel];
}

/*void pomocnisort(vector<int> a,int n,int i){
    int najveci = i;
    int l = LijevoDijete(i);
    int d = DesnoDijete(i);
    if(l < n && a[l] > a[najveci]) najveci = l;
    if(d < n && a[d] > a[najveci]) najveci = d;
    if(najveci != i){
        swap(a[i],a[najveci]);
        pomocnisort(a,n,najveci);
    }
}*/

/*
void gomilaSort(vector<int> &a){
    int n = a.size();
    for(int i = n/2 - 1;i>=0;i--){
        pomocnisort(a,n,i);
    }
    for(int i = n-1;i>=0;i--){
        swap(a[0],a[i]);
        pomocnisort(a,i,0);
    }
    stvoriGomilu(a);
    int vel = a.size();
    for(int i = 0 ;i<=a.size()-2;i--){
        izbaciPrvi(a,vel);
    }
}
*/
