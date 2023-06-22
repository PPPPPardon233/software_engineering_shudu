// #include <bits/stdc++.h>
// using namespace std;
// map<int ,int,greater<int>> p;
// int main(){
//     int n,m,k;
//     cin>>n>>m>>k;
//     for(int i=0;i<n;i++){
//         int temp_time,temp_src;
//         cin>>temp_time>>temp_src;
//         map<int,int>::iterator it;
//         it=p.find(temp_time);
//         if(it!=p.end()){
//             it->second+=temp_src;
//         }
//         else{
//             p[temp_time]=temp_src;
//         }
//     }
//     int max_time=p.begin()->first;
//     //cout<<max_time<<p.size();
//     while(p.begin()->second<=m){
//         m-=p.begin()->second;
//         max_time--;
//         if(p.size()>=2){
//             map<int,int>::iterator it1=++p.begin();
//             if(max_time==(it1)->first){
//                 it1->second+=p.begin()->second;
//                 p.erase(p.begin());
//             }
//         }
//     }
//     cout<<(max_time<k?k:max_time);
// }


// int n;
// typedef struct user{
//     int DN;
//     int key;
// }usr;
// map<int,vector<usr>>attr2usr;

// bool isDigit(char temp){
//     if(temp<='9'&&temp>='0')
//         return true;
//     else
//         return false;
// }

// set<int> dealer1(int num1,int num2){
//     set<int> ans;
//     map<int,vector<usr>>::iterator it=attr2usr.find(num1);
//     if(it==attr2usr.end()){
//         return ans;
//     }
//     for(int i=0;i<it->second.size();i++){
//         if(it->second[i].key==num2){
//             ans.insert(it->second[i].DN);
//         }
//     }
//     return ans;
// }

// set<int> dealer2(int num1,int num2){
//     set<int> ans;
//     map<int,vector<usr>>::iterator it=attr2usr.find(num1);
//     if(it==attr2usr.end()){
//         return ans;
//     }
//     for(int i=0;i<it->second.size();i++){
//         if(it->second[i].key!=num2){
//             ans.insert(it->second[i].DN);
//         }
//     }
//     return ans;
// }

// set<int> strHandler(string temp){
//     if(temp[0]=='&'||temp[0]=='|'){
//         int stac=1;
//         for(int i=2;i<temp.length();i++){
//             if(temp[i]=='(') ++stac;
//             else if(temp[i]==')') --stac;
//             if(stac==0){
//                 set<int> ans1=strHandler(temp.substr(2,i-2));
//                 set<int> ans2=strHandler(temp.substr(i+2,temp.length()-i-3));
//                 set<int> ans;
//                 if(temp[0]=='&')
//                     set_intersection(ans1.begin(),ans1.end(),ans2.begin(),ans2.end(),inserter(ans,ans.begin()));
//                 if(temp[0]=='|')
//                     set_union(ans1.begin(),ans1.end(),ans2.begin(),ans2.end(),inserter(ans,ans.begin()));
//                 return ans;
//             }
//         }
//     }
//     if(isDigit(temp[0])){
//         for(int i=0;i<temp.length();i++){
//             if(!(isDigit(temp[i]))){
//                 int num1=atoi(temp.substr(0,i).c_str());
//                 int num2=atoi(temp.substr(i+1,temp.length()-i-1).c_str());
//                 set<int> ans;
//                 if(temp[i]==':')
//                     ans=dealer1(num1,num2);
//                 if(temp[i]=='~')
//                     ans=dealer2(num1,num2);
//                 return ans;
//             }
//         }
//     }
// }

// int main(){
//     cin>>n;
//     for(int i=0;i<n;i++){
//         int DN,numOfAttr;
//         cin>>DN>>numOfAttr;
//         for(int j=0;j<numOfAttr;j++){
//             int attr,val_attr;
//             cin>>attr>>val_attr;
//             usr temp;
//             temp.DN=DN;
//             temp.key=val_attr;
//             attr2usr[attr].push_back(temp);
//         }
//     }
//     int m;
//     cin>>m;
//     string str;
//     for(int i=0;i<m;i++){
//         cin>>str;
//         set<int> ans=strHandler(str);
//         if(ans.size()==0)
//             cout<<endl;
//         else{
//             set<int>::iterator it;
//             for(set<int>::iterator it=ans.begin();it!=ans.end();++it){
//                 if(it==ans.begin())
//                     cout<<*it;
//                 else
//                     cout<<" "<<*it;
//             }
//             if(i!=m-1)cout<<endl;
//         }
//     }
//     return 0;
// }

// int round_0 (double n){
//     if (n > 0)
//         return n - int(n) >= 0.5 ? int(n)+1 : int(n);
//     else
//         return -n - int(-n) >= 0.5 ? -(int(-n) + 1) : -int(-n);
// }

// #define pi acos(-1)
// #define sq pow(0.5,0.5)
// int main(){
//     int matrix[8][8];
//     int s_matrix[8][8]{0};
//     map<int ,int>_turn;
//     int turn[14]={0,2,5,9,14,20,27,35,42,48,53,57,60,62};
//     int Turn[14]={0,1,0,1,0 , 1, 0, 0, 1, 0, 1, 0, 1, 0};
//     for(int i=0;i<14;i++){
//         _turn[turn[i]]=Turn[i];
//     }
//     for(int i=0;i<8;i++){
//         for(int j=0;j<8;j++){
//             cin>>matrix[i][j];
//         }
//     }
//     int N,opt,round=0,i=0,j=0;
//     cin>>N>>opt;
//     int scanMatrix[64];
//     for(int i=0;i<64;i++){
//         if(i<N)
//             cin>>scanMatrix[i];
//         else
//             scanMatrix[i]=0;
//     }
//     bool temp=false;
//     while(round<64){
//         s_matrix[i][j]=scanMatrix[round];
//         map<int,int>::iterator it=_turn.find(round);
//         if(it==_turn.end()){
//             if (temp) {
//                 i++;
//                 j--;
//             }
//             else {
//                 i--;
//                 j++;
//             }
//         }
//         else{
//             temp=!temp;
//             if(it->second==0)j++;
//             else i++;
//         }
//         round++;
//     }
//     if(opt==0){
//         for(int i=0;i<8;i++){
//             for(int j=0;j<8;j++){
//                 cout<<s_matrix[i][j]<<" ";
//                 if(j==7) cout<<endl;
//             }
//         }
//     }
//     else if(opt==1){
//         for(int i=0;i<8;i++){
//             for(int j=0;j<8;j++){
//                 s_matrix[i][j]=s_matrix[i][j]*matrix[i][j];
//             }
//         }
//         for(int i=0;i<8;i++){
//             for(int j=0;j<8;j++){
//                 cout<<s_matrix[i][j]<<" ";
//                 if(j==7) cout<<endl;
//             }
//         }
//     }
//     else{
//         for(int i=0;i<8;i++){
//             for(int j=0;j<8;j++){
//                 s_matrix[i][j]=s_matrix[i][j]*matrix[i][j];
//             }
//         }
//         double sum=0;
//         int ans[8][8];
//         for(int i=0;i<8;i++){
//             for(int j=0;j<8;j++){
//                 sum=0;
//                 for(int p=0;p<8;p++){
//                     for(int q=0;q<8;q++){
//                         double au,av;
//                         if(p==0) au=sq;
//                         else au=1;
//                         if(q==0) av=sq;
//                         else av=1;
//                         sum+=0.25*au*av*(double)s_matrix[p][q]*cos(pi/8*(i+0.5)*p)*cos(pi/8*(j+0.5)*q);
//                     }
//                 }
//                 ans[i][j]=round_0(sum+128);
//                 if(ans[i][j]>255) ans[i][j]=255;
//                 if(ans[i][j]<0) ans[i][j]=0;
//             }
//         }
//         for(int i=0;i<8;i++){
//             for(int j=0;j<8;j++){
//                 cout<<ans[i][j]<<" ";
//                 if(j==7) cout<<endl;
//             }
//         }
//     }
//     return 0;
// }

// int n,m;
// int rely[100];
// int date[100];
// vector<int> _rely[100];

// int find_early(int subNo){
//     if(rely[subNo]==0) return 1;
//     int ans=date[rely[subNo]-1]+find_early(rely[subNo]-1);
//     return ans;
// }

// int find_late(int subNo){
//     if(_rely[subNo].size()==0)
//         return n+1-date[subNo];
//     else{
//         int ans=365;
//         for(int i=0;i<_rely[subNo].size();i++){
//             int temp=find_late(_rely[subNo][i])-date[subNo];
//             if(ans>temp) ans=temp;
//         }
//         return ans;
//     }
// }

// int main(){
//     cin>>n>>m;
//     for(int i=0;i<m;i++){
//         cin>>rely[i];
//     }
//     for(int i=0;i<m;i++){
//         cin>>date[i];
//     }
//     bool ifContinue=true;
//     for(int i=0;i<m;i++){
//         int temp=find_early(i);
//         cout<<temp<<" ";
//         if(temp+date[i]>n+1) ifContinue=false;
//     }
//     cout<<endl;
//     if(ifContinue){
//         for(int i=0;i<m;i++){
//             if(rely[i]!=0){
//                 _rely[rely[i]-1].push_back(i);
//             }
//         }
//         for(int i=0;i<m;i++){
//             int temp=find_late(i);
//             cout<<temp<<" ";
//         }
//     }
//     return 0;
// }

// int main(){
//     int n;
//     double i;
//     cin>>n;
//     scanf("%lf", &i);
//     double money[n+1];
//     for(int i=0;i<=n;i++){
//         scanf("%lf", &money[i]);
//     }
//     double ans=0;
//     for(int j=0;j<=n;j++){
//         if(money[j]!=0){
//             ans+=money[j]*pow((1/(1+i)),j);
//         }
//     }
//     printf("%f", ans);
//     return 0;
// }

// int main(){
//     int n,m;
//     cin>>n>>m;
//     int a[n+1];
//     for(int i=0;i<=n;i++){
//         if(i==0) a[i]=0;
//         else cin>>a[i];
//     }
//     int c[n+1];
//     for(int i=0;i<=n;i++){
//         if(i==0) c[i]=1;
//         else if(i==1) c[i]=a[i];
//         else{
//             c[i]=c[i-1]*a[i];
//         }
//     }
//     int ans[n+1];
//     int plus=0;
//     for(int i=1;i<=n;i++){
//         ans[i]=(m%c[i]-plus)/c[i-1];
//         plus+=ans[i]*c[i-1];
//     }
//     for(int i=1;i<=n;i++){
//         cout<<ans[i]<<" ";
//     }
//     return 0;
// }

// const int N = 300010;
// int n, m, v, sum;
// int f[N];
// int main() {
//     cin >> n >> m;
//     for (int i = 0; i < n; i++) {
//         cin >> v;
//         sum += v;
//         for (int j = sum; j >= v; j--) {
//             f[j] = max(f[j], f[j - v] + v);
//         }
//     }
//     for (int i = m;; i++) {
//         if (f[i] >= m) {
//             cout << f[i];
//             break;
//         }
//     }
//     return 0;
// }
 
// int n,m,r;
// struct Data{
//     int d,u,p;
// };
// vector<Data> v[1010];
// map<int,pair<int,int> > pos;
// map<int,bool> st;
 
// void setf(int p,int d){
//     if(!st[p]) pos[p]={d,d+6};
//     else{
//         if(d<=pos[p].second+1) 
//             pos[p].second=d+6;
//         else 
//             pos[p]={d,d+6};
//     }
//     st[p]=true;
// }
 
// bool check(int d1,int u,int p,int d){
//     if(st[p]&&d1>=d-6&&d1<=d&&d1>=pos[p].first&&d<=pos[p].second) 
//         return true;
//     return false;
// }
 
// int main(){
//     cin>>n;
//     for(int h=0;h<n;h++){
//         cin>>r>>m;
//         for(int i=1;i<=r;i++){
//             int t;
//             cin>>t;
//             setf(t,h);
//         }
//         for(int i=1;i<=m;i++){
//             int d,u,p;
//             cin>>d>>u>>p;
//             if(d<=h) v[h].push_back({d,u,p});
//         }
//         vector<int> ans;
//         for(int i=(h-6>=0?h-6:0);i<=h;i++){
//             for(int j=0;j<v[i].size();j++){
//                 if(check(v[i][j].d,v[i][j].u,v[i][j].p,h)) 
//                     ans.push_back(v[i][j].u);
//             }
//         }
//         sort(ans.begin(),ans.end());
//         ans.erase(unique(ans.begin(),ans.end()),ans.end());
//         cout<<h;
//         for(int i=0;i<ans.size();i++) 
//             cout<<" "<<ans[i];
//         cout<<endl;
//     }
//     return 0;
// }

// int main(){
//     int n,sum=0;
//     cin>>n;
//     int a[n];
//     for(int i=0;i<n;i++){
//         cin>>a[i];
//         sum+=a[i];
//     }
//     double average=(double)sum/(double)n;
//     double Da=0;
//     for(int i=0;i<n;i++){
//         Da+=pow((double)a[i]-average,2);
//     }
//     Da/=n;
//     for(int i=0;i<n;i++){
//         double ans=0;
//         ans=((double)a[i]-average)/pow(Da,0.5);
//         printf("%f\n",ans);
//     }
//     return 0;
// }


// int main(){
//     int n,L,S,ans=0;
//     cin>>n>>L>>S;
//     map<pair<int,int>,int> tree;
//     pair<int,int> Tree[n];
//     for(int i=0;i<n;i++){
//         int tree_x,tree_y;
//         cin>>tree_x>>tree_y;
//         pair<int,int> curr_tree;
//         curr_tree.first=tree_x;
//         curr_tree.second=tree_y;
//         Tree[i]=curr_tree;
//         tree[curr_tree]=0;
//     }
//     int treasure[S+1][S+1];
//     for(int i=S;i>=0;i--){
//         for(int j=0;j<=S;j++){
//             cin>>treasure[i][j];
//         }
//     }
//     for(int i=0;i<n;i++){
//         if(Tree[i].first+S>L||Tree[i].second+S>L){
//             continue;
//         }
//         else{
//             int conv=0;
//             for(int p=0;p<=S;p++){
//                 for(int q=0;q<=S;q++){
//                     pair<int,int> t;
//                     t.first=Tree[i].first+p;
//                     t.second=Tree[i].second+q;
//                     map<pair<int,int>,int>::iterator it=tree.find(t);
                    
//                     int ifTree=it==tree.end()?0:1;
//                     if(treasure[p][q]==ifTree) conv++;
//                 }
//             }
//             if(conv==pow(S+1,2)) ans++;
//         }
//     }
//     cout<<ans<<endl;
// }

// map<string,set<string>>usr2opt;
// map<string,set<string>>usr2kind;
// map<string,set<string>>usr2name;
// map<string,set<string>>one2usr;
// map<string,set<string>>grp2usr;
// int n,m,q;

// vector<string> stringSplit(const string& strIn, char delim) {
//     char* str = const_cast<char*>(strIn.c_str());
//     string s;
//     s.append(1, delim);
//     vector<string> elems;
//     char* splitted = strtok(str, s.c_str());
//     while (splitted != NULL) {
//         elems.push_back(string(splitted));
//         splitted = strtok(NULL, s.c_str());
//     }
//     return elems;
// }


// int main(){
//     ios::sync_with_stdio(false);
//     cin>>n>>m>>q;
//     cin.ignore();
//     for(int i=0;i<n;i++){
//         string temp;
//         getline(cin,temp);
//         vector<string> curr=stringSplit(temp,' ');
//         string name=curr[0];
//         int num1,num2,num3;
//         num1=atoi(curr[1].c_str());
//         num2=atoi(curr[2+num1].c_str());
//         num3=atoi(curr[3+num1+num2].c_str());
//         for(int j=1;j<=num1;j++){
//             usr2opt[name].insert(curr[1+j]);
//         }
//         for(int j=1;j<=num2;j++){
//             usr2kind[name].insert(curr[2+num1+j]);
//         }
//         for(int j=1;j<=num3;j++){
//             usr2name[name].insert(curr[3+num1+num2+j]);
//         }
//     }
//     for(int i=0;i<m;i++){
//         string temp;
//         //cin.ignore();
//         getline(cin,temp);
//         vector<string> curr=stringSplit(temp,' ');
//         string usr=curr[0];
//         int round=atoi(curr[1].c_str());
//         for(int j=0;j<round;j++){
//             if(curr[2*(j+1)]=="g"){
//                 grp2usr[curr[2*(j+1)+1]].insert(usr);
//             }
//             else{
//                 one2usr[curr[2*(j+1)+1]].insert(usr);
//             }
//         }
//     }

//     for(int i=0;i<q;i++){
//         string temp;
//         //cin.ignore();
//         getline(cin,temp);
//         vector<string> curr=stringSplit(temp,' ');
//         string one=curr[0];
//         int numOfGrp=atoi(curr[1].c_str());
//         set<string> user;
//         set<string> opt;
//         set<string> name;
//         set<string> kind;
//         map<string,set<string>>::iterator it;
//         //all-user
//         it=one2usr.find(one);
//         if(it!=one2usr.end()){
//             set_union(it->second.begin(),it->second.end(),user.begin(),user.end(),inserter(user,user.begin()));
//         }
//         for(int j=0;j<numOfGrp;j++){
//             it=grp2usr.find(curr[2+j]);
//             if(it!=grp2usr.end()){
//                 set_union(it->second.begin(),it->second.end(),user.begin(),user.end(),inserter(user,user.begin()));
//             }
//         }
//         set<string>::iterator it1;
//         //opt
//         for(it1=user.begin();it1!=user.end();it1++){
//             it=usr2opt.find(*it1);
//             if(it!=usr2opt.end()){
//                 set_union(it->second.begin(),it->second.end(),opt.begin(),opt.end(),inserter(opt,opt.begin()));
//             }
//         }
//         //kind
//         for(it1=user.begin();it1!=user.end();it1++){
//             it=usr2kind.find(*it1);
//             if(it!=usr2kind.end()){
//                 set_union(it->second.begin(),it->second.end(),kind.begin(),kind.end(),inserter(kind,kind.begin()));
//             }
//         }
//         //name
//         for(it1=user.begin();it1!=user.end();it1++){
//             it=usr2name.find(*it1);
//             if(it!=usr2name.end()){
//                 set_union(it->second.begin(),it->second.end(),name.begin(),name.end(),inserter(name,name.begin()));
//             }
//         }

//         string curr_opt=curr[2+numOfGrp];
//         string curr_kind=curr[3+numOfGrp];
//         string curr_name=curr[4+numOfGrp];
//         if(!(opt.find(curr_opt)==opt.end()&&opt.find("*")==opt.end())){
//             if(!(kind.find(curr_kind)==kind.end()&&kind.find("*")==kind.end())){
//                 if(!(name.find(curr_name)==name.end()&&name.size()!=0)){
//                     cout<<1<<endl;
//                     continue;
//                 }
//             }
//         }
//         cout<<0<<endl;
//     }
// }

// int main(){
//     int n,k,x,y,ans=0;
//     cin>>n>>k;
//     set<int> neg_ini;
//     for(int i=1;i<=n;i++){
//         neg_ini.insert(i);
//     }
//     for(int i=0;i<k;i++){
//         cin>>x>>y;
//         if(neg_ini.find(y)!=neg_ini.end()){
//             ans++;
//         }
//         set<int>::iterator it=neg_ini.find(x);
//         if(it!=neg_ini.end()){
//             neg_ini.erase(it);
//         }
//     }
//     cout<<ans<<endl;
//     return 0;
// }

// int n,m,k,q;
// int cnt[100005]{0};
// int main(){
//     cin>>n>>m>>k;
//     for(int i=1;i<n;i++){
//         int t,c;
//         cin>>t>>c;
//         int x=t+1-k-c;
//         int y=t-k;
//         if(y<0) 
//             continue;
//         x=max(1,x);
//         cnt[x]++;
//         cnt[y+1]--;
//     }
//     for(int i=1;i<100005;i++){
//         cnt[i]+=cnt[i-1];
//     }
//     while(m--){
//         cin>>q;
//         cout<<cnt[q]<<endl;
//     }
//     return 0;
// }

// struct Node{  
//     int id;   
//     int cnt;  
//     int from;  
//     map<int,bool> book;
//     bool operator < (const Node &a)const{ 
//         if(cnt!=a.cnt) return cnt>a.cnt;
//         else return id>a.id;
//     }
// }node[1006];
 
// map<int,bool> qu[1006]; 
// int n,m,g;
 
// priority_queue<Node> chose(int &a,int &na,int &pa,int paa,int &paar){
//     vector<Node> c1;
//     if(na){
//         for(int j=1;j<=n;j++){
//             if(node[j].from==na) c1.push_back(node[j]);
//         }
//     }
//     else{
//         for(int j=1;j<=n;j++) c1.push_back(node[j]);
//     }
//     vector<Node> c2;
//     if(pa){
//         for(int j=0;j<c1.size();j++){
//             if(qu[c1[j].from][pa]) c2.push_back(c1[j]);
//         }
//     }
//     else c2=c1;
//     vector<Node> c3;
//     if(paa){
//         for(int j=0;j<c2.size();j++){
//             if(!c2[j].book[paa]) c3.push_back(c2[j]);
//         }
//     }
//     else c3=c2;
//     priority_queue<Node> final;
//     for(int j=0;j<c3.size();j++) final.push(c3[j]);
//     return final;
// }
 
// int ans(int tf,priority_queue<Node> &final,int &a,int paa){
//     while(tf&&!final.empty()){
//         Node temp=final.top();
//         final.pop();
//         cout<<temp.id<<' ';
//         node[temp.id].cnt++;
//         node[temp.id].book[a]=true;
//         qu[temp.from][a]=true;
//         if(a!=paa) temp.cnt++,final.push(temp);
//         tf--;
//     }
//     return tf;
// }
 
// int main(){
//     cin>>n>>m;
//     for(int i=1;i<=n;i++) node[i].id=i;
//     for(int i=1;i<=n;i++){
//         int temp;
//         cin>>temp;
//         node[i].from=temp;
//     }
//     cin>>g;
//     while(g--){
//         int f,a,na,pa,paa,paar;
//         cin>>f>>a>>na>>pa>>paa>>paar;
//         priority_queue<Node> final=chose(a,na,pa,paa,paar);
//         int tf=ans(f,final,a,paa);
//         if(tf&&!paar){
//             final=chose(a,na,pa,0,paar);
//             tf=ans(tf,final,a,0);
//         }
//         while(tf--) cout<<0<<' ';
//         cout<<endl;
//     }
//     return 0;
// }

// int main(){
//     int n,N;
//     cin>>n>>N;
//     int price[n]{0};
//     queue<int> ans;
//     for(int i=1;i<=n;i++){
//         cin>>price[i];
//         ans.push(price[i]);
//     }
//     int sum=0,first=0,last=0,round=0;
//     while(1){
//         if(ans.size()==0)
//             last=N;
//         else
//             last=ans.front();
//         sum+=(last-first)*(round++);
//         first=last;
//         if(ans.size()==0)
//             break;
//         ans.pop();
//     }
//     cout<<sum<<endl;
//     return 0;
// }

// long long int n,N;
// int main(){
//     cin>>n>>N;
//     int A[n];
//     int f[N]{0};
//     int g[N];
//     for(int i=0;i<n;i++){
//         cin>>A[i];
//         f[A[i]]=i+1;
//     }
//     int round=0;
//     long long int r=N/(n+1);
//     long long int sum=0;
//     for(long long int i=0;i<N;i++){
//         if(f[i]!=0)
//             round=f[i];
//         else   
//             f[i]=round;
//         g[i]=i/r;
//         sum+=abs(f[i]-g[i]);
//     }
//     cout<<sum<<endl;
//     return 0;
// }

// #include <iostream>
// #include <fstream>
// #include <string>
// #include <vector>
// #include <ctime>
// #include <cstdlib>
// #include <cstring>
// using namespace std;

// const int MAXN = 9;
// const int MAXM = 100;

// int map[MAXN][MAXN];
// int ans[MAXN][MAXN];
// int cnt;
// int difficulty;
// int blanks;
// bool uniqueAns;

// bool check(int row, int col, int num) {
//     for (int i = 0; i < MAXN; i++) {
//         if (map[row][i] == num || map[i][col] == num) {
//             return false;
//         }
//     }
//     int r = row / 3 * 3, c = col / 3 * 3;
//     for (int i = r; i < r + 3; i++) {
//         for (int j = c; j < c + 3; j++) {
//             if (map[i][j] == num) {
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// void dfs(int row, int col) {
//     if (row >= MAXN) {
//         memcpy(ans, map, sizeof(map));
//         cnt++;
//         return;
//     }
//     int nextRow = col == MAXN - 1 ? row + 1 : row;
//     int nextCol = (col + 1) % MAXN;
//     if (map[row][col] != 0) {
//         dfs(nextRow, nextCol);
//         return;
//     }
//     for (int i = 1; i <= MAXN; i++) {
//         if (check(row, col, i)) {
//             map[row][col] = i;
//             dfs(nextRow, nextCol);
//             if (cnt > 1 || (uniqueAns && cnt == 1)) {
//                 return;
//             }
//         }
//     }
//     map[row][col] = 0;
// }

// void generate() {
//     ofstream fout("sudoku.txt");
//     if (!fout) {
//         cout << "Failed to open file!" << endl;
//         return;
//     }
//     srand(time(NULL));
//     for (int i = 0; i < cnt; i++) {
//         memset(map, 0, sizeof(map));
//         dfs(0, 0);
//         for (int j = 0; j < MAXN; j++) {
//             for (int k = 0; k < MAXN; k++) {
//                 fout << ans[j][k] << " ";
//             }
//             fout << endl;
//         }
//         fout << endl;
//     }
//     fout.close();
// }

// bool readFromFile(string fileName) {
//     ifstream fin(fileName);
//     if (!fin) {
//         cout << "Failed to open file!" << endl;
//         return false;
//     }
//     int n = 0;
//     while (fin >> map[n / MAXN][n % MAXN]) {
//         n++;
//     }
//     fin.close();
//     if (n != MAXN * MAXN) {
//         cout << "Invalid file format!" << endl;
//         return false;
//     }
//     return true;
// }

// bool writeToFile(string fileName) {
//     ofstream fout(fileName);
//     if (!fout) {
//         cout << "Failed to open file!" << endl;
//         return false;
//     }
//     for (int i = 0; i < MAXN; i++) {
//         for (int j = 0; j < MAXN; j++) {
//             fout << ans[i][j] << " ";
//         }
//         fout << endl;
//     }
//     fout.close();
//     return true;
// }

// bool generateGames() {
//     srand(time(NULL));
//     for (int i = 0; i < cnt; i++) {
//         memset(map, 0, sizeof(map));
//         dfs(0, 0);
//         int randOrder[MAXN * MAXN];
//         for (int j = 0; j < MAXN * MAXN; j++) {
//             randOrder[j] = j;
//         }
//         for (int j = MAXN * MAXN - 1; j >= 1; j--) {
//             int k = rand() % (j + 1);
//             swap(randOrder[j], randOrder[k]);
//         }
//         for (int j = 0; j < blanks; j++) {
//             int row = randOrder[j] / MAXN, col = randOrder[j] % MAXN;
//             int tmp = map[row][col];
//             map[row][col] = 0;
//             int cnt = 0;
//             for (int k = 1; k <= MAXN; k++) {
//                 if (check(row, col, k)) {
//                     cnt++;
//                 }
//             }
//             if (cnt != 1) {
//                 map[row][col] = tmp;
//             }
//         }
//         if (uniqueAns) {
//             int backupMap[MAXN][MAXN];
//             memcpy(backupMap, map, sizeof(map));
//             cnt = 0;
//             dfs(0, 0);
//             if (cnt != 1) {
//                 memcpy(map, backupMap, sizeof(map));
//                 i--;
//                 continue;
//             }
//         }
//         string fileName = "game" + to_string(i + 1) + ".txt";
//         if (!writeToFile(fileName)) {
//             return false;
//         }
//     }
//     return true;
// }

// int main(int argc, char* argv[]) {
//     if (argc <= 1) {
//         cout << "No parameter specified!" << endl;
//         return 0;
//     }
//     cnt = 1;
//     difficulty = 2;
//     blanks = 50;
//     uniqueAns = false;
//     for (int i = 1; i < argc; i++) {
//         if (strcmp(argv[i], "-c") == 0) {
//             i++;
//             if (i >= argc) {
//                 cout << "Invalid parameter!" << endl;
//                 return 0;
//             }
//             cnt = atoi(argv[i]);
//         } else if (strcmp(argv[i], "-s") == 0) {
//             i++;
//             if (i >= argc) {
//                 cout << "Invalid parameter!" << endl;
//                 return 0;
//             }
//             if (!readFromFile(argv[i])) {
//                 return 0;
//             }
//             memset(ans, 0, sizeof(ans));
//             cnt = 1;
//         } else if (strcmp(argv[i], "-n") == 0) {
//             i++;
//             if (i >= argc) {
//                 cout << "Invalid parameter!" << endl;
//                 return 0;
//             }
//             cnt = atoi(argv[i]);
//         } else if (strcmp(argv[i], "-m") == 0) {
//             i++;
//             if (i >= argc) {
//                 cout << "Invalid parameter!" << endl;
//                 return 0;
//             }
//             difficulty = atoi(argv[i]);
//         } else if (strcmp(argv[i], "-r") == 0) {
//             i++;
//             if (i >= argc) {
//                 cout << "Invalid parameter!" << endl;
//                 return 0;
//             }
//             blanks = atoi(argv[i]);
//         } else if (strcmp(argv[i], "-u") == 0) {
//             uniqueAns = true;
//         } else {
//             cout << "Invalid parameter!" << endl;
//             return 0;
//         }
//     }
//     if (cnt <= 0 || difficulty < 1 || difficulty > 3 || blanks < 0 || blanks > MAXN * MAXN) {
//         cout << "Invalid parameter!" << endl;
//         return 0;
//     }
//     if (strcmp(argv[1], "-c") == 0) {
//         generate();
//     } else if (strcmp(argv[1], "-s") == 0) {
//         dfs(0, 0);
//         if (cnt == 1) {
//             if (!writeToFile("solution.txt")) {
//                 return 0;
//             }
//         } else {
//             cout << "No solution or multiple solutions!" << endl;
//         }
//     } else if (strcmp(argv[1], "-n") == 0) {
//         if (!generateGames()) {
//             return 0;
//         }
//     }
//     return 0;
// }

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include <stdexcept>

class Sudoku {
public:
    int SIZE = 9;
    int UNASSIGNED = 0;

    Sudoku() : grid(SIZE, std::vector<int>(SIZE, UNASSIGNED)) {}

    bool solve() {
        int row, col;

        if (!findUnassignedLocation(row, col)) {
            return true;
        }

        for (int num = 1; num <= SIZE; ++num) {
            if (isSafe(row, col, num)) {
                grid[row][col] = num;

                if (solve()) {
                    return true;
                }

                grid[row][col] = UNASSIGNED;
            }
        }
        return false;
    }

    void generate(int holes, bool unique, int difficulty) {
        //std::random_device rd;
        //std::mt19937 gen(rd());
        std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> dist(1, SIZE);

        Sudoku tmp;
        std::fill(tmp.grid.begin(), tmp.grid.end(), std::vector<int>(SIZE, UNASSIGNED));
        for (int i = 0; i < SIZE * difficulty; ++i) {
            int row = dist(gen) - 1;
            int col = dist(gen) - 1;
            int num = dist(gen);

            if (tmp.grid[row][col] == UNASSIGNED && tmp.isSafe(row, col, num)) {
                tmp.grid[row][col] = num;
            }
        }

        if (!tmp.solve()) {
            generate(holes, unique, difficulty);
            return;
        }

        *this = tmp;

        std::uniform_int_distribution<> holeDist(0, SIZE - 1);
        for (int i = 0; i < holes; ++i) {
            int row = holeDist(gen);
            int col = holeDist(gen);

            if (grid[row][col] != UNASSIGNED) {
                grid[row][col] = UNASSIGNED;
            } else {
                --i;
            }
        }

        if (unique) {
            Sudoku tmp2(*this);
            if (!tmp2.solve()) {
                generate(holes, unique, difficulty);
            }
        }
    }

    void loadFromFile(const std::string &filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Error: Cannot open file.");
        }

        for (int row = 0; row < SIZE; ++row) {
            for (int col = 0; col < SIZE; ++col) {
                file >> grid[row][col];
            }
        }
    }

    void saveToFile(const std::string &filename) const {
        std::ofstream file(filename, std::ios::app);
        if (!file) {
            throw std::runtime_error("Error: Cannot open file.");
        }

        for (int row = 0; row < SIZE; ++row) {
            for (int col = 0; col < SIZE; ++col) {
                file << grid[row][col] << (col == SIZE - 1 ? '\n' : ' ');
            }
        }
        file << "\n";
    }

private:
    std::vector<std::vector<int>> grid;

    bool findUnassignedLocation(int &row, int &col) {
        for (row = 0; row < SIZE; ++row) {
            for (col = 0; col < SIZE; ++col) {
                if (grid[row][col] == UNASSIGNED) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isSafe(int row, int col, int num) {
        return !usedInRow(row, num) && !usedInCol(col, num) && !usedInBox(row - row % 3, col - col % 3, num);
    }

    bool usedInRow(int row, int num) {
        return std::find(grid[row].begin(), grid[row].end(), num) != grid[row].end();
    }

    bool usedInCol(int col, int num) {
        return std::any_of(grid.begin(), grid.end(), [col, num](const std::vector<int> &row) {
            return row[col] == num;
        });
    }

    bool usedInBox(int boxStartRow, int boxStartCol, int num) {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (grid[row + boxStartRow][col + boxStartCol] == num) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            throw std::runtime_error("Error: Insufficient arguments.");
        }

        int generatedCount = 0;
        int holes = 0;
        bool unique = false;
        int difficulty = 1;
        bool generateMode = false;
        bool solveMode = false;
        std::string inputFile;
        std::string outputFile = "sudoku_output.txt";

        for (int i = 1; i < argc; ++i) {
            std::string arg(argv[i]);

            if (arg == "-c") {
                if (i + 1 < argc) {
                    generatedCount = std::stoi(argv[++i]);
                    generateMode = true;
                } else {
                    throw std::runtime_error("Error: Missing argument for '-c'.");
                }
            } else if (arg == "-s") {
                if (i + 1 < argc) {
                    inputFile = argv[++i];
                    solveMode = true;
                } else {
                    throw std::runtime_error("Error: Missing argument for '-s'.");
                }
            } else if (arg == "-n") {
                if (i + 1 < argc) {
                    generatedCount = std::stoi(argv[++i]);
                    generateMode = true;
                } else {
                    throw std::runtime_error("Error: Missing argument for '-n'.");
                }
            } else if (arg == "-m") {
                if (i + 1 < argc) {
                    difficulty = std::stoi(argv[++i]);
                    if (difficulty < 1 || difficulty > 3) {
                        throw std::runtime_error("Error: Difficulty must be between 1 and 3.");
                    }
                } else {
                    throw std::runtime_error("Error: Missing argument for '-m'.");
                }
            } else if (arg == "-r") {
                if (i + 1 < argc) {
                    holes = std::stoi(argv[++i]);
                } else {
                    throw std::runtime_error("Error: Missing argument for '-r'.");
                }
            } else if (arg == "-u") {
                unique = true;
            } else {
                throw std::runtime_error("Error: Invalid argument.");
            }
        }

        if (generateMode) {
            std::ofstream file(outputFile);
            if (!file) {
                throw std::runtime_error("Error: Cannot open output file.");
            }
            file.close();

            Sudoku sudoku;
            for (int i = 0; i < generatedCount; ++i) {
                sudoku.generate(holes, unique, difficulty);
                sudoku.saveToFile(outputFile);
            }
        }

        if (solveMode) {
            Sudoku sudoku;
            sudoku.loadFromFile(inputFile);
            if (sudoku.solve()) {
                sudoku.saveToFile(outputFile);
            } else {
                throw std::runtime_error("Error: Failed to solve the Sudoku puzzle.");
            }
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}