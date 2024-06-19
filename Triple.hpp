#pragma once
#include <iostream>

template<typename S>
class Triple {
private:
    S first;
    S second;
    S third;

public:
    Triple() = default;
    Triple(const S& first, const S& second, const S& third);
    const S& getFirst() const;
    const S& getSecond() const;
    const S& getThird() const;
    void setFirst(const S& value);
    void setSecond(const S& value);
    void setThird(const S& value);
};

template<typename S>
Triple<S>::Triple(const S& first, const S& second, const S& third) : first(first), second(second), third(third) {

}

template<typename S>
const S& Triple<S>::getFirst() const {
    return first;
}

template<typename S>
const S& Triple<S>::getSecond() const {
    return second;
}

template<typename S>
const S& Triple<S>::getThird() const {
    return third;
}

template<typename S>
void Triple<S>::setFirst(const S& value) {
    first = value;
}

template<typename S>
void Triple<S>::setSecond(const S& value) {
    second = value;
}

template<typename S>
void Triple<S>::setThird(const S& value) {
    third = value;
}

template<typename S>
std::ostream& operator<<(std::ostream& os, const Triple<S>& object) {
    os << object.getFirst() << " " << object.getSecond() << " " << object.getThird();
    return os;
}
