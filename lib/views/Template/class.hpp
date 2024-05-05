#ifndef Template_h
#define Template_h
#include "../abstract.hpp"

class Template:public View {
private:
    int example;
public:
    Template(std::string _id);
    ~Template();
    void display();
    ViewRequest capture(Key _k);
};

#endif