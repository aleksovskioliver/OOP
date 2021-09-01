#include <iostream>
#include<cstring>
using namespace std;

class BadInputException{
private:
    char error[100];
public:
    BadInputException(char *error=""){
        strcpy(this->error,error);
    }
    void message(){
        cout<<error<<endl;}
};
class StudentKurs{
   protected:
       char ime[30];
       int ocenkaPismeno;
       bool daliUsno;
       static int MAX;
   public:
    StudentKurs(char* ime,int finalenIspit){
       strcpy(this->ime,ime);
       this->ocenkaPismeno=finalenIspit;
       this->daliUsno=false;
     }
     static void setMAX(int max){
        StudentKurs::MAX=max;
     }
     static const int MINOCENKA = 6;

     int ocenka(){}

    friend ostream &operator<<(ostream &out,StudentKurs &sk){
        out<<sk.getIme()<<" --- "<<sk.ocenka();
        return out;
    }
    char *getIme(){
        return ime;}
    bool getDaliUsno(){
        return daliUsno;}
    int getOcenka(){
        return ocenkaPismeno;}
};
int StudentKurs::MAX=10;
class StudentKursUsno : public StudentKurs{
private:
    char *ocenaUsno;
public:
    StudentKursUsno(char* ime="",int finalenIspit=0,char *ocenaUsno="")
    :StudentKurs(ime,finalenIspit){
        this->ocenaUsno = new char[strlen(ocenaUsno)+1];
        strcpy(this->ocenaUsno,ocenaUsno);
    }
    int ocenka(){
        int vkupna = StudentKurs::getOcenka();
        if(strcmp(ocenaUsno,"odlicen")==0){
            return vkupna+2;
        }
        else if(strcmp(ocenaUsno,"dobro")==0){
            return vkupna+1;
        }
        else if(strcmp(ocenaUsno,"losho")==0){
            return vkupna-1;
        }
    }
    friend ostream &operator<<(ostream &out,StudentKursUsno &sku){
        out<<sku.ocenka()<<endl;
        return out;
    }
    StudentKursUsno &operator+=(char *ocenkaUsno){
        int n = strlen(ocenkaUsno);
        bool flag=false;
        for(int i=0;i<n;i++){
            if(!isalpha(ocenaUsno[i])){
                flag=true;
                break;}
        }
        if(flag)
            throw BadInputException("Greshna opisna ocenka");
        else{
            this->daliUsno=true;
            this->ocenaUsno = new char[n];
            strcpy(this->ocenaUsno,ocenkaUsno);
            return *this;
        }
    }
};
class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
      strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++){
        //ako studentot ima usno isprashuvanje
        if (studenti[i]->getDaliUsno()){
            this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
        }
        else this->studenti[i]=new StudentKurs(*studenti[i]);
      }
      this->broj=broj;
    }
    ~KursFakultet(){
    for (int i=0;i<broj;i++) delete studenti[i];
    }
    void pecatiStudenti(){
        cout<<"Kursot "<<naziv<<" go polozile:"<<endl;
        for(int i=0;i<broj;i++){
            if(studenti[i]->ocenka()>=6){
                cout<<*studenti[i];
            }
        }
    }
    int ocenka(){

    }
    void postaviOpisnaOcenka(char *ime,char *opisnaOcenka){
        for(int i=0;i<broj;i++){
            if(strcmp(studenti[i]->getIme(),ime)==0){
                StudentKursUsno *s = dynamic_cast<StudentKursUsno *>(studenti[i]);
                if(s!=0){
                    (*s)+=opisnaOcenka;
                }
            }
        }
    }

};

int main(){

StudentKurs **niza;
int n,m,ocenka;
char ime[30],opisna[10];
bool daliUsno;
cin>>n;
niza=new StudentKurs*[n];
for (int i=0;i<n;i++){
   cin>>ime;
   cin>>ocenka;
   cin>>daliUsno;
   if (!daliUsno)
    niza[i]=new StudentKurs(ime,ocenka);
   else
    niza[i]=new StudentKursUsno(ime,ocenka);
}

KursFakultet programiranje("OOP",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;

for (int i=0;i<m;i++){
   cin>>ime>>opisna;
   try{
  	 programiranje.postaviOpisnaOcenka(ime,opisna);
   }
   catch(BadInputException &e){
        e.message();
        }
}

StudentKurs::setMAX(9);

programiranje.pecatiStudenti();

}
