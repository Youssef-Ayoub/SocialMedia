#include<iostream>
#include<fstream>
using namespace std ;
#include"LinkedList.h"

Node* head = NULL ;
LinkedList l ;
string usernames[100] ;
int i = 0 ;

void AddUser(User&obj){
    l.push(&head,obj) ;
    usernames[i] = obj.getusername() ;
    i++ ;
}
void divideusers (string line, string &u, string &n, string &e)
{
    int arr[2];
    int s=line.length();
    int j=0;
    for (int i=0 ; i<s; ++i)
    {
        if (line[i]==',')
        {
            arr[j]= i;
            ++j;
        }
    }
    u=line.substr(0,arr[0]);
    n = line.substr(arr[0]+2,arr[1]-arr[0]-2);
    e =line.substr(arr[1]+2, s);

}
void dividerelations (string line, string &to, string &from)
{
    int n;
    int s=line.length();

    for (int i=0 ; i<s; ++i)
    {
        if (line[i]==',')
        {
            n= i;

        }
    }
    to=line.substr(0,n);
    from = line.substr(n+2,s);
}
void loadfromfile()
{
    //Getting Users from file
    fstream input;
    string line ;
    string Username[9],name[9],email[9] ;
    int j=0;
    input.open("all-users.in") ;
    while(getline(input,line)){
        divideusers(line,Username[j],name[j],email[j]);
        ++j;

    }
    //Getting relations from file
    fstream in;
    string w ,to [6], from[6] ;
    int k=0;
    in.open("all-users-relations.in") ;
    while(getline(in,w))
    {
        dividerelations(w, to[k], from[k]);
        ++k;
    }
    in.close();


    User u1(name[0],Username[0],email[0]),
    u2(name[1],Username[1],email[1]),
    u3(name[2],Username[2],email[2]),
    u4(name[3],Username[3],email[3]),
    u5(name[4],Username[4],email[4]),
    u6(name[5],Username[5],email[5]),
    u7(name[6],Username[6],email[6]),
    u8(name[7],Username[7],email[7]),
    u9(name[8],Username[8],email[8]) ;

    u8.addfriend(u3) ;
    u5.addfriend(u2) ;
    u2.addfriend(u6) ;
    u3.addfriend(u4) ;
    u7.addfriend(u6) ;
    u9.addfriend(u8) ;

    AddUser(u1);
    AddUser(u2);
    AddUser(u3);
    AddUser(u4);
    AddUser(u5);
    AddUser(u6);
    AddUser(u7);
    AddUser(u8);
    AddUser(u9);
}
int main()
{
    loadfromfile();
    int n ;
    string username ;
    User* temp ;
    User* currentUser ;
    i = l.getsz() ;
    while(1){
        cout << "1. Login in\n2. Exit\n" ;
        cin >> n ;
        if(n == 2)
            exit(0) ;
        else{
            cout << "Enter your username: " ;
            cin >> username ;
            while(l.search(head,username) == "Not Found"){
                cout << "Invalid username" << endl;
                cin >> username ;
            }
        }
        currentUser = &l.searchLogin(head,username) ;
        while(n != 6){
            cout << endl;
            cout << "1. List all friends\n2. Search by username\n3. Add friend\n4. Remove friend\n5. people you may know\n6. Logout\n";
            cin >> n ;
            if(n == 1){currentUser->displayfriends() ;}

            else if(n == 2){cout << "enter his/her username: " ; cin >> username ; cout << currentUser->searchfriend(username);}

            else if(n == 3){
                cout << "Enter his/her Username: " ;
                cin >> username ;
                temp = &l.searchLogin(head,username) ;
                if(currentUser->searchfriend(username) == "Not Found"){currentUser->addfriend(*temp); cout << "You are now friends" ;}
                else cout << "You are already friends" ;
            }

            else if(n == 4){
                cout << "Enter his/her Username: " ;
                cin >> username ;
                temp = &l.searchLogin(head,username) ;
                if(currentUser->searchfriend(username) != "Not Found"){
                    currentUser->removefriend(*temp) ;
                    cout << "DONE" ;
                }
            }

            else if(n == 5){
                for(int j = 0 ; j < i ; ++j){
                    if(currentUser->searchfriend(usernames[j]) == "Not Found" && usernames[j] != currentUser->getusername()){
                        temp =  &l.searchLogin(head,usernames[j]) ;
                        cout << temp->getusername() << " , " << temp->getname() << endl;
                    }
                }
            }
        }
    }

    return 0 ;
}
