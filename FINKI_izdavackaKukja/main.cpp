#include<iostream>
#include<cstring>
using namespace std;

class Book{
protected:
    char isbn[20];
    char naslov[50];
    char avtor[30];
    int cena;
public:
    Book(char *isbn="",char *naslov="",char *avtor="",int cena=0){
        strcpy(this->isbn,isbn);
        strcpy(this->naslov,naslov);
        strcpy(this->avtor,avtor);
        this->cena=cena;
    }
    virtual float bookPrice()=0;

    bool operator>(Book &b){
        if(this->cena>b.cena){
            return true;}
        else return false;
    }
    friend ostream &operator<<(ostream &out,Book &b){
        out<<b.isbn<<": "<<b.naslov<<", "<<b.avtor<<" "<<b.bookPrice()<<endl;
        return out;
    }
    void setISBN(char *i){
        strcpy(this->isbn,i);}
};
class OnlineBook : public Book{
private:
    char *url;
    int size;
public:
    OnlineBook(char *isbn,char *naslov,char *avtor,int cena,char *url,int size)
    :Book(isbn,naslov,avtor,cena){
        this->size=size;
        this->url = new char[strlen(url)+1];
        strcpy(this->url,url);
    }
    float bookPrice(){
        if(size>20){
            return cena*1.2;
        }
        else {
            return cena;}
    }
};
class PrintBook : public Book{
private:
    float masa;
    bool zaliha;
public:
    PrintBook(char *isbn="",char *naslov="",char *avtor="",int cena=0,float masa=0,bool zaliha=false)
    :Book(isbn,naslov,avtor,cena){
        this->masa=masa;
        this->zaliha=zaliha;
    }
    float bookPrice(){
        if(masa>0.7){
            return cena*1.15;
        }
        else return cena;
    }
};
void mostExpensiveBook (Book** books, int n){
    float najskapa = books[0]->bookPrice();
    int online=0,pecateni=0,maxIndex=0;
    for(int i=0;i<n;i++){
        OnlineBook *o=dynamic_cast<OnlineBook *>(books[i]);
        if(o!=0)
            online++;
        else
            pecateni++;
        if(books[i]->bookPrice()>najskapa){
            najskapa=books[i]->bookPrice();
            maxIndex=i;
        }
    }
    cout<<"Finki-Education"<<endl;
    cout<<"Total number of online books: "<<online<<endl;
    cout<<"Total number of print books: "<<pecateni<<endl;
    cout<<"The most expensive book is: "<<endl;
    cout<<*books[maxIndex];
}
int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}
