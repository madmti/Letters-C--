#include "class.hpp"

Template::Template(std::string _id) : View(_id) {
    example = 0;
    req_keys = std::vector<Key>{

    };
};

void Template::clear() {
    frame.clear();
};

void Template::display() {

};

ViewRequest Template::capture(Key k) {

    return ViewRequest(false);
};