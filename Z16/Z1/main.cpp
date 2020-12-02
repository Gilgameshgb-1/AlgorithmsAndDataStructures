#include <iostream>
#include <string>
#include <vector>

const int defaultKapacitet = 1000;

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


//testne funkcije

void Funkcija1(NizMapa<int,double> n){
    std::cout<<n.brojElemenata();
    n[1] = 2;
    std::cout<<n.brojElemenata();
    n.obrisi();
    std::cout<<n.brojElemenata();
}

void Funkcija2(NizMapa<std::string,double> n){
    std::cout<<n.brojElemenata();
    n["zasto sam uzeo ovo kao izborni"] = 0;
    std::cout<<n.brojElemenata();
    n.obrisi();
    std::cout<<n.brojElemenata();
}

void Funkcija3(NizMapa<double,double> n){
    std::cout<<n.brojElemenata();
    n[5.64] = 2.23;
    std::cout<<n.brojElemenata();
    n.obrisi();
    std::cout<<n.brojElemenata();
}

void Funkcija4(NizMapa<int,int> n){
    std::cout<<n.brojElemenata();
    n[0] = 3;
    std::cout<<n.brojElemenata();
    n.obrisi();
    std::cout<<n.brojElemenata();
}

void Funkcija5(NizMapa<std::string,std::string> n){
    std::cout<<n.brojElemenata();
    n["asdasd"] = "asdsa";
    std::cout<<n.brojElemenata();
    n.obrisi();
    std::cout<<n.brojElemenata();
}

int main() {
    NizMapa<std::string,std::string> m;
m["Sarajevo"] = "BiH";
m["Zagreb"] = "Hrvatska";
std::cout << m.brojElemenata() << " " << m["Zagreb"] << " '"; // 2 Hrvatska

// Test praznih elemenata
std::cout << m["Beograd"] <<"' '"; // ''
std::cout << m["zagreb"] << "' "; // ''
m.obrisi("Zagreb");
/*    NizMapa<int,double> n1;
    n1[0] = 3.2;
    NizMapa<std::string,double> n2;
    n2["nesto"] = 2.4;
    NizMapa<double,double> n3;
    n3[2.5] = 23.5;
    NizMapa<int,int> n4;
    n4[0] = 0;
    NizMapa<std::string,std::string> n5;
    n5["ugh"] = "eugh";
    Funkcija1(n1);
    Funkcija2(n2);
    Funkcija3(n3);
    Funkcija4(n4);
    Funkcija5(n5);*/
    return 0;
}
