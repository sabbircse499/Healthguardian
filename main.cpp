#include <iostream>
#include <iomanip>
#include "sqlite3.h"
#include <string.h>

using namespace std;

//built in function
//database
void connect();
void deleter(string remov);//Admin delete
void readr(string bggroup);//Find blood donor
int login(string phone,string namelog);//Login check
void regi();//Registration

//non database
void makerequest();
void bloodfind();
void devinfo();

//global veriable
int result;
string phonenumber,bggroup;
int age;
sqlite3 *db;
sqlite3_stmt *stmt;
string query,name,email;
string adminpassword,remov;
string pass="4720";
int logcheck=0;
int logafter;


int main()
{
    // Loop variable
    int i = 1;
    // Login variables
    string namelog, phonelog;
    // Create a new database
    sqlite3_open("healthguardian.db", &db);
    connect();
    // User choice variable
    int c;
   // outer while
while (i != 0)
{
    system("cls");
     cout<<"\n\n<-----------------------------Welcome Health gurdian ------------------------------->\n\n";
    cout << "->Registration press ->01\n";
    cout << "->Login press ->02\n";
    cout << "->FAQ : press ->03\n";
    cout << "Enter choice : ";
    cin >> c;
    system("cls");

    switch (c)
    {
    case 1:
        cout << "Registration\n";
        cout << "-------------------------------------\n";
        regi();
        break;

    case 2:
        {
        cout << "Login\n";
        cout << "-------------------------------------\n";
        cout << "Enter your name :";
        cin >> namelog;
        cout << "Enter your phonenumber :";
        cin >> phonelog;
        int check = login(phonelog, namelog);
        //cout<<"Check : "<<check;

           // system("cls");
            // inner while
            int j = 1;
            while (j!= 0) {
                    if (check > 0) {
              system("cls");
                // ... (existing code)
                cout<<"---------------------------------------HOME PAGE--------------------------------------";
                cout << "\n\n->Find Blood Donor  press ->1\n";
                cout<<"->Make Blood Donor request Press ->2\n";
                cout << "->Developer Info  ->3\n";
                cout<<"->Admin Panel ->4\n\n";
                cout << "->Enter Choice :";
                cin >> logafter;

                if (logafter == 1) {
                    cout << "Quick Blood donor Finder :";
                    cin >> bggroup;
                    readr(bggroup);
                }
                //IF 1 CLOSE


                if(logafter==2){
 string bloodrequ;
 string ppblm; //patient problem
 string reciname;
 string reciphone;
 string reciaddress;
 string hospitalname;
 string gender;
 string pblm;
 int nth; //How many bags of blood?
system("cls");
cout<<"\n---------Make Blood Donor request---------\n"<<endl;

    cout<<"Enter recipient bloodgroup :";
    cin>>bloodrequ;

    if(bloodrequ=="a+" || bloodrequ=="a-"||bloodrequ=="b+"||bloodrequ=="b-"|| bloodrequ=="o+" || bloodrequ=="o-"||bloodrequ=="ab+"||bloodrequ=="ab-"){

    cout<<"Enter blood recipient name :";
    cin>>reciname;
    cout<<"Enter blood recipient phone :";
    cin>>reciphone;
    cout<<"Enter recipient problem :";
    cin>>pblm;
    cout<<"Enter blood receving address :";
    cin>>reciaddress;
    cout<<"Enter recipient hospital-name :";
    cin>>hospitalname;
    cout<<"Enter recipient gender: ";
    cin>>gender;
    cout<<"How many bags of blood?";
    cin>>nth;

    //find Available blood donor
                string abd;
                cout<<"Show Available Blood Donor(y/n) :";
                cin>>abd;
                if(abd=="y"){
                readr(bloodrequ);
                }
   }
   else{
    cout<<"Your input Blood group is wrong ! Try again ?"<<endl;
   }

                }


                //if 2 close hare
                if (logafter == 3) {
                    devinfo();
                }
                //IF 3 CLOSE

                if(logafter==4){

                cout << "Admin Password :";
                cin >> adminpassword;

                if (adminpassword == pass)
                  {
                    cout << "Which Id you  want to remove your Data-Base(id or *(all)) ?:";
                    cin >> remov;
                    deleter(remov);
                   }
                }
                //IF 4 CLOSE

            }
                cout << "Show HOME PAGE ->1 Logout ->0:";
                cin >> j;
            }

        // inner while close
    }
    break;

    case 3:
cout<<"<--------------------------------FAQ------------------------------------>";
cout<<"Health Guardians Blood Donation Application simplifies and streamlines \n"<<
       "the blood donation process. Users can seamlessly registe_r, log in, and \n"<<
       "access a quick blood donor finder. The intuitive interface ensures a user\n"<<
       "friendly experience. The app prioritizes security with a dedicated admin \n"<<
       "panel fo_r database management. Robust features include user registration, \n"<<
       "login authentication, and the ability to query blood donors based on blood\n"<<
        "groups. Additionally, an informative developer info section enriches the \n"<<
         "user experience. Health Guardian stands as an essential tool in promoting \n"<<
         "lood donation, ensuring a healthier and safer community.\n";
        break;

    default:
        cout << "Invalid input .Please Press Write Input !";
    }
    cout << "\n\nShow Main menu ->1 Exit From THIS APPLICATION ->0:";
    cin >> i;
}

    // Close the SQLite connection
    sqlite3_close(db);
}

//connection

void connect(){
if(sqlite3_open("healthguardian.db",&db) ==SQLITE_OK){
result = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS user(name varchar(50),phonenumber varchar(50),email varchar(50),bggroup varchar(50),age int)", -1, &stmt, NULL);
sqlite3_step(stmt);
sqlite3_finalize(stmt);
if(result !=SQLITE_OK){
    cout<<" connect Error :"<< sqlite3_errmsg(db)<<"\n";
}
else {
    cout<<"Table Connection  Successfully \n";
}
}
}

//insert

void regi(){
cout<<"Enter your name : ";
cin>>name;
cout<<"Enter your phonenumber :";
cin>>phonenumber;
cout<<"Enter your email :";
cin>>email;
cout<<"Enter your Blood Group :";
cin>>bggroup;
cout<<" Enter your age :";
cin>>age;

//query and prepare
query="INSERT INTO user(name,phonenumber,email,bggroup,age) VALUES(?,?,?,?,?); ";
result=sqlite3_prepare_v2(db, query.c_str(),-1,&stmt,NULL);

//text binding
sqlite3_bind_text(stmt,1,name.c_str(),name.length(),SQLITE_TRANSIENT);
sqlite3_bind_text(stmt,2,phonenumber.c_str(),phonenumber.length(),SQLITE_TRANSIENT);
sqlite3_bind_text(stmt,3,email.c_str(),email.length(),SQLITE_TRANSIENT);
sqlite3_bind_text(stmt,4,bggroup.c_str(),bggroup.length(),SQLITE_TRANSIENT);
sqlite3_bind_int(stmt, 5, age);

sqlite3_step(stmt);
sqlite3_finalize(stmt);
if(result!=SQLITE_OK){
    cout<<"insert error :"<<sqlite3_errmsg(db)<<"\n";
}
else {
    cout<<" Registration Data Insert Successfully \n";
}
}
void readr(string bggroup) {
    //query = "SELECT rowid,* FROM user WHERE bggroup=?";
    query = "SELECT rowid,* FROM user WHERE age BETWEEN 18 AND 40 AND bggroup=?";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    // text binding for the WHERE clause
    sqlite3_bind_text(stmt, 1, bggroup.c_str(), bggroup.length(), SQLITE_TRANSIENT);

    if (result != SQLITE_OK) {
        cout << "Read error: " <<sqlite3_errmsg(db) << "\n";
    } else {
        cout << "\n--------------------------------------------------------------\n";
        cout << left <<
            setw(15) << "ID" <<
            setw(15) << "Name" <<
            setw(15) << "Phonenumber" <<
            setw(30) << "Email" <<
            setw(15) << "Blood Group" <<
            setw(15) << "Age";
        cout << "\n--------------------------------------------------------\n";

        while (result = sqlite3_step(stmt) == SQLITE_ROW) {
            cout << left << setw(15) << sqlite3_column_text(stmt, 0) <<
                setw(15) << sqlite3_column_text(stmt, 1) <<
                setw(15) << sqlite3_column_text(stmt, 2) <<
                setw(30) << sqlite3_column_text(stmt, 3) <<
                setw(15) << sqlite3_column_text(stmt, 4) <<
                setw(15) << sqlite3_column_int(stmt, 5) << "\n";
        }
        cout << "\n------------------------------------------------------------\n";
    }

    sqlite3_finalize(stmt);
}

int login(string phone, string namelog) {
   query = "SELECT rowid,* FROM user WHERE phonenumber=?";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    // text binding for the WHERE clause
    sqlite3_bind_text(stmt, 1, phone.c_str(), phone.length(), SQLITE_TRANSIENT);

    if (result != SQLITE_OK) {
        cout << "Login error: " << sqlite3_errmsg(db) << "\n";
    }
    else {
        // Step through the result set (should have one row if the user exists)
        if (sqlite3_step(stmt) == SQLITE_ROW) {
        logcheck++;
            cout << "Login successful! Welcome " << namelog << "\n";
        }
        else {
            cout << "User not found. Please register.\n";
        }
    }

    sqlite3_finalize(stmt);
 return logcheck;
}

//Admin panel

void deleter(string remov) {
    // Assuming "db" is a global variable or passed as a parameter

     query = "DELETE FROM user WHERE rowid=?";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        cout << "Delete preparation error: " << sqlite3_errmsg(db) << "\n";
        return;
    }
    // text binding for the WHERE clause
    sqlite3_bind_text(stmt, 1, remov.c_str(), remov.length(), SQLITE_TRANSIENT);

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        cout << "Delete execution error: " << sqlite3_errmsg(db) << "\n";
    } else {
        cout << "Delete successful! Rows affected: " << sqlite3_changes(db) << "\n";
    }

    sqlite3_finalize(stmt);
}

void devinfo(){

			cout<<"<-----developer----->\n------HEALTH GURDIAN-----\n----cse dept----\n-----northern university bangladesh-----\n"<<endl;

			cout << "<-----instructor----->\n <-----Jannatul Nesha  ------>\n<----cse dept----> \n <-----northern university bangladesh----->" <<endl;


}
