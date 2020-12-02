#include <iostream>

template <typename TipEl>
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
};

template <typename TipEl>
class DvostrukaLista : public Lista<TipEl>
{
    struct Cvor {
        TipEl element;
        Cvor* sljedeci = nullptr;
        Cvor* prethodni = nullptr;
    };
    Cvor* head;
    Cvor* tail;
    Cvor* tekuci;
    int BrEl;
public:
    DvostrukaLista()
    {
        head = nullptr;
        tail = nullptr;
        tekuci = nullptr;
        BrEl = 0;
    };
    /*DvostrukaLista &operator = (const DvostrukaLista<TipEl> &L)
    {
        if(&L != this) {
            Cvor* temp1 = L.head;
            Cvor* temp2 = nullptr;
            while(temp1 != nullptr) {
                Cvor* novi = new Cvor;
                novi->element = temp1->element;
                if(temp2 == nullptr) {
                    head = novi;
                }else{
                    temp2->sljedeci = novi;
                }
                temp2 = novi;
                if(temp1 == L.tekuci){
                    tekuci = novi;
                }
                temp1 = temp1->sljedeci;
            }
            tail = temp2;
        }
        return *this;
    }*/
    ~DvostrukaLista()
    {
        while(head!=nullptr) {
            tekuci = head;
            head = head->sljedeci;
            delete tekuci;
        }
        tail = nullptr;
        tekuci = nullptr;
    };
    int brojElemenata() const
    {
        return BrEl;
    };
    TipEl& trenutni()
    {
        return tekuci->element;
    };
    TipEl trenutni() const
    {
        return tekuci->element;
    };
    bool prethodni()
    {
        if (tekuci == head) {
            return false;
        }
        tekuci = tekuci->prethodni;
        return true;
    };
    bool sljedeci()
    {
        if (tekuci == tail) {
            return false;
        }
        tekuci = tekuci->sljedeci;
        return true;
    };
    void pocetak()
    {
        tekuci = head;
    };
    void kraj()
    {
        tekuci = tail;
    };
    void obrisi()
    {
        BrEl--;
        if(tekuci == head) {
            head = head->sljedeci;
            delete tekuci;
            tekuci = head;
            if(BrEl == 0) tail=head = nullptr;
        } else if(tekuci == tail) {
            tail = tail->prethodni;
            delete tekuci;
            tekuci = tail;
            if(BrEl == 0) head=tail = nullptr;
        } else {
            Cvor* temp = tekuci->sljedeci;
            tekuci->prethodni->sljedeci = tekuci->sljedeci;
            tekuci->sljedeci->prethodni = tekuci -> prethodni;
            delete tekuci;
            if(tekuci == nullptr) tail = tekuci;
            tekuci = temp;
        }
    };
    void dodajIspred(const TipEl& el)
    {
        Cvor* temp = new Cvor;
        temp->element = el;
        temp->sljedeci = nullptr;
        temp->prethodni = nullptr;
        if(BrEl == 0) {
            head = temp;
            tekuci = temp;
            tail = temp;
            BrEl++;
        } else {
            temp->sljedeci = tekuci;
            temp->prethodni = tekuci->prethodni;
            if(tekuci->prethodni!=nullptr) {
                tekuci->prethodni->sljedeci = temp;
            }
            tekuci->prethodni = temp;
            if(head==tekuci) head = temp;
            BrEl++;
        }
    };
    void dodajIza(const TipEl& el)
    {
        Cvor* temp = new Cvor;
        temp->element = el;
        temp->sljedeci = nullptr;
        temp->prethodni = nullptr;
        if(BrEl == 0) {
            head = temp;
            tekuci = temp;
            tail = temp;
            BrEl++;
        } else {
            temp->sljedeci = tekuci->sljedeci;
            tekuci->sljedeci = temp;
            temp->prethodni = tekuci;
            if(temp->sljedeci != nullptr) {
                tekuci->sljedeci->prethodni = temp;
            }
            if(tail == tekuci) tail = temp;
            BrEl++;
        }
    };
    TipEl& operator[](int x )
    {
        if(x<0 || x>= BrEl) throw "Van opsega!";
        Cvor* temp = head;
        for(int i = 0; i<x; i++) {
            temp = temp->sljedeci;
        }
        return temp->element;
    };
    TipEl operator[](int x ) const
    {
        if(x<0 || x>= BrEl) throw "Van opsega!";
        Cvor* temp = head;
        for(int i = 0; i<x; i++) {
            temp = temp->sljedeci;
        }
        return temp->element;
    };
};


template <typename TipEl>
class Iterator{
    const DvostrukaLista<TipEl> *l;
    typename DvostrukaLista<TipEl>::Cvor *trenutniL;
public:
    Iterator(const Lista<TipEl> &lista){
        DvostrukaLista<TipEl> &pok = (DvostrukaLista<TipEl> &)lista;
        this->lista = &pok;
        
    }
};

template <typename Tip>
Tip dajMaksimum(const Lista<Tip> &n)
{
    Tip max = n[n.brojElemenata()-2];
/*    for(int i = 0; i<n.brojElemenata(); i++){
        if(n[i] > max) max = n[i]; INDEKSIRANJE DAJE LOSE PERFORMANSE, UVODI SE ITERATOR
    }*/
    return max;
}

//TESTNE METODE

/*  
    virtual TipEl& operator[](int x ) = 0;
    virtual TipEl operator[](int x ) const = 0;*/

template <typename TipEl>
void brojElemenataTest(DvostrukaLista<TipEl> &l){
    int temp = l.brojElemenata();
    l.dodajIza(8);
    if(l.brojElemenata() > temp) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void TrenutniNonConst(DvostrukaLista<TipEl> &l){
    if(l.trenutni() == 1) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void TrenutniConst(const DvostrukaLista<TipEl> &l){
    if(l.trenutni() == 1) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void PrethodniTest(DvostrukaLista<TipEl> &l){
    if(l.prethodni() == NULL) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void SljedeciTest(DvostrukaLista<TipEl> &l){
    if(l.sljedeci() == 1) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void PocetakTest(DvostrukaLista<TipEl> &l){
    l.pocetak();
    if(l.trenutni() == 1) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void KrajTest(DvostrukaLista<TipEl> &l){
    l.kraj();
    if(l.trenutni() == 2) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void ObrisiTest(DvostrukaLista<TipEl> &l){
    l.obrisi();
    if(l.brojElemenata() == 9) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void DodajIspredTest(DvostrukaLista<TipEl> &l){
    l.dodajIspred(2);
    l.prethodni();
    if(l.trenutni() == 2) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void DodajIzaTest(DvostrukaLista<TipEl> &l){
    l.dodajIza(3);
    l.sljedeci();
    if(l.trenutni() == 3) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void TestiranjeOperatora1(DvostrukaLista<TipEl> &l){
    if(l[0] == 1) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}


template <typename TipEl>
void TestiranjeOperatora2(const DvostrukaLista<TipEl> &l){
    if(l[0] == 1) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

int main()
{
    Lista<int>* l;
    l = new DvostrukaLista<int>;
    for (int i(1); i<=5; i++){
    	l->dodajIza(i);
        l->sljedeci();
    }
    l->pocetak();
    for (int i(0); i<5; i++)
    	std::cout << (*l)[i] << " ";
    delete l;

    return 0;
}
