#include <iostream>

class Fruit{
    protected:
        std::string name, color;
    public:
        Fruit(std::string m_name, std::string m_color) : name(m_name), color(m_color){
        }
        std::string getColor(){
            return color;
        }
};

class Apple : public Fruit{
    public:
        Apple(std::string m_color) : Fruit("apple", m_color){

        }
        Apple(std::string m_color, std::string m_name) : Fruit(m_name, m_color){

        }
        std::string getName(){
            return name;
        }
};

class Banana : public Fruit{
    public:
        Banana() : Fruit("banana", "yellow"){

        }
        std::string getName(){
            return name;
        }
};

class GrannySmith : public Apple{
    public:
        GrannySmith() : Apple("green", "Granny Smith apple"){

        }
        std::string getName(){
            return name;
        }
};

int main()
{
	Apple a("red");
	Banana b;
	GrannySmith c;
 
	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
	
	return 0;
}