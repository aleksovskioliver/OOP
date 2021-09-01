#include <iostream>
#include<cstring>
#define MAX 100
using namespace std;

class UserExistsException{
private:
    char error[250];
public:
    UserExistsException(char *error=""){
        strcpy(this->error,error);
    }
    void message(){
        cout<<error<<endl;}

};

enum typeC{
    standard=0,loyal,vip};

class Customer{
private:
    char ime[50];
    char email[50];
    typeC vid;
    static int osnovenPopust;
    const static int dopPopust;
    int brKupuvaci;
public:
    Customer(char *ime="",char *email="",typeC vid=standard,int brKupuvaci=0){
        strcpy(this->ime,ime);
        strcpy(this->email,email);
        this->vid=vid;
        this->brKupuvaci=brKupuvaci;
    }
    friend ostream &operator<<(ostream &out,Customer &c){
        out<<c.ime<<endl;
        out<<c.email<<endl;
        out<<c.brKupuvaci<<endl;
        if(c.vid==0){
            out<<"standard "<<"0"<<endl;
        }
        else if(c.vid==1){
            out<<"loyal "<<osnovenPopust<<endl;
        }
        else if(c.vid==2){
            out<<"vip "<<dopPopust+osnovenPopust<<endl;
        }
        return out;
    }
    char *getMail(){
        return email;}
    char *getIme(){
        return ime;}
    static void setDiscount1(int popust){
        Customer::osnovenPopust=popust;}
    void setType(typeC type){
        this->vid=type;}
    void setType(int type){
        this->vid=(typeC)type;
    }
    void update(){
        if(vid==standard && brKupuvaci>5){
            vid=loyal;
        }
        else if(vid==loyal && brKupuvaci>10){
            vid=vip;
        }
    }
};
int Customer::osnovenPopust = 10;
const int Customer::dopPopust=20;

class FINKI_bookstore{
private:
    Customer *customers;
    int broj;
public:
    FINKI_bookstore(){
       this->customers = new Customer[0];
        broj=0;
    }
    FINKI_bookstore(Customer *customers,int broj){
        this->broj=broj;
        this->customers = new Customer[broj];
        for(int i=0;i<broj;i++){
            this->customers[i]=customers[i];
        }
    }
    FINKI_bookstore(FINKI_bookstore &fb){
        this->broj=fb.broj;
        this->customers = new Customer[fb.broj];
        for(int i=0;i<fb.broj;i++){
            this->customers[i]=fb.customers[i];
        }
    }
     FINKI_bookstore &operator=(FINKI_bookstore &fb){
        if(this!=&fb){
            this->broj=fb.broj;
            delete []customers;
            this->customers = new Customer[fb.broj];
            for(int i=0;i<fb.broj;i++){
                this->customers[i]=fb.customers[i];
            }
    }
    return *this;
}
    FINKI_bookstore &operator+=(Customer &c){
        bool flag=true;
        for(int i=0;i<broj;i++){
            if(strcmp(customers[i].getMail(),c.getMail())==0){
                flag=false;
                throw UserExistsException("The user already exists in the list");
            }
        }
        if(flag){
            Customer *tmp = new Customer[broj+1];
            for(int i=0;i<broj;i++){
                tmp[i]=customers[i];
            }
            tmp[broj++]=c;
            delete []customers;
            customers=tmp;
            return *this;
        }
    }
    void setCustomers(Customer *customers,int n){
        this->broj=broj;
        this->customers = new Customer[broj];
        for(int i=0;i<broj;i++){
            this->customers[i]=customers[i];
        }
    }

    friend ostream &operator<<(ostream &out,FINKI_bookstore &fb){
        for(int i=0;i<fb.broj;i++){
            out<<fb.customers[i];
        }
        return out;
    }
    ~FINKI_bookstore (){
        delete []customers;}
    void update(){
        for(int i=0;i<broj;i++){
            customers[i].update();
        }
    }
};
int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    fc+=c;

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception!!!) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    fc+=c;

    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;

}
