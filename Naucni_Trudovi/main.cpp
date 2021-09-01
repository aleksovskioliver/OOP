#include <iostream>
#include<cstring>
using namespace std;

class Exception{
private:
    char error[100];
public:
    Exception(char *error=""){
        strcpy(this->error,error);}
    void message(){
        cout<<error<<endl;
    }

};
class Trud{
private:
    char type;
    int godina;
public:
    Trud(char type='\0',int godina=0){
        this->type=type;
        this->godina=godina;
    }
    char getType(){
        return type;}
    int getGodina(){
        return godina;}
    friend istream &operator>>(istream &is,Trud &t){
        is>>t.type>>t.godina;
        return is;}
};
class Student{
private:
    char ime[30];
    int index;
    int upis;
    int *oceni;
    int polozeni;
public:
    Student(char *ime,int index,int upis,int *oceni,int polozeni){
        strcpy(this->ime,ime);
        this->index=index;
        this->upis=upis;
        this->polozeni=polozeni;
        this->oceni= new int[polozeni];
        for(int i=0;i<polozeni;i++)
            this->oceni[i]=oceni[i];
    }
    virtual double rang(){
        double vkupno=0;
        for(int i=0;i<polozeni;i++){
            vkupno+=oceni[i];
        }
        return vkupno/polozeni;
    }
    friend ostream &operator<<(ostream &out,Student &s){
        out<<s.index<<" "<<s.ime<<" "<<s.upis<<" "<<s.rang()<<endl;
    }
    int getUpis(){
        return upis;}
    int getIndex(){
        return index;}
};
class PhDStudent : public Student{
private:
    Trud *trudovi;
    int brTrudovi;
    static int conference;
    static int journal;
public:
    PhDStudent(char *ime,int index,int upis,int *oceni,int polozeni,Trud *trudovi,int brTrudovi)
    :Student(ime,index,upis,oceni,polozeni){
        this->brTrudovi=brTrudovi;
        this->trudovi = new Trud[brTrudovi];
        for(int i=0;i<brTrudovi;i++)
            this->trudovi[i]=trudovi[i];
    }
    double rang(){
         double vkupno=Student::rang();
         for(int i=0;i<brTrudovi;i++){
            if(trudovi[i].getType()=='C' || trudovi[i].getType()=='c')
                vkupno+=conference;
            if(trudovi[i].getType()=='J' || trudovi[i].getType()=='j')
                vkupno+=journal;
         }
         return vkupno;
    }
    PhDStudent &operator+=(Trud &t){
        if(t.getGodina()<Student::getUpis())
            throw Exception("Ne moze da se vnese dadeniot trud");
        else{
            Trud *tmp = new Trud[brTrudovi+1];
            for(int i=0;i<brTrudovi;i++){
                tmp[i]=trudovi[i];
            }
            tmp[brTrudovi++]=t;
            delete []trudovi;
            trudovi=tmp;
            return *this;
        }
    }
    static void setConf(int c){
        PhDStudent::conference=c;}
    static void setJour(int j){
        PhDStudent::journal=j;}
};
int PhDStudent::conference=1;
int PhDStudent::journal=3;

int main()
{
    /*Trud x('c', 2020);
    int ocenki[5] = {10,10,10,10,10};
    PhDStudent pero("Pero", 185001, 2018, ocenki, 5, &x, 1);
    cout << pero;
    Trud y('c', 2021);
    pero += y;
    cout << pero;*/
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        for(int i=0; i<m; i++)
            if(dynamic_cast<PhDStudent*>(niza[i])&&niza[i]->getIndex()==indeks)
                *dynamic_cast<PhDStudent*>(niza[i]) += t;

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        for(int i=0; i<m; i++)
            if(dynamic_cast<PhDStudent*>(niza[i])&&niza[i]->getIndex()==indeks)
                *dynamic_cast<PhDStudent*>(niza[i]) += t;

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        try{
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
            cout << phd;
        }
        catch(Exception &e){	e.message();	}

    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                try{
                niza[i] = new Student(ime, indeks, god, oceni, n);
                }
                catch(Exception &e){
                	e.message();}
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                try{
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
                }
                catch(Exception &e){
                	e.message();}
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        for(int i=0; i<m; i++){
            if(dynamic_cast<PhDStudent*>(niza[i])&&niza[i]->getIndex()==indeks)
                try{    *dynamic_cast<PhDStudent*>(niza[i]) += t;   }
                catch(Exception& x) { x.message(); }
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setConf(conf);
        PhDStudent::setJour(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}
