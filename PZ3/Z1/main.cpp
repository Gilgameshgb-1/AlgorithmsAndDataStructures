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
    virtual TipEl &vrh() = 0;
    virtual int brojElemenata() = 0;
};

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


//TESTOVI METODA

template <typename TipEl>
void Testbrisi(Stek<TipEl> &s){
    s.brisi();
    if(s.brojElemenata() == 0) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void TestStavi(const TipEl &el,Stek<TipEl> &s){
    int brojel = s.brojElemenata(); 
    s.stavi(el);
    if(s.brojElemenata() != brojel && el == s.vrh()) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void TestSkini(Stek<TipEl> &s){
    TipEl temp(0);
    int tmp = s.brojElemenata();
    s.stavi(temp);
    TipEl povratno = s.skini();
    if(temp == povratno && s.brojElemenata() == tmp) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void TestVrh(Stek<TipEl> &s){
    TipEl temp = TipEl(0);
    s.stavi(TipEl(0));
    if(s.vrh() == temp) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

template <typename TipEl>
void TestBrojaElemenata(Stek<TipEl> &s){
    int temp = s.brojElemenata();
    s.brisi();
    if(s.brojElemenata() != temp && temp!=0) std::cout<<"OK\n";
    else std::cout<<"NIJE OK\n";
}

//V

int main()
{
    Stek<int> s;
    for (int i(1); i<=5; i++){
       s.stavi(i);
    }
	TestVrh(s);
	TestSkini(s);
	TestBrojaElemenata(s);
	Testbrisi(s);
	TestStavi(2,s);
    return 0;
}
