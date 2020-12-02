#include <iostream>
#include <vector>

template <typename TipEl>
class BazniStack
{
public:
    BazniStack() {};
    virtual ~BazniStack() {};
    virtual void brisi() = 0;
    virtual void stavi(const TipEl &el) = 0;
    virtual TipEl skini() = 0;
    virtual TipEl &vrh() = 0;
    virtual int brojElemenata() = 0;
};

template <typename TipEl>
class Red: public BazniStack<TipEl>
{
    TipEl* red;
    int kapacitet = 1000000;
    int pocetak;
    int kraj;
    //int FIFO = 0;
public:
    Red() : pocetak(-1),kraj(-1)
    {
        red = new TipEl[kapacitet];
    };
    Red(const Red<TipEl> &s)
    {
        pocetak = s.pocetak;
        kraj = s.kraj;
        red = new TipEl[kapacitet];
        for(int i = 0; i<kraj-pocetak+1; i++) {
            red[i] = s.red[i];
        }
    }
    void Prosiri()
    {
        kapacitet *=2;
        TipEl* Tmpred = new TipEl[kapacitet];
        for(int i =0; i<kraj-pocetak+1; i++) {
            Tmpred[i] = red[i];
        }
        delete[] red;
        red = Tmpred;
    }
    Red &operator = (const Red<TipEl> &s)
    {
        if(&s == this) return *this;
        delete[] red;
        pocetak = s.pocetak;
        kraj = s.kraj;
        red = new TipEl[kapacitet];
        for(int i = 0; i<kraj-pocetak+1; i++) {
            red[i] = s.red[i];
        }
        return *this;
    }
    
    ~Red()
    {
        delete[] red;
    };
    void brisi()
    {
        delete[] red;
        red = new TipEl[kapacitet];
        pocetak = -1;
        kraj = -1;
    };
    void stavi(const TipEl &el)
    {
        kraj = (kraj+1)%kapacitet;
        red[kraj] = el;
        if(pocetak == -1) pocetak = 0;
    };
    TipEl skini()
    {
       if(pocetak == -1) throw "Red je prazan!";
        TipEl temp = red[pocetak];
        if(pocetak == kraj) pocetak = kraj = -1;
        else pocetak = (pocetak+1)%kapacitet;
        return temp;
    };
    TipEl &vrh()
    {
        return red[pocetak];
    };
    int brojElemenata()
    {
        if(pocetak == -1) return 0;
        return kraj-pocetak+1;
    };
};

//TESTOVI METODA

template <typename TipEl>
void TestBrisi(Red<TipEl> &s){
    int temp = s.brojElemenata();
    s.brisi();
    if(temp != s.brojElemenata() && s.brojElemenata() == 0) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void TestStavi(TipEl &el,Red<TipEl> &s){
    int broj = s.brojElemenata();
    s.stavi(el);
    if(s.brojElemenata() > broj) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void TestSkini(Red<TipEl> &s){
    int temp = s.brojElemenata();
    s.skini();
    if(temp != s.brojElemenata()) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void Testvrh(Red<TipEl> &s){
    //2 je drugi uneseni element u mainu
    if(2 == s.vrh()) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void TestBrojaElemenata(Red<TipEl> &s){
    int temp = s.brojElemenata();
    s.skini();
    if(temp != s.brojElemenata()) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
class Stek: public BazniStack<TipEl>
{
    TipEl* stack;
    int kapacitet = 100;
    int top;
public:
    Stek() : top(-1) {stack = new TipEl[kapacitet];};
    Stek(const Stek<TipEl> &s){
        top = s.top;
        stack = new TipEl[kapacitet];
        for(int i = 0;i<top+1;i++){
            stack[i] = s.stack[i];
        }
    }
    void Prosiri(){
        kapacitet *=2;
        TipEl* TmpStack = new TipEl[kapacitet];
        for(int i =0;i<top+1;i++){
            TmpStack[i] = stack[i];
        }
        delete[] stack;
        stack = TmpStack;
    }
    Stek &operator = (const Stek<TipEl> &s){
        if(&s == this) return *this;
        delete[] stack;
        top = s.top;
        stack = new TipEl[kapacitet];
        for(int i = 0;i<top+1;i++){
            stack[i] = s.stack[i];
        }
        return *this;
    }
    ~Stek()
    {
        delete[] stack;
    };
    void brisi()
    {
        delete[] stack;
        stack = new TipEl[kapacitet];
        top = -1;
    };
    void stavi(const TipEl &el)
    {
        if(top+1>=kapacitet) Prosiri();
        stack[++top] = el;
    };
    TipEl skini()
    {
        if(top == -1) throw "Stack je prazan!";
        TipEl temp = stack[top--];
        return temp;
    };
    TipEl &vrh()
    {
        return stack[top];
    };
    int brojElemenata()
    {
        return top+1;
    };
};
//for(int i = 0;i<br;i++) r.stavi(r.skini)

//ZADACI SA TUTORIJALA 4

//SREDNJA VRIJEDNOST

//OVO RADI
template <typename TipEl>
void IzbacivanjeSrednjeVrijednosti(Red<TipEl> &r){
    double suma = 0;
    for(int i = 0;i<r.brojElemenata();i++){
        TipEl temp = r.skini();
        suma += temp;
        r.stavi(temp);
    }//O(n)
    suma = suma/r.brojElemenata();
    for(int i = 0;i<r.brojElemenata();i++){
        TipEl temp = r.skini();
        if(suma>temp){
        }else{
            r.stavi(temp);
        }
    }//O(n)
}//KOMPLEKSNOST O(n)

void ParnoNeparnoRedovi(Red<int> &r1, Red<int> &r2){
    int vel2 = r2.brojElemenata();
    int k = 0;
    int z = 0;
    for(int i = 0; i < vel2; i++){
        if(r2.vrh() % 2 == 0) {
            r1.stavi(r2.skini());
            z++;
        }else r2.stavi(r2.skini());
    }
    int vel1 = r1.brojElemenata() - z;
    for(int i = 0; i < vel1; i++){
        if(r1.vrh() % 2 == 0) {
            r1.stavi(r1.skini());
        }else{ 
            r2.stavi(r1.skini());
            k++;
        }
    }
    vel1 = r2.brojElemenata() - k;
    for(int i = 0; i < vel1; i++){
        r2.stavi(r2.skini());
    }
}

int SumaSteka(Stek<int> s){
    if(s.brojElemenata() == 1) return s.skini();
    else return s.skini() + SumaSteka(s);
}

/*void Isprepleti(Stek<Red<int>> &s,Red<int> &r1, Red<int> &r2){
    int vel = r1.brojElemenata();
    while( i <= vel){
        int el = r1.vrh();
        r1.stavi(el);
        if(i!=vel){
            int el2;
            if(i > r1.brojElemenata()){
                el2 = r2.vrh();
                r2.skini();
            }else{
                el2 = r1.vrh();
                r1.skini();
                r1.stavi()
            }
        }
    }
}



int ispreplitaniRedovi(Stek<Red<int>> &s, Red<int> &r){
    if(s.brojElemenata() != 0){
        Red<int> red = s.vrh();
        s.skini();
        Red<int> pomocni = s.vrh();
        Isprepleti(red, r, pomocni);
        ispreplitaniRedovi(s, r);
        s.push_(red);
    }
}*/

int pretraga(std::vector<Stek<int>> vs, Red<int> r){
    int indeks, min;
    int rSize = r.brojElemenata();
    int sumaReda = 0;
    for(int i = 0; i < rSize; i++){
        int T = r.skini();
        sumaReda += T;
        r.stavi(T);
    }
    min = SumaSteka(vs[0]);
    for(int i = 1; i < vs.size(); i++){
        if(abs(sumaReda - min) > abs(sumaReda - SumaSteka(vs[i]))){
            indeks = i;
            min = SumaSteka(vs[i]);
        }
    }
    return indeks;
}

int binarnaPretragaMax(std::vector<int> v, int l, int d){
    int j = (l+d)/2;
    if(v[j - 1] < v[j] && v[j] > v[j + 1]) return j;
    else if(v[j - 1] < v[j] && v[j + 1] > v[j]) return binarnaPretragaMax(v, j, d);
    else return binarnaPretragaMax(v, 0, j);
}

int pretraga(Red<Stek<int>> r, std::vector<int> vec){
    int indeksNajveci = binarnaPretragaMax(vec, 0, vec.size());
    int vel = r.brojElemenata();
    for(int i = 0; i < vel; i++){
        if(SumaSteka(r.vrh()) < vec[indeksNajveci]){
            r.skini();
        }else{
            r.stavi(r.skini());
        }
    }
    return r.brojElemenata();
}

int main()
{
    
   Red<int> s1;
    s1.stavi(2);
    s1.stavi(5);
    s1.stavi(9);
    s1.stavi(12);
    s1.stavi(14);
    s1.stavi(16);
    
    Red<int> s2;
    s2.stavi(6);
    
    Red<int> s3;
    s3.stavi(1);
    
    Red<int> r;
    r.stavi(3);
    r.stavi(7);
    r.stavi(11);
    
    Stek<Red<int>> v;
    v.stavi(s1);
    v.stavi(s2);
    v.stavi(s3);

    ispreplitaniRedovi(v, r);

    return 0;
}
