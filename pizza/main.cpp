#include <iostream>
#include<cstring>
using namespace std;
class NegativnaVrednost{
private:
    char error[250];
public:
    NegativnaVrednost(char *error=""){
        strcpy(this->error,error);
    }
    void message(){
        cout<<error<<endl;
    }

};
class Oglas{
private:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
public:
    Oglas(char *naslov="",char *kategorija="",char *opis="",float cena=0){
        strcpy(this->naslov,naslov);
        strcpy(this->kategorija,kategorija);
        strcpy(this->opis,opis);
        this->cena=cena;
    }
    bool operator>(Oglas &o){
        if(this->cena>o.cena){
            return true;
        }
        else
            return false;
    }
    char *getKategorija(){
        return kategorija;}
    friend ostream &operator<<(ostream &out,Oglas &o){
        out<<o.naslov<<endl;
        out<<o.opis<<endl;
        out<<o.cena<<" evra"<<endl;
        return out;
    }
    float getCena(){
        return cena;}
    char *getNaslov(){
        return naslov;}
    char *getOpis(){
        return opis;}
};
class Oglasnik{
private:
    char ime[20];
    Oglas *oglasi;
    int brOglasi;
public:
    Oglasnik(){
        oglasi = new Oglas[0];
        brOglasi=0;
    }
    Oglasnik(char *ime=""){
        strcpy(this->ime,ime);
        oglasi = new Oglas[0];
        brOglasi=0;
    }
    Oglasnik &operator+=(Oglas &novOglas){
        if(novOglas.getCena()<0){
            throw NegativnaVrednost("Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!");
        }
        else{
            Oglas *tmp = new Oglas[brOglasi+1];
            for(int i=0;i<brOglasi;i++){
                tmp[i]=oglasi[i];
            }
            tmp[brOglasi++]=novOglas;
            delete []oglasi;
            oglasi=tmp;
            return *this;
        }
    }
    friend ostream &operator<<(ostream &out,Oglasnik &ogl){
        out<<ogl.ime<<endl;
        for(int i=0;i<ogl.brOglasi;i++){
            out<<ogl.oglasi[i].getNaslov()<<endl;
            out<<ogl.oglasi[i].getOpis()<<endl;
            out<<ogl.oglasi[i].getCena()<<endl;
        }
        return out;
    }
    void oglasiOdKategorija(const char *k){
        for(int i=0;i<brOglasi;i++){
            if(strcmp(oglasi[i].getKategorija(),k)==0){
                cout<<oglasi[i]<<endl;
            }
        }
    }
    void najniskaCena(){
        int ind=0;
        float najniska = oglasi[0].getCena();
        for(int i=0;i<brOglasi;i++){
            if(najniska>oglasi[i].getCena()){
                najniska=oglasi[i].getCena();
                ind=i;
            }
        }
        cout<<oglasi[ind];
    }
    ~Oglasnik(){
        delete []oglasi;
    }
};

int main(){
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            try{
                Oglas o(naslov, kategorija, opis, cena);
                ogl+=o;
            }
            catch(NegativnaVrednost &e){
            	e.message();}
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            try{
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
            }
            catch(NegativnaVrednost &e){
            	e.message();}
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}
