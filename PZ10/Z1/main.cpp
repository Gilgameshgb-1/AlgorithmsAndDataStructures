#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

template <typename TipOznake>
class Grana;

template <typename TipOznake>
class Cvor;

template <typename TipOznake>
class GranaIterator;

template <typename TipOznake>
class UsmjereniGraf{
public:
    UsmjereniGraf(int brojCvorova) {};
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
    virtual TipOznake dajOznakuGrane(int polazni,int dolazni) const = 0;
    virtual Grana<TipOznake> dajGranu(int polazni,int dolazni){
        return Grana<TipOznake>(this,polazni,dolazni);
    };
    virtual Cvor<TipOznake> dajCvor(int cvor){
        return Cvor<TipOznake>(this,cvor);
    };
    virtual GranaIterator<TipOznake> dajGranePocetak()  = 0;
    virtual GranaIterator<TipOznake> dajGraneKraj()  = 0;
    virtual GranaIterator<TipOznake> dajSljedecuGranu(int polazni,int dolazni)  = 0;
/*    friend class  Grana<TipOznake>;
    friend class  Cvor<TipOznake>;*/
};


template<typename TipOznake>
class Cvor{
    UsmjereniGraf<TipOznake> *graf;
    int redniBroj;
public:
    Cvor(UsmjereniGraf<TipOznake>* graf,int redniBroj):graf(graf),redniBroj(redniBroj){};
    TipOznake dajOznaku() const{
        return graf->dajOznakuCvora(redniBroj);
    }
    void postaviOznaku(TipOznake oznaka){
        graf->postaviOznakuCvora(redniBroj,oznaka);
    }
    int dajRedniBroj() const{
        return redniBroj;
    }
/*    friend class  Grana<TipOznake>;
    friend class  UsmjereniGraf<TipOznake>;*/
};

template <typename TipOznake>
class Grana{
    int polazni,dolazni;
    UsmjereniGraf<TipOznake>* graf;
public:
    Grana(UsmjereniGraf<TipOznake>* graf,int polazni,int dolazni):graf(graf),polazni(polazni),dolazni(dolazni){};
    float dajTezinu() const{
        return graf->dajTezinuGrane(polazni,dolazni);
    };
    void postaviTezinu(float tezina){
        graf->postaviTezinuGrane(polazni,dolazni,tezina);
    };
    TipOznake dajOznaku() const{
        return graf->dajOznakuGrane(polazni,dolazni);
    };
    void postaviOznaku(TipOznake oznaka){
        graf->postaviOznakuGrane(polazni,dolazni,oznaka);
    };
    Cvor<TipOznake> dajPolazniCvor() const {
        return graf->dajCvor(polazni);
    }
    Cvor<TipOznake> dajDolazniCvor() const{
        return graf->dajCvor(dolazni);
    }
/*    friend class  Cvor<TipOznake>;
    friend class  UsmjereniGraf<TipOznake>;*/
};


template <typename TipOznake>
class MatricaGraf: public UsmjereniGraf<TipOznake>{
    struct PodaciGrane{
        TipOznake oznaka;
        float tezina;
        bool postoji;
    };
    std::vector<std::vector<PodaciGrane>> matrica;
    std::vector<TipOznake> oznakeCvorova;
public:  
    MatricaGraf(int brojCvorova): UsmjereniGraf<TipOznake>(brojCvorova){
        postaviBrojCvorova(brojCvorova);
        oznakeCvorova.resize(brojCvorova);
        for(int i = 0; i < matrica.size(); i++){
            for(int j = 0; j<matrica.size(); j++) matrica[i][j].tezina = 999;//alociranje podataka grane
        }
    };
    int dajBrojCvorova() const {
        return matrica.size();
    };
    void postaviBrojCvorova(int brojCvorova){
        if(brojCvorova < matrica.size())
            throw "ne moze se smanjiti broj cvorova";
        PodaciGrane nepostojeca;
        nepostojeca.postoji = false;
        for(int i = 0;i<matrica.size();i++){
            matrica[i].resize(brojCvorova,nepostojeca);
        }
        std::vector<PodaciGrane> prazanRed(brojCvorova,nepostojeca);
        matrica.resize(brojCvorova,prazanRed);
    };
    void dodajGranu(int polazni, int dolazni, float tezina){
        PodaciGrane g;
        g.tezina = tezina;
        g.postoji = true;
        matrica[polazni][dolazni] = g;
        //ovo sljedece je za kruskalov algoritam ovo cini graf neusmjerenim
        //matrica[dolazni][polazni] = g;
    };
    void obrisiGranu(int polazni,int dolazni){
        matrica[polazni][dolazni].postoji = false;
    };
    void postaviTezinuGrane(int polazni,int dolazni, float tezina){
        matrica[polazni][dolazni].tezina = tezina;
    };
    float dajTezinuGrane(int polazni,int dolazni){
        return matrica[polazni][dolazni].tezina;
    };
    bool postojiGrana(int polazni,int dolazni){
        return matrica[polazni][dolazni].postoji;
    };
    void postaviOznakuCvora(int cvor, TipOznake oznaka){
        oznakeCvorova[cvor] = oznaka;
    };
     TipOznake dajOznakuCvora(int cvor) const{
        return oznakeCvorova[cvor];
    };
    void postaviOznakuGrane(int polazni,int dolazni ,TipOznake oznaka) {
        matrica[polazni][dolazni].oznaka = oznaka;
    };
    TipOznake dajOznakuGrane(int polazni,int dolazni) const {
        return matrica[polazni][dolazni].oznaka;
    };
    GranaIterator<TipOznake> dajGranePocetak()  {
        GranaIterator<TipOznake> it(this,0,-1);
        return ++it;
    };
    GranaIterator<TipOznake> dajGraneKraj()  {
        GranaIterator<TipOznake> it(this,-1,-1);
        return it;
    };
    
    GranaIterator<TipOznake> dajSljedecuGranu(int polazni,int dolazni) {
        for(int i(polazni); i<matrica.size(); i++){
            for(int j(0);j<matrica.size();j++){
                if(i == polazni && j<=dolazni) continue;
                if(matrica[i][j].postoji){
                    return GranaIterator<TipOznake>(this,i,j);
                }
            }
        }
        return GranaIterator<TipOznake>(this,-1,-1);
    };
/*    Grana<TipOznake> dajGranu(int polazni,int dolazni) const{
        return Grana<TipOznake>(this,polazni,dolazni);
    };
    Cvor<TipOznake> dajCvor(int cvor) const{
        return Cvor<TipOznake>(this,cvor);
    };*/
    void Djikstra(int pocetak){
        std::vector<double> CvorTezina(matrica.size());
        std::vector<bool> posjecen(matrica.size(), 0);
        for(int i = 0; i < matrica.size(); i++) CvorTezina[i] = 999;
        
        CvorTezina[pocetak] = 0;
        posjecen[pocetak] = true;
        
        std::vector<int> ZaIspis;
        
        for(int i = 0; i < matrica.size(); i++){
            int najblizi = dajNajblizeg(CvorTezina, posjecen);
            posjecen[najblizi] = true;
            ZaIspis.push_back(najblizi);
            for(int j = 0; j < matrica[i].size(); j++){
                if(CvorTezina[najblizi] + matrica[najblizi][j].tezina < CvorTezina[j]) {
                    CvorTezina[j] = CvorTezina[najblizi] + matrica[najblizi][j].tezina;
                }
            }
        }
        
        //ispis puta
        for(int i = 0; i < ZaIspis.size(); i++) std::cout <<"\n" << ZaIspis[i];
    }
    int dajNajblizeg(std::vector<double> &CvorTezina, std::vector<bool> &posjecen){
        int min = 999;
        int x = 0;
        for(int i = 0; i < matrica.size(); i++){
            if(CvorTezina[i] < min && !posjecen[i]){
                min = CvorTezina[i];
                x = i;
            }
        }
        return x;
    }
    void Kruskal(){
        int min = 999;
        
        int u = 0;
        int v = 0;
        int x,y;
        int BrojIvica = 1;
        int total = 0;
        std::vector<int> roditelj(matrica.size(), -1);
        
        
        while(BrojIvica < matrica.size()){
            min = 999;
            for(int i = 0; i < matrica.size(); i++){
                for(int j = 0; j < matrica.size(); j++){
                    if(matrica[i][j].tezina < min){
                        min = matrica[i][j].tezina;
                        x = u = i;
                        y = v = j;
                    }
                }
            }
            while(roditelj[u] != -1){
                u = roditelj[u];
            }
            while(roditelj[v] != -1){
                v = roditelj[v];
            }
            if(v != u){
                BrojIvica++;
                std::cout<<"\nPronasli smo ivicu: "<<"("<<x<<", "<<y<<")";
                roditelj[v] = u;
            }
            matrica[x][y].tezina = matrica[y][x].tezina = 999;
        }
    }
    void ispisi(){
        for(int i = 0; i<matrica.size();i++){
            for(int j = 0; j < matrica[i].size(); j++){
                std::cout<<"  "<<matrica[i][j].tezina;
            }
            std::cout<<"\n";
        }
    }
};

template <typename TipOznake>
class GranaIterator{
    UsmjereniGraf<TipOznake>* graf;
    int polazni,dolazni;
public:
    GranaIterator(UsmjereniGraf<TipOznake>* graf,int polazni,int dolazni): graf(graf),polazni(polazni),dolazni(dolazni){};
    Grana<TipOznake> operator*(){
        return Grana<TipOznake>(graf,polazni,dolazni);
    };
    bool operator == (const GranaIterator& iter) const{
        return (graf == iter.graf && polazni == iter.polazni && dolazni == iter.dolazni);
    };
    bool operator != (const GranaIterator& iter) const{
        return !(graf == iter.graf && polazni == iter.polazni && dolazni == iter.dolazni);

    };
    GranaIterator& operator++(){
        if(polazni == -1 && dolazni == -1){
            throw "iterator pokazuje iza kraja";
        }
        GranaIterator g = graf->dajSljedecuGranu(polazni,dolazni);
        polazni = g.polazni;
        dolazni = g.dolazni;
        return  *this;
    };
    GranaIterator operator++(int){
        GranaIterator tmp(*this);
        ++(*this);
        return tmp;
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

int main()
{
    
    MatricaGraf<int> g(6);
    g.dodajGranu(0, 1, 2);
    g.dodajGranu(0, 2, 4);
    g.dodajGranu(1, 3, 7);
    g.dodajGranu(1, 2, 1);
    g.dodajGranu(2, 4, 3);
    g.dodajGranu(4, 3, 2);
    g.dodajGranu(3, 5, 1);
    g.dodajGranu(4, 5, 5);
    
//    for(int i = 0; i <= 5; i++) g.postaviOznakuCvora(i, i);*/
/*    g.dodajGranu(0,1,3);
    g.dodajGranu(0,4,2);
    g.dodajGranu(0,2,4);
    g.dodajGranu(4,2,3);
    g.dodajGranu(4,1,5);
    g.dodajGranu(3,1,6);
    g.dodajGranu(3,2,5);
    g.dodajGranu(3,0,7);
    g.dodajGranu(4,3,4);
    g.dodajGranu(1,2,5);*/
    //g.Djikstra(0);
    
    //g.ispisi();
    
    //g.Kruskal();
    
 return 0;
}

