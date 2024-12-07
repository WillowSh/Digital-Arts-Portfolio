#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main() {
    std::ifstream inputFile("shark.ply");
    std::ofstream outputFile("shark1.ply");
    std::string line;
    std::vector<std::string> modifiedLines;

    while (std::getline(inputFile, line)) {
        if (line.find("element vertex") != std::string::npos) {
            modifiedLines.push_back(line); // Copy the line
            modifiedLines.push_back("property uchar red\nproperty uchar green\nproperty uchar blue");
        } else if (line.find("end_header") != std::string::npos) {
            modifiedLines.push_back(line); // Copy the line
            break;
        } else {
            modifiedLines.push_back(line); // Copy other lines as is
        }
    }

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        float x, y, z;
        ss >> x >> y >> z;

        int r, g, b;
        // Your logic to compute the RGB values for each point goes here
        // For simplicity, let's assume RGB values are all set to 255 (white)
        r = g = b = 255;

        modifiedLines.push_back(line); // Copy the original point
        modifiedLines.push_back(std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b));
    }

    inputFile.close();

    // Write the modified lines to the output file
    for (const std::string& modifiedLine : modifiedLines) {
        outputFile << modifiedLine << std::endl;
    }

    outputFile.close();
    std::cout << "Processing completed. Output saved to output.ply" << std::endl;
    return 0;
}
