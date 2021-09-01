#include <iostream>
#include<cstring>
using namespace std;

class Server{
protected:
    char IP[45];
    char host[100];
public:
    Server(char *IP="",char *host=""){
        strcpy(this->IP,IP);
        strcpy(this->host,host);
    }
    Server(const Server &s){
        strcpy(this->IP,s.IP);
        strcpy(this->host,s.host);
    }
    Server &operator=(const Server &s){
        if(this!=&s){
        strcpy(this->IP,s.IP);
        strcpy(this->host,s.host);
        }
        return *this;
    }
    virtual float total_price()=0;
    bool operator>(Server &s){
        if(this->total_price()>s.total_price())
            return true;
        else return false;
    }
};
class DedicatedServer : public Server{
private:
    float osnovnaCena;
    int RAM;
    int *hardDisc;
    int brDisc;
public:
    DedicatedServer(char *IP,char *host,float osnovnaCena,int RAM)
    :Server(IP,host){
        this->osnovnaCena=osnovnaCena;
        this->RAM=RAM;
        this->brDisc=brDisc;
        for(int i=0;i<brDisc;i++){
            this->hardDisc[i]=hardDisc[i];
        }
    }
    DedicatedServer(const Server &s,float osnovnaCena,int RAM,int *hardDisc,int brDisc)
    :Server(s){
        this->osnovnaCena=osnovnaCena;
        this->RAM=RAM;
        this->brDisc=brDisc;
        for(int i=0;i<brDisc;i++){
            this->hardDisc[i]=hardDisc[i];
        }
    }
    DedicatedServer(const DedicatedServer &ds)
    :Server(ds){
        this->osnovnaCena=ds.osnovnaCena;
        this->RAM=ds.RAM;
        this->brDisc=ds.brDisc;
        for(int i=0;i<ds.brDisc;i++){
            this->hardDisc[i]=ds.hardDisc[i];
        }
    }
    DedicatedServer &operator=(const DedicatedServer &ds)
    {   if(this!=&ds){
            strcpy(this->IP,ds.IP);
            strcpy(this->host,ds.host);
            this->osnovnaCena=ds.osnovnaCena;
            this->RAM=ds.RAM;
            this->brDisc=ds.brDisc;
            delete []hardDisc;
            for(int i=0;i<ds.brDisc;i++){
                this->hardDisc[i]=ds.hardDisc[i];
            }
    }
    return *this;
}

    int getHardDisc(){
        int vkHard=0;
        for(int i=0;i<brDisc;i++){
            vkHard+=hardDisc[i];
        }
        return vkHard;
    }
    float total_price(){
        return osnovnaCena+(getHardDisc()*0.5)+(RAM*20);
    }
    DedicatedServer &operator+=(int hard){
        int *tmp;
        tmp= new int[brDisc+1];
        for(int i=0;i<brDisc;i++){
            tmp[i]=hardDisc[i];
        }
        tmp[brDisc++]=hard;
        delete []hardDisc;
        hardDisc=tmp;
        return *this;
    }
    DedicatedServer operator++(int){
        DedicatedServer d(*this);
        RAM++;
        return d;
    }
    friend ostream &operator<<(ostream &out,DedicatedServer &ds){
        out<<ds.host<<": "<<ds.IP<<endl;
        out<<ds.total_price()<<", "<<ds.RAM<<endl;
        out<<ds.brDisc<<", "<<ds.getHardDisc()<<endl;
        return out;
    }
};
class VirtualServer : public Server{
private:
    int jadra;
    int protok;
public:
    VirtualServer(char *IP,char *host,int jadra,int protok):Server(IP,host){
        this->jadra=jadra;
        this->protok=protok;
    }
    VirtualServer(const Server &s,int jadra,int protok):Server(s){
        this->jadra=jadra;
        this->protok=protok;
    }
    VirtualServer(const VirtualServer &vs):Server(vs){
        this->jadra=vs.jadra;
        this->protok=vs.protok;
    }
    VirtualServer &operator=(const VirtualServer &vs){
        if(this!=&vs){
        strcpy(this->IP,IP);
        strcpy(this->host,host);
        this->jadra=vs.jadra;
        this->protok=vs.protok;
        }
        return *this;
    }
    VirtualServer &operator+=(int j){
        this->jadra +=j;
        return *this;
    }
    friend ostream &operator<<(ostream &out,VirtualServer &vs){
        out<<vs.host<<": "<<vs.IP<<endl;
        out<<vs.jadra<<", "<<vs.protok<<endl;
        return out;
    }
    float total_price(){
        return jadra*5 + protok*10;
    }
    VirtualServer operator++(int){
        VirtualServer vs(*this);
        protok++;
        return vs;
    }
};
float totalCost(Server **serveri,int n){
    float total=0;
    for(int i=0;i<n;i++){
        total+=serveri[i]->total_price();
    }
    return total;
}
Server& biggestInvoice(Server **serveri,int n){
    Server *max = serveri[0];
    for(int i=0;i<n;i++){
        if(serveri[i]->total_price()>max->total_price())
            max=serveri[i];
    }
    return *max;
}
int main() {
  int test_case;
  char hostname[101];
  char ip[46];
  int ram;
  int basic_price;
  int disk_space;
  int num_cores;
  int bandwith;

  int num_inc;

  cin >> test_case;
  if (test_case == 1) {
    // Test Case Business Invoice - Constructor, operator <<
    cin >> ip >> hostname;
    cin >> basic_price >> ram;
    DedicatedServer ds(ip, hostname, basic_price, ram);
    cout << ds;
  } else if (test_case == 2) {
    // Test Case Business Invoice - Constructor, operators <<, ++
    cin >> ip >> hostname;
    cin >> basic_price >> ram;
    DedicatedServer ds(ip, hostname, basic_price, ram);
    cout << ds;

    cin >> num_inc;
    for (int i = 0; i < num_inc; ++i) {
      ds++;
    }
    cout << ds;
  } else if (test_case == 3) {
    // Test Case Business Invoice - Constructor, total_price, operators <<,
    cin >> ip >> hostname;
    cin >> basic_price >> ram;
    DedicatedServer ds(ip, hostname, basic_price, ram);
    cout << ds;

    cin >> num_inc;
    for (int i = 0; i < num_inc; ++i) {
      ds++;
    }

    cin >> num_inc;
    for (int i = 0; i < num_inc; ++i) {
      cin >> disk_space;
      ds += disk_space;
    }

    cout << ds;
  } else if (test_case == 4) {
    cin >> ip >> hostname;
    cin >> basic_price >> ram;
    DedicatedServer ds(ip, hostname, basic_price, ram);
    cout << ds;
    cout << ds.total_price()<< endl;
    cin >> num_inc;
    for (int i = 0; i < num_inc; ++i) {
      ds++;
    }

    cin >> num_inc;
    for (int i = 0; i < num_inc; ++i) {
      cin >> disk_space;
      ds += disk_space;
    }

    cout << ds;
    cout << ds.total_price();

  } else if (test_case == 5) {
    cin >> ip >> hostname;
    cin >> num_cores >> bandwith;
    VirtualServer vs(ip, hostname, num_cores, bandwith);
    cout << vs;
  }
  else if (test_case == 6) {
    cin >> ip >> hostname;
    cin >> num_cores >> bandwith;
    VirtualServer vs(ip, hostname, num_cores, bandwith);
    cout << vs;
    cin >> num_inc;
    for (int i = 0; i < num_inc; ++i) {
      vs++;
    }

    cin >> num_inc;
    vs += num_inc;

    cout << vs;

  } else if (test_case == 7) {
    cin >> ip >> hostname;
    cin >> num_cores >> bandwith;
    VirtualServer vs(ip, hostname, num_cores, bandwith);
    cout << vs;
    cout << vs.total_price() << endl;

    cin >> num_inc;
    for (int i = 0; i < num_inc; ++i) {
      vs++;
    }

    cin >> num_inc;
    vs += num_inc;
    cout << vs;
    cout << vs.total_price();
  } else if (test_case == 8) {

    int num_servers;
    int server_type;

    cin >> num_servers;
    Server **s = new Server *[num_servers];
    for (int j = 0; j < num_servers; ++j) {

      cin >> server_type;
      if (server_type == 1) {
        cin >> ip >> hostname;
        cin >> basic_price >> ram;
        DedicatedServer *dsp =
            new DedicatedServer(ip, hostname, basic_price, ram);

        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
          (*dsp)++;
        }

        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
          cin >> disk_space;
          (*dsp) += disk_space;
        }

        cout << *(dsp);
        cout << dsp->total_price() << endl;

        s[j] = dsp;
      }
      if (server_type == 2) {

        cin >> ip >> hostname;
        cin >> num_cores >> bandwith;
        VirtualServer *vsp =
            new VirtualServer(ip, hostname, num_cores, bandwith);

        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
          (*vsp)++;
        }

        cin >> num_inc;
        (*vsp) += num_inc;

        cout << (*vsp);
        cout << vsp->total_price() << endl;
        s[j] = vsp;
      }
    }

    cout << "The cost of all servers is:\n";
    cout << totalCost(s, num_servers);
    cout << endl;

    cout << "Biggest invoice:\n";
    Server &server = biggestInvoice(s, num_servers);

    Server *ss = &server;
    DedicatedServer *bip;
    VirtualServer *pip;
    if (dynamic_cast<DedicatedServer *>(ss)) {
      bip = dynamic_cast<DedicatedServer *>(ss);
      cout << *bip << bip->total_price();
    }
    if (dynamic_cast<VirtualServer *>(ss)) {
      pip = dynamic_cast<VirtualServer *>(ss);
      cout << *pip << pip->total_price();
    }
  }
  return 0;
}
