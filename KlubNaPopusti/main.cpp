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
    basic,premium};

class Chlen{
private:
    char name[100];
    tipC tipChlen;
    static int osnovenPopust;
    const static int dopolitelenPopust;
    int god;
public:
    Chlen(char *name="",tipC tipChlen=basic,int god=0){
        strcpy(this->name,name);
        this->tipChlen=tipChlen;
        this->god=god;
    }
    double popust(){
        if(tipChlen==0){
            return osnovenPopust;
        }
        else if(tipChlen==1){
            return osnovenPopust+dopolitelenPopust;
        }
    }
    static void setPopust1(int p){
        osnovenPopust=p;
    }
    friend ostream &operator<<(ostream &out,Chlen &c){
        out<<c.name<<endl;
        if(c.tipChlen==0){
            out<<"Basic ";
        }
        else if(c.tipChlen==1){
            out<<"Premium ";
        }
        out<<c.god<<" "<<c.popust()<<endl;
    }
    int getGod(){
        return god;}
    char *getName(){
        return name;}
    tipC getTipChlen(){
        return tipChlen;}
};
int Chlen::osnovenPopust=0.1;
const int Chlen::dopolitelenPopust=0.15;

class FINKI_club{
private:
    int osnovnaClenarina;
    Chlen *chlenovi;
    int brChlenovi;
public:
    FINKI_club(){
        this->osnovnaClenarina=0;
        this->chlenovi=new Chlen[0];
        this->brChlenovi=brChlenovi;
    }
    FINKI_club(Chlen *clenovi,int brChlenovi){
        this->brChlenovi=brChlenovi;
            for(int i=0;i<brChlenovi;i++){
                this->chlenovi[i]=chlenovi[i];
        }
    }
    void setChlenovi(Chlen *clenovi,int brChlenovi){
        this->brChlenovi=brChlenovi;
            for(int i=0;i<brChlenovi;i++){
                this->chlenovi[i]=chlenovi[i];
        }
    }
    FINKI_club &operator-=(int godina){
        if(godina<0){
            throw NotValidYear("Nevalidna godina");
        }
        else{
            Chlen *tmp;
            for(int i=0;i<brChlenovi;i++){
                if(godina<chlenovi[i].getGod()){
                    tmp[i]=chlenovi[i];
                }
            }
            delete[]chlenovi;
            chlenovi=tmp;
            return *this;
        }
    }
    friend ostream &operator<<(ostream &out,FINKI_club &fc){
        for(int i=0;i<fc.brChlenovi;i++){
            out<<fc.chlenovi[i].getName()<<endl;
            if(fc.chlenovi[i].getTipChlen()==0){
                out<<"basic ";
            }
            else if(fc.chlenovi[i].getTipChlen()==1){
                out<<"premium ";
            }
            out<<fc.chlenovi[i].getGod()<<" "<<fc.chlenovi[i].popust()<<endl;
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
