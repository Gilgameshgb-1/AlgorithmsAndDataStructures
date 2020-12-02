#include <iostream>
#include <vector>

class MaxHeap{
    int* niz;
    int kapacitet;
    int velicina;
public:
    MaxHeap(int max){
        kapacitet = max;
        velicina = 0;
        niz = new int[kapacitet];
        for(int i = 0; i < kapacitet; i++) niz[i] = -1;
    }
    ~MaxHeap(){delete[] niz;}
    int LijevoDijete(int i){return 2*i + 1;}
    int DesnoDijete(int i){return 2*i + 2;}
    int Roditelj(int i){return (i-1)/2;}
    bool JeLiList(int i) const {return (i >= velicina/2 && i < velicina);}
    int DajVelicinu() const {return velicina;}
    void Prikazi() const{ for(int i = 0; i < velicina; i++) std::cout<<niz[i]<<" ";}
    void UmetniUGomilu(const int& x){
        niz[velicina] = x;
        PopraviGore(velicina);
        velicina++;
    }
    void PopraviGore(int i){
        while(niz[i] > niz[Roditelj(i)]){
            int temp = niz[i];
            niz[i] = niz[Roditelj(i)];
            niz[Roditelj(i)] = temp;
            i = Roditelj(i);
        }
    }
    int Izbaci(){
        int temp = niz[0];
        PopraviDolje();
        return temp;
    }
    void PopraviDolje(int i = 0){
        if(velicina == 0) return;
        niz[i] = niz[--velicina];
        while(niz[i] < niz[LijevoDijete(i)] || niz[i] < niz[DesnoDijete(i)]){
            if(niz[LijevoDijete(i)] > niz[DesnoDijete(i)]){
                int temp = niz[i];
                niz[i] = niz[LijevoDijete(i)];
                niz[LijevoDijete(i)] = temp;
                i = LijevoDijete(i);
            }else{
                int temp = niz[i];
                niz[i] = niz[DesnoDijete(i)];
                niz[DesnoDijete(i)] = temp;
                i = DesnoDijete(i);
            }
        }
    }
};

std::vector<int> HeapSort(MaxHeap H){
    std::vector<int> v;
    while(H.DajVelicinu() != 1) v.push_back(H.Izbaci());
    return v;
}

int main(){
    MaxHeap h(100);
    h.UmetniUGomilu(40);
    h.UmetniUGomilu(30);
    h.UmetniUGomilu(20);
    h.UmetniUGomilu(10);
    h.UmetniUGomilu(25);
    h.UmetniUGomilu(9);
    h.UmetniUGomilu(11);
    h.UmetniUGomilu(60);
    
    //h.Izbaci();
    h.Prikazi();
    
    int x = h.DajVelicinu();
    
    for(int i = 0; i < x; i++) std::cout<<" "<<h.Izbaci();
    
    //std::vector<int> v = HeapSort(h);
    //std::cout<<"\nSortiran Heap\n";
    //for(int i = 0; i < v.size(); i++) std::cout<<" "<<v[i];
    return 0;
}