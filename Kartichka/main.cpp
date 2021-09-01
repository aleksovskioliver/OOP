#include <iostream>
#include<cstring>
using namespace std;

class OutOfBoundException{
private:
    char error[100];
public:
    OutOfBoundException(char *error=""){
        strcpy(this->error,error);}
    void message(){
        cout<<error<<endl;
    }
};
class Karticka{
protected:
    char smetka[15];
    int pin;
    bool povekjePin;
public:
    Karticka(char *smetka="",int pin=0){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }
    virtual int tezinaProbivanje(){
        int tmp,br=0;
        tmp=pin;
        while(tmp){
            br++;
            tmp/=10;
        }
        return br;
    }
    friend ostream &operator<<(ostream &out,Karticka &k){
        out<<k.getSmetka()<<": "<<k.tezinaProbivanje()<<endl;
        return out;
    }
    char *getSmetka(){
        return smetka;}
    bool getDopolnitelenPin(){
        return povekjePin;}
};
class SpecijalnaKaricka : public Karticka{
private:
    int *pins;
    int brPin;
    const int P=4;
public:
    SpecijalnaKaricka(char *smetka,int pin):Karticka(smetka,pin){
        brPin=0;
        pins = new int[0];
        povekjePin = true;
    }
    int tezinaProbivanje(){
        int t1=Karticka::tezinaProbivanje();
        return t1+brPin;
    }
    SpecijalnaKaricka &operator+=(int novPin){
            int *tmp = new int[brPin+1];
            for(int i=0;i<brPin;i++){
                tmp[i]=pins[i];
            }
            tmp[brPin++]=novPin;
            delete []pins;
            pins=tmp;
            return *this;
        }
    ~SpecijalnaKaricka(){
        delete []pins;}
    int getBrPin(){
        return brPin;}
    const int getP(){
        return P;}
};
class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
          strcpy(this->naziv,naziv);
          for (int i=0;i<broj;i++){
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKaricka(*dynamic_cast<SpecijalnaKaricka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
          }
          this->broj=broj;
    }
    ~Banka(){
        for (int i=0;i<broj;i++) delete karticki[i];
    }
    static void setLimit(int limit){
        Banka::LIMIT=limit;
    }
    void pecatiKarticki(){
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite:"<<endl;
        for(int i=0;i<broj;i++){
            if(karticki[i]->tezinaProbivanje()<=7){
                cout<<*karticki[i];
            }
        }
    }
    void dodadiDopolnitelenPin(char *smetka,int novPin){
        bool flag = false;
            int index;
        for(int i=0;i<broj;i++){
            if(strcmp(karticki[i]->getSmetka(),smetka)==0){
                flag=true;
                index = i;
            }
        }
        if(flag){
            SpecijalnaKaricka *sk = dynamic_cast<SpecijalnaKaricka *>(karticki[index]);
            if(sk!=0){
                if(sk->getBrPin()>=sk->getP())
                    throw OutOfBoundException("Brojot na pin kodovi ne moze da go nadmine dozvolenoto");
                *sk+=novPin;
            }
        }
    }
};
int Banka::LIMIT=7;
int main(){

Karticka **niza;
int n,m,pin;
char smetka[16];
bool daliDopolnitelniPin;
cin>>n;
niza=new Karticka*[n];
for (int i=0;i<n;i++){
   cin>>smetka;
   cin>>pin;
   cin>>daliDopolnitelniPin;
   if (!daliDopolnitelniPin)
    niza[i]=new Karticka(smetka,pin);
   else
    niza[i]=new SpecijalnaKaricka(smetka,pin);
}

Banka komercijalna("Komercijalna",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;
for (int i=0;i<m;i++){
   cin>>smetka>>pin;
    try{
  	 komercijalna.dodadiDopolnitelenPin(smetka,pin);
    }
    catch(OutOfBoundException &o){
    	o.message();}
}

Banka::setLimit(5);

komercijalna.pecatiKarticki();

}
