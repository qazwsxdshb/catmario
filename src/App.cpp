#include "App.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

bool App::LoadMapFromCSV(const std::string& filename, int map[24][200]) {
    // 使用相對路徑指向 Resources/Map 目錄
    std::string fullPath = GA_RESOURCE_DIR"/Map/" + filename;
    std::ifstream file(fullPath);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open CSV file: " << fullPath << std::endl;
        return false;
    }

    std::string line;
    int row = 0;

    while (std::getline(file, line) && row < 24) {
        std::stringstream ss(line);
        std::string value;
        int col = 0;

        while (std::getline(ss, value, ',') && col < 200) {
            try {
                map[row][col] = std::stoi(value);
                ++col;
            } catch (const std::exception& e) {
                std::cerr << "Error: Invalid value at row " << row << ", col " << col << " in " << fullPath << ": " << value << std::endl;
                file.close();
                return false;
            }
        }

        if (col != 200) {
            std::cerr << "Error: Invalid number of columns in row " << row << " of " << fullPath << ": expected 200, got " << col << std::endl;
            file.close();
            return false;
        }

        ++row;
    }

    if (row != 24) {
        std::cerr << "Error: Invalid number of rows in " << fullPath << ": expected 24, got " << row << std::endl;
        file.close();
        return false;
    }

    file.close();

    // 調試：輸出樣本數據以確認加載
    std::cout << "Debug: Loaded " << fullPath << ", sample data: map[0][0]=" << map[0][0]
              << ", map[23][0]=" << map[23][0] << ", map[23][199]=" << map[23][199] << std::endl;

    return true;
}

void App::LoadAllMaps() {
    // 加載所有地圖並檢查結果
    if (!LoadMapFromCSV("zerostart.csv", zerostart)) {
        std::cerr << "Warning: Failed to load zerostart map, initializing to zero" << std::endl;
        for (int i = 0; i < 24; ++i) {
            for (int j = 0; j < 200; ++j) {
                zerostart[i][j] = 0;
            }
        }
    } else {
        std::cout << "Success: Loaded zerostart map" << std::endl;
    }

    if (!LoadMapFromCSV("onestart.csv", onestart)) {
        std::cerr << "Warning: Failed to load onestart map, initializing to zero" << std::endl;
        for (int i = 0; i < 24; ++i) {
            for (int j = 0; j < 200; ++j) {
                onestart[i][j] = 0;
            }
        }
    } else {
        std::cout << "Success: Loaded onestart map" << std::endl;
    }

    if (!LoadMapFromCSV("twostart.csv", twostart)) {
        std::cerr << "Warning: Failed to load twostart map, initializing to zero" << std::endl;
        for (int i = 0; i < 24; ++i) {
            for (int j = 0; j < 200; ++j) {
                twostart[i][j] = 0;
            }
        }
    } else {
        std::cout << "Success: Loaded twostart map" << std::endl;
    }

    if (!LoadMapFromCSV("twoend.csv", twoend)) {
        std::cerr << "Warning: Failed to load twoend map, initializing to zero" << std::endl;
        for (int i = 0; i < 24; ++i) {
            for (int j = 0; j < 200; ++j) {
                twoend[i][j] = 0;
            }
        }
    } else {
        std::cout << "Success: Loaded twoend map" << std::endl;
    }

    if (!LoadMapFromCSV("threestart.csv", threestart)) {
        std::cerr << "Warning: Failed to load threestart map, initializing to zero" << std::endl;
        for (int i = 0; i < 24; ++i) {
            for (int j = 0; j < 200; ++j) {
                threestart[i][j] = 0;
            }
        }
    } else {
        std::cout << "Success: Loaded threestart map" << std::endl;
    }
}

// ... 其他 App.cpp 的實現（假設 Zero、Start、ChangeMap 等函數已存在）