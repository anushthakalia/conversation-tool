#include <iostream> 
#include <cstring>
#include <algorithm>
#include <string>
#include <cassert>
#include <iomanip>
using namespace std;
 
#define MAX 100

 
string gram[MAX][MAX];  //to store entered grammar
string dpr[MAX];
int p,np;       //np-> number of productions
 
string join_nt( string a, string b)   //concatenates unique non-terminals
{
    int i;
    string r=a;
    for(i=0;i<b.length();i++)
        if(r.find(b[i]) > r.length())
            r+=b[i];
    return (r);
}
 
void split_right(string a)    //seperates right hand side of entered grammar
{
    int i;
    p=0;
    while(a.length())
    {
        i=a.find("|");
        if(i>a.length() || i==-1)
        {
            dpr[p++] = a;
            a="";
        }
        else
        {
            dpr[p++] = a.substr(0,i);
            a=a.substr(i+1,a.length());
        }
    }
}
 
int CNF_left(string a)   //checks if LHS of entered grammar is in CNF
{
    if(a.length()==1 && a[0]>='A' && a[0]<='Z')
        return 1;
    return 0;
}
 
int CNF_right(string a)   //checks if RHS of grammar is in CNF
{
    if (a.length() == 1 && a[0]>='a' && a[0] <='z')
        return 1;
    if (a.length()==2 && a[0]>='A' && a[0]<='Z' && a[1]>='A' && a[1]<='Z' )
        return 1;
    return 0;
}
 
string search_prod(string p) //returns a concatenated string of variables which can produce string p
{
    int j,k;
    string r="";
    for(j=0;j<np;j++)
    {
        k=1;
        while(gram[j][k] != "")
        {
            if(gram[j][k] == p)
            {
                r=join_nt(r,gram[j][0]);
            }
            k++;
        }
    }  
    return r;
}

 
string combination(string a, string b)  //creates every combination of variables from a and b . For eg: BA * AB = {BA, BB, AA, BB}
{
    int i,j;
    string pri=a,re="";
    for(i=0;i<a.length();i++)
        for(j=0;j<b.length();j++)
        {
            pri="";
            pri=pri+a[i]+b[j];
            re=re+search_prod(pri);     //searches if the generated productions can be created or not
        }      
    return re;
}
 
int main()
{
    int i,pt,j,l,k;
    string a,str,r,pr,start;
    cout<<"*************************************************"<<endl;
    cout<<"For terminal symbols:"<<endl;
    cout<<"VP:M"<<endl;
    cout<<"NP:K"<<endl;
    cout<<"PP:L"<<endl;
    cout<<"Det:D"<<endl;
    cout<<"**Use small letters  for denoting terminal symbols"<<endl;
     cout<<"*************************************************"<<endl;
    cout<<"Enter the start variable"<<endl;
    cin>>start;
    cout<<"Enter the number of grammer rules:"<<endl;
    cin >> np;
    cout<<"Enter the grammer rules below:   "<<endl;
    
    for(i=0;i<np;i++)
    {
        cin >> a;
        pt=a.find("->");
        gram[i][0] = a.substr(0,pt);
        if (CNF_left(gram[i][0]) == 0)
        {
            cout<<"\nEntered grammer not in CNF";
            abort();
        }
        a = a.substr(pt+2, a.length());
        split_right(a);
        for(j=0;j<p;j++)
        {
            gram[i][j+1]=dpr[j];
            if (CNF_right(dpr[j]) == 0)
            {
                cout<<"\nEntered grammer not in CNF";
                abort();
            }
        }
    }
    string matrix[MAX][MAX],st;
    cout<<"\nEnter the string to make the CYK table: "<<endl;
    cin >> str;
   
    for( i=0;i<str.length();i++)       //Assigns values to principal diagonal of matrix
    {
        r="";
        st = "";
        st+=str[i];
        for(j=0;j<np;j++)
        {
            k=1;
            while(gram[j][k] != "")
            {
                if(gram[j][k] == st)
                {
                    r=join_nt(r,gram[j][0]);  // this ouputs the end line, using rules where simply result are terminal symbols.
                }
                k++;
            }
        }
        matrix[i][i]=r;
    }
    int ii,kk;
    for(k=1;k<str.length();k++)       //Assigns values to upper half of the matrix
    {
        for(j=k;j<str.length();j++)
        {
            r="";
            for(l=j-k;l<j;l++)
            {
                pr = combination(matrix[j-k][l],matrix[l+1][j]);
                r = join_nt(r,pr);
            }
            matrix[j-k][j] = r;
        }
    }
     cout<<"*****************CYK Table*******************"<<endl;
    for(i=0;i<str.length();i++)   //Prints the matrix
    {
        k=0;
        l=str.length()-i-1;
        for(j=l;j<str.length();j++)
        {
            cout<<setw(5)<<matrix[k++][j]<<" ";
        }
        cout<<endl;
    }
             
    int f=0;
    for(i=0;i<start.length();i++)
        if(matrix[0][str.length()-1].find(start[i]) <= matrix[0][str.length()-1].length())   //Checks if last element of first row contains a Start variable
        {
            
            return 0;
        }
        else{
        cout<<"CYK table cannot be generated\n";
    }
    return 0;
}