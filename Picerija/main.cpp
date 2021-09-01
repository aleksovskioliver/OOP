#include <iostream>
#include<cstring>
using namespace std;

enum Size{
    mala=0,golema,familijarna};
class Pizza{
protected:
    char name[20];
    char ingredients[100];
    float inPrice;
public:
    Pizza(char *name="",char *ingredients="",float inPrice=0){
        strcpy(this->name,name);
        strcpy(this->ingredients,ingredients);
        this->inPrice=inPrice;
    }
    friend ostream &operator<<(ostream &out,Pizza &p){
        out<<p.name<<": "<<p.ingredients;
        return out;
        }
    virtual float ProdaznaCena() = 0;
    bool operator<(Pizza &p){
        if(this->ProdaznaCena()<p.ProdaznaCena()){
            return true;
        }
        else
            return false;
    }
};
class FlatPizza : public Pizza{
private:
    Size size;
public:
    FlatPizza(char *name="",char *ingredients="",float inPrice=0,Size size=mala)
    :Pizza(name,ingredients,inPrice){
        this->size=size;
    }
    float ProdaznaCena(){
        if(size==0){
            return inPrice*0.1;
        }
        else if(size==1){
            return inPrice*0.3;
        }
        else if(size==2){
            return inPrice*0.5;
        }
    }
    friend ostream &operator<<(ostream &out,FlatPizza &fp){
        out<<fp.name<<": "<<fp.ingredients<<", ";
        if(fp.size==0){
            out<<"small - ";
        }
        else if(fp.size==1){
            out<<"big - ";
        }
        else if(fp.size==2){
            out<<"family - ";
        }
        out<<fp.ProdaznaCena()<<endl;
        return out;
    }
     double price(){
        return inPrice;
    }
};
class FoldedPizza : public Pizza{
private:
    bool brasno;
public:
    FoldedPizza(char *name="",char *ingredients="",float inPrice=0,bool brasno=false)
    :Pizza(name,ingredients,inPrice){
        this->brasno=brasno;
    }
    float ProdaznaCena(){
        if(brasno){
            return inPrice*0.1;
        }
        else {
            return inPrice*0.3;
        }
    }
    friend ostream &operator<<(ostream &out,FoldedPizza &ff){
       out<<ff.name<<": "<<ff.ingredients<<", ";
        if(ff.brasno){
            out<<"wf ";
        }
        else{
            out<<"nwf ";
        }
        out<<ff.ProdaznaCena()<<endl;
        return out;
    }
    void setWhiteFlour(bool flour){
        brasno=flour;
    }
    double price(){
        return inPrice;
    }
};
void expensivePizza(Pizza **pizzi,int n){
    float maxCena = pizzi[0]->ProdaznaCena();
    int maxIndex;
    for(int i=0;i<n;i++){
        if(pizzi[i]->ProdaznaCena()>maxCena){
            maxCena=pizzi[i]->ProdaznaCena();
            maxIndex=i;
        }
    }
    cout<<*pizzi[maxIndex];
}

int main() {
  int test_case;
  char name[20];
  char ingredients[100];
  float inPrice;
  Size size;
  bool whiteFlour;

  cin >> test_case;
  if (test_case == 1) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FlatPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 2) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    int s;
    cin>>s;
    FlatPizza fp(name, ingredients, inPrice, (Size)s);
    cout << fp;

  } else if (test_case == 3) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 4) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    fp.setWhiteFlour(false);
    cout << fp;

  } else if (test_case == 5) {
	// Test Cast - operator <, price
    int s;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp1;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp2;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
    cout << *fp3;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
    fp4->setWhiteFlour(false);
    cout << *fp4;

    cout<<"Lower price: "<<endl;
    if(*fp1<*fp2)
        cout<<fp1->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp1<*fp3)
        cout<<fp1->price()<<endl;
    else cout<<fp3->price()<<endl;

    if(*fp4<*fp2)
        cout<<fp4->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp3<*fp4)
        cout<<fp3->price()<<endl;
    else cout<<fp4->price()<<endl;

  } else if (test_case == 6) {
	// Test Cast - expensivePizza
    int num_p;
    int pizza_type;

    cin >> num_p;
    Pizza **pi = new Pizza *[num_p];
    for (int j = 0; j < num_p; ++j) {

      cin >> pizza_type;
      if (pizza_type == 1) {
        cin.get();
        cin.getline(name,20);

        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << (*fp);
        pi[j] = fp;
      }
      if (pizza_type == 2) {

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp =
            new FoldedPizza (name, ingredients, inPrice);
        if(j%2)
          (*fp).setWhiteFlour(false);
        cout << (*fp);
        pi[j] = fp;

      }
    }

    cout << endl;
    cout << "The most expensive pizza:\n";
    expensivePizza(pi,num_p);


  }
  return 0;
}
