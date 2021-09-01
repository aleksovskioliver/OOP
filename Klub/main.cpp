#include <iostream>
#include<cstring>
using namespace std;

class NotValidYear{
private:
    char error[100];
public:
    NotValidYear(char *error=""){
        strcpy(this->error,error);}
    void message(){
        cout<<error<<endl;}

};

enum tipC{
    basic=0,premium};
class Chlen{
private:
    char ime[100];
    tipC tipChlen;
    int godina;
    static int osnovenPopust;
    const static int dopolnitelenPopust;
public:
    Chlen(char *ime="",tipC tipChlen=basic,int godina=0){
        strcpy(this->ime,ime);
        this->tipChlen=tipChlen;
        this->godina=godina;
    }
    static void setPopust1(int p){
        Chlen::osnovenPopust=p;
    }
    friend ostream &operator<<(ostream &out,Chlen &c){
        out<<c.ime<<endl;
        if(c.tipChlen==0){
            out<<"basic "<<c.godina<<" "<<osnovenPopust<<endl;
        }
        else if(c.tipChlen==1)
            out<<"premium "<<c.godina<<" "<<osnovenPopust+dopolnitelenPopust<<endl;
        return out;
    }
    int getGodina(){
        return godina;}
    int calcpopust() {
        if(tipChlen == basic)
            return osnovenPopust;
        if(tipChlen == premium)
            return osnovenPopust + dopolnitelenPopust;
    }
};
int Chlen::osnovenPopust=10;
const int Chlen::dopolnitelenPopust=15;

class FINKI_club{
private:
    int clenarina;
    Chlen *chlenovi;
    int brChlenovi;
public:
    FINKI_club(){
        this->chlenovi = new Chlen[0];
        this->brChlenovi=0;
    }
    FINKI_club(Chlen *chlenovi,int brChlenovi){
        this->brChlenovi=brChlenovi;
        this->chlenovi = new Chlen[brChlenovi];
        for(int i=0;i<brChlenovi;i++)
            this->chlenovi[i]=chlenovi[i];
    }
    FINKI_club &operator-=(int yr){
        if(yr<0)
            throw NotValidYear("Vnesena e negativna vrednost za godinata!");
        else{
            int br=0;
            for(int i=0;i<brChlenovi;i++){
                if(chlenovi[i].getGodina()>=yr)
                    br++;
            }
            Chlen *tmp = new Chlen[br];
            br=0;
            for(int i=0;i<brChlenovi;i++){
                if(chlenovi[i].getGodina()>=yr){
                    tmp[br]=chlenovi[i];
                    br++;
                }
            }
            chlenovi=tmp;
            brChlenovi=br;
            return *this;

        }
    }
    friend ostream &operator<<(ostream &out, FINKI_club &f){
        for(int i=0;i<f.brChlenovi;i++){
            out<<f.chlenovi[i];
        }
        return out;
    }
    void setChlenovi(Chlen *clenovi,int n){
        this->brChlenovi=brChlenovi;
        this->chlenovi = new Chlen[brChlenovi];
        for(int i=0;i<brChlenovi;i++)
            this->chlenovi[i]=chlenovi[i];
    }
    void naplatiChlenarina(){
        float suma=0;
        for(int i=0;i<brChlenovi;i++){
            suma = clenarina - (clenarina * (chlenovi[i].calcpopust()/100.0));
            cout<<chlenovi[i]<<suma<<endl;
        }
    }
};
int main(){
	int testCase;
	cin >> testCase;

	char ime[100];
    int tipChlen;
	int popust;
    int god;


	if (testCase == 1){
		cout << "===== Testiranje na klasata Chlen ======" << endl;
        cin.get();
		cin.getline(ime,100);
        cin >> tipChlen;
		cin >> god;
        cout << "===== CONSTRUCTOR ======" << endl;
		Chlen c(ime, (tipC) tipChlen, god);
		cout << c;

	}

    if (testCase == 2){
		cout << "===== Testiranje na static clenovi ======" << endl;
		cin.get();
		cin.getline(ime,100);
        cin >> tipChlen;
		cin >> god;
        cout << "===== CONSTRUCTOR ======" << endl;
		Chlen c(ime, (tipC) tipChlen, god);
		cout << c;

		c.setPopust1(5);

        cout << c;
	}

	if (testCase == 3){
		cout << "===== Testiranje na klasata FINKI-club ======" << endl;
        FINKI_club fc;
        int n;
        cin >> n;
        Chlen chlen[100];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(ime,100);
            cin >> tipChlen;
            cin >> god;
            Chlen c(ime, (tipC) tipChlen, god);
            chlen[i] = c;
        }

        fc.setChlenovi(chlen, n);

        cout << fc <<endl;
	}
	if (testCase == 4){
		cout << "===== Testiranje na operatorot -= ======" << endl;
		FINKI_club fc;
		int n;
        cin >> n;
        Chlen chlen[100];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(ime,100);
            cin >> tipChlen;
            cin >> god;
            Chlen c(ime, (tipC) tipChlen, god);
            chlen[i] = c;
        }

        fc.setChlenovi(chlen, n);
        cout << "OPERATOR -=" << endl;
        int godina;
        cin >> godina;
        fc-=godina;

        cout << fc;
	}

	if (testCase == 5){
		cout << "===== Testiranje na operatorot -= (so iskluchok) ======" << endl;
		FINKI_club fc;
		int n;
        cin >> n;
        Chlen chlen[100];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(ime,100);
            cin >> tipChlen;
            cin >> god;
            Chlen c(ime, (tipC) tipChlen, god);
            chlen[i] = c;
        }

        fc.setChlenovi(chlen, n);
        cout << "OPERATOR -=" << endl;
        int godina;
        cin >> godina;
        fc-=godina;

        cout << fc;
	}
/*
	if (testCase == 6){
		cout << "===== Testiranje na metodot naplatiChlenarina  ======" << endl << endl;
		FINKI_club fc(1000);
		int n;
        cin >> n;
        Chlen chlen[100];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(ime,100);
            cin >> tipChlen;
            cin >> god;
            Chlen c(ime, (tipC) tipChlen, god);
            chlen[i] = c;
        }

        fc.setChlenovi(chlen, n);

        cout << "Naplati chlenarina:" << endl;
        fc.naplatiChlenarina();
	}
	*/
	return 0;
}
