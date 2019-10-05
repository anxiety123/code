#include<bits/stdc++.h>
using namespace std;

struct swa{
    string a;
    string b;
    struct swa* parent;

};
map<string,swa*> maps;
struct swa* create(string a,string b,struct swa* s){
    struct swa* s1=(struct swa*)malloc(sizeof(struct swa));
    s1->a=a;
    s1->b=b;
    s1->parent=s;
    return s1;
}

vector<string> getWords(string x4){
    vector<string> strv;
    istringstream ss(x4); 
    do { 
        string word; 
        ss >> word; 
        strv.push_back(word);
    } while (ss); 
    return strv;
}
map<string,pair<int,int>> make_2dArray(int m,int n,string str[][100],vector<string> s,map<string,pair<int,int>> temp){
    pair<int,int> c;
    int count=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            str[i][j]=s[count];
           count++;
            c.first=i;
            c.second=j;
            temp[str[i][j]]=c;
        }
    }
    return temp;
}
map<string,pair<int,int>> swap(string x, string y,string str[][100],map<string,pair<int,int>> temp){
    
    pair<int,int> xc,yc;
    xc = temp[x];
    yc = temp[y];
    str[xc.first][xc.second]=y;
    str[yc.first][yc.second]=x;
    temp[x]=yc;
    temp[y]=xc;
    return temp;
}
vector<string> save(int m,int n,string str[][100],vector<string> arrangements,swa* temp22){
    string x="";
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            x=x+str[i][j]+" ";
        }
    }
    if(maps.find(x)!=maps.end()){
        maps[x]=temp22;
        arrangements.push_back(x);
    }
     
     return arrangements;
}
vector<string> allpos(int m,int n, map<string,pair<int,int>> temp,string str[][100], vector<string> v,string t){
    int a,b;
    swa* temp22;
    swa* temp2= maps[t];
    for(int i=0;i<m;i++){
        a=i;
        for(int j=0;j<n-1;j++){
            b=j+1;
            temp = swap(str[i][j],str[a][b],str,temp);
            temp22 = create(str[i][j],str[a][b],temp2);
            v = save(m,n,str,v,temp22);
            temp = swap(str[i][j],str[a][b],str,temp);
            free(temp22);
        }
    }
    for(int i=0;i<m-1;i++){
        a=i+1;
        temp = swap(str[i][0],str[a][0],str,temp);
        temp22 = create(str[i][0],str[a][0],temp2);
        v = save(m,n,str,v,temp22);
        temp = swap(str[i][0],str[a][0],str,temp);
        free(temp22);
    }
    for(int i=0;i<m-1;i++){
        a=i+1;
        temp = swap(str[i][n-1],str[a][n-1],str,temp);
        temp22 = create(str[i][n-1],str[a][n-1],temp2);
        v = save(m,n,str,v,temp22);
       temp = swap(str[i][n-1],str[a][n-1],str,temp);
       free(temp22);
    }
    free(temp2);
    sort(v.begin(), v.end());
    // for(int i = 0; i  < v.size(); i++) {
    //     cout << v[i] << endl;   
    return v;
    
}
void print(vector<string> t){
    vector<vector<string>> kk; 
    for(int i=0;i<t.size();i++){
        swa* temp = maps[t[i]];
        vector<string> p;
         while(temp->parent!=NULL){
            string s = "swap "+temp->a+" "+temp->b;
            p.push_back(s);
            temp=temp->parent;
        }
        kk.push_back(p);
    }
    sort(kk.begin(),kk.end());
    vector<string> p2=kk[0];
    for(int i=0;i<p2.size();i++){
        cout<<p2[i]<<endl;
    }

   
}


int main(){

    int t;
    cin>>t;
    while(t--)
    {
        int m,n;
        cin>>m>>n;
        pair<int,int> c;
        map<string,pair<int,int>> temp,temp2;
        vector<string> v;
        string str[100][100],str2[100][100];
        string s1="",s2="";
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                cin>>str[i][j];
                s1=s1+str[i][j]+" ";
                c.first=i;
                c.second=j;
                temp[str[i][j]]=c;
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                cin>>str2[i][j];
                s2=s2+str2[i][j]+" ";
                c.first=i;
                c.second=j;
                temp2[str[i][j]]=c;
            }
        }
        queue<vector<string>> q;
        string t=s1;
        int flag =0,count=0;
        maps[s1]=create(NULL,NULL,NULL);
        vector<string> s,k ;
        v=allpos(m,n,temp,str,v,t);
        q.push(v);
        while(!q.empty()){
            v=q.front();
            for(int i = 0; i  < v.size(); i++) {
                t=v[i];
                if(t==s2){
                    flag =1;
                    k.push_back(t);
                }
                else{
                    if(maps.find(t)!=maps.end()){
                        s=getWords(t);
                        temp=make_2dArray(m,n,str,s,temp);
                        v=allpos(m,n,temp,str,v,t);
                        q.push(v);
                    }
                }
            }
            if(flag==1){
                print(k);
                break;
            }
            q.pop();   
        }
    }
    return 0;

}
