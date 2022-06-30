#include <bits/stdc++.h>

using namespace std ;

class details                  //Class for login credentials
{
    public:
	int ID;
	int PASS;
};
class store_details
{
	public:
		int ID;
		int PASS;
		string time;
};
class regiment                //Class for regiment status
{
    public:
    char CODE[5];
    int PASSWORD;
    char food[15] ;
    char ammo[15] ;
    char med[15] ;
    int coord_x;
    int coord_y;
};
int id, pass,flag=0, choice, password, pos, x, y;
char code[5];
void menu();
void update();
void excess();
void deficiency();
void administrator();

void update()
{
	fstream f ;
	f.open("regiment.dat" , ios::in | ios::binary |ios::out);
	regiment d;
	cout<<"\n\t\t\tEnter CODE: ";
	cin>>code ;
	cout<<"\t\t\tEnter Password: ";
	cin>>password;
	int flag=0;

	while(!f.eof())
    {
        pos= f.tellg();
        f.read((char*)&d,sizeof (d));
        if(strcmp(d.CODE,code)==0 && password==d.PASSWORD)    // Checking credentials for updation
        {
        	flag=1 ;
        	cout<<"\n\t\t\tAccess Granted";
            int c ;
            cout<<"\n\t\t\tUse 1,2,3 to set Excess , Sufficient , Deficient :";
            cout<<endl<<"\n\t\t\tSet Food: ";
            cin>>c ;
            if(c==1) strncpy(d.food, "excess", sizeof(d.food));
            else if(c==2) strncpy(d.food, "sufficient", sizeof(d.food));
            else if(c==3) strncpy(d.food, "deficient", sizeof(d.food));
            else
            {
                    cout<<"\n\t\t\tWrong input.\n\t\t\tPlease try again.";
                    exit(0);
            }
            cout<<endl<<"\n\t\t\tSet Ammunition: ";
            cin>>c ;
            if(c==1) strncpy(d.ammo, "excess", sizeof(d.food));
            else if(c==2) strncpy(d.ammo, "sufficient", sizeof(d.food));
            else if(c==3) strncpy(d.ammo, "deficient", sizeof(d.food));
            else
            {
                    cout<<"\n\t\t\tWrong input.\n\t\t\tPlease try again.";

                    exit(0);
            }
            cout<<endl<<"\n\t\t\tSet Medicine: ";
            cin>>c ;
            if(c==1) strncpy(d.med, "excess", sizeof(d.food)) ;
            else if(c==2) strncpy(d.med, "sufficient", sizeof(d.food)) ;
            else if(c==3) strncpy(d.med, "deficient", sizeof(d.food)) ;
            else
            {
                    cout<<"\n\t\t\tWrong input.\n\t\t\tPlease try again.";
                    exit(0);
            }
            strncpy(d.CODE,code, sizeof(d.CODE));
            d.PASSWORD=password;
            f.seekp(pos);
            f.write((char*)&d,sizeof (d)); // Updating status in file
            break;
        }

    }
    f.close();
    if(flag==1)
    cout<<"\n\t\t\tUpdate Successful."<<endl ;
    else
    {
        cout<<"\n\t\t\tWrong credentials. Please try again.";
        update();
    }

}

bool cmp(pair<double,regiment> &r1 , pair<double,regiment> &r2)
{
    if(r1.first==r2.first)
        return r1.second.CODE < r2.second.CODE ;
    return r1.first < r2.first ;
}

void deficiency()
{
	ifstream fin ;
    map<string,vector<pair<double,regiment>>> mvp ;
    regiment r ;
    char result[50];
	fin.open("regiment.dat" , ios::in | ios::binary);
	while(fin.read((char*)&r,sizeof (r)))
	{
        if(strcmp(r.CODE,code)==0)
        {
            x=r.coord_x;
            y=r.coord_y;
            break;
        }
	}
    fin.close();
    fin.open("regiment.dat" , ios::in | ios::binary);
	while(fin.read((char*)&r,sizeof (r)))
	{

        int sq=(x-r.coord_x)*(x-r.coord_x)+(y-r.coord_y)*(y-r.coord_y);
        double dis=sqrt(1.0*sq);

		if(strcmp(r.food,"deficient")==0)
            mvp["Food"].push_back(make_pair(dis,r));

		if(strcmp(r.ammo,"deficient")==0)
            mvp["Ammunition"].push_back(make_pair(dis,r));

		if(strcmp(r.med,"deficient")==0)
            mvp["Medicine"].push_back(make_pair(dis,r));


	}
    for(auto &x : mvp) sort(x.second.begin(),x.second.end(),cmp);
    for(auto &x : mvp)
    {
        cout<<"\n\t\t\tRegiments Deficient in : \n\t\t\t"<<x.first<<"\n\t\t" ;
        for(auto &pp : x.second) cout<<"\t"<<pp.first<<"km "<<pp.second.CODE<<"\t";
        cout<<"\n";
    }
	fin.close();

	menu();
}

void excess()
{
	ifstream fin ;
	regiment r ;
	char result[50];
	fin.open("regiment.dat" , ios::in | ios::binary);
    map<string,vector<pair<double,regiment>>> mvp ;
	while(fin.read((char*)&r,sizeof (r)))
	{
        if(strcmp(r.CODE,code)==0)
        {
            x=r.coord_x;
            y=r.coord_y;
            break;
        }
	}
    fin.close();
    fin.open("regiment.dat" , ios::in | ios::binary);
	while(fin.read((char*)&r,sizeof (r)))
	{

        int sq=(x-r.coord_x)*(x-r.coord_x)+(y-r.coord_y)*(y-r.coord_y);
        double dis=sqrt(1.0*sq);

		if(strcmp(r.food,"excess")==0)
            mvp["Food"].push_back(make_pair(dis,r));

		if(strcmp(r.ammo,"excess")==0)
            mvp["Ammunition"].push_back(make_pair(dis,r));

		if(strcmp(r.med,"excess")==0)
            mvp["Medicine"].push_back(make_pair(dis,r));


	}
    for(auto &x : mvp) sort(x.second.begin(),x.second.end(),cmp);
    for(auto &x : mvp)
    {
        cout<<"\n\t\t\tRegiments Excess in : \n\t\t\t"<<x.first<<"\n\t\t";
        for(auto &pp : x.second) cout<<"\t"<<pp.first<<"km "<<pp.second.CODE<<"\t";
        cout<<"\n";
    }
	fin.close();
	menu();
}

void menu()
{

        cout<<"\n\n\n\t\t\t1. Update status\n\t\t\t2. Check for deficient supply\n\t\t\t3. Check for excess supply\n\t\t\t4. Exit\n\t\t\tEnter your preference:";
        cin>>choice;
        switch(choice)
        {
                case 1 :   update();
                           break;
                case 2 :   deficiency();
                           break;
                case 3 :   excess();
                           break;
                case 4 :   exit(0);
                default : cout<<"\n\t\t\tInvalid input. Please try again.";

                          menu();

        }
}

void administrator()
{
	fstream f ;
	f.open("logs.dat" , ios::app | ios::binary); // File to store logs
	details C;
	store_details Cw;
	cout<<"\n\t\t\tEnter regiment code: ";
	cin>>code;
	cout<<"\n\t\t\tEnter ID:";
	cin>>id;
	cout<<"\n\t\t\tEnter password:";
	cin>>pass;
	Cw.ID=id ;
	Cw.PASS=pass ;
	time_t my_time = time(NULL);
        Cw.time= ctime(&my_time);
	f.write((char*)&Cw,sizeof(Cw)); // Storing login details in a file
	f.close();
	fstream c1;
	c1.open("login.dat",ios::in|ios::binary);
	while(!c1.eof())
	{
            c1.read((char*)&C,sizeof(C));
			if(id==C.ID)                    // Checking login credentials
			if(pass==C.PASS)
				{

					flag=1;
					c1.close();
					menu();
					break;
				}

    }
	if(flag==0)
	{
				cout<<"\n\n\n\t\t\tWrong password";
				cout<<"\n\t\t\tPlease enter again.";

				c1.close();
				administrator();
	}


}



int main()
{
	administrator();
}
