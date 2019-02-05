#include <string>
#include <cmath>
#include <sstream>
#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>

using namespace std;


class Figure {
public:
  virtual string Name() const = 0;

  virtual double Perimeter() const = 0;

  virtual double Area() const = 0;
};


class Triangle : public Figure {
public:
  Triangle(const double& a, const double& b, const double& c) : 
    a_(a), b_(b), c_(c) {}

  string Name() const override {
    return "TRIANGLE";
  }

  double Perimeter() const override {
    return a_ + b_ + c_;
  }

  double Area() const override {
    double p = Perimeter() / 2.0;
    return sqrt(p * (p - a_) * (p - b_) * (p - c_));
  }

private:
  const double a_, b_, c_;
};


class Rect : public Figure {
public:
  Rect(const double& a, const double& b) :
    a_(a), b_(b) {}

  string Name() const override {
    return "RECT";
  }

  double Perimeter() const override {
    return 2 * (a_ + b_);
  }

  double Area() const override {
    return a_ * b_;
  }

private:
  const double a_, b_;
};


class Circle : public Figure {
public:
  Circle(const double& r) : r_(r) {}

  string Name() const override {
    return "CIRCLE";
  }

  double Perimeter() const override {
    return 2 * 3.14 * r_;
  }

  double Area() const override {
    return 3.14 * r_ * r_;
  }

private:
  const double r_;
};


shared_ptr<Figure> CreateFigure(istream& input_s) {
  string type;
  input_s >> type;

  if (type == "RECT") {
    double a, b;
    input_s >> a >> b;
    return make_shared<Rect>(a, b);

  } else if (type == "TRIANGLE") {
    double a, b, c;
    input_s >> a >> b >> c;
    return make_shared<Triangle>(a, b, c);

  } else if (type == "CIRCLE") {
    double r;
    input_s >> r;
    return make_shared<Circle>(r);
  }
}


int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);
    string command;
    is >> command;

    if (command == "ADD") {
      figures.push_back(CreateFigure(is));

    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
      
    } else if (command == "QUIT") {
      break;
    }
  }
  return 0;
}