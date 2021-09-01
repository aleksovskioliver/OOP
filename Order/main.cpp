#include<iostream>
#include<string.h>
#define MAX 50
using namespace std;

class InvalidOrderException{
private:
    char error[150];
public:
    InvalidOrderException(char *error=""){
        strcpy(this->error,error);
    }
    void print(){
        cout<<error<<endl;}

};

enum productType{
    hrana=0,pijalok,elektornika,kozmetika};

class Order{
private:
    char ime[50];
    productType type;
    float cena;
    static int osnovenPopust;
    const static int dopolnitelenPopust;
public:
    Order(char *ime="",float cena=0,productType type=hrana){
        strcpy(this->ime,ime);
        this->type=type;
        this->cena=cena;
    }
    void setDiscount1(int p){
        Order::osnovenPopust=p;
    }
    friend ostream &operator<<(ostream &out,Order &o){
        out<<o.ime<<endl;
        out<<o.cena<<endl;
        if(o.type==0)
            out<<"Hrana "<<o.osnovenPopust+o.dopolnitelenPopust<<"%"<<endl;
        else if(o.type==1)
            out<<"Pijalok "<<o.osnovenPopust+o.dopolnitelenPopust<<"%"<<endl;
        else if(o.type==2)
            out<<"Elektronika "<<o.osnovenPopust<<"%"<<endl;
        else if(o.type==3)
            out<<"Kozmetika "<<"0%"<<endl;
    }
    char *getIme(){
        return ime;}
    int getCountDiscount(){
        if(type==0){
            return osnovenPopust+dopolnitelenPopust;
        }
        else if(type==1){
            return osnovenPopust+dopolnitelenPopust;
        }
        else if(type==2){
            return osnovenPopust;
        }
        else if(type==1){
            return 0;
        }
    }
};
int Order::osnovenPopust=5;
const int Order::dopolnitelenPopust=3;
class FINKI_MARKET{
private:
    Order *orders;
    int br;
public:
    FINKI_MARKET(){
        this->orders=new Order[0];
        this->br=0;
    }
    FINKI_MARKET(Order *orders,int br){
        this->br=br;
        this->orders=new Order[br];
        for(int i=0;i<br;i++){
            this->orders[i]=orders[i];
        }
    }
    FINKI_MARKET(FINKI_MARKET &fm){
        this->br=fm.br;
        this->orders=new Order[fm.br];
        for(int i=0;i<fm.br;i++){
            this->orders[i]=fm.orders[i];
        }
    }
    FINKI_MARKET &operator=(FINKI_MARKET &fm){
        if(this!=&fm){
            this->br=fm.br;
            delete []orders;
            this->orders=new Order[fm.br];
            for(int i=0;i<fm.br;i++){
                this->orders[i]=fm.orders[i];
            }
        }
        return *this;
    }
    FINKI_MARKET &operator+=(Order &newOrder){
        bool flag=true;
        for(int i=0;i<br;i++){
            if(strcmp(orders[i].getIme(),newOrder.getIme())==0){
                flag=false;
                throw InvalidOrderException("The product for this order already exists in the list!");
            }
        }
        if(flag){
            Order *tmp = new Order[br+1];
            for(int i=0;i<br;i++){
                tmp[i]=orders[i];
            }
            tmp[br++]=newOrder;
            delete []orders;
            orders=tmp;
            return *this;
        }
    }
    void setOrders(Order *orders,int br){
        this->br=br;
        this->orders=new Order[br];
        for(int i=0;i<br;i++){
            this->orders[i]=orders[i];
        }
    }
    friend ostream &operator<<(ostream &out,FINKI_MARKET &fm){
        for(int i=0;i<fm.br;i++){
            out<<fm.orders[i];
        }
        return out;
    }
    void maxDiscount(){
        int maxIndex=0;
        int max = orders[0].getCountDiscount();
        for(int i=0;i<br;i++){
            if(max<orders[i].getCountDiscount()){
                max=orders[i].getCountDiscount();
                maxIndex=i;
            }
        }
        Order tmp;
        for(int i=0;i<br;i++){
            for(int j=0;j<br-1-i;j++){
                if(orders[i].getCountDiscount()<orders[j].getCountDiscount()){
                    tmp=orders[i];
                    orders[i]=orders[j];
                    orders[j]=tmp;
                }
            }
        }
        for(int i=0;i<br;i++){
            cout<<orders[i];
        }
        cout<<orders[maxIndex];
    }

};
int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  float price;
  int type;
  int discount;

  if (testCase == 1){
    cout << "===== Test Case - Order Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin>>price;
    cin >> type;
    cout << "===== CONSTRUCTOR ======" << endl;
    Order c(name, price, (productType) type);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Orders ======" << endl;
   cin.get();
    cin.getline(name,MAX);
    cin>>price;
    cin >> type;
    cout << "===== CONSTRUCTOR ======" << endl;
    Order c(name, price, (productType) type);
    cout << c;
    c.setDiscount1(9);
    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI_MARKET ======" << endl;
    FINKI_MARKET fc;
    int n;
    cin >> n;
    Order orders[MAX];
    for(int i = 0; i < n; ++i) {
        cin.get();
        cin.getline(name,MAX);
        cin>>price;
        cin >> type;
        Order c(name, price, (productType) type);
      orders[i] = c;
    }

    fc.setOrders(orders, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_MARKET fc;
    int n;
    cin >> n;
    Order orders[MAX];
    for(int i = 0; i < n; ++i) {
        cin.get();
        cin.getline(name,MAX);
        cin>>price;
        cin >> type;
        Order c(name, price, (productType) type);
      orders[i] = c;
    }

    fc.setOrders(orders, n);

    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin>>price;
    cin >> type;
    Order c(name, price, (productType) type);
    fc+=c;

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_MARKET fc;
    int n;
    cin >> n;
    Order orders[MAX];
    for(int i = 0; i < n; ++i) {
        cin.get();
        cin.getline(name,MAX);
        cin>>price;
        cin >> type;
        Order c(name, price, (productType) type);
      orders[i] = c;
    }

    fc.setOrders(orders, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin>>price;
    cin >> type;
    Order c(name, price, (productType) type);
    try{
      fc+=c;
    }catch(InvalidOrderException e){
      e.print();
    }

    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - maxDiscount method  ======" << endl << endl;
    FINKI_MARKET fc;
    int n;
    cin >> n;
    Order orders[MAX];
    for(int i = 0; i < n; ++i) {
        cin.get();
        cin.getline(name,MAX);
        cin>>price;
        cin >> type;
        Order c(name, price, (productType) type);
      orders[i] = c;
    }

    fc.setOrders(orders, n);

    cout << "MaxDiscount:" << endl;
    fc.maxDiscount();
    cout << fc;
  }
  return 0;

}

