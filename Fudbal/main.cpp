#include <iostream>
#include<cstring>
using namespace std;

class FudbalskaEkipa{
protected:
    char name[100];
    int golovi[10];
public:
    FudbalskaEkipa(char *name,int *golovi){
        strcpy(this->name,name);
        for(int i=0;i<10;i++){
            this->golovi[i]=golovi[i];
        }
    }
    FudbalskaEkipa(FudbalskaEkipa &fk){
        strcpy(this->name,fk.name);
        for(int i=0;i<10;i++){
            this->golovi[i]=fk.golovi[i];
        }
    }
    FudbalskaEkipa &operator=(FudbalskaEkipa &fk){
        if(this!=&fk){
            strcpy(this->name,fk.name);
            delete []golovi;
            for(int i=0;i<10;i++){
                this->golovi[i]=fk.golovi[i];
            }
        }
        return *this;
    }
    virtual double uspeh() =0;
    friend ostream &operator<<(ostream &out,FudbalskaEkipa &fk){
        out<<fk.getIme()<<endl;
        out<<fk.name<<endl;
        out<<fk.uspeh()<<endl;
    return out;
    }
    virtual char *getIme()=0;

    FudbalskaEkipa &operator+=(int novi){
        int tmp[10];
        for(int i=0;i<9;i++){
            tmp[i]=golovi[i+1];
        }
        tmp[10]=novi;
        delete []golovi;
        for(int i=0;i<10;i++)
            golovi[i]=tmp[i];

        return *this;
    }
    bool operator>(FudbalskaEkipa &fk){
        if(this->uspeh()>fk.uspeh())
            return true;
        else
            return false;
    }
};
class Klub : public FudbalskaEkipa{
private:
    char ime[50];
    int tituli;
public:
    Klub(char *name,int *golovi,char *ime,int tituli)
    :FudbalskaEkipa(name,golovi){
        strcpy(this->ime,ime);
        this->tituli=tituli;
    }
    double uspeh(){
        int vkgolovi=0;
        for(int i=0;i<10;i++){
            vkgolovi+=golovi[i];
        }
        return ((vkgolovi*3)+(tituli*1000));
    }
    char *getIme(){
        return ime;}
};
class Reprezentacija : public FudbalskaEkipa{
private:
    char drzava[50];
    int nastapi;
public:
    Reprezentacija(char *name,int *golovi,char *drzava,int nastapi)
    :FudbalskaEkipa(name,golovi){
        strcpy(this->drzava,drzava);
        this->nastapi=nastapi;
    }
    char *getIme(){
        return drzava;}
    double uspeh(){
        int vkGolovi=0;
        for(int i=0;i<10;i++){
            vkGolovi+=golovi[i];
        }
        return ((vkGolovi*3)+(nastapi*50));
    }


};
void najdobarTrener(FudbalskaEkipa **fk,int n){
    double max = fk[0]->uspeh();
    int maxIndex=0;
    for(int i=0;i<n;i++){
        if(fk[i]->uspeh()>max)
            max=fk[i]->uspeh();
            maxIndex=0;
    }
    cout<<*fk[maxIndex];

}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}
