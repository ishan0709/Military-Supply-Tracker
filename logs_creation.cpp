#include <bits/stdc++.h>

using namespace std ;

int main()
{
       class log
       {
           public:
            int ID;
            int PASS;
            string time;
       }s;
       fstream b1;
				b1.open("logs.dat",ios::out|ios::binary);
				cin>>s.ID;
				cin>>s.PASS;
				time_t my_time = time(NULL);
                s.time= ctime(&my_time);
				b1.write((char*)&s,sizeof (s));
				b1.close();
        return 0;
}
