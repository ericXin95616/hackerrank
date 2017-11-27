#include <iostream>
#include <sstream>
using namespace std;

class Student {
    private:
        int age;
        std::string first_name;
        std::string last_name;
        int standard;
    public:
        void set_age(const int a){this->age = a;}
        int get_age(){return this->age;}
        void set_standard(const int s){this->standard = s;}
        int get_standard(){return standard;}
        void set_first_name(const std::string& fn){this->first_name = fn; }
        std::string get_first_name(){return this->first_name; }
        void set_last_name(const std::string& ln){this->last_name = ln; }
        std::string get_last_name(){return this->last_name; }
        
        std::string to_string() {
            std::stringstream ss;
            std::string toString;
            std::string temp;
            
            ss << this->age;
            ss >> temp;
            
            toString += temp + "," + first_name + "," + last_name + ",";
            
            ss.clear();
            ss.str("");
            ss << this->standard;
            ss >> temp;
            
            toString += temp;
            return toString;
        }
};

int main() {
    int age, standard;
    string first_name, last_name;
    
    cin >> age >> first_name >> last_name >> standard;
    
    Student st;
    st.set_age(age);
    st.set_standard(standard);
    st.set_first_name(first_name);
    st.set_last_name(last_name);
    
    cout << st.get_age() << "\n";
    cout << st.get_last_name() << ", " << st.get_first_name() << "\n";
    cout << st.get_standard() << "\n";
    cout << "\n";
    cout << st.to_string();
    
    return 0;
}

