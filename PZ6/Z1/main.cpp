#include <iostream>
#include <string>
#include <fstream>

template<typename Tip>
void bubble_sort(Tip* niz, int vel){
    for(int i = vel-1;i>=0;i--){
        for(int j=1;j<=i;j++){
            if(niz[j-1]>niz[j]) {
               Tip temp = niz[j-1];
               niz[j-1] = niz[j];
               niz[j] = temp;
            }
        }
    }
};

template<typename Tip>
void selection_sort(Tip* niz, int vel){
    for(int i = 0; i<=vel-2;i++){
        Tip min = niz[i];
        int pmin = i;
        for(int j = i+1;j<=vel-1;j++){
            if(niz[j]<min){
                min = niz[j];
                pmin = j;;
            }
        }
        niz[pmin] = niz[i];
        niz[i] = min;
    }
};

template <typename Tip>
void zamijeni(Tip* niz,int i,int j){
    Tip priv = niz[i];
    niz[i] = niz[j];
    niz[j] = priv;
}

template <typename Tip>
int particija(Tip* niz,int prvi,int zadnji){
    Tip pivot = niz[prvi];
    int p = prvi + 1;
    while(p<=zadnji){
        if(niz[p]<=pivot){
            p++;
        }else break;
    }
    for(int i = p+1;i<=zadnji;i++ ){
        if(niz[i]<pivot){
            zamijeni(niz,p,i);
            p++;
        }/*else break;*/
    }
    zamijeni(niz,prvi,p-1);
    return p-1;
}

template<typename Tip>
void kvik(Tip* niz,int p,int z){
    if(p<z){
        int j = particija(niz,p,z);
        kvik(niz,p,j-1);
        kvik(niz,j+1,z);
    }
}

template<typename Tip>
void quick_sort(Tip* niz, int vel){
    kvik(niz,0,vel-1);
};

template<typename Tip>
void merge(Tip* niz, int l,int p,int q,int u){
    int i = 0;
    int j = q-l;
    int k = l;
    Tip *B = new Tip[u-l+1];
    for(int z = 0;z<=u-l;z++){
        B[z]=niz[l+z];
    }
    while(i<=p-l && j<=u-l){
        if(B[i]<B[j]) niz[k]=B[i++];
        else niz[k]=B[j++];
        k++;
    }
    while(i<=p-l){niz[k++] = B[i++];}
    while(j<=u-l){niz[k++] = B[j++];}
    delete[] B;
}

template<typename Tip>
void merge_s(Tip* niz,int l,int u){
    if(u>l){
        int p = (l+u-1)/2;
        int q = p+1;
        merge_s(niz,l,p);
        merge_s(niz,q,u);
        merge(niz,l,p,q,u);
    }
}

template<typename Tip>
void merge_sort(Tip* niz, int vel){
    merge_s(niz,0,vel-1);
};

void ucitaj(std::string filename, int*& niz, int &vel){
    int brojac = 0;
    std::ifstream ulaz(filename);
    if(!ulaz) std::cout<<"Datoteka ne postoji";
    else{
        while(ulaz){
            if(!ulaz || ulaz.eof()) break;
            int br;
            ulaz >> br;
            brojac++;
        }
        ulaz.clear();
        ulaz.close();
        std::ifstream ulaz(filename);
        niz = new int[brojac];
        for(int i = 0;i<brojac;i++){
            if(!ulaz || ulaz.eof()) break;
            int br;
            ulaz >>br;
            if(ulaz) niz[i] = br;
        }
        vel = brojac;
    }
};

void generisi(std::string filename,int vel){
    std::ofstream out(filename);
    for(int i = 0;i<vel;i++){
        int br = std::rand()%100001;
        out<<br;
        if(i!=vel-1) out<<" ";
    }
}

//testiranje 

void testiranje(std::string filename){
    int size = 0;
    int *niz = nullptr;
    ucitaj(filename,niz,size);
    int izbor = 0;
    std::cout<<"Izaberite vas sort! 1-bubble,2 - ss, 3- qs, 4 -ms";
    std::cin>>izbor;
    clock_t t1,t2;
    if(izbor == 1){
        t1 = clock();
        bubble_sort(niz,size);
        t2 = clock();
    }else if(izbor == 2){
        t1 = clock();
        selection_sort(niz,size);
        t2 = clock();
    }else if(izbor == 3){
        t1 = clock();
        quick_sort(niz,size);
        t2 = clock();
    }else if(izbor == 4){
        t1 = clock();
        merge_sort(niz,size);
        t2 = clock();
    }
    int t_ek = (t2-t1)/(CLOCKS_PER_SEC/1000);
    auto priv = niz;
    bool sortirano = true;
    for(int i = 0;i<size-1;i++){
        if(priv[i]>priv[i+1]){sortirano = false;}
    }
    if(sortirano) std::cout<<"sortirano!";
    else std::cout<<"nije sortirano!";
    std::cout<<"sortiranje je trajalo " <<t_ek<<" ms.";
    priv = niz;
    std::ofstream izlazni_tok("rjesenje_testa.txt");
    for(int i = 0;i<size;i++) izlazni_tok<<priv[i]<<" ";
    delete[] niz;
}

int main(){
    int br;
    std::cout<<"Unseite broj elemenata";
    std::cin>>br;
    generisi("brojevi.txt",br);
    testiranje("brojevi.txt");
    return 0;
}
