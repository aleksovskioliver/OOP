#include <iostream>
#include<cstring>
using namespace std;

class SMS{
protected:
    float cena;
    char tel[12];
public:
    SMS(char *tel="",float cena=0){
        strcpy(this->tel,tel);
        this->cena=cena;
    }
    virtual float SMS_cena()=0;
    friend ostream &operator<<(ostream &out,SMS &sms){
        out<<sms.tel<<": "<<sms.cena;
        return out;
    }
};
class RegularSMS : public SMS{
private:
    char *sodrzina;
    bool roaming;
    static double rProcent;
    static const double danok;

public:
    RegularSMS(char *tel="",float cena=0,char *sodrzina="",bool roaming=false)
    :SMS(tel,cena){
        this->sodrzina = new char[strlen(sodrzina)+1];
        strcpy(this->sodrzina,sodrzina);
        this->roaming=roaming;
    }
    float SMS_cena(){
        float vkupna=0;
        int len = (strlen(sodrzina)-1)/16;
            if(roaming==true){
                return len * (cena*rProcent);
                }
            else{
                len*((cena*danok)+cena);
            }
    }
    static void set_rProcent(double procent){
        RegularSMS::rProcent=procent;
    }
};
double RegularSMS::rProcent= 3;
const double RegularSMS::danok=0.18;

class SpecialSMS : public SMS{
private:
    bool hum;
public:
    SpecialSMS(char *tel="",float cena=0,bool hum=false)
    :SMS(tel,cena){
        this->hum=hum;
    }
    float SMS_cena(){
        if(hum=false){
            return cena*0.18*1.5;
        }
        else{
            return cena*1.5;
        }
    }
};
void vkupno_SMS(SMS** poraka, int n){
    int regular=0,special=0;
    float regcena=0,speccena=0;
    for(int i=0;i<n;i++){
        RegularSMS *rs = dynamic_cast<RegularSMS *>(poraka[i]);
        if(rs!=0){
            regular++;
            regcena+=poraka[i]->SMS_cena();
        }
        SpecialSMS *ss = dynamic_cast<SpecialSMS *>(poraka[i]);
        if(ss!=0){
            special++;
            speccena+=poraka[i]->SMS_cena();
        }
    }
    cout<<regular<<" "<<regcena;
    cout<<special<<" "<<speccena;
}


int main(){

	char tel[20], msg[1000];
	float cena;
	float price;
    int p;
	bool roam, hum;
	SMS  **sms;
	int n;
	int tip;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing RegularSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new RegularSMS(tel, cena, msg, roam);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 2){
		cout << "====== Testing SpecialSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
			cin >> hum;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new SpecialSMS(tel, cena, hum);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 3){
		cout << "====== Testing method vkupno_SMS() ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i<n; i++){

			cin >> tip;
			cin >> tel;
			cin >> cena;
			if (tip == 1) {

				cin.get();
				cin.getline(msg, 1000);
                cin >> roam;

				sms[i] = new RegularSMS(tel, cena, msg, roam);

			}
			else {
				cin >> hum;

				sms[i] = new SpecialSMS(tel, cena, hum);
			}
		}

		vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
    if (testCase == 4){
		cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			sms1 = new RegularSMS(tel, cena, msg, roam);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
        	cin >> p;
        	RegularSMS::set_rProcent(p);
        	sms2 = new RegularSMS(tel, cena, msg, roam);
        	cout << *sms2;

        delete sms1, sms2;
	}
    if (testCase == 5){
		cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
			cin >> hum;
			sms1 = new SpecialSMS(tel, cena, hum);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
			cin >> hum;
        	cin >> p;

        	sms2 = new SpecialSMS(tel, cena, hum);
        	cout << *sms2;

        delete sms1, sms2;
	}

	return 0;
}
