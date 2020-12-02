#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

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
class AVLCvor{
public:
    AVLCvor(){
        lijevo = desno = roditelj = nullptr;
    }
    AVLCvor(const TipKljuca &kljuc,const TipVrijednosti &vrijednost):kljuc(kljuc),vrijednost(vrijednost){}
    TipKljuca kljuc;
    TipVrijednosti vrijednost;
    int balans = 0;
    AVLCvor<TipKljuca,TipVrijednosti> *lijevo = 0,*desno = 0,*roditelj = 0;
};


template <typename TipKljuca,typename TipVrijednosti>
class AVLStabloMapa : public Mapa<TipKljuca, TipVrijednosti>{
    AVLCvor<TipKljuca,TipVrijednosti>* korijen;
    int BrojEl;
    
    void Brisanje(AVLCvor<TipKljuca,TipVrijednosti> *p){
        if(p){
            Brisanje(p->lijevo);
            Brisanje(p->desno);
            delete p;
        }
        korijen = nullptr;
    }
    
public:
    AVLStabloMapa() :korijen(nullptr),BrojEl(0){};
    ~AVLStabloMapa(){
        Brisanje(korijen);
    }
    AVLStabloMapa(const AVLStabloMapa/*<TipKljuca,TipVrijednosti>*/ &m):korijen(0),BrojEl(0){
        AVLCvor<TipKljuca,TipVrijednosti> *temp = m.korijen;
        Preorder(temp);
    }
    AVLStabloMapa/*<TipKljuca,TipVrijednosti>*/ &operator=(const AVLStabloMapa/*<TipKljuca,TipVrijednosti>*/ &m){
        if(&m == this) return *this;
        this->obrisi();
        korijen = 0;
        AVLCvor<TipKljuca,TipVrijednosti> *temp = m.korijen;
        Preorder(temp);
        return *this;
    }
    
    void Preorder(AVLCvor<TipKljuca,TipVrijednosti> *p){
        if(p!=0){
            this->dodaj(p->kljuc) = p->vrijednost;
            Preorder(p->lijevo);
            Preorder(p->desno);
        }
    }
    
    int brojElemenata() const {return BrojEl;}
    
    TipVrijednosti &operator[](const TipKljuca &kljuc){
        auto p = korijen;
        while(p!=0 && kljuc !=p->kljuc){
            if(kljuc < p->kljuc){
                p=p->lijevo;
            }else{
                p=p->desno;
            }
        }
        if(p != nullptr) return p->vrijednost;
        AVLCvor<TipKljuca,TipVrijednosti> * temp = new AVLCvor<TipKljuca,TipVrijednosti>(kljuc,TipVrijednosti{});
        this->Umetni(temp);
        return temp->vrijednost;
    }
    
    TipVrijednosti &dodaj(TipKljuca kljuc){
        AVLCvor<TipKljuca,TipVrijednosti> * temp = new AVLCvor<TipKljuca,TipVrijednosti>(kljuc,TipVrijednosti{});
        this->Umetni(temp);
        return temp->vrijednost;
    }
    
    TipVrijednosti operator[](const TipKljuca &kljuc) const{
       auto p = korijen;
        while(p!=0 && kljuc !=p->kljuc){
            if(kljuc < p->kljuc){
                p=p->lijevo;
            }else{
                p=p->desno;
            }
        }
        if(p!=nullptr) return p->vrijednost;
        TipVrijednosti temp{};
        return temp;
    }
    
    void obrisi(){
        Brisanje(korijen);
        BrojEl = 0;
    }
    
    void obrisi(const TipKljuca &kljuc){
        AVLCvor<TipKljuca,TipVrijednosti> *p = korijen, *q = 0;
        AVLCvor<TipKljuca,TipVrijednosti> *temp = 0,*pp=0,*rp=0;
        while(p!=0 && kljuc != p->kljuc){
            q = p;
            if(kljuc<p->kljuc) p = p->lijevo;
            else p=p->desno;
        }
        if(p==0) throw std::logic_error("Nije pronadjeno");
        if(p->lijevo == 0) rp = p->desno;
        else if(p->desno ==0) rp = p->lijevo;
        else{
            pp = p;
            rp = p->lijevo;
            temp = rp->desno;
            while(temp!=0){
                pp = rp;
                rp = temp;
                temp = rp->desno;
            }
            if(pp != p){
                pp->desno = rp->lijevo;
                rp->lijevo = p->lijevo;
                pp->roditelj = rp;
                rp->roditelj = q;
                if(pp->desno) pp->desno->roditelj = pp;
            }
            rp->desno = p->desno;
            p->desno->roditelj = rp;
        }
        if(q==0){
            korijen = rp;
            if(korijen) korijen->roditelj = nullptr;
        }else if(p == q->lijevo){
            q->lijevo = rp;
            if(rp) rp->roditelj = q;
        }else{
            q->desno = rp;
            if(rp) rp->roditelj = q;
        }
        if(p->roditelj && p->roditelj->lijevo == p) p->roditelj->balans--;
        else if(p->roditelj) p->roditelj->balans++;
        delete p;
        BrojEl--;
    }
    
    void Umetni(AVLCvor<TipKljuca,TipVrijednosti>* &z){
        AVLCvor<TipKljuca,TipVrijednosti>* y = 0, *x = korijen;
        while(x!=0){
            y=x;
            if(z->kljuc<x->kljuc) x = x->lijevo;
            else x=x->desno;
        }
        bool imaRodjaka(false);
        if(y==0){
            korijen = z;
            BrojEl++;
            imaRodjaka = true;
        }else{
            if(z->kljuc < y->kljuc){
                y->lijevo = z;
                z->roditelj = y;
                BrojEl++;
                if(y->desno){
                    imaRodjaka = true;
                    y->balans = 0;
                }
            }else{
                y->desno = z;
                z->roditelj = y;
                BrojEl++;
                if(y->lijevo){
                    imaRodjaka = true;
                    y->balans = 0;
                }
            }
        }
        if(!imaRodjaka) azurirajBalans(z);
    }
    
    void azurirajBalans(AVLCvor<TipKljuca,TipVrijednosti>* &c){
        if(c->roditelj == nullptr) return;
        if(!(c->lijevo && c->desno && c->balans == 0)){
            if(c->roditelj->lijevo == c) c->roditelj->balans++;
            else c->roditelj->balans--;
        }
        bool kontrola = true;
        AVLCvor<TipKljuca,TipVrijednosti> * r = c->roditelj;
        AVLCvor<TipKljuca,TipVrijednosti> * r1 = c;
        if(c->balans > 0 && c->roditelj->balans < -1){
            jednostrukaRotacijaUdesno(r1);
            jednostrukaRotacijaUlijevo(r);
            kontrola = false;
        }else if(c->balans < 0 && c->roditelj->balans > 1){
            jednostrukaRotacijaUlijevo(r1);
            jednostrukaRotacijaUdesno(r);
            kontrola = false;
        }else if(c->roditelj->balans < -1){
            jednostrukaRotacijaUlijevo(r);
            kontrola = false;
        }else if(c->roditelj->balans > 1){
            jednostrukaRotacijaUdesno(r);
            kontrola = false;
        }
        if(kontrola) azurirajBalans(c->roditelj);
    }
    
    void jednostrukaRotacijaUlijevo(AVLCvor<TipKljuca,TipVrijednosti> * &c){
        if(c->roditelj && c->roditelj->lijevo == c){
            c->roditelj->lijevo = c->desno;
        }else if(c->roditelj) c->roditelj->desno = c->desno;
        AVLCvor<TipKljuca,TipVrijednosti> * temp = c->desno;
        bool imaDesno = false;
        if(c->desno->lijevo){
            c->desno = temp->lijevo;
            temp->lijevo->roditelj = c;
            temp->lijevo = nullptr;
            imaDesno = true;
        }
        temp->roditelj = c->roditelj;
        if(c->roditelj) c->roditelj = temp;
        else{
            c->roditelj = temp;
            korijen = temp;
        }
        temp->lijevo = c;
        c->balans = 0;
        temp->balans = 0;
        if(!imaDesno) c->desno = nullptr;
    }
    
    void jednostrukaRotacijaUdesno(AVLCvor<TipKljuca,TipVrijednosti>* &c){
        if(c->roditelj && c->roditelj->lijevo ==  c) c->roditelj->lijevo = c->lijevo;
        else if(c->roditelj) c->roditelj->desno = c->lijevo;
        AVLCvor<TipKljuca,TipVrijednosti>* temp = c->lijevo;
        bool imaLijevo = false;
        if(c->lijevo->desno){
            c->lijevo = temp->desno;
            temp->desno->roditelj = c;
            temp->desno = nullptr;
            imaLijevo = true;
        }
        temp->roditelj = c->roditelj;
        if(c->roditelj) c->roditelj = temp;
        else{
            c->roditelj = temp;
            korijen = temp;
        } 
        temp->desno = c;
        temp->balans = 0;
        c->balans = 0;
        if(!imaLijevo) c->lijevo = nullptr;
    }
    
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

int main(){
    AVLStabloMapa<int,int> m;
    BinStabloMapa<int,int> b;
    
    clock_t vrijeme1 = clock();
    int vel = 100;
    
    for(int i = 0;i<100;i++){
        m[i]= i;
    }
    
    clock_t vrijeme2 = clock();
    
    int ukvrijeme1 = (vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Vrijeme izvrsavanja doodavanje AVL "<<ukvrijeme1<<" ms.\n";
 
    clock_t vrijeme3 = clock();
    for(int i = 0;i<100;i++){
        b[i]= i;
    }
    
    clock_t vrijeme4 = clock();
    
    int ukvrijeme2 = (vrijeme4-vrijeme3)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Vrijeme izvrsavanja dodavanje Bin "<<ukvrijeme2<<" ms.\n";
 
 
     clock_t vrijeme5 = clock();
    
    for(int i = 0;i<100;i++){
        m.obrisi(i);
    }
    
    clock_t vrijeme6 = clock();
    
    int ukvrijeme3 = (vrijeme6-vrijeme5)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Vrijeme izvrsavanja brisanje AVL "<<ukvrijeme3<<" ms.\n";
 
    clock_t vrijeme7 = clock();
    for(int i = 0;i<100;i++){
        b.obrisi(i);
    }
    
    clock_t vrijeme8 = clock();
    
    int ukvrijeme4 = (vrijeme8-vrijeme7)/(CLOCKS_PER_SEC/1000);
    std::cout<<"Vrijeme izvrsavanja brisanje Bin "<<ukvrijeme4<<" ms.";
 
 
 //AVL RADI DOSTA BRZE OD BIN 
 
    return 0;
}
