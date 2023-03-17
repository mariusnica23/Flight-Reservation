#include<iostream>
#include<string>
#include<math.h>
#include<stdlib.h>
#include<map>
#include<regex>
#include<fstream>

using namespace std;


string RSA(string x)
{
    return x;
}

class Data{
public:
    int zi;
    int luna;
    int an;
};

class Zbor
{   
    
    public:
    Data dataZbor;
    string orasPlecare;
    string orasSosire;
    string numarZbor;
    
};

class CitireScriere
{
    public:
   static map<string, string> citire_bd (string path)
    {   string mail;
        string parola;
        map<string, string> bd;
        ifstream fin(path);
        while(fin>>mail>>parola)
        {
            bd[mail]=parola;
        }
        return bd;
    }
   static void scriere_bd (string path, map<string, string> bd)
    {   ofstream fout(path);
        map<string, string>::iterator it;
        for (it = bd.begin(); it != bd.end(); it++)
         fout << it->first<<" "<<it->second << "\n";
    }

};
class Autentificare
{   public:
     bool login(string mail, string parola, map<string, string> bd)
     {
         try
            {
                if(bd.find(mail)==bd.end())
                    throw "Utilizatorul nu a fost gasit\n" ;
                else
                    {
                        if(bd[mail].compare(RSA(parola))==0)
                        {
                            cout<<"Bine ati venit!\n";
                            return true;
                        }
                        else
                            throw "Mail sau parola gresita!Incercat din nou!\n" ;
                    }
            }
            catch(char const* e) 
            {   
                
                cout<< e << '\n';
                return false;
            }
     }
     bool signIn(string mail, string parola, string parola_repetata, map<string, string> bd)
     {
         try
         {
              if(mail.find("@")==string::npos)
              throw "Mail incorect!\n";
              if(parola.length() < 6)
              throw "Parola este prea scurta!\n";
              if(parola.compare(parola_repetata)!=0)
              throw "Parola repetata nu este corecta\n!";

              bd[mail]= RSA(parola);
              cout<<"Autentificare cu succes!\n";
              CitireScriere::scriere_bd("Baza_de_date.txt", bd);
              return true;
         }
         catch(char const* e)
         {
             cout<< e << '\n';
             return false;
         }
         
     }
};


class Operator
{
    string user;
    string parola;
    public:
        void adaugaZbor(Zbor , vector <Zbor> );
        void stergeZbor(string , vector <Zbor> );
    int formatDataGresita(Data data){
        if(data.luna == 2){
            if(data.zi > 29){
                return 0;
            }
        }
        else if(data.zi > 31){
            return 0;
        }
        return 1;
    }

    int dataInTrecut(Data data)
    {
        if(data.an < 2021){
            return 0;
        }
        else if(data.an == 2021 && data.luna < 12){
            return 0;
        }
        else if(data.an == 2021 && data.luna == 12 && data.zi < 12){
            return 0;
        }
        return 1;
    }
    int caractereInexistente(string a){
        for(int i = 0; i < a.length(); i++){
            if(a[i] < 65 || (a[i] > 90 && a[i] < 97) || a[i] > 122){
                return 0;
            }
        }
        return 1;
    }

    void adaugareZbor(){
        Zbor zbor;
        char c1, c2;

        cout<<"== Sa incepem adaugarea unui nou zbor =="<<endl;
        cout<<"Introduceti numarul zborului: ";
        cin>>zbor.numarZbor;
        cout<<endl<<"Oras plecare: ";
        cin>>zbor.orasPlecare;
        cout<<endl<<"Oras sosire: ";
        cin>>zbor.orasSosire;
        cout<<endl<<"Data zborului: (DD/MM/YY): ";
        cin>>zbor.dataZbor.zi;
        cin>>c1;
        cin>>zbor.dataZbor.luna;
        cin>>c2;
        cin>>zbor.dataZbor.an;

        if(formatDataGresita(zbor.dataZbor) == 0){
            cout<<"Formatul datei este gresit!"<<endl;
        }
        else if(dataInTrecut(zbor.dataZbor) == 0){
            cout<<"Data introdusa este in trecut!"<<endl;
        }
        else if(caractereInexistente(zbor.orasPlecare) == 0 || caractereInexistente(zbor.orasSosire) == 0){
            cout<<"Caractere inexistente in numele oraselor!"<<endl;
        }
        else{
            ofstream output("zboruri.txt", ios::app);
            output<<zbor.numarZbor << " " << zbor.orasPlecare << " " << zbor.orasSosire << " " << zbor.dataZbor.zi << "/" << zbor.dataZbor.luna << "/" << zbor.dataZbor.an << endl;
        }
    }

    void StergereZbor(){
        Zbor zbor;
        string x;

        cout<<"Introduceti numarul de zbor pe care vreti sa il stergeti!"<<endl;
        cin>>zbor.numarZbor;

        ofstream temp("temp.txt");
        ifstream file("zboruri.txt");

        while(getline(file, x)){
            if (x != zbor.numarZbor){
                temp << x << endl;
                cout<<"Zborul cu numarul "<<zbor.numarZbor<<" a fost sters."<<endl;
        }

        temp.close();
        file.close();
        remove("zboruri.txt");
        rename("temp.txt", "zboruri.txt");
        }
    }
};

class Utilizator
{
    string user;
    string parola;
    public:
        void cautareZbor(Zbor , vector<Zbor>);
        void rezervareZbor(Zbor );
        void cautareZbor(){
        Zbor zbor;
        string x;
        char c1,c2;

        stringstream s1;
        stringstream s2;
        stringstream s3;

        string ss1,ss2,ss3;

        cout<<"Introduceti numarul zborului: ";
        cin>>zbor.numarZbor;
        cout<<"Orasul de plecare: ";
        cin>>zbor.orasPlecare; 
        cout<<"Orasul de sosire: ";
        cin>>zbor.orasSosire;
        cout<<"Data zborului: (DD/MM?YY): ";
        cin>>zbor.dataZbor.zi;
        cin>>c1;
        cin>>zbor.dataZbor.luna;
        cin>>c2;
        cin>>zbor.dataZbor.an;

        s1 << zbor.dataZbor.zi;
        s2 << zbor.dataZbor.luna;
        s3 << zbor.dataZbor.an;

        s1 >> ss1;
        s2 >> ss2;
        s3 >> ss3;
        
        ifstream file("zboruri.txt");

        while(file){
            getline(file, x);
            if(x == zbor.numarZbor + " " + zbor.orasPlecare + " " + zbor.orasSosire + " " + ss1 + "/" + ss2 + "/" + ss3){
                cout<<"Zbor gasit!"<<endl;
                break;
            }
            if(file.eof()){
                cout<<"Zbor inexistent"<<endl;
            }
        }

    }

    void rezervareBilete(){
        Zbor zbor;
        int numarBilete;
        string x;
        char c1,c2;

        stringstream s1;
        stringstream s2;
        stringstream s3;

        string ss1,ss2,ss3;
        
        ifstream file("zboruri.txt");

        cout<<"Cate bilete doriti sa rezervati?"<<endl;
        cin >> numarBilete;
        cout<<"La ce zbor?"<<endl;
        cin>>zbor.numarZbor;
        cout<<"Orasul de plecare: ";
        cin>>zbor.orasPlecare;
        cout<<"Orasul de sosire: ";
        cin>>zbor.orasSosire;
        cout<<"Data zborului: (DD/MM?YY): ";
        cin>>zbor.dataZbor.zi;
        cin>>c1;
        cin>>zbor.dataZbor.luna;
        cin>>c2;
        cin>>zbor.dataZbor.an;

        s1 << zbor.dataZbor.zi;
        s2 << zbor.dataZbor.luna;
        s3 << zbor.dataZbor.an;

        s1 >> ss1;
        s2 >> ss2;
        s3 >> ss3;

        while(file){
            getline(file, x);
            if(x == zbor.numarZbor + " " + zbor.orasPlecare + " " + zbor.orasSosire + " " + ss1 + "/" + ss2 + "/" + ss3){
               // cout<< a <<" a rezervat "<< numarBilete <<" bilete la zborul "<< zbor.numarZbor<<endl;
                break;  
            }
            else if(file.eof()){
                cout<<"Zbor inexistent"<<endl;
            }
        }
    }
};

int main()
{
    int opt;
    string mail;
    string parola;
    string parola_repetata;
    Autentificare aut;
    while(true)
    {
        cout<<"Utilizator sau operator?Alege 0 sau 1\n";
        cin>>opt;
        switch (opt)
        {
        case 0:
           {
                        
            int opt_utiliz;
            map<string, string> bd=CitireScriere::citire_bd("Baza_de_date.txt");
            bool signedin=false;
            while(signedin==false)
               {   cout<<"Logare sau autentificare?Alege 0 sau 1\n";
                    cin>>opt_utiliz;
                   switch (opt_utiliz)
                    {
                        
                        case 0:
                            {
                            cout<<"Introduceti mail-ul\n";
                            cin>>mail;
                            cout<<"Introduceti parola\n";
                            cin>>parola;
                            if (signedin==aut.login(mail, parola, bd))
                            
                                cout<<"Login nereusit! Incercati din nou!\n";
                            else
                                signedin=aut.login(mail, parola, bd);
                            break;
                            }
                        case 1:
                            {
                                cout<<"Introduceti mail-ul\n";
                                cin>>mail;
                                cout<<"Introduceti parola\n";
                                cin>>parola;
                                cout<<"Introduceti din nou parola\n";
                                cin>>parola_repetata;
                                signedin=aut.signIn(mail, parola, parola_repetata, bd);
                                break;
                            }
                        default:
                            cout<<"Alege o optiune valida\n";

                            break;
                    }
               }
            //Operatiuni zbor
            break;
           }
        case 1:
        {
            int opt_operator;
            map<string, string> bd=CitireScriere::citire_bd("Baza_de_date_operator.txt");
            bool signedin=false;
            while(signedin==false)
            {
                cout<<"Introduceti username-ul\n";
                cin>>mail;
                cout<<"Introduceti parola\n";
                cin>>parola;
                signedin=aut.login(mail, parola, bd);
            }
            switch (opt_operator)
            {
            case 0:
                /* code */
                break;
            
            default:
                break;
            }
           break;
        }
        default:
            cout<<"Alege o optiune valida\n";
            break;
        }
    }
//     map<string, string> bd=citire_bd("Baza_de_date.txt");
//     map<string, string>::iterator it;
//   for (it = bd.begin(); it != bd.end(); it++)
//     {
//          cout << it->first<<it->second << " ";
//     }
//     bd["abcd"]="1234";
//     scriere_bd("Baza_de_date.txt", bd);
    
}