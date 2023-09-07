#include <iostream>
#include "manager.hpp"

// temporary
#include "serialSensor.hpp"

SerialSensor licznik = SerialSensor("licznik", "/dev/ttyUSB0", 115200, 1000);

// end of temporary

void print_usage() {
    std::cout << "Usage: sensor-operating-system <config file>\n";
}



int main(int argc, char* argv[]) {
    Manager manager = Manager();
    manager.addSensor(licznik);


}
    
