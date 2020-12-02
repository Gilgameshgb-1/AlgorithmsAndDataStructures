#include <iostream>
#include <string>
#include <vector>

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


unsigned int djbhash(std::string ulaz, unsigned int max) {
	unsigned int suma=5381; 
// 5381 je pocetna vrijednost 
// koja poboljsava distribuciju
	for (int i(0); i<ulaz.length(); i++)
		suma = suma*33 + ulaz[i];
	return suma % max;
}

//HASH MAPA
template<typename TipKljuca, typename TipVrijednosti>
class HashMapa: public Mapa<TipKljuca,TipVrijednosti>{
    TipKljuca *nizK;
    TipVrijednosti *nizV;
    int kapacitet  , brojEl;
    TipVrijednosti prazan = TipVrijednosti();
    unsigned int(*pokNaFun)(TipKljuca,unsigned int);
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
    HashMapa() : kapacitet(defaultKapacitet),brojEl(0),nizK(new TipKljuca[defaultKapacitet]{}),nizV(new TipVrijednosti[defaultKapacitet]{}),pokNaFun(nullptr){
       // prazan = TipVrijednosti(0);
    };
     ~ HashMapa(){
        delete[] nizK;
        delete[] nizV;
    };
    
    HashMapa(const HashMapa<TipKljuca,TipVrijednosti> &n) : kapacitet(n.kapacitet),brojEl(n.brojEl),nizK(new TipKljuca[n.kapacitet]{}),nizV(new TipVrijednosti[n.kapacitet]{}),pokNaFun(n.pokNaFun){
        for(int i =0 ;i<defaultKapacitet; i++){
            nizK[i] = n.nizK[i];
            nizV[i] = n.nizV[i];
        }

    }
    
    HashMapa<TipKljuca,TipVrijednosti>& operator = (const HashMapa<TipKljuca,TipVrijednosti> &n){
        if(&n == this) return *this;
        delete[] nizK;
        delete[] nizV;
        kapacitet = n.kapacitet;
        brojEl = n.brojEl;
        pokNaFun = n.pokNaFun;
        nizK = new TipKljuca[kapacitet];
        nizV = new TipVrijednosti[kapacitet];
        for(int i =0 ;i<defaultKapacitet; i++){
            nizK[i] = n.nizK[i];
            nizV[i] = n.nizV[i];
        }
        return *this;
    }
    TipVrijednosti operator[](const TipKljuca& kljuc) const{
        if(!pokNaFun) throw "Nema hash funkcije, postavite hash funkciju";
        unsigned int indeks = pokNaFun(kljuc,defaultKapacitet);
   //     for(int i = 0;i<defaultKapacitet;i++){
            if(nizK[indeks] == kljuc) return nizV[indeks];
   //     }
        return TipVrijednosti(0); 
    };
    TipVrijednosti &operator[](const TipKljuca& kljuc){
        if(!pokNaFun) throw "Nema hash funkcije, postavite hash funkciju";
        
        unsigned int indeks = pokNaFun(kljuc,defaultKapacitet);
   //     for(int i = 0;i<defaultKapacitet;i++){
            if(nizK[indeks] == kljuc) return nizV[indeks];
    //    }
        TipKljuca Tempkljuc = nizK[indeks];
        nizK[indeks] = kljuc;
        brojEl++;
        return nizV[indeks];
    };

    int brojElemenata() const {return brojEl;};
    void obrisi(){
       for(int i = 0;i<defaultKapacitet;i++){
           nizK[i] = TipKljuca();
       }
       for(int i = 0;i<defaultKapacitet;i++){
           nizV[i] = TipVrijednosti();
       }
    brojEl = 0;
    };
    void obrisi(const TipKljuca& kljuc){
        if(!pokNaFun) throw "Nema hash funkcije, postavite hash funkciju";
        unsigned int indeks = pokNaFun(kljuc,defaultKapacitet);
        if(nizK[indeks] == kljuc){
            nizV[indeks] = TipVrijednosti();
            brojEl--;
            return;
        }
        throw "nije pronadjen kljuc";
    };
    void definisiHashFunkciju(unsigned int(*pokNaFun1)(TipKljuca,unsigned int)){
        pokNaFun = pokNaFun1;
    }
};

//NIZ MAPA I BINSTABLO MAPA

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
};

unsigned int CustomHash(int ulaz,unsigned int max){
    unsigned int suma = 23;
    suma = suma*31+ulaz;
    return suma%max;
}



int main() {

// Osnovni test funkcionalnosti HashMapa
HashMapa<std::string,std::string> m;
m.definisiHashFunkciju(djbhash);
m["Sarajevo"] = "BiH";
m["Zagreb"] = "Hrvatska";
cout << m.brojElemenata() << " " << m["Zagreb"] << " '"; // 2 Hrvatska

// Test praznih elemenata
cout << m["Beograd"] <<"' '"; // ''
cout << m["zagreb"] << "' "; // ''
m.obrisi("Zagreb");

// Potpuno korektna HashMapa nece kreirati objekte "Beograd" i "zagreb"
// jer oni nemaju vrijednosti pa ce se ispod ispisati 1
// Ali to zahtijeva implementaciju "Pristupnika" pa cemo priznavati
// rjesenje koje ispise broj 3
cout << m.brojElemenata(); // 3 ili 1

// Test brisanja
cout << " '" << m["Zagreb"] << "' " ; // ''
m.obrisi();
cout << m.brojElemenata(); // 0
cout << " '" << m["Sarajevo"] << "' "; // ''

/*    BinStabloMapa <int,int> m;
    NizMapa<int, int> n;
    HashMapa<int,int> h;
    h.definisiHashFunkciju(CustomHash);
    int vel(10000);
    
    std::vector<int> vektor;
    for(int i = 0;i<vel;i++){
        vektor.push_back(rand()%vel);
    }
    
    clock_t vrijeme1 = clock();
    
    for(int i = 0 ;i<vel;i++){
        m[vektor[i]] = i;
    }

    clock_t vrijeme2 = clock();
    int ukvrijeme1 = (vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/1000);
    
    std::cout<<"Vrijeme izvrsavanja dodavanja random elementa binstablo: "<<ukvrijeme1<<" ms\n";
    
    clock_t vrijeme_3 = clock();
    
    for(int i = 0;i<vel;i++){
        n[vektor[i]] = i;
    }
    
    clock_t vrijeme_4 = clock();
    int ukvrijeme2 = (vrijeme_4-vrijeme_3)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Vrijeme izvrsavanja dodavanja random elementa nizmapa: "<<ukvrijeme2<<" ms\n";

    clock_t vrijeme_H1 = clock();
    
    for(int i = 0;i<vel;i++){
        h[vektor[i]] = i;
    }
    
    clock_t vrijeme_H2 = clock();
    int ukvrijeme3 = (vrijeme_H2-vrijeme_H1)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Vrijeme izvrsavanja dodavanja random elementa hashmapa: "<<ukvrijeme3<<" ms\n";

    clock_t vrijeme5 = clock();
    
    for(int i = 0;i<vel;i++){
        m[vektor[i]] = i;
    }
    
    clock_t vrijeme6 = clock();
    int ukvrijeme4 = (vrijeme6-vrijeme5)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Vrijeme izvrsavanja pristupa svim elementa binstablo: "<<ukvrijeme4<<" ms\n";

    clock_t vrijeme7 = clock();
    
    for(int i = 0;i<vel;i++){
        n[vektor[i]] = i;
    }
    
    clock_t vrijeme8 = clock();
    int ukvrijeme5 = (vrijeme8-vrijeme7)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Vrijeme izvrsavanja pristupa svim elementa nizmapa: "<<ukvrijeme5<<" ms\n";

    clock_t vrijeme9 = clock();
    
    for(int i = 0;i<vel;i++){
        h[vektor[i]] = i;
    }
    
    clock_t vrijeme10 = clock();
    int ukvrijeme6 = (vrijeme10-vrijeme9)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Vrijeme izvrsavanja pristupa svim elementa hashmapa: "<<ukvrijeme6<<" ms\n";

    clock_t vrijeme11 = clock();
    
    for(int i = 0;i<1000;i++) m[i]=i;
    for(int i = 0;i<1000;i++) m.obrisi(i);
    
    clock_t vrijeme12 = clock();
    int ukvrijeme7 = (vrijeme12-vrijeme11)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Vrijeme izvrsavanja brisanja 1000 elementa binstablo: "<<ukvrijeme7<<" ms\n";

    clock_t vrijeme13 = clock();
    
    for(int i = 0;i<1000;i++) n[i]=i;
    for(int i = 0;i<1000;i++) n.obrisi(i);
    
    clock_t vrijeme14 = clock();
    int ukvrijeme8 = (vrijeme14-vrijeme13)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Vrijeme izvrsavanja brisanja 1000 elementa nizmapa: "<<ukvrijeme8<<" ms\n";


    clock_t vrijeme15 = clock();
    
    for(int i = 0;i<1000;i++) h[i]=i;
    for(int i = 0;i<1000;i++) h.obrisi(i);
    
    clock_t vrijeme16 = clock();
    int ukvrijeme9 = (vrijeme16-vrijeme15)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Vrijeme izvrsavanja brisanja 1000 elementa hashmapa: "<<ukvrijeme9<<" ms\n";
*/
    /*
    Dodavanje elemenata u nizmapu traje dosta duze, kao i u hashmapu u odnosu na binarno stablo
    Pristup elementima je dosta brzi u binstablo ali nizmapa i hashmapa i hashmapa dosta sporije rade
    zbog kolizije
    Brisanje je kod binstabla najbrze , potom kod hashmape, potom kod nizmape
    */

    return 0;
}
