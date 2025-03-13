#include<iostream>
#include<set>
#include<vector>
#include<random>
#include<time.h>
using namespace std;

class Person {
    friend ostream& operator<<(ostream &os,const Person &p);
    string name;
    int age;
    public:
    Person(): name{"Unknown"}, age{0} {}
    Person(string name,int age):name{name}, age{age} {}
    bool operator<(const Person &rhs) const {
        return this->age<rhs.age;
    }
    bool operator>(const Person &rhs) const {
        return this->age>rhs.age;
    }
};
ostream& operator<<(ostream &os,const Person &p) {
    os<<p.name<<":"<<p.age;
    return os;
}

template<typename T>
void display(const set<T> &st) {
    cout<<"[ ";
    for(const auto &ele:st)
    {
        cout<<ele<<" ";
    }
    cout<<"]\n";
}
template<typename T>
void display(const set<T,greater<T>> &st) {
    cout<<"[ ";
    for(const auto &ele:st)
    {
        cout<<ele<<" ";
    }
    cout<<"]\n";
}

void test0() {
    cout<<"===== test0 ====="<<endl;
    set<int> st1{1,5,2,3,4,4,5};
    set<int,greater<int>> st2={10,20,30,40,40,40,40,50};
    set<int,less<int>> st3=st1;
    set<int,greater<int>> st4(st2);
    cout<<"Direct List Initialization: ";
    display(st1);
    cout<<"size: "<<st1.size()<<endl;
    cout<<"max_size: "<<st1.max_size()<<endl;
    cout<<"Copy List Initialization with greater<>: ";
    display(st2);
    cout<<"count: "<<st2.count(40)<<endl;
    st2.clear();
    cout<<"clear: "; display(st2);
    cout<<"empty: "<<st2.empty()<<endl;
    
    cout<<"Copy Initialization (using '='): ";
    display(st3);
    st3.insert(6);
    cout<<"insert: ";   display(st3);

    cout<<"Copy Constructor Initialization: ";
    display(st4);
    st4.erase(30);
    cout<<"Erase: ";    display(st4);
    auto it=st4.find(20);
    if(it!=st4.end())
        st4.erase(it);
    cout<<"Find and Erase: ";   display(st4);
    st1.swap(st3);
    cout<<"swap: ";     display(st1);    display(st3);
}

void test1() {
    cout<<"===== test1 ====="<<endl;
    set<Person> st1={{"Larry",1},{"Moe",2},{"Curly",3}};
    display(st1);
    set<Person,greater<Person>> st2={{"Rohit Sharma",45},{"Virat Kohli",18},{"MS Dhoni",07},{"Sachin Tendulkar",10}};
    display(st2);
    st1.emplace("James",50);
    st1.emplace("Suraj",10);
    display(st1);
    st1.emplace("Frank",50);    //Can't insert, ordering is based on age and 50 already exists
    st1.emplace("Larry",100);    //'Larry exists already but still it will get inserted
    display(st1);
    auto it=st1.find(Person{"Moe",2});
    if(it!=st1.end())
        st1.erase(it);
    it=st1.find(Person("XXXX",50));
    if(it!=st1.end())
        st1.erase(it);
    display(st1);
}

void test2() {
    cout<<"===== test2 ====="<<endl;
    set<string,greater<string>> s{"A","B","c"};
    auto result=s.insert("D");
    cout<<boolalpha;
    cout<<"first: "<<*(result.first)<<" second: "<<result.second<<endl;
    result=s.insert("A");
    cout<<"first: "<<*(result.first)<<" second: "<<result.second<<endl;
    display(s);
}

void test3() {
    cout<<"===== test3 =====\n";
    vector<int> arr;
    srand(time(0));
    for(int i=0;i<10;i++)
    {
    arr.push_back(rand()%100+1);
    }
    cout<<"arr1: ";
    for(auto i:arr)
        cout<<i<<"  ";
    cout<<endl;    
    set<int> s1(arr.begin(),arr.end());
    cout<<"Set initialized by vector: ";    display(s1);
    arr={1,2,3,4,5};
    cout<<"arr2: ";
    for(auto i:arr)
        cout<<i<<"  ";
    cout<<endl;
    s1.insert(arr.begin(),arr.end());
    cout<<"Insert: ";    display(s1);
}

int main() {
    test0();
    test1();
    test2();
    test3();
    return 0;
}