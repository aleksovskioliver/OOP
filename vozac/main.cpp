#include <iostream>
#include<cstring>
using namespace std;

class Vozac{
protected:
    char ime[100];
    int vozrast;
    int brTrki;
    bool veteran;
public:
    Vozac(char *ime="",int vozrast=0,int brTrki=0,bool veteran=false){
        strcpy(this->ime,ime);
        this->vozrast=vozrast;
        this->brTrki=brTrki;
        this->veteran=veteran;
    }
    friend ostream &operator<<(ostream &out,Vozac &v){
        out<<v.ime<<endl;
        out<<v.vozrast<<endl;
        out<<v.brTrki<<endl;
        if(v.veteran)
            out<<"VETERAN"<<endl;
        return out;
    }
    bool operator==(Vozac &v){
        if(this->zarabotuvacka()==v.zarabotuvacka()){
            return true;
        }
        else
            return false;
    }
    virtual double zarabotuvacka()=0;
    virtual double danok()=0;

};
class Avtomobilist : public Vozac{
private:
    double cena;
public:
    Avtomobilist(char *ime="",int vozrast=0,int brTrki=0,bool veteran=false,double cena=0)
    :Vozac(ime,vozrast,brTrki,veteran){
        this->cena=cena;
    }
    double zarabotuvacka(){
        return cena/5;
    }
    double danok(){
        if(brTrki>10)
            return zarabotuvacka()*0.15;
        else
            return zarabotuvacka()*0.1;
    }
};
class Motociklist : public Vozac{
private:
    int mokjnost;
public:
    Motociklist(char *ime="",int vozrast=0,int brTrki=0,bool veteran=false,int mokjnost=0)
    :Vozac(ime,vozrast,brTrki,veteran){
        this->mokjnost=mokjnost;
    }
    double zarabotuvacka(){
        return mokjnost*20;
    }
    double danok(){
        if(veteran)
            return zarabotuvacka()*0.25;
        else
            return zarabotuvacka()*0.2;
    }
};
int soIstaZarabotuvachka(Vozac **vozaci,int n,Vozac *v){
    int br=0;
    for(int i=0;i<n;i++){
        if(vozaci[i]->zarabotuvacka()==v->zarabotuvacka())
            br++;
    }
    return br;
}


int main() {
	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->danok() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
	return 0;
}
