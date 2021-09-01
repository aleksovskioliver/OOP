#include <iostream>
#include<cstring>
using namespace std;

class Folder{
private:
    char *ime;
    char *sopstvenik;
    int sirina,visina;
public:

    Folder(char *ime="untitled"){
       this->ime = new char[strlen(ime)+1];
        strcmp(this->ime,ime);
    }
    friend ostream &operator<<(ostream &out,Folder &f){
        out<<f.ime;
        return out;
    }

};

int main() {

  char ime[12];
  cin>>ime;
  Folder folder(ime);
  cout<<folder;

    return 0;
};
