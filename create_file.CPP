#include <bits/stdc++.h>

using namespace std ;

int main()
{
       struct login
       {
       int ID;
       int PASS;
       }s;
       fstream b1;
				b1.open("login.dat",ios::app|ios::binary);
				cin>>s.ID;
				cin>>s.PASS;
				b1.write((char*)&s,sizeof (s));
				b1.close();
}
