#include <iostream>
#include<set>
#include<map>

using namespace std;

class person_compare{
    public:
    bool operator()(pair<string,int>p1,pair<string,int>p2){
        return p1.second<p2.second;
    }
    
};


int main(){
    int no_oftransaction;
    int friends;
    cin>>no_oftransaction;
    cin>>friends;
    string x,y;  // x gives y an amount 
    int amount;
    map<string,int>net;
    while(no_oftransaction--){
        cin>>x>>y>>amount;
        if(net.count(x)==0){
            net[x]=0;
        }
        if(net.count(y)==0){
            net[y]=0;
        }
        net[x]-=amount;
        net[y]+=amount;
        
    }
    // iterate over the person , who has non zero net add them in the multiset
    multiset<pair<string,int>,person_compare>m;
    for(auto p:net){
        string person=p.first;
        int amount=p.second;
        if(net[person]!=0){
            m.insert(make_pair(person,amount));
        }
    }
    // pop out two person and try to settle them
    int count=0;
    while(!m.empty()){
        auto low=m.begin();
        auto high=prev(m.end());
        int debit=low->second;
        string debit_person=low->first;
        int credit=high->second;
        string credit_person=high->first;
         // erase
        m.erase(low);
        m.erase(high);
        //settlement
        int settlement_amount=min(-debit,credit);
        // settlement amount transfer from donor to accepter
        debit+=settlement_amount;
        credit-=settlement_amount;
        
        // print the transaction betweeen the people
        cout<<debit_person<<"will pay"<<settlement_amount<<"to"<<credit_person<<endl;
        if(debit!=0){
            m.insert(make_pair(debit_person,debit));
        }
        if(credit!=0){
            m.insert(make_pair(credit_person,credit));
        }
    
        count+=1;
    }
    cout<<count<<endl;
}
    