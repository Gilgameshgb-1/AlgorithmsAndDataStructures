#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <vector>

/*template <typename TipEl>
class Lista
{
public:
    Lista() {};
    virtual ~Lista() {};
    virtual int brojElemenata() const = 0;
    virtual TipEl& trenutni() = 0;
    virtual TipEl trenutni() const = 0;
    virtual bool prethodni() = 0;
    virtual bool sljedeci() = 0;
    virtual void pocetak() = 0;
    virtual void kraj() = 0;
    virtual void obrisi() = 0;
    virtual void dodajIspred(const TipEl& el) = 0;
    virtual void dodajIza(const TipEl& el) = 0;
    virtual TipEl& operator[](int x ) = 0;
    virtual TipEl operator[](int x ) const = 0;
    virtual void dodajSortirano(const TipEl &el) = 0;
};

template <typename TipEl>
class NizLista : public Lista<TipEl>
{
    int kapacitet = 100;
    int duzina;
    int tekuci;
    TipEl *niz;
public:
    NizLista()
    {
        niz = new TipEl[kapacitet];
        duzina = tekuci = 0;
    };
    NizLista(const NizLista<TipEl> &l)
    {
        kapacitet = l.kapacitet;
        duzina = l.duzina;
        tekuci = l.tekuci;
        niz = new TipEl[kapacitet];
        std::copy(l.niz,l.niz+l.duzina,niz);
    }
    NizLista &operator = (const NizLista<TipEl> &l)
    {
        if(&l != this) {
            delete[] niz;
            kapacitet = l.kapacitet;
            duzina = l.duzina;
            tekuci = l.tekuci;
            niz = new TipEl[kapacitet];
            std::copy(l.niz,l.niz+l.duzina,niz);
        }
        return *this;
    }
    ~NizLista()
    {
        delete[] niz;
    };
    int brojElemenata() const
    {
        return duzina;
    };
    TipEl& trenutni()
    {
        if(duzina <= 0) throw "\nNema elemenata u nizu!";
        return niz[tekuci];
    };
    TipEl trenutni() const
    {
        if(duzina <= 0) throw "\nNema elemenata u nizu!";
        return niz[tekuci];
    };
    bool prethodni()
    {
        if(duzina == 0) throw "\nNema elemenata u nizu!";
        if(tekuci != 0) {
            tekuci--;
            return true;
        }
        return false;
    };
    bool sljedeci()
    {
        if(duzina == 0) throw "\nNema elemenata u nizu!";
        if(tekuci < duzina -1) { // OVDJE DODALI - 1
            tekuci++;
            return true;
        }
        return false;
    };
    void pocetak()
    {
        if(duzina == 0) throw "\nNema elemenata u nizu!";
        tekuci = 0;
    };
    void kraj()
    {
        if(duzina == 0) throw "\nNema elemenata u nizu!";
        tekuci = duzina;
    };
    void obrisi()
    {
        if(duzina == 0) throw "\nNema elemenata u nizu!";
        if(tekuci != duzina) {
            for(int i = tekuci ; i<duzina; i++) {
                niz[i]=niz[i+1];
            }
            duzina--;
        } else if(tekuci == duzina) {
            tekuci--;
            duzina--;
        }
    };
    void dodajIspred(const TipEl& el)
    {
        if(duzina == 0) {
            niz[0] = el;
            duzina++;
        } else {
            if(duzina + 1 >= kapacitet ) {
                kapacitet *=2;
                TipEl* nizTemp = new TipEl[kapacitet];
                for(int i = 0; i<duzina; i++) {
                    nizTemp[i] = niz[i];
                }
                delete[] niz;
                niz = nizTemp;
            }
            duzina++;
            for(int i = tekuci; i<duzina; i++) {
                niz[i+1] = niz[i];
            }
            niz[tekuci] = el;
            tekuci++;
        }
    };
    void dodajIza(const TipEl& el)
    {
        if(duzina == 0) {
            niz[0] = el;
            duzina++;
        } else {
            if(duzina + 1 >= kapacitet ) {
                kapacitet *=2;
                TipEl* nizTemp = new TipEl[kapacitet];
                for(int i = 0; i<duzina; i++) {
                    nizTemp[i] = niz[i];
                }
                delete[] niz;
                niz = nizTemp;
            }
            duzina++;
            for(int i = duzina ; i>tekuci+1; i--) {
                niz[i] = niz[i-1];
            }
            niz[tekuci+1] = el;
        }
    } ;
    TipEl& operator[](int x )
    {
        return niz[x];
    };
    TipEl operator[](int x ) const
    {
        return niz[x];
    };
};

template <typename TipEl>
class JednostrukaLista : public Lista<TipEl>
{
    struct Cvor {
        TipEl el;
        Cvor* sljedeci;
    };
    Cvor* prvi;
    Cvor* zadnji;
    Cvor* trenutno;
    int BrojElem;
public:
    JednostrukaLista()
    {
        prvi = nullptr;
        zadnji = nullptr;
        trenutno = nullptr;
        BrojElem = 0;
    };
    JednostrukaLista(const JednostrukaLista<TipEl> &l)
    {
        Cvor* temp = l.prvi;
        Cvor* temp2=nullptr;
        while(temp!=nullptr) {
            Cvor* novi = new Cvor;
            novi->el = temp->el;
            if(temp2==nullptr) {
                prvi = novi;
            } else {
                temp2->sljedeci = novi;
            }
            temp2 = novi;
            if(temp == l.trenutno) {
                trenutno = novi;
            }
            temp = temp->sljedeci;
        }
        zadnji = temp2;
    };
    JednostrukaLista<TipEl> &operator = (const JednostrukaLista<TipEl>  &l)
    {

        while(prvi!=0) {
            trenutno = prvi;
            prvi = prvi->sljedeci;
            delete trenutno;
        }

        Cvor* temp = l.prvi;
        Cvor* temp2=nullptr;
        while(temp!=nullptr) {
            Cvor* novi = new Cvor;
            novi->el = temp->el;
            if(temp2 == nullptr) {
                prvi = novi;
            } else {
                temp2->sljedeci = novi;
            }
            temp2 = novi;
            if(temp == l.trenutno) {
                trenutno = novi;
            }
            temp = temp->sljedeci;
        }
        zadnji = temp2;
    };
    ~JednostrukaLista()
    {
        while(prvi!=nullptr) {
            trenutno = prvi;
            prvi = prvi->sljedeci;
            delete trenutno;
        }
    };
    int brojElemenata() const
    {
        return BrojElem;
    };
    TipEl& trenutni()
    {
        return trenutno->el;
    };
    TipEl trenutni() const
    {
        return trenutno->el;
    };
    bool prethodni()
    {
        if(trenutno == prvi) return false;
        Cvor* temp = prvi;
        while(temp->sljedeci != trenutno) {
            temp = temp->sljedeci;
        }
        trenutno = temp;
        return true;
    };
    bool sljedeci()
    {
        if(trenutno->sljedeci == 0) return false;
        trenutno = trenutno->sljedeci;
        return true;
    };
    void pocetak()
    {
        trenutno = prvi;
    };
    void kraj()
    {
        trenutno = zadnji;
    };
    void obrisi()
    {
        if(trenutno == prvi) {
            prvi = prvi->sljedeci;
            delete trenutno;
            BrojElem--;
            trenutno = prvi;
        } else {
            Cvor* temp = prvi;
            while(temp->sljedeci != trenutno) {
                temp = temp->sljedeci;
            }
            temp -> sljedeci = trenutno->sljedeci;
            delete trenutno;
            BrojElem--;
            trenutno = temp->sljedeci;
            if(trenutno == nullptr) {
                zadnji = trenutno = temp;
            }
        }
    };
    void dodajIspred(const TipEl& el)
    {
        Cvor* temp = new Cvor;
        temp->el = el;
        BrojElem++;
        if(prvi==nullptr) {
            prvi = zadnji = trenutno = temp;
            temp->sljedeci = 0;
        } else if(trenutno == prvi) {
            temp->sljedeci = prvi;
            prvi = temp;
        } else {
            Cvor* tmp = prvi;
            while(tmp->sljedeci != trenutno) {
                tmp= tmp->sljedeci;
            }
            temp -> sljedeci = tmp->sljedeci;
            tmp->sljedeci = temp;
        }
    };
    void dodajIza(const TipEl& el)
    {
        Cvor* temp = new Cvor;
        temp->el = el;
        BrojElem++;
        if(prvi==nullptr) {
            prvi = zadnji = trenutno = temp;
            temp->sljedeci = 0;
        } else {
            temp->sljedeci = trenutno->sljedeci;
            trenutno ->sljedeci = temp;
            if(zadnji = trenutno) {
                zadnji = temp;
            }
        }
    };
    TipEl& operator[](int x )
    {
        Cvor* temp = prvi;
        for(int i = 0; i<x; i++) {
            temp = temp->sljedeci;
        }
        return temp->el;
    };
    TipEl operator[](int x ) const
    {
        Cvor* temp = prvi;
        for(int i = 0; i<x; i++) {
            temp = temp->sljedeci;
        }
        return temp->el;
    };
    void bruh()
    {
        this->ispisUnatraad(trenutno);
    };
    void ispisUnazad(Cvor* c )
    {
        if(c->sljedeci == 0) std::cout << c->el;
        else {
            ispisUnazad(c->sljedeci);
            std::cout << c->el;
        }
    };
    void dodajSortirano(const TipEl &el)
    {
        if(BrojElem == 0) {
            Cvor* T = new Cvor;
            T->el = el;
            prvi = zadnji = trenutno = T;
            BrojElem++;
            return;
        } else {
            Cvor* T = new Cvor;
            Cvor* temp = prvi;
            T->el = el;
            while(temp != zadnji) {
                if(temp->sljedeci->el > el) {
                    T->sljedeci = temp->sljedeci;
                    temp->sljedeci = T;
                    BrojElem++;
                    return;
                }
                temp = temp->sljedeci;
            }
            BrojElem++;
            temp->sljedeci = T;
            T->sljedeci = 0;
            zadnji = T;
            return;
        }
    };
    void UnazadRekurzivno(Cvor* t)
    {
        if(t == kraj) std::cout<<t->el;
        else {
            UnazadRekurzivno(t->sljedeci);
            std::cout<<t->el;
        }
    };
    Cvor* dajPrvi()
    {
        return prvi;
    };
    void dodajNto(const TipEl& el, int n){
        Cvor* T = new Cvor;
        T->el = el;
        if(BrojElem == 0){
            prvi = zadnji = trenutno = T;
            BrojElem++;
        }else{
            if(n == BrojElem){
                zadnji->sljedeci = T;
                zadnji = T;
                T->sljedeci = 0;
                BrojElem++;
            }else{
                Cvor* temp = prvi;
                for(int i = 0; i < n - 1; i++) temp = temp->sljedeci;
                T->sljedeci = temp->sljedeci;
                temp->sljedeci = T;
                BrojElem++;
            }
        }
    };
    void obrisiOdKraja(int k){
       int i = 0;
       if(k < 0 || k > this->brojElemenata()) throw std::range_error("Parametar k van opsega");
       if(k == this->brojElemenata()){
           Cvor* temp = prvi;
           prvi = temp->sljedeci;
           prvi->sljedeci = temp->sljedeci->sljedeci;
           delete temp;
            return;
       }
       Cvor* prijeBrisanja = prvi;
       Cvor* naBrisanju = prvi;
       naBrisanju = naBrisanju->sljedeci;
       for(int i = 0; i < (this->brojElemenata() - k) - 1; i++){
           prijeBrisanja = prijeBrisanja->sljedeci;
           naBrisanju = naBrisanju->sljedeci;
       }
       prijeBrisanja->sljedeci = naBrisanju->sljedeci;
       naBrisanju->sljedeci = 0;
       delete naBrisanju;
    };
    void brisiOdAdoB(int a, int b){
        if(a == b) throw std::range_error("Nepravilno proslijedjeni parametri");
        Cvor* A = new Cvor;
        Cvor* B = new Cvor;
        Cvor* temp = prvi;
        for(int i = 0; i < BrojElem; i++){
            if(temp->el == a){
                A = temp;
                break;
            }
            temp = temp->sljedeci;
        }
        temp = prvi;
        for(int i = 0; i < BrojElem; i++){
            if(temp->el == b){
                B = temp;
                break;
            }
            temp = temp->sljedeci;
        }
        if(A < B){
            temp = A;
            temp = temp->sljedeci;
            while(temp != B){
                A->sljedeci = temp->sljedeci;
                temp->sljedeci = 0;
                delete temp;
                temp = A->sljedeci;
            }
        }else{
            temp = A;
            zadnji = A;
            while(temp != 0){
                temp = temp->sljedeci;
                A->sljedeci = temp->sljedeci;
                temp->sljedeci = 0;
                delete temp;
                temp = A->sljedeci;
            }
            temp = prvi;
            while(temp != B){
                prvi = temp->sljedeci;
                temp->sljedeci = 0;
                delete temp;
                temp = prvi;
            }
        }
    };
    friend void IzbaciIzListe(JednostrukaLista<char> &l);
    void Premjesti(int n, int m, int k){
        if(k >= n && k <= m) throw std::range_error("Van opsega");
        Cvor* prijeK = prvi;
        for(int i = 1; i < k; i++) prijeK = prijeK->sljedeci;
        n--;
        while(m != n){
            Cvor* T = prvi->sljedeci;
            Cvor* roditeljT = prvi;
            for(int i = 1; i < m; i++){
                T = T->sljedeci;
                roditeljT = roditeljT->sljedeci;
            }
            Cvor *novo = new Cvor;
            novo->el = T->el;
            roditeljT->sljedeci = T->sljedeci;
            T->sljedeci = 0;
            delete T;
            novo->sljedeci = prijeK->sljedeci;
            prijeK->sljedeci = novo;
            prijeK = prijeK->sljedeci;
            m--;
        }
    }
    void PremetNaPola(){
        if(this->brojElemenata()%2 == 0) throw std::domain_error("Nemoguce prevrnuti");
        int pola = this->brojElemenata()/2;
        Cvor* T = prvi;
        Cvor* prijeT = prvi;
        T = T->sljedeci;
        for(int i = 1; i < pola; i++){
            T = T->sljedeci;
            prijeT = prijeT->sljedeci;
        }
        prijeT->sljedeci = T->sljedeci;
        T->sljedeci = 0;
        delete T;
        this->BrojElem--;
        int Lijevo = brojElemenata()/2;
        int i = 1;
        while(i < Lijevo){
            T = prvi;
            prvi = prvi->sljedeci;
            T->sljedeci = prijeT->sljedeci;
            prijeT->sljedeci = T;
            i++;
        }
        prijeT = prvi;
        for(int i = 1; i < brojElemenata() - 1; i++) prijeT = prijeT->sljedeci;
        T = trenutno;
        Lijevo++;
        while(Lijevo < brojElemenata()){
            zadnji->sljedeci = T->sljedeci;
            T->sljedeci = prijeT->sljedeci;
            prijeT->sljedeci = 0;
            zadnji = prijeT;
            prijeT = trenutno;
            for(int i = 1; i < brojElemenata() - i; i++) prijeT = prijeT->sljedeci;
            Lijevo++;
            T = T->sljedeci;
        }
    }
};

template <typename TipEl>
struct Cvor {
    TipEl el;
    Cvor* sljedeci;
};

template <typename TipEl>
void IzbaciIzListe(JednostrukaLista<char> &l){
        Cvor<TipEl>* pointerBeforeMax = l.prvi;
        Cvor<TipEl>* pointerToMax = 0;
        Cvor<TipEl>* temp = l.prvi;
        int max = 0;
        while(temp != 0){
            if(IsNumber(temp->sljedeci->el)){
                if(changeToNumber(temp->sljedeci->el) > max){
                    max = changeToNumber(temp->sljedeci->el);
                    pointerToMax = temp->sljedeci; 
                    pointerBeforeMax = temp;
                } 
            }
            temp = temp->sljedeci;
        }
        pointerBeforeMax->sljedeci = pointerToMax->sljedeci;
        pointerToMax->sljedeci = 0;
        delete pointerToMax;
}

bool IsNumber(char x)
{
    return (x >= '0' && x <= '9');
}

int changeToNumber(char x){
    return x - '0';
}

bool isteCifre(Lista<char> &l1, Lista<char> &l2)
{

    std::vector<int> v1;
    std::vector<int> v2;

    l1.pocetak();
    l2.pocetak();

    for(int i = 0; i < l1.brojElemenata(); i++) {
        if(IsNumber(l1.trenutni())) v1.push_back(l1.trenutni());
        l1.sljedeci();
    }
    for(int i = 0; i < l2.brojElemenata(); i++) {
        if(IsNumber(l2.trenutni())) v2.push_back(l2.trenutni());
        l2.sljedeci();
    }

    if(v1.size() != v2.size()) return false;
    else {
        for(int i = 0; i < v1.size(); i++) {
            if(v1[i] != v2[i]) return false;
        }
    }
    return true;
}


//Provjera ispravnosti !!!!!!!!!!!!!!!!!!!!
template<typename TipEl>
void Test_dodaj_ispred(NizLista<TipEl> &l)
{
    l.dodajIspred("nesto");
    l.dodajIspred("novo");
    if(l.trenutni() != "novo") {
        std::cout<<l.trenutni();
    } else std::cout<<"NOT OK";
}

template<typename TipEl>
void Test_dodaj_iza(NizLista<TipEl> &l)
{
    l.dodajIza("novo");
    l.dodajIza("nesto");
    if(l.trenutni() != "nesto") {
        std::cout<<l.trenutni();
    } else std::cout<<"NOT OK";
}

template<typename TipEl>
void Test_BrojEl(NizLista<TipEl> &l)
{
    int z = l.brojElemenata();
    TipEl el(0);
    l.dodajIspred(el);
    if(l.brojElemenata()-1 == (z)) {
        std::cout<<"OK";
    } else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_prethodni(NizLista<TipEl> &l)
{
    auto temp = l.trenutni();
    if(l.prethodni() != temp && l.brojElemenata()>1) std::cout<< "OK";
    else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_sljedeci(NizLista<TipEl> &l)
{
    auto temp = l.trenutni();
    if(l.sljedeci() != temp && l.brojElemenata()>1) std::cout<< "OK";
    else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_trenutni_const(const NizLista<TipEl> &l)
{
    auto temp = l.trenutni();
    TipEl el(0);
    l.dodajIza(el);
    if(l.trenutni() == el) std::cout<<"OK";
    else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_trenutni_nonconst(NizLista<TipEl> &l)
{
    auto temp = l.trenutni();
    TipEl el(0);
    l.trenutni() = el;
    if(l.trenutni() != temp) std::cout<<"OK";
    else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_Kraj(NizLista<TipEl> &l)
{
    l.pocetak();
    auto temp = l.trenutni();
    l.kraj();
    if(temp != l.trenutni() && l.brojElemenata() > 1) {
        std::cout<<"OK";
    } else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_Pocetak(NizLista<TipEl> &l)
{
    l.pocetak();
    auto temp = l.trenutni();
    l.kraj();
    if(temp != l.trenutni() && l.brojElemenata() > 1) {
        std::cout<<"OK";
    } else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_brisi(NizLista<TipEl> &l)
{
    int temp = l.brojElemenata();
    l.obrisi();
    if(temp != 0 && temp!=l.brojElemenata()) std::cout<<"OK";
    else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_Operator1(NizLista <TipEl> &l)
{
    auto temp = l[0];
    l[0] = new TipEl(0);
    std::cout<<temp;
}


template <typename TipEl>
void Test_Operator2(const NizLista <TipEl> &l)
{
    auto temp = l[0];
    std::cout<<temp;
}


//Test druge klase


template<typename TipEl>
void Test_dodaj_ispred1(JednostrukaLista<TipEl> &l)
{
    l.dodajIspred("nesto");
    l.dodajIspred("novo");
    if(l.trenutni() != "novo") {
        std::cout<<l.trenutni();
    } else std::cout<<"NOT OK";
}

template<typename TipEl>
void Test_dodaj_iza1(JednostrukaLista<TipEl> &l)
{
    l.dodajIza("novo");
    l.dodajIza("nesto");
    if(l.trenutni() != "nesto") {
        std::cout<<l.trenutni();
    } else std::cout<<"NOT OK";
}

template<typename TipEl>
void Test_BrojEl1(JednostrukaLista<TipEl> &l)
{
    int z = l.brojElemenata();
    TipEl el(0);
    l.dodajIspred(el);
    if(l.brojElemenata()-1 == (z)) {
        std::cout<<"OK";
    } else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_prethodni1(JednostrukaLista<TipEl> &l)
{
    auto temp = l.trenutni();
    if(l.prethodni() != temp && l.brojElemenata()>1) std::cout<< "OK";
    else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_sljedeci1(JednostrukaLista<TipEl> &l)
{
    auto temp = l.trenutni();
    if(l.sljedeci() != temp && l.brojElemenata()>1) std::cout<< "OK";
    else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_trenutni_const1(const JednostrukaLista<TipEl> &l)
{
    auto temp = l.trenutni();
    TipEl el(0);
    l.dodajIza(el);
    if(l.trenutni() == el) std::cout<<"OK";
    else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_trenutni_nonconst1(JednostrukaLista<TipEl> &l)
{
    auto temp = l.trenutni();
    TipEl el(0);
    l.trenutni() = el;
    if(l.trenutni() != temp) std::cout<<"OK";
    else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_Kraj1(JednostrukaLista<TipEl> &l)
{
    l.pocetak();
    auto temp = l.trenutni();
    l.kraj();
    if(temp != l.trenutni() && l.brojElemenata() > 1) {
        std::cout<<"OK";
    } else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_Pocetak1(JednostrukaLista<TipEl> &l)
{
    l.pocetak();
    auto temp = l.trenutni();
    l.kraj();
    if(temp != l.trenutni() && l.brojElemenata() > 1) {
        std::cout<<"OK";
    } else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_brisi1(JednostrukaLista<TipEl> &l)
{
    int temp = l.brojElemenata();
    l.obrisi();
    if(temp != 0 && temp!=l.brojElemenata()) std::cout<<"OK";
    else std::cout<<"NOT OK";
}

template <typename TipEl>
void Test_Operator11(NizLista <TipEl> &l)
{
    auto temp = l[0];
    l[0] = new TipEl(0);
    std::cout<<temp;
}


template <typename TipEl>
void Test_Operator21(const NizLista <TipEl> &l)
{
    auto temp = l[0];
    std::cout<<temp;
}
*/



/*int main()
{
    A<int> a;
    for(int i = 0; i < 5; i++) a.dodaj(i);
    */
/*    JednostrukaLista<int> l;
    for (int i(1); i<=9; i++){
        l.dodajIza(i);
        l.sljedeci();
    }
    l.pocetak();
    l.PremetNaPola();
    
    l.pocetak();
    for(int i(1); i<=8; i++) {
        if(i!=8) std::cout<<l.trenutni()<<"->";
        else std::cout<<l.trenutni();
        l.sljedeci();
    }
    */
    
    
  //  return 0;
//}

#include <iostream>
#include <stdexcept>
using namespace std;
 
template <typename Tip>
class Lista
{
public:
    Lista () {}
    virtual ~Lista() {}
    virtual int brojElemenata() const  = 0;
    virtual const Tip& trenutni () const = 0;
    virtual Tip& trenutni () = 0;
    virtual bool prethodni() = 0;
    virtual bool sljedeci() = 0;
    virtual void pocetak () = 0;
    virtual void kraj() = 0;
    virtual void obrisi () = 0;
    virtual void dodajIspred (const Tip& el) = 0 ;
    virtual void dodajIza (const Tip& el) = 0;
    virtual const Tip& operator[] (int i) const = 0;
    virtual Tip& operator[] (int i) = 0;
};
 
 
template <typename Tip>
class NizLista: public Lista <Tip>
{
private:
    Tip** niz;
    int vel, br_el, trenutan;
 
public:
 
    NizLista(): Lista<Tip>(), niz(new Tip* [1000]), br_el(0), vel(1000), trenutan(0) {} //mozda trebam naslijediti konstrzuktor iz liste
 
    NizLista(const NizLista<Tip>& lista)
    {
 
        vel = lista.vel;
        br_el = lista.br_el;
        trenutan = lista. trenutan;
        niz = new Tip* [vel]{};
        for (int i = 0; i < br_el; i++) {
            niz[i] = new Tip (*lista.niz[i]);
        }
    }
 
    ~NizLista()
    {
        for (int i = 0; i < br_el; i++) {
            delete niz[i];
        }
        delete[] niz;
 
        // br_el = 0;
        // vel = 0;
        // trenutan = 0;
    }
 
    NizLista<Tip>& operator = (const NizLista<Tip>& lista)
    {
 
        if (&lista == this) return *this;
 
 
        for (int i = 0; i < br_el; i++) {
            delete niz[i];
        }
        delete[] niz;
        br_el = 0;
        vel = 0;
        trenutan = 0;
 
        vel = lista.vel;
        br_el = lista.br_el;
        trenutan = lista. trenutan;
        niz = new Tip* [vel] {};
        for (int i = 0; i < br_el; i++) {
            niz[i] = new Tip(*lista.niz[i]);
        }
        return *this;
    }
 
 
    int brojElemenata () const
    {
        return br_el;
    }
 
     const Tip& trenutni() const
    {
 
        if (!br_el) throw std::logic_error ("Prazna lista!");
        return *niz[trenutan];
    }
 
    Tip& trenutni()
    {
 
        if (!br_el) throw std::logic_error ("Prazna lista!");
        return *niz[trenutan];
    }
 
    bool prethodni()
    {
 
        if (!br_el) throw std::logic_error ("Prazna lista!");
        if (!trenutan) return false;
        else trenutan--;
        return true;
    }
 
    bool sljedeci()
    {
 
        if (!br_el) throw std::logic_error ("Prazna lista!");
        if (trenutan == br_el - 1) return false;
        else trenutan++;
        return true;
    }
 
    void pocetak()
    {
 
        if (!br_el) throw std::logic_error ("Prazna lista!");
        trenutan = 0;
    }
    void kraj()
    {
 
        if (!br_el) throw std::logic_error ("Prazna lista");
        trenutan = br_el-1;
    }
 
    void obrisi()
    {
        if (!br_el) throw std::logic_error ("Prazna lista");
 
        delete niz[trenutan];  //probati dal moze bez ovog, dal je curenj ememorije
        for (int i = trenutan; i < br_el - 1; i++)
            niz[i] = niz[i+1];
        br_el--;
        if (trenutan == br_el && br_el>0) trenutan--;
 
    }
 
    void dodajIspred (const Tip& el)
    {
 
        if (br_el == vel) {
            vel *= 2;
            Tip** niz2 = new Tip* [vel];
            for (int i = 0; i <br_el; i++) {
                niz2[i] = niz[i];
            }
            delete[] niz;
            niz = niz2;
          // return 0;
        }
        if (!br_el) {
            niz[0] = new Tip (el);
            trenutan = 0;
            br_el++;
            //return 0;
        }
        else {
            for (int i = br_el; i > trenutan; i--) {
                niz[i] = niz[i-1];
            }
            niz[trenutan] = new Tip(el);
          /* if (br_el != 1)*/trenutan++;
            br_el++;
          // return 0;
        }
        //std::cout << "trenutni:" << trenutan << "Broj elemenata:" <<br_el;
    } //nisam pokrila slucaj kada moram kapacitet puta 2
 
    void dodajIza (const Tip& el)
    {
        if (br_el == vel) {
            vel *= 2;
            Tip** niz2 = new Tip*[vel];
            for (int i = 0; i <br_el; i++) {
                niz2[i] = niz[i];
            }
            delete[] niz;
            niz = niz2;
        }
        if (!br_el) {
            niz [0] = new Tip (el);
            trenutan = 0;
            br_el++;
 
        }
        else {
            for (int i = br_el; i > trenutan + 1; i--) {
                niz[i] = niz[i-1];
            }
            niz[trenutan+1] = new Tip (el);
            br_el++;
            //return;
        }
 
    }//nisam pokrila slucaj kapaciteta puta 2
 
    const Tip& operator[] (int i) const
    {
 
        if (i < 0 || i >= br_el) throw std::domain_error ("Nesipravan index!");
        else return *niz[i];
 
    }
 
    Tip& operator[] (int i)
    {
 
        if (i < 0 || i >= br_el) throw std::domain_error ("Neispravan index!");
        else return *niz[i];
    }
 
};
 
 
 
template <typename Tip>
class JednostrukaLista: public Lista <Tip>
{
private:
    struct Cvor {
        Tip element;
        Cvor* sljedeci;
        //Cvor (const Tip& element, Cvor* sljedeci): element(element), sljedeci(sljedeci) {}
    };
    int vel;
    Cvor* pocetak2;
    Cvor* trenutan2;
    Cvor* kraj2;
 
public:
 
    JednostrukaLista(): Lista<Tip>(), vel(0), pocetak2(0), trenutan2(0), kraj2(0) {}
 
    JednostrukaLista(const JednostrukaLista<Tip>& lista) {
 
        vel =  lista.vel;
        pocetak2 = lista.pocetak2;
        Cvor * pom = pocetak2;
        Cvor * pom2 = 0;
 
        while (pom) {
            Cvor* alocirani = new Cvor;
            alocirani -> element = pom -> element;
            if (!pom2) {
                pocetak2 = alocirani;
            }
            else pom2 -> sljedeci = alocirani;
            pom2 = alocirani;
            if (pom == lista.trenutan2) {
                trenutan2 = alocirani;
            }
            pom = pom -> sljedeci;
        }
        kraj2 = pom2;
 
    }
    ~JednostrukaLista() {
        /*Cvor* privremeni = pocetak2;
        Cvor* privremeni2(nullptr);
      while (privremeni > 0) {
            privremeni2 = privremeni;
            privremeni = privremeni -> sljedeci;
            delete privremeni2;
        }*/
        while(pocetak2!=nullptr) {
            trenutan2 = pocetak2;
            pocetak2 = pocetak2->sljedeci;
            delete trenutan2;
        }
    }
 
    JednostrukaLista<Tip>& operator = (const JednostrukaLista<Tip>& lista) {
 
        if (this == &lista) return *this;
 
         while (pocetak2 != 0) {
            trenutan2 = pocetak2;
            pocetak2 = pocetak2 -> sljedeci;
            delete trenutan2;
        }
            vel =  lista.vel;
        pocetak2 = lista.pocetak2;
        Cvor * pom = pocetak2;
        Cvor * pom2 = 0;
 
        while (pom) {
            Cvor* alocirani = new Cvor;
            alocirani -> element = pom -> element;
            if (!pom2) {
                pocetak2 = alocirani;
            }
            else pom2 -> sljedeci = alocirani;
            pom2 = alocirani;
            if (pom == lista.trenutan2) {
                trenutan2 = alocirani;
            }
            pom = pom -> sljedeci;
        }
        kraj2 = pom2;
 
        return *this;
    }
 
    virtual int brojElemenata() const
    {
        return vel;
    }
 
    virtual const Tip& trenutni () const
    {
        if (!vel) throw std::logic_error ("Prazna lista!");
        return trenutan2 -> element;
    }
 
    virtual Tip& trenutni ()
    {
        if (!vel) throw std::logic_error ("Prazna lista!");
        return trenutan2 -> element;
    }
 
    virtual bool prethodni()
    {
 
        if (!vel) throw std::logic_error ("Prazna lista!");
        if (!pocetak2) return false;
        if (trenutan2 == pocetak2) return false;
 
        auto p = pocetak2;
        while (p -> sljedeci != trenutan2) {
          p = p->sljedeci;
        }
        trenutan2 -> sljedeci = p;
        trenutan2 = p;
        return true;
    }
 
    virtual bool sljedeci()
    {
 
        if (!vel) throw std::logic_error ("Prazna lista!");
      if (!trenutan2) trenutan2 = pocetak2; //?
        if (trenutan2 -> sljedeci == 0) return false;
        trenutan2 = trenutan2 -> sljedeci;
        return true;
    }
 
    virtual void pocetak ()
    {
 
        if (!pocetak2) throw std::logic_error ("Prazna lista!");
        trenutan2 = pocetak2;
    }
 
    virtual void kraj()
    {
        if (!kraj2) throw std::logic_error ("Prazna lista!");
        Cvor* p = pocetak2;
        while ( p -> sljedeci != kraj2)
            p = p -> sljedeci;
        trenutan2 = p;
    }
 
    virtual void dodajIspred (const Tip& el)
    {
        Cvor* p = new Cvor;
        p -> element = el;
        vel++;
        if (!pocetak2) {
            pocetak2 = p;
            trenutan2 = p;
            kraj2 = p;
            p -> sljedeci = 0;
        }
        else if (trenutan2 == pocetak2){
            p -> sljedeci = pocetak2;
            pocetak2 = p;
        }
        else {
             Cvor* pom = pocetak2;
            while (pom -> sljedeci != trenutan2)
                pom = pom -> sljedeci;
            p -> sljedeci = pom -> sljedeci;
            pom -> sljedeci = p;
 
    }
    }
 
    virtual void dodajIza (const Tip& el)
    {
 
        Cvor* p = new Cvor;
        p -> element = el;
        vel++;
        if (!pocetak2) {
            pocetak2 = p;
            trenutan2 = p;
            kraj2 = p;
            p -> sljedeci = 0;
        }
        else {
            p -> sljedeci = trenutan2 -> sljedeci;
            trenutan2 -> sljedeci = p;
            if (trenutan2 == kraj2)
                kraj2 = p;
        }
    }
 
    virtual const Tip& operator[] (int i) const
    {
 
        if (i < 0 ||i >= vel) throw std::range_error ("Nepravilan index!");
 
        int brojac = 0;
        Cvor* pom = pocetak2;
 
        while (pom != nullptr) {
            if (brojac == i) return pom -> element;
            pom = pom -> sljedeci;
            brojac++;
 
        }
    }
 
    virtual Tip& operator[] (int i)
    {
 
        if (i < 0 ||i >= vel) throw std::range_error ("Nepravilan index!");
 
        int brojac = 0;
        Cvor* pom = pocetak2;
 
        while (pom != nullptr) {
            if (brojac == i) return pom -> element;
            pom = pom -> sljedeci;
            brojac++;
 
        }
    }
 
    virtual void obrisi () {
 
        if (!pocetak2) throw std::logic_error ("Prazna lista!");//nema sta brisat ako je lista orazna
        vel--;
        if (trenutan2 == pocetak2){
            pocetak2 = pocetak2 -> sljedeci;
            delete trenutan2;
            trenutan2 = pocetak2;
        if (!vel) kraj2 = 0;
        }
        else {
            Cvor* pom = pocetak2;
            while (pom -> sljedeci != trenutan2) {
                pom = pom -> sljedeci;
            }
            pom -> sljedeci = trenutan2 -> sljedeci;
            delete trenutan2;
            trenutan2 = pom -> sljedeci;
            if (!trenutan2){
                kraj2 = pom;
                trenutan2 = pom;
            }
        }
    }
};
 
template <typename Tip>
bool test_lista_brojElemenata(const Lista<Tip>& lista) {
    return lista.brojElemenata() == 10;
}
 
template <typename Tip>
bool test_lista_trenutni( Lista<Tip>& lista) {
    return lista.trenutni() = 9;
}
 
template <typename Tip>
bool test_lista_prethodni(Lista<Tip>& lista) {
    lista.prethodni();
    return lista.trenutni() == 1;
}
 
template <typename Tip>
bool test_lista_sljedeci(Lista<Tip>& lista) {
    lista.sljedeci();
    return lista.trenutni() ==7;
}
 
template <typename Tip>
bool test_lista_pocetak(Lista<Tip>& lista) {
    lista.pocetak();
    return lista.trenutni() == 0;
}
 
template <typename Tip>
bool test_lista_kraj(Lista<Tip>& lista) {
    lista.kraj();
    return lista.trenutni() = 9;
}
 
template <typename Tip>
bool test_lista_obrisi(Lista<Tip>& lista) {
    lista.obrisi();
    return lista.brojElemenata() == 4;
}
 
template <typename Tip>
bool test_lista_dodajIza(Lista<Tip>& lista) {
    lista.dodajIza(1);
    return lista.brojElemenata() == 4 && lista.sljedeci();
}
 
template <typename Tip>
bool test_lista_dodajIspred(Lista<Tip>& lista) {
    lista.dodajIspred(8);
    return lista.brojElemenata() == 5 && lista.prethodni();
}
 
template <typename Tip>
bool test_lista_operator(Lista<Tip>& lista) {
    return lista[2] = 5;
}
 
template <typename Tip>
bool test_niz_operator(NizLista<Tip>& lista) {
    return lista[2] = 5;
}
 
template <typename Tip>
bool test_lista_operator(JednostrukaLista<Tip>& lista) {
    return lista[2] = 5;
}
 
template <typename Tip>
bool ProvjeraOperatorDodjeleN (NizLista<Tip>& lista) {
    NizLista<Tip>l2;
    l2 = lista;
    return l2.brojElemenata() == lista.brojElemenata() && l2[0] == lista[0];
}

int main(){
/*JednostrukaLista<int> lista;
for (int i(1); i<=5; i++)
	lista.dodajIspred(i);
{
    JednostrukaLista<int> lista2(lista);
    JednostrukaLista<int> lista3;
    lista3=lista;
    lista.obrisi();
    std::cout << lista2.brojElemenata();
    std::cout << " " << lista3.brojElemenata() << " ";
}
std::cout << lista.brojElemenata();*/
    return 0;
}