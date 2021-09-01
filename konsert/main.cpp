#include <iostream>
#include<cstring>
using namespace std;

class Koncert{
protected:
    char naziv[20];
    char lokacija[20];
    static float sezonskiPopust;
    double cenaBilet;
public:
    Koncert(char *naziv="",char *lokacija="",double cenaBilet=0){
        strcpy(this->naziv,naziv);
        strcpy(this->lokacija,lokacija);
        this->cenaBilet=cenaBilet;
    }
    static void setSezonskiPopust(float s){
        Koncert::sezonskiPopust=s;
    }
    virtual float cena(){
        return (cenaBilet-(cenaBilet*sezonskiPopust));
    }
    char *getNaziv(){
        return naziv;}
    friend ostream &operator<<(ostream &out,Koncert &k){
        out<<k.naziv<<": "<<k.cena()<<endl;
    }
    static float getSezonskiPopust(){
        return sezonskiPopust;}
};
float Koncert::sezonskiPopust=0.2;
class ElektronskiKoncert : public Koncert{
private:
    char *Dj;
    float casovi;
    bool zabava;
public:
    ElektronskiKoncert(char *naziv="",char *lokacija="",double cenaBilet=0,char *Dj="",float casovi=0,bool zabava=false)
    :Koncert(naziv,lokacija,cenaBilet){
        this->Dj = new char[strlen(Dj)+1];
        strcpy(this->Dj,Dj);
        this->casovi=casovi;
        this->zabava=zabava;
    }
    float cena(){
        int vkupna=Koncert::cena();
        if(casovi>7)
            vkupna+=360;
        else if(casovi>5)
            vkupna+=150;
        if(zabava)
            vkupna-=50;
        else
            vkupna+=100;
        return vkupna;
    }
};
void najskapKoncert(Koncert ** koncerti, int n){
    int vkupno=0,elektronski=0;
    int maxIndex=0;
    float maxCena = koncerti[0]->cena();
    for(int i=0;i<n;i++){
        ElektronskiKoncert *ek = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
        if(ek!=0){
            elektronski++;
        }
        if(maxCena<koncerti[i]->cena()){
            maxCena=koncerti[i]->cena();
            maxIndex=i;
        }
    }
    cout<<"Najskap koncert: "<<*koncerti[maxIndex];
    cout<<"Elektronski koncerti: "<<elektronski<<" od vkupno "<<n<<endl;
}
bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski){
    bool flag = false;
    for(int i=0;i<n;i++){
        if(elektronski==true && dynamic_cast<ElektronskiKoncert *>(koncerti[i])){
            flag=true;
            cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena();
        }
        else{
            if(elektronski==false && strcmp(koncerti[i]->getNaziv(),naziv)==0){
                flag=true;
                cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena();
            }
        }
    }
    return flag;
}
int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

        cin>>tip;
        if (tip==1){//Koncert
        	cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
        }
        else if (tip==2){//cena - Koncert
            cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
        }
        else if (tip==3){//ElektronskiKoncert
            cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
            ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
            cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
        }
        else if (tip==4){//cena - ElektronskiKoncert
             cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
             ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
             cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
        }
        else if (tip==5) {//najskapKoncert

        }
        else if (tip==6) {//prebarajKoncert
            Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
        	najskapKoncert(koncerti,5);
        }
        else if (tip==7){//prebaraj
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
            bool elektronski;
        	cin>>elektronski;
        	if(prebarajKoncert(koncerti,5, "Area",elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

            if(prebarajKoncert(koncerti,5, "Area",!elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

        }
        else if (tip==8){//smeni cena
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[2] -> setSezonskiPopust(0.9);
        	najskapKoncert(koncerti,4);
        }

    return 0;
}
