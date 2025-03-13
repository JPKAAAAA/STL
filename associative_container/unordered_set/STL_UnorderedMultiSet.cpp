#include<iostream>
#include<unordered_set>
#include<string>
using namespace std;

struct Person {
    string first,last;
    Person(): first("unknown"), last{"unknown"} {}
    Person(string f,string l): first(f), last(l) {}
    bool operator==(const Person &p) const {
        return first==p.first && last==p.last;
    }
};

class MyHashFunction {
    public:
    size_t operator()(const Person &p) const {
        return (hash<string>()(p.first)^hash<string>()(p.last));
    }
};

template<typename T>
void display(unordered_multiset<T> uset)
{
    cout<<"[";
    for(auto i:uset)
        cout<<i<<" ";
    cout<<"]"<<endl;
}

void display(unordered_multiset<Person,MyHashFunction> uset)
{
    cout<<"[";
    for(auto p:uset)
        cout<<p.first<<" "<<p.last<<"  ";
    cout<<"]"<<endl;
}

void test1() {
    cout<<"===== test1 =====\n";
    unordered_multiset<Person,MyHashFunction> uset;
    Person p1;
    Person p2("Suraj","Jha"),p3("Sagar","Jha");
    Person p4{"Reena","Jha"};
    uset.insert({p1,p2,p3,p4});
    uset.insert(Person("Suraj","Jha"));
    uset.insert(Person{"Rohit","Sharma"});
    uset.insert({"Virat","Kohli"});
    uset.insert({{"MS","Dhoni"},Person("Sachin","Tendulkar"),Person{"Rohit","Sharma"}});
    uset.emplace("Suraj","Jha");
    display(uset);
    cout<<"This unordered_set Contains "<<uset.bucket_count()<<"  buckets.\n";
}

void test2() {
    cout<<"===== test2 =====\n";
    unordered_multiset<int> us{1,2,3,4,5,10,15,20,25,30,35,40,45,50,60,70,80,90,100,200,300,400,500,1000};
    display(us);
    cout<<"This unordered_set Contains "<<us.bucket_count()<<"  buckets.\n";
    cout<<"Max Buckets: "<<us.max_bucket_count()<<endl;
    for(int i=0;i<us.bucket_count();i++)
        cout<<"The Bucket["<<i<<"] contains "<<us.bucket_size(i)<<" elements.\n";
    for(unordered_set<int>::iterator itr=us.begin();itr!=us.end();itr++)
        cout<<*itr<<" is present in Bucket["<<us.bucket(*itr)<<"]"<<endl;
}

void test3() {
    //create your own hash function for int
}

int main(int argc,char* argv[])
{
    test1();
    test2();
    return 0;
}