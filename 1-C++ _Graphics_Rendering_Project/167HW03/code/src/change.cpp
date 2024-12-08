#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main() {
    std::ifstream inputFile("/Users/shanjiang/balboa_public/scenes/hw3/balance.ply");
    std::ofstream outputFile("/Users/shanjiang/balboa_public/scenes/hw3/balance2.ply");
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

    // 假设z坐标的范围是minZ到maxZ
    float minZ = -10.0; // 请根据您的数据调整这些值
    float maxZ = 120.0;

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        float x, y, z;
        ss >> x >> y >> z;

        // 计算颜色值
        float ratio = (z - minZ) / (maxZ - minZ);
        int r = 139 * (1 - ratio); // R值从139渐变到0
        int g = 0;                 // G值保持0
        int b = 0;                 // B值保持0

        // 创建一个新字符串，包含坐标和颜色值
        std::string combinedLine = std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z)
                                   + " " + std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b);
        modifiedLines.push_back(combinedLine);
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
