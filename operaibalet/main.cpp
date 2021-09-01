#include <iostream>
#include<cstring>
using namespace std;

class Delo{
private:
    char ime[50];
    int godina;
    char zemja[50];
public:
    Delo(char *ime="",int godina=0,char *zemja=""){
        strcpy(this->ime,ime);
        this->godina=godina;
        strcpy(this->zemja,zemja);
    }
    bool operator==(Delo &d){
        if(strcmp(this->ime,d.getIme())==0)
            return true;
        else
            return false;
    }
    char *getIme(){
        return ime;}
    int getGodina(){
        return godina;}
    char *getZemja(){
        return zemja;}

};
class Pretstava{
protected:
    Delo delo;
    int brKarti;
    char data[15];
public:
    Pretstava(Delo delo,int brKarti,char *data){
        this->brKarti=brKarti;
        this->delo=delo;
        strcpy(this->data,data);
    }
    virtual int cena(){
        int m=0,n=0;
        int god=delo.getGodina();

        if(god>1900)
            m=50;
        else if(god>1800)
            m=75;
        else
            m=100;
        if(strcmp(delo.getZemja(),"Rusija")==0)
            n=150;
        else if(strcmp(delo.getZemja(),"Italija")==0)
            n=100;
        else
            n=80;
        return n+m;
    }
    int getKarti(){
        return brKarti;}
    Delo getDelo(){
        return delo;}
};
class Opera : public Pretstava{
private:
public:
    Opera(Delo delo,int brKarti,char *data):Pretstava(delo,brKarti,data){}
};
class Balet : public Pretstava{
private:
    static int cenaBalet;
public:
    Balet(Delo delo,int brKarti,char *data):Pretstava(delo,brKarti,data){
    }
    int cena(){
        int vkupna=Pretstava::cena();
        return vkupna+cenaBalet;
    }
    static void setCenaBalet(int c){
        Balet::cenaBalet=c;
    }
};
int Balet::cenaBalet=150;

int prihod(Pretstava **pretstavi,int n){
    int vkupno=0;
    for(int i=0;i<n;i++){
        vkupno+=pretstavi[i]->cena()*pretstavi[i]->getKarti();
    }
    return vkupno;
}
int brojPretstaviNaDelo(Pretstava **pretstavi,int n,Delo &d){
    int br=0;
    for(int i=0;i<n;i++){
        if(pretstavi[i]->getDelo()==d)
            br++;
    }
    return br;
}
//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;

    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;

    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();

        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

    }break;

    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();

        }
        cout<<prihod(pole,n);
    }break;

    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;

    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }

        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;

    };


return 0;
}
