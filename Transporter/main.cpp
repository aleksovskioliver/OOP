#include <iostream>
#include<cstring>
using namespace std;

class Transport{
protected:
    char *destinacija;
    int cena;
    int rastojanie;
public:
    Transport(char *destinacija="",int cena=0,int rastojanie=0){
        this->destinacija = new char[strlen(destinacija)+1];
        strcpy(this->destinacija,destinacija);
        this->cena=cena;
        this->rastojanie=rastojanie;
    }
    virtual float cenaTransport() = 0;
    bool operator<(Transport &t){
        if(this->rastojanie<t.getRastojanie()){
            return true;
        }
        else
            return false;
    }
    int getRastojanie(){
        return rastojanie;}
    char *getDestinacija(){
        return destinacija;}
    int getCena(){
    	return cena;}
};
class AvtomobilTransport : public Transport{
private:
    bool sofer;
public:
    AvtomobilTransport(char *destinacija="",int cena=0,int rastojanie=0,bool sofer=false)
    :Transport(destinacija,cena,rastojanie){
        this->sofer=sofer;
    }
    float cenaTransport(){
        if(sofer)
            return cena*1.2;
        else
            return cena;
    }
};
class KombeTransport : public Transport{
private:
    int brPatnici;
public:
    KombeTransport(char *destinacija="",int cena=0,int rastojanie=0,int brPatnici=0)
    :Transport(destinacija,cena,rastojanie){
        this->brPatnici=brPatnici;
    }
    float cenaTransport(){
        float c=Transport::getCena();
        for(int i=0;i<brPatnici;i++){
            c=c-200;
        }
        return c;
    }
};
void pecatiPoloshiPonudi(Transport **ponudi,int n,AvtomobilTransport &at){
    int br=0,j=0;
    Transport **tmp = new Transport*[n];
    for(int i=0;i<n;i++){
        if(ponudi[i]->cenaTransport()>at.cenaTransport()){
            tmp[j]=ponudi[i];
            j++;
            br++;
        }
    }
    Transport *pom;
    for(int i=0;i<br-1;i++){
        for(int j=0;j<br-1-i;j++){
            if(tmp[j]->cenaTransport()>tmp[j+1]->cenaTransport()){
                pom=tmp[j];
                tmp[j]=tmp[j+1];
                tmp[j+1]=pom;
            }
        }
    }
    for(int i=0;i<n;i++){
        cout<<tmp[i]->getDestinacija()<<" "<<tmp[i]->getRastojanie()<<" "<<tmp[i]->cenaTransport()<<endl;
    }
}


int main(){

char destinacija[20];
int tip,cena,rastojanie,lugje;
bool shofer;
int n;
cin>>n;
Transport  **ponudi;
ponudi=new Transport *[n];

for (int i=0;i<n;i++){

    cin>>tip>>destinacija>>cena>>rastojanie;
    if (tip==1) {
        cin>>shofer;
        ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

    }
    else {
        cin>>lugje;
        ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
    }


}

AvtomobilTransport nov("Ohrid",2000,600,false);
pecatiPoloshiPonudi(ponudi,n,nov);

for (int i=0;i<n;i++) delete ponudi[i];
delete [] ponudi;
return 0;
}
