#include <iostream>
#include<cstring>
using namespace std;
class InvalidProductionDate{
private:
    char error[250];
public:
  InvalidProductionDate(char *error=""){
    strcpy(this->error,error);
  }
    void message(){
        cout<<error<<endl;}
};
enum tip{
    smartphone=0,computer};

class Device{
private:
    char ime[100];
    tip Tip;
    static double proverka;
    int godina;
public:
    Device(char *ime="",tip Tip=smartphone,int godina=0){
        strcpy(this->ime,ime);
        this->Tip=Tip;
        this->godina=godina;
    }
    static void setPocetniCasovi(double casovi){
        Device::proverka=casovi;
    }
    friend ostream &operator<<(ostream &out,Device &dev){
        out<<dev.ime<<endl;
        if(dev.Tip==0){
            out<<"Mobilen ";
        }
        else if(dev.Tip==1){
            out<<"Laptop ";
        }
        if(dev.godina>2015 && dev.Tip==1){
            out<<proverka+4<<endl;
        }
        else if(dev.godina>2015 || dev.Tip==1){
            out<<proverka+2<<endl;
        }
        else{
            out<<proverka<<endl;
        }
        return out;
    }
    int getGodina(){
        return godina;}
};
double Device::proverka=1;
class MobileServis{
private:
    char address[100];
    Device *devices;
    int brUredi;
public:
    MobileServis(){
        devices = new Device[0];
        brUredi=0;
    }
    MobileServis(char *addres=""){
        strcpy(this->address,addres);
        devices=new Device[0];
        brUredi=0;
    }
    MobileServis(MobileServis &mob){
        this->brUredi=mob.brUredi;
        strcpy(this->address,mob.address);
        this->devices = new Device[mob.brUredi];
        for(int i=0;i<mob.brUredi;i++){
            devices[i]=mob.devices[i];
        }
    }
    MobileServis &operator=(MobileServis &mob){
        if(this!=&mob){
            this->brUredi=mob.brUredi;
            strcpy(this->address,mob.address);
            delete []devices;
            this->devices = new Device[mob.brUredi];
            for(int i=0;i<mob.brUredi;i++){
                devices[i]=mob.devices[i];
            }
        }
            return *this;
    }
    MobileServis &operator+=(Device &newDevice){
        if(newDevice.getGodina()>2019 || newDevice.getGodina()<2000){
            throw InvalidProductionDate("Невалидна година на производство");
        }
        else{
            Device *tmp = new Device[brUredi+1];
            for(int i=0;i<brUredi;i++){
                tmp[i]=devices[i];
            }
            tmp[brUredi++]=newDevice;
            delete devices;
            devices=tmp;
            return *this;
        }
    }
    void pecatiCasovi(){
        cout<<"Ime: "<<address<<endl;
        for(int i=0;i<brUredi;i++){
            cout<<devices[i];
        }
    }

    ~MobileServis(){
        delete []devices;}

};

int main()
{
	int testCase;
	cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> tipDevice;
		cin >> godina;
		Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
		MobileServis t(ime);
        cout<<ig;
		}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
	}
	if (testCase == 3){
		cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
        try{
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
            }
       catch(InvalidProductionDate &e){
            	e.message();}
        }
        t.pecatiCasovi();
	}

	if (testCase == 4){
		cout <<"===== Testiranje na konstruktori ======"<<endl;
		 cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
           try{
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
           }
            catch(InvalidProductionDate &e){
            	e.message();}


        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}
	if (testCase == 5){
		cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            t+=tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
		Device::setPocetniCasovi(2);
        t.pecatiCasovi();
	}

		if (testCase == 6){
		cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
		cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try{
          	     Device tmp(ime,(tip)tipDevice,godina);
           		 t+=tmp;
            }
            catch(InvalidProductionDate &e){
            	 e.message();
            }
        }
		Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}

	return 0;

}
