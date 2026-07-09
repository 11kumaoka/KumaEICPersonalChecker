#include <iostream>
#include <string>

#include "EventAna.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " input.root [output.root]" << std::endl;
        return 1;
    }

    const std::string inputFile = argv[1];
    const std::string outputFile = (argc >= 3) ? argv[2] : "test.root";

    EventAna analyzer(inputFile, outputFile);
    analyzer.EventLoop();
    return 0;
}