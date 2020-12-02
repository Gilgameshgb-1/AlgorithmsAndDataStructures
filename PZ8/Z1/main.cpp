#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

const int defaultKapacitet = 1000;

using namespace std;

template <typename TipKljuca, typename TipVrijednosti>
class Mapa{
public:
    Mapa(){};
    virtual ~ Mapa(){};
    virtual TipVrijednosti &operator[](const TipKljuca& kljuc) = 0;
    virtual  TipVrijednosti operator[](const TipKljuca& kljuc) const = 0;
    virtual int brojElemenata() const = 0;
    virtual void obrisi() = 0;
    virtual void obrisi(const TipKljuca& kljuc) = 0;
};

template <typename TipKljuca, typename TipVrijednosti>
class NizMapa : public Mapa<TipKljuca,TipVrijednosti> {
    TipKljuca *nizK;
    TipVrijednosti *nizV;
    int kapacitet  , brojEl;
    TipVrijednosti prazan;
    
    void povecaj(){
        kapacitet *=2;
        TipKljuca *tempNizK = new TipKljuca[kapacitet];
        TipVrijednosti *tempNizV = new TipVrijednosti[kapacitet];
        for(int i =0 ;i<brojEl; i++){
            tempNizK[i] = nizK[i];
            tempNizV[i] = nizV[i];
        }
        delete[] nizK;
        delete[] nizV;
        nizK = tempNizK;
        nizV = tempNizV;
    }
    
public:
    NizMapa() : kapacitet(defaultKapacitet),brojEl(0),nizK(new TipKljuca[defaultKapacitet]),nizV(new TipVrijednosti[defaultKapacitet]){
       // prazan = TipVrijednosti(0);
    };
     ~ NizMapa(){
        delete[] nizK;
        delete[] nizV;
    };
    
    NizMapa(const NizMapa<TipKljuca,TipVrijednosti> &n) : kapacitet(n.kapacitet),brojEl(n.brojEl),nizK(new TipKljuca[n.kapacitet]),nizV(new TipVrijednosti[n.kapacitet]){
        for(int i =0 ;i<n.brojEl; i++){
            nizK[i] = n.nizK[i];
            nizV[i] = n.nizV[i];
        }
    }
    
    NizMapa<TipKljuca,TipVrijednosti>& operator = (const NizMapa<TipKljuca,TipVrijednosti> &n){
        if(&n == this) return *this;
        delete[] nizK;
        delete[] nizV;
        kapacitet = n.kapacitet;
        brojEl = n.brojEl;
        nizK = new TipKljuca[kapacitet];
        nizV = new TipVrijednosti[kapacitet];
        for(int i =0 ;i<n.brojEl; i++){
            nizK[i] = n.nizK[i];
            nizV[i] = n.nizV[i];
        }
        return *this;
    }
    
    TipVrijednosti &operator[](const TipKljuca& kljuc){
        for(int i = 0;i<brojEl;i++){
            if(nizK[i] == kljuc) return nizV[i];
        }
        if(brojEl == kapacitet) povecaj();
        nizK[brojEl] = kljuc;
        nizV[brojEl] = TipVrijednosti();
        return nizV[brojEl++];
    };
    TipVrijednosti operator[](const TipKljuca& kljuc) const{
        for(int i = 0;i<brojEl;i++){
            if(nizK[i] == kljuc) return nizV[i];
        }
        return TipVrijednosti(0); 
    };
    int brojElemenata() const {return brojEl;};
    void obrisi(){
        brojEl = 0;
    };
    void obrisi(const TipKljuca& kljuc){
        for(int i = 0 ;i<brojEl; i++){
            if(nizK[i] == kljuc){
                nizK[i] = nizK[brojEl-1];
                nizV[i] = nizV[brojEl-1];
                brojEl--;
                return;
            }
        }
        throw "nije pronadjen kljuc";
    };
};

template <typename TipKljuca,typename TipVrijednosti>
class BinStabloMapa : public Mapa<TipKljuca, TipVrijednosti>{
    struct Cvor {
        TipKljuca kljuc;
        TipVrijednosti vrijednost;
        Cvor* lijevo;
        Cvor* desno;
        Cvor* roditelj;
        Cvor(const TipKljuca &k,const TipVrijednosti &v,Cvor* l,Cvor* d,Cvor *r):kljuc(k),vrijednost(v),lijevo(l),desno(d),roditelj(r){};
    };
    Cvor* korijen;
    int BrojEl;
    TipVrijednosti prazan;
    
    Cvor* trazi(const TipKljuca &kljuc, Cvor* c) const{
        if(c == nullptr) return nullptr;
        if(kljuc == c->kljuc) return c;
        if(kljuc < c->kljuc) return trazi(kljuc,c->lijevo);
        return trazi(kljuc,c->desno);
    }
    
    Cvor* dodaj(const TipKljuca &kljuc,const TipVrijednosti &vrijednost, Cvor*& c,Cvor* roditelj){
        if(c == nullptr){
            c = new Cvor(kljuc,vrijednost,0,0,roditelj);
            BrojEl++;
            return c;
        }
        if(kljuc == c->kljuc) return c;
        if(kljuc < c->kljuc) return dodaj(kljuc,vrijednost,c->lijevo,c);
        return dodaj(kljuc,vrijednost,c->desno,c);
    }
    
    void ObrisiSve(Cvor* c){
        if(c==nullptr) return;
        ObrisiSve(c->lijevo);
        ObrisiSve(c->desno);
        delete c;
        BrojEl--;
    }
    
    void Kopiraj(Cvor*& cOvaj, Cvor* cDrugi, Cvor* roditelj){
        if(cDrugi == 0) return;
        cOvaj = new Cvor(cDrugi->kljuc,cDrugi->vrijednost,0,0,roditelj);
        Kopiraj(cOvaj->lijevo,cDrugi->lijevo,cOvaj);
        Kopiraj(cOvaj->desno,cDrugi->desno,cOvaj);
        BrojEl++;
    }
    
public:
    BinStabloMapa() :Mapa<TipKljuca,TipVrijednosti>(),korijen(0),BrojEl(0),prazan(TipVrijednosti()){};
    ~BinStabloMapa(){
        ObrisiSve(korijen);
    }
    BinStabloMapa(const BinStabloMapa<TipKljuca,TipVrijednosti> &m):korijen(0),BrojEl(0),prazan(TipVrijednosti()){
        Kopiraj(korijen,m.korijen,0);
    }
    BinStabloMapa<TipKljuca,TipVrijednosti> &operator=(const BinStabloMapa<TipKljuca,TipVrijednosti> &m){
        if(&m == this) return *this;
        ObrisiSve(korijen);
        korijen = 0;
        Kopiraj(korijen,m.korijen,0);
        return *this;
    }
    int brojElemenata() const {return BrojEl;}
    TipVrijednosti &operator[](const TipKljuca &kljuc){
        Cvor *c = dodaj(kljuc,TipVrijednosti(),korijen,0);
        return c->vrijednost;
    }
    TipVrijednosti operator[](const TipKljuca &kljuc) const{
        Cvor* c=trazi(kljuc,korijen);
        if(c ==0){
            return prazan;
        }else{
            return c->vrijednost;
        }
    }
    void obrisi(){
        ObrisiSve(korijen);
        korijen = 0;
    }
    
    void ObrisiPom(Cvor* c){
        if(c == nullptr) return;
        if(c == korijen){
            if(c->desno != nullptr){
                korijen = c->desno;
                if(c->desno->lijevo == nullptr){
                    c->desno->lijevo = c->lijevo;
                }else{
                    
                }
            }else{
                korijen = c->lijevo;
            }
            delete c;
            BrojEl--;
        }
        else if(c->lijevo == 0 && c->desno == 0){
            if(c == c->roditelj->lijevo){
                c->roditelj->lijevo = nullptr;
            }else c->roditelj->desno = nullptr;
            delete c;
            BrojEl--;
        }else if(c->lijevo !=0 && c->desno !=0){
            Cvor* tmp = c->lijevo;
            
            while(tmp->desno!=0){
                tmp = tmp->desno;
            }
            
            c->kljuc = tmp->kljuc;
            c->vrijednost = tmp->vrijednost;
            
            ObrisiPom(tmp);
            
        }else {
            Cvor* dijete = c->lijevo;
            if(dijete ==nullptr) dijete = c->desno;
            //cout<<c->vrijednost; problem bio ispod sa nekim visecim pokazivacem
            if(c == c->roditelj->lijevo){
                c->roditelj->lijevo = dijete;
            }else c->roditelj->desno = dijete;
            dijete->roditelj = c->roditelj;
            delete c;
            BrojEl--;
        }
    }
    void obrisi(const TipKljuca &kljuc){
        Cvor* c = trazi(kljuc,korijen);
        ObrisiPom(c);
    }
    TipKljuca Daj(){
        return korijen->lijevo->lijevo->kljuc;
    }
    TipKljuca dajMin(Cvor* c){
        while(c->lijevo != 0) c = c->lijevo;
        return c->kljuc;
    }
    TipKljuca dajMax(Cvor* c){
        while(c->desno != 0) c = c->desno;
        return c->kljuc;
    }
    bool Inorder_1(Cvor* korijen, TipKljuca k){
        if(korijen != 0){
            Inorder_2(korijen->lijevo, k);
            if(korijen->kljuc > k) return false;
            Inorder_2(korijen->desno, k);
        }
        return true;
    }
    bool operator<(BinStabloMapa<TipKljuca, TipVrijednosti> c){
        TipKljuca k = dajMin(c.korijen);
        if(!Inorder_1(korijen, k)) return false;
        return true;
    }
    bool Inorder_2(Cvor* korijen, TipKljuca k){
        if(korijen != 0){
            Inorder_2(korijen->lijevo, k);
            if(korijen->kljuc < k) return false;
            Inorder_2(korijen->lijevo, k);
        }
        return true;
    }
    bool operator>(BinStabloMapa<TipKljuca, TipVrijednosti> c){ //zadatak 1
        TipKljuca k = dajMax(c.korijen);
        if(!Inorder_2(korijen, k)) return false;
        return true;
    }
    Cvor* Inorder_3(Cvor* korijen, const TipKljuca &k){ 
        if(korijen != 0){
            return Inorder_3(korijen->lijevo, k);
            if(korijen->kljuc == k) {
               return korijen;
               std::cout<<"Pronadjeno inorder redoslijedom pretrage: "<<korijen->kljuc<<"\n";
            }
            return Inorder_3(korijen->desno, k);
        }
    }
    bool Inorder_4(Cvor* korijen, const TipKljuca &k){ 
        if(korijen != 0){
            Inorder_3(korijen->lijevo, k);
            if(korijen->kljuc == k) {
               return true;
               std::cout<<"Pronadjeno inorder redoslijedom pretrage: "<<korijen->kljuc<<"\n";
            }
            Inorder_3(korijen->desno, k);
        }
        std::cout<<"\nBruh!\n";
    }
    TipVrijednosti prviManji(const TipKljuca &kljuc){  //zadatak 2
    Inorder_4(korijen, kljuc);
        Cvor* pronadjen = Inorder_3(korijen ,kljuc);
        TipVrijednosti max = pronadjen->vrijednost;
        std::cout<<"!"<<max<<"\n";
        if(pronadjen->lijevo != 0){
            pronadjen = pronadjen->lijevo;
            max = pronadjen->vrijednost;
            while(pronadjen->desno != 0){
                pronadjen = pronadjen->desno;
                if(pronadjen->vrijednost > max) max = pronadjen->vrijednost;
            }
        }
        return max;
    }
    //zadatak 3
    void InOrder(Cvor* korijen, const TipKljuca &a, const TipKljuca &b, std::vector<TipVrijednosti> &v){
        if(korijen == 0) return;
        InOrder(korijen->lijevo, a, b, v);
        if(korijen->kljuc >= a && korijen->kljuc <= b) {v.push_back(korijen->vrijednost);}
        InOrder(korijen->desno, a, b, v);
    };
    std::vector<TipVrijednosti> od_do(const TipKljuca &a, const TipKljuca &b){
        std::vector<TipVrijednosti> povratni;
        InOrder(korijen, a, b, povratni);
        std::reverse(std::begin(povratni), std::end(povratni));
        return povratni;
    }
};

int GenerisanjeBin(BinStabloMapa<int,int> &mapa){
    int x = 0;
    int n = 15000;
    for(int i = 0;i<n;i++){
        int y = rand()%100000;
        mapa[y] = 3;
        if(i == n/2) x = y;
    }
    return x;
}

int GenerisanjeNiz(NizMapa<int,int> &mapa){
    int x = 0;
    int n = 15000;
    for(int i = 0;i<n;i++){
        int y = rand()%100000;
        mapa[y] = 3;
        if(i == n/2) x = y;
    }
    return x;
}

int main() {
BinStabloMapa<int,int> Bmapa;
/*NizMapa<int,int> Nmapa;
int prvi,drugi,ukvrijeme;
clock_t vrijeme1,vrijeme2;

vrijeme1 = clock();
Bmapa[100002] = 2;
vrijeme2 = clock();

ukvrijeme = (vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/100000);
cout<<"Vrijeme potrebno za dodavanje novog elementa u mapu(binarno stablo): "<<ukvrijeme<<"ms(/100)\n";
vrijeme1 = clock();
Nmapa[100002] = 2;
vrijeme2 = clock();
ukvrijeme = (vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/100000);
cout<<"Vrijeme potrebno za dodavanje novog elementa u mapu(niz mapa): "<<ukvrijeme<<"ms(/100)\n";

vrijeme1 = clock();
Bmapa[prvi] = 6969;
vrijeme2 = clock();

ukvrijeme = (vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/100000);
cout<<"Vrijeme trazenja u mapi(binarno stablo): "<<ukvrijeme<<"ms(/100)\n";

vrijeme1 = clock();
Nmapa[prvi] = 6969;
vrijeme2 = clock();

ukvrijeme = (vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/100000);
cout<<"Vrijeme trazenja u mapi(niz mapa): "<<ukvrijeme<<"ms(/100)\n";


//Jasno se moze zakljuciti da je ubacivanje u niz dosta brze nego ubacivanje u binarno stablo
//ali primjecuje se da je pretraga dosta brza kod binarnog stabla nego kod niz mape */

    BinStabloMapa<int, int> m;

    m[60] = 60;
    m[40] = 40;
    m[30] = 30;
    m[15] = 15;
    m[35] = 35;
    m[50] = 50;
    m[45] = 45;
    m[55] = 55;
    m[100] = 100;
    m[150] = 150;
    m[80] = 80;
    m[70] = 70;
    m[90] = 90;
    m[140] = 140;
    m[160] = 160;
    
    return 0;
}
