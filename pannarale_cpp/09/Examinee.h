#ifndef Examinee_h
#define Examinee_h

#include<string>

class Examinee {
public:
  Examinee(const std::string& name, int id) {
    name_ = name;
    id_ = id;
  }

  bool operator<(const Examinee& rhs) const {
    return id_ < rhs.id_;
  }

  std::string name() const {
    return name_;
  }

  int id() const {
    return id_;
  }

private:
  std::string name_;
  int id_;
};
#endif
