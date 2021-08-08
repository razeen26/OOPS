#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

class account
{
    public:
    string username;
    string password;
};

class cinema
{
    public:
    char cine_name[20];
    char cine_time[10];
    void get()
    {
        fflush(stdin);
        cout<<"\nEnter Cinema Movie: ";
        gets(cine_name);
        cout<<"\nEnter it's timing: ";
        gets(cine_time);
    }
    void put()
    {
        cout<<"\nMovie name: "<<cine_name;
        cout<<"\nMovie timing: "<<cine_time<<endl;
    }
}cine;

class admin:public account
{
    public:
    admin()
    {
        username="admin";
        password="admin";
    }
    friend void admin_login();
}admin_obj;

void admin_login()
{
    fstream admin_file;
    string s,s1;
    int temp;
    string temp_username,temp_password;
    admin_file.open("admin.txt",ios::in);
    getline(admin_file,s,' ');
    getline(admin_file,s1,'\n');
    cout<<"\nEnter Username for Admin: ";
    cin>>temp_username;
    cout<<"\nEnter Password for Admin: ";
    cin>>temp_password;
    if(s==temp_username&&s1==temp_password)
    {
        cout<<"Access Granted!";
    }
    else
    {
        cout<<"Wrong Username/Password!";
        return;
    }
    admin_file.close();
    do
    {
        cout<<"What do you want to do?\n\n1. Show Movies\n2. Remove Movies and Timing\n3. Add Movies and Timing\n4. Change Password\n5. Exit\n\nEnter: ";
        cin>>temp;
        switch(temp)
        {
            case 1: {
                        cout<<"\nPrinting Movies list:\n";
                        ifstream movie_file;
                        cinema c;
                        movie_file.open("movies.txt",ios::in);
                        movie_file.seekg(0,ios::beg);
                        while(!movie_file.eof())
                        {
                            movie_file>>c.cine_name;
                            movie_file>>c.cine_time;
                            cout<<c.cine_name<<"  "<<c.cine_time<<endl;
                        }
                        movie_file.close();
                        break;
                    }

            case 2: {
                        string temp;
                        string str;
                        fstream movie,dup_movie;
                        cout<<"Enter the name of the movie to be deleted: ";
                        cin>>temp;
                        movie.open("movies.txt",ios::in);
                        dup_movie.open("dup_movies.txt",ios::out);
                        while(!movie.eof())
                        {
                            getline(movie,str,' ');
                            if(!movie.eof())
                            {
                                if(temp!=str)
                                {
                                    getline(movie,str,'\n');
                                    getline(movie,str,' ');
                                    dup_movie<<str<<" ";
                                    getline(movie,str,'\n');
                                    dup_movie<<str<<endl;
                                }
                            }
                            getline(movie,str,'\n');
                        }
                        cout<<"\nDeleted\n";
                        movie.close();
                        dup_movie.close();
                        remove("movies.txt");
                        rename("dup_movies.txt","movies.txt");
                        break;
                    }

            case 3: {
                        ofstream movies_file;
                        movies_file.open("movies.txt",ios::app);
                        cine.get();
                        movies_file<<cine.cine_name<<" ";
                        movies_file<<cine.cine_time<<endl;
                        cout<<"Movie added!";
                        movies_file.close();
                        break;
                    }

            case 4: {
                        cout<<"Enter new password for Admin: ";
                        cin>>admin_obj.password;
                        fstream f;
                        f.open("admin.txt",ios::out);
                        s1=admin_obj.password;
                        f<<s<<" "<<s1<<endl;
                        break;
                    }

            case 5: {
                        cout<<"\n--------------EXITTING FROM ADMIN MENU---------------\n";
                        break;
                    }
        }
    }
    while(temp!=5);
    admin_file.close();
}

class user:public account
{
    public:
    void get()
    {
        cout<<"\nEnter Username: ";
        cin>>username;
        cout<<"\nEnter Password: ";
        cin>>password;
    }
    friend void user_login();
    friend void user_signup();
}user_obj;

void user_login()
{
    string temp_username;
    string temp_password;
    bool status=0;
    cout<<"\nEnter Username: ";
    cin>>temp_username;
    cout<<"\nEnter Password: ";
    cin>>temp_password;
    fstream fin;
    fin.open("users.txt",ios::in);
    while(!fin.eof())
    {
        fin.read((char*)&user_obj,sizeof(user_obj));
        if(!fin.eof())
        {
            if(temp_username==user_obj.username&&temp_password==user_obj.password)
            {
                status=1;
                cout<<"\nAccess granted!\n";
                break;
            }
            else
            {
                status=0;
            }
        }
    }
    int temp;
    fin.close();
    if(status==0)
    {
        cout<<"\nAccount not found!\n";
        return;
    }
    else
    {
        do
        {   cout<<"\nUser Menu:\n1. View Movies\n2. Book movies\n3. Exit\nEnter: ";
            cin>>temp;
            switch(temp)
            {
                case 1: {
                        cout<<"\nPrinting Movies list:\n";
                        ifstream movie_file;
                        cinema c;
                        movie_file.open("movies.txt",ios::in);
                        movie_file.seekg(0,ios::beg);
                        while(!movie_file.eof())
                        {
                            movie_file>>c.cine_name;
                            movie_file>>c.cine_time;
                            cout<<c.cine_name<<"  "<<c.cine_time<<endl;
                        }
                        movie_file.close();
                        break;
                            }
                case 2: {
                            string temp_movie;
                            bool status=0;
                            string s,s1;
                            cout<<"Enter Movie name: ";
                            cin>>temp_movie;
                            fstream movies;
                            movies.open("movies.txt",ios::in);
                            while(!movies.eof())
                            {
                                getline(movies,s,' ');
                                if(!movies.eof())
                                {
                                    if(temp_movie==s)
                                    {
                                        cout<<"\nTickets booked!\n";
                                        status=1;
                                        break;
                                    }
                                    else
                                        status=0;
                                }
                                getline(movies,s,'\n');
                            }
                            movies.close();
                            if(status==0)
                                cout<<"Movie not found!\n";
                            break;
                        }
                case 3: {
                            cout<<"\n----------------EXITTING USER MENU-----------------\n";
                            break;
                        }
            }
        }
        while(temp!=3);
    }
}

void user_signup()
{
    cout<<"\nEnter new details:\n";
    user_obj.get();
    fstream fout;
    fout.open("users.txt",ios::out);
    fout.write((char*)&user_obj,sizeof(user_obj));
    fout.close();
    cout<<"Log in:\n";
    user_login();
}

int main()
{
    int n;
    fstream admin_file,movies_file;
    admin_file.open("admin.txt",ios::out);
    admin_file<<admin_obj.username<<" "<<admin_obj.password<<endl;
    admin_file.close();
    movies_file.open("movies.txt",ios::out | ios::app);
    movies_file<<cine.cine_name<<" "<<cine.cine_time<<endl;
    movies_file.close();
    do
    {
        cout<<"\nMENU:\n\n1. Admin\n2. User\n3. Exit\n\nEnter: ";
        cin>>n;
        switch(n)
        {
            case 1: {
                        cout<<"\nAdmin Login:\n";
                        admin_login();
                        break;
                    }
            case 2: {
                        int m;
                        cout<<"\nUser Login:\n1. Login\n2. Sign Up\n3. Exit\nEnter: ";
                        cin>>m;
                        switch(m)
                        {
                            case 1: {
                                        user_login();
                                        break;
                                    }
                            case 2: {
                                        user_signup();
                                        break;
                                    }
                            case 3: {
                                        cout<<"\n------EXITTING FROM USER MENU-------\n";
                                        break;
                                    }
                            break;
                        }
                    }
            case 3: {
                        cout<<"\n\n-----------------------EXITTING------------------------\n\n";
                        break;
                    }
        }
    }
    while(n!=3);
}
