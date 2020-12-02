#include <iostream>

template <typename TipEl>
class BazniStack
{
public:
    BazniStack() {};
    virtual ~BazniStack() {};
    virtual void brisi() = 0;
    virtual void stavi(const TipEl &el) = 0;
    virtual TipEl skini() = 0;
    virtual TipEl &celo() = 0;
    virtual int brojElemenata() = 0;
};

template <typename TipEl>
class DvostraniRed: public BazniStack<TipEl>
{
    TipEl* red;
    int kapacitet = 1000000;
    int pocetak;
    int kraj;
public:
    Red() : pocetak(-1),kraj(-1){
       red = new TipEl[kapacitet]; 
    };
    
    ~Red(){delete[] red;};
    
    void brisi(){
        delete[] red;
        red = new TipEl[kapacitet];
        pocetak = -1;
        kraj = -1;
    }
    
    int brojElemenata(){
        if(pocetak == -1) return 0;
        return kraj-pocetak+1;
    }
    
    void staviNaVrh(){
       kraj = (kraj+1)%kapacitet;
       red[kraj] = el;
       if(pocetak == -1) pocetak = 0;
    };
    
    TipEl skiniSaVrha(){
        if(pocetak == -1) throw "Red je prazan!";
        TipEl temp = red[pocetak];
        
    }
    
};

int main() {
    std::cout << "Zadaća 2, Zadatak 1";
    return 0;
}
