#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <list>
#include <queue>

using namespace std;

template <typename TipOznake>
class Grana;

template <typename TipOznake>
class Cvor;

template <typename TipOznake>
class GranaIterator;

template <typename TipOznake>
class ListaGraf;

template <typename TipOznake>
class UsmjereniGraf{
public:
    UsmjereniGraf() = default;
    virtual ~UsmjereniGraf() { };
    virtual int dajBrojCvorova() const = 0;
    virtual void postaviBrojCvorova(int brojCvorova) = 0;
    virtual void dodajGranu(int polazni, int dolazni, float tezina) = 0;
    virtual void obrisiGranu(int polazni,int dolazni) = 0;
    virtual void postaviTezinuGrane(int polazni,int dolazni, float tezina) = 0;
    virtual float dajTezinuGrane(int polazni,int dolazni) = 0;
    virtual bool postojiGrana(int polazni,int dolazni) = 0;
    virtual void postaviOznakuCvora(int cvor, TipOznake oznaka) = 0;
    virtual TipOznake dajOznakuCvora(int cvor) const = 0;
    virtual void postaviOznakuGrane(int polazni,int dolazni ,TipOznake oznaka) = 0;
    virtual TipOznake dajOznakuGrane(int polazni,int dolazni)  = 0;
    virtual Grana<TipOznake> &dajGranu(int polazni,int dolazni) = 0;
    virtual Cvor<TipOznake> &dajCvor(int cvor)= 0;
    virtual GranaIterator<TipOznake> dajGranePocetak()  = 0;
    virtual GranaIterator<TipOznake> dajGraneKraj()  = 0;
    //virtual GranaIterator<TipOznake> dajSljedecuGranu(int polazni,int dolazni)  = 0;
};

template<typename TipOznake>
class Cvor{
    TipOznake oznaka;
    UsmjereniGraf<TipOznake> *graf;
    int redniBroj;
public:
    Cvor(int redni_Broj,UsmjereniGraf<TipOznake> &u){
        graf = &u;
        redniBroj = redni_Broj;
    }
    TipOznake dajOznaku() const{
        return oznaka;   
    }
    void postaviOznaku(TipOznake o){
        oznaka = o;
    }
    int dajRedniBroj() const{
        return redniBroj;
    }
};

template<typename TipOznake>
class Grana{
    int p;
    int d;
    float tezina;
    TipOznake oznaka;
    UsmjereniGraf<TipOznake> *graf;
public:
    Grana(int a,int b,UsmjereniGraf<TipOznake> &gr,float t){
        p = a;
        d = b;
        tezina = t;
        graf = &gr;
    }
    
    Grana(const Grana<TipOznake> &g){
        p = g.p;
        d = g.d;
        tezina = g.tezina;
        graf = g.graf;
        oznaka = g.oznaka;
    }
    
    float dajTezinu(){
        return tezina;
    }
    void postaviTezinu(float t) {tezina = t;};
    TipOznake dajOznaku(){return oznaka;}
    void postaviOznaku(TipOznake o){ oznaka = o;};
    bool operator == (Grana<TipOznake> gr){
        return (gr.p == p && gr.d == d);
    }
    bool operator != (Grana<TipOznake> gr){
        return !(gr.p == p && gr.d == d);
    }
    Cvor<TipOznake> dajPolazniCvor(){
        return graf->dajCvor(p);
    }
    Cvor<TipOznake> dajDolazniCvor(){
        return graf->dajCvor(d);
    }
};

template <typename TipOznake>
class GranaIterator{
    int dolazni,polazni,pozicija;
    vector<Grana<TipOznake>> grane;
    UsmjereniGraf<TipOznake> *graf;
public:

    GranaIterator(UsmjereniGraf<TipOznake> &gr,vector<Grana<TipOznake>> g,int p,int d,int poz){
        grane = g;
        polazni = p;
        dolazni = d;
        pozicija = poz;
        graf = &gr;
    }
    
    Grana<TipOznake> operator*(){
        int brojac = 0;
        for(int i = 0;i<graf->dajBrojCvorova();i++){
            for(int j = 0;j<graf ->dajBrojCvorova();j++){
                if(graf->postojiGrana(i,j) && brojac < pozicija) brojac++;
                else if(brojac >= pozicija && graf->postojiGrana(i,j)) return graf->dajGranu(i,j);
            }
        }
    }
    
    GranaIterator(const GranaIterator<TipOznake> &g){
        dolazni = g.dolazni;
        polazni = g.polazni;
        pozicija = g.pozicija;
        grane = g.grane;
    }
    
    GranaIterator<TipOznake> &operator=(const GranaIterator<TipOznake> &g){
        dolazni = g.dolazni;
        polazni = g.polazni;
        pozicija = g.pozicija;
        grane = g.grane;
    }
    
    bool operator==(const GranaIterator &it) const{
        return(polazni == it.polazni && dolazni == it.dolazni);
    }
    
    bool operator!=(const GranaIterator &it) const{
        return!(polazni == it.polazni && dolazni == it.dolazni);
    }
    
    GranaIterator &operator++(){
        pozicija++;
        return *this;
    }
    
    GranaIterator operator++(int){
        GranaIterator temp(*this);
        ++(*this);
        return temp;
    }
};

template<typename TipOznake>
class ListaGraf: public UsmjereniGraf<TipOznake>
{
    vector<vector<int>> incidencija;
    vector<Cvor<TipOznake>> vektorcvorova;
    vector<Grana<TipOznake>> vektorgrana;
public:
    ~ListaGraf(){};
    ListaGraf(int broj){
        for(int i = 0;i<broj;i++){
            vektorcvorova.push_back(Cvor<TipOznake>(i,*this));
            incidencija.push_back(vector<int>());
        }
    }
    
    ListaGraf(const ListaGraf<TipOznake> &l){
        incidencija = l.incidencija;
        vektorcvorova = l.vektorcvorova;
        vektorgrana = l.vektorgrana;
    }
    
    ListaGraf<TipOznake> &operator =(const ListaGraf<TipOznake> &l){
        if( &l == this) return *this;
        incidencija = l.incidencija;
        vektorcvorova = l.vektorcvorova;
        vektorgrana = l.vektorgrana;
    }
    
    int dajBrojCvorova() const {return vektorcvorova.size();}
    
    void postaviBrojCvorova(int broj) {
        int temp = incidencija.size();
        for(int i = temp; i <broj; i++){
            vektorcvorova.push_back(Cvor<TipOznake> (i,*this));
            incidencija.push_back(vector<int>());
        }
    } 
    
    void dodajGranu(int polazni, int dolazni, float tezina){
        for(int j = 0;j<incidencija[polazni].size();j++){
            if(incidencija[polazni][j] == dolazni) throw "Grana postoji!";
        }
        incidencija[polazni].push_back(dolazni);
        vektorgrana.push_back(Grana<TipOznake>(polazni,dolazni,*this,tezina));
    }
    
    void obrisiGranu(int polazni, int dolazni){
        for(int j = 0;j<incidencija[polazni].size();j++){
            if(incidencija[polazni][j]==dolazni){
                incidencija[polazni].erase(incidencija[polazni].begin()+j);
                break;
            }
        }
        for(int j = 0;j<vektorgrana.size();j++){
            if(vektorgrana[j]==Grana<TipOznake>(polazni,dolazni,*this,0)){
                vektorgrana.erase(vektorgrana.begin()+j);
                break;
            }
        }
    }
    
    void postaviTezinuGrane(int polazni,int dolazni, float tezina){
        for(int i = 0;i<vektorgrana.size();i++){
            if(vektorgrana[i] == Grana<TipOznake>(polazni,dolazni,*this,tezina)){
                vektorgrana[i].postaviTezinu(tezina);
                return;
            }
        }
    }
    
    float dajTezinuGrane(int polazni,int dolazni){
        for(int i = 0;i<vektorgrana.size();i++){
            if(vektorgrana[i] == Grana<TipOznake>(polazni,dolazni,*this,0)){
                return vektorgrana[i].dajTezinu();
            }
        }
    }
    
    bool postojiGrana(int polazni,int dolazni){
        for(int i = 0;i<incidencija[polazni].size();i++){
            if(incidencija[polazni][i]== dolazni) return true;
        }
        return false;
    }
    
    void postaviOznakuCvora(int cvor, TipOznake oznaka){
        vektorcvorova[cvor].postaviOznaku(oznaka); 
    }
    
    TipOznake dajOznakuCvora(int cvor) const{
        return vektorcvorova[cvor].dajOznaku();
    }
    
    void postaviOznakuGrane(int polazni,int dolazni, TipOznake oznaka){
        for(int i = 0;i < vektorgrana.size(); i++){
            if(vektorgrana[i] == Grana<TipOznake>(polazni,dolazni,*this,0)){
                vektorgrana[i].postaviOznaku(oznaka);
                return;
            }
        }
    }
    
    TipOznake dajOznakuGrane(int polazni,int dolazni)  {
        for(int i = 0;i<vektorgrana.size();i++){
            if(vektorgrana[i] == Grana<TipOznake>(polazni,dolazni,*this,0)){
                return vektorgrana[i].dajOznaku();
            }
        }
    }
    
    Cvor<TipOznake> &dajCvor(int cvor){
        return vektorcvorova[cvor];
    }  
    
    Grana<TipOznake> &dajGranu(int polazni,int dolazni){
        for(int i = 0;i<vektorgrana.size();i++){
            if(vektorgrana[i] == Grana<TipOznake>(polazni,dolazni,*this,0)) return vektorgrana[i];
        }
    }
    
    GranaIterator<TipOznake> dajGranePocetak(){
        return GranaIterator<TipOznake> (*this,vektorgrana,vektorgrana[0].dajPolazniCvor().dajRedniBroj(),vektorgrana[0].dajDolazniCvor().dajRedniBroj(),0);
    }
    
    GranaIterator<TipOznake> dajGraneKraj(){
        return GranaIterator<TipOznake> (*this,vektorgrana,vektorgrana[vektorgrana.size()-1].dajPolazniCvor().dajRedniBroj(),vektorgrana[vektorgrana.size()-1].dajDolazniCvor().dajRedniBroj(),vektorgrana.size()-1);
    }
};





//heshmapa
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
class HashMapaLan: public Mapa<TipKljuca,TipVrijednosti>
{
    vector<list<pair<TipKljuca,TipVrijednosti>>*> el;
    int BrojEl;
    unsigned int (*pokNaFun)(TipKljuca,unsigned int);
public:  
    HashMapaLan(): el(1000),BrojEl(0),pokNaFun(nullptr){};
    
    HashMapaLan(const HashMapaLan<TipKljuca,TipVrijednosti> &m): el(m.el.size()),BrojEl(m.BrojEl),pokNaFun(m.pokNaFun){
        for(int i = 0;i<el.size();i++){
            if(m.el[i]) el[i] = new list<pair<TipKljuca,TipVrijednosti>>(*m.el[i]);
        }  
    };
    
    HashMapaLan &operator = (const HashMapaLan<TipKljuca,TipVrijednosti> &m){
        if(this==&m) return *this;
        this->obrisi();
        el.resize(m.el.size(),nullptr);
        BrojEl = m.BrojEl;
        pokNaFun = m.pokNaFun;
        for(int i = 0;i<el.size();i++){
            if(m.el[i]) el[i] = new list<pair<TipKljuca,TipVrijednosti>>(*m.el[i]);
        }
    }
    
    TipVrijednosti operator[](const TipKljuca &kljuc) const{
       if(!pokNaFun) throw "Nema hash funkcije!";
       unsigned int indeks = pokNaFun(kljuc,el.size());
       if(el[indeks]){
           for(auto it1 = el[indeks]->begin();it1!= el[indeks]->end();it1++){
               if(it1->first == kljuc) return it1->second;
           }
       }
       return TipVrijednosti{};
    };
    
    TipVrijednosti &operator[](const TipKljuca &kljuc){
        if(!pokNaFun) throw "Nema hash funkcije!";
        unsigned int indeks = pokNaFun(kljuc,el.size());
        if(el[indeks] == nullptr){
            el[indeks] = new list<pair<TipKljuca,TipVrijednosti>>{pair<TipKljuca,TipVrijednosti>(kljuc,TipVrijednosti{})};
            BrojEl++;
            auto it = el[indeks]->begin();
            return it->second;
        }else{
            auto it = el[indeks]->begin();
            for(auto it1 = el[indeks]->begin();it1!=el[indeks]->end();it1++){
                if(it1->first == kljuc) return it1->second;
            }
            while( it!= el[indeks]->end() && it->first < kljuc) it++;
            BrojEl++;
            return(el[indeks]->insert(it,pair<TipKljuca,TipVrijednosti>(kljuc,TipVrijednosti{})))->second;
        }
    };
    
    int brojElemenata() const {return BrojEl;}
    
    void obrisi(){
        for(int i = 0;i<el.size();i++){
            delete el[i];
            BrojEl = 0;
            el[i] = nullptr;
        }
    };
    
    void obrisi(const TipKljuca &kljuc){
        if(!pokNaFun) throw "Nema hash funkcije";
        unsigned int indeks = pokNaFun(kljuc,el.size());
        if(el[indeks] != nullptr){
            auto it1 = el[indeks]->begin();
            for(;it1 != el[indeks]->end();it1++){
                  if(it1->first == kljuc){
                      el[indeks]->erase(it1);
                      if(el[indeks]->empty()){
                          delete el[indeks];
                          el[indeks] = nullptr;
                      }
                      BrojEl--;
                      return;
                  }
            }
        }
    };
    
    void definisiHashFunkciju(unsigned int(*pokNaFun_)(TipKljuca,unsigned int)){
        pokNaFun = pokNaFun_;
    };
    
    ~HashMapaLan(){
        for(int i = 0; i<el.size();i++){
            delete el[i];
        }
    };
    
};


template <typename TipOznake>
void bfs(UsmjereniGraf<TipOznake> *graf, std::vector<Cvor<TipOznake>> &bfs_obilazak, Cvor<TipOznake> pocetni_cvor){
    std::queue<Cvor<TipOznake>> red;
    red.push(pocetni_cvor);
    bfs_obilazak.push_back(pocetni_cvor);
    
    while(!red.empty() && bfs_obilazak.size() != graf->dajBrojCvorova()){
        Cvor<TipOznake> cvor =  red.front();
        red.pop();
        bool pamti = false;
        std::vector<Cvor<TipOznake>> izlazeci;
        for(int i = 0;i<graf->dajBrojCvorova();i++){
            if(graf->postojiGrana(cvor.dajRedniBroj(),i)){
                izlazeci.push_back(graf->dajCvor(i));
                red.push(graf->dajCvor(i));
            }
        }
        for(int i = 0;i<izlazeci.size();i++){
            pamti = false;
            for(int j = 0;j<bfs_obilazak.size();j++){
                if(izlazeci[i].dajRedniBroj() == bfs_obilazak[j].dajRedniBroj()) pamti = true;
            }
            if(!pamti) bfs_obilazak.push_back(izlazeci[i]);
        }
    }
}


template <typename TipOznake>
void dfs(UsmjereniGraf<TipOznake> *graf,vector<Cvor<TipOznake>> &dfs_obilazak,Cvor<TipOznake> cvor){
    bool pamti = false;
    for(int i  = 0;i<dfs_obilazak.size();i++){
        if(dfs_obilazak[i].dajRedniBroj() == cvor.dajRedniBroj()){
            pamti = true;
            break;
        }
    }
    if(!pamti) dfs_obilazak.push_back(cvor);
    for(int i = 0;i<graf->dajBrojCvorova();i++){
        if(graf->postojiGrana(cvor.dajRedniBroj(),i) && !pamti){
            dfs(graf,dfs_obilazak,graf->dajCvor(i));
        }
    }
}




int main() {
UsmjereniGraf<bool> *g = new ListaGraf<bool>(6);
    g->dodajGranu(0, 1, 2.5);
    g->dodajGranu(1, 0, 1.2);
    g->dodajGranu(1, 2, 0.1);
    g->dodajGranu(0, 0, 3.14);
    for (GranaIterator<bool> iter = g->dajGranePocetak();
         iter != g->dajGraneKraj(); ++iter) cout<<"im gay";
     /* cout << "(" << (*iter).dajPolazniCvor().dajRedniBroj() << ","
           << (*iter).dajDolazniCvor().dajRedniBroj() << ") -> "
           << (*iter).dajTezinu() << "; ";*/
  delete g;
    return 0;
}
