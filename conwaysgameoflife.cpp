#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>

using namespace std;

const int rows = 20;
const int cols = 80;

vector<vector<bool>> convertTo2DVector(bool** array, int rows, int cols) {
    vector<vector<bool>> result;

    for (int i = 0; i < rows; ++i) {
        vector<bool> row;
        for (int j = 0; j < cols; ++j) {
            row.push_back(array[i][j]);
        }
        result.push_back(row);
    }

    return result;
}

// Function to initialize the grid randomly
void initializeGrid(vector<vector<bool>> &grid) {
    for (int i = 0; i < rows; i++) {
        vector<bool> row;
        for (int j = 0; j < cols; j++) {
            row.push_back(rand() % 2 == 0);
        }
        grid.push_back(row);
    }
}

/**
 * Makes several gliders at the start of the rows
 * Looks like this:
 *   | |O| |
 *   | | |O|
 *   |O|O|O|
*/    
#define EMPTYROWS 2          
void initializeGliderGrid(vector<vector<bool>> &grid) {
    for (int i = 0; i < rows-EMPTYROWS; i++) {
        vector<bool> row;
        if (i % 6 == 0) {
            for (int j = 0; j < cols; j++) {
                row.push_back(0);
                row.push_back(1);
                row.push_back(0);
                row.push_back(0);
                row.push_back(0);

            }
        }
        else if (i  % 6 == 1) {
            for (int j = 0; j < cols; j++) {
                row.push_back(0);
                row.push_back(0);
                row.push_back(1);
                row.push_back(0);
                row.push_back(0);

            }
        }
        else if (i % 6 == 2) {
            for (int j = 0; j < cols; j++) {
                row.push_back(1);
                row.push_back(1);
                row.push_back(1);
                row.push_back(0);
                row.push_back(0);

            }
        }
        else {
            for (int j = 0; j < cols; j++) {
                row.push_back(0);
            }
        }
        grid.push_back(row);
    }
    for (int i = rows-EMPTYROWS; i < rows; i++) {
        vector<bool> row;
        for (int j = 0; j < cols; j++) {
            row.push_back(0);
        }
        grid.push_back(row);
    }
}
void initializeOneGliderGrid(vector<vector<bool>> &grid) {
    for (int i = 0; i < rows; i++) {
        vector<bool> row;
        if (i == 0) {
                row.push_back(0);
                row.push_back(1);
                row.push_back(0);
            for (int j = 3; j < cols; j++) {
                row.push_back(0);
                

            }
        }
        else if (i == 1) {
                row.push_back(0);
                row.push_back(0);
                row.push_back(1);
            for (int j = 3; j < cols; j++) {
                row.push_back(0);

            }
        }
        else if (i == 2) {
                row.push_back(1);
                row.push_back(1);
                row.push_back(1);
            for (int j = 3; j < cols; j++) {
                row.push_back(0);

            }
        }
        else {
            for (int j = 0; j < cols; j++) {
                row.push_back(0);
            }
        }
        grid.push_back(row);
    }
}
void initializeOscillatingGrid(vector<vector<bool>> &grid) {
    vector<vector<bool>> oscillatingGrid(rows, vector<bool>(cols, false));

    //blinker
    oscillatingGrid[1][1] = true;
    oscillatingGrid[1][2] = true;
    oscillatingGrid[1][3] = true;

    // //toad
    oscillatingGrid[5][5] = true;
    oscillatingGrid[5][6] = true;
    oscillatingGrid[5][7] = true;
    oscillatingGrid[6][4] = true;
    oscillatingGrid[6][5] = true;
    oscillatingGrid[6][6] = true;

    //pulsar

    oscillatingGrid[2][40] = true;
    oscillatingGrid[2][41] = true;
    oscillatingGrid[2][42] = true;

    oscillatingGrid[2][46] = true;
    oscillatingGrid[2][47] = true;
    oscillatingGrid[2][48] = true;

    //top 4 verticals
    oscillatingGrid[4][38] = true;
    oscillatingGrid[5][38] = true;
    oscillatingGrid[6][38] = true;

    oscillatingGrid[4][43] = true;
    oscillatingGrid[5][43] = true;
    oscillatingGrid[6][43] = true;

    oscillatingGrid[4][45] = true;
    oscillatingGrid[5][45] = true;
    oscillatingGrid[6][45] = true;

    oscillatingGrid[4][50] = true;
    oscillatingGrid[5][50] = true;
    oscillatingGrid[6][50] = true;

    //middle 4 horizontals
    oscillatingGrid[7][40] = true;
    oscillatingGrid[7][41] = true;
    oscillatingGrid[7][42] = true;

    oscillatingGrid[7][46] = true;
    oscillatingGrid[7][47] = true;
    oscillatingGrid[7][48] = true;

    oscillatingGrid[9][40] = true;
    oscillatingGrid[9][41] = true;
    oscillatingGrid[9][42] = true;

    oscillatingGrid[9][46] = true;
    oscillatingGrid[9][47] = true;
    oscillatingGrid[9][48] = true;

    //bottom 4 verticals
    oscillatingGrid[4+6][38] = true;
    oscillatingGrid[5+6][38] = true;
    oscillatingGrid[6+6][38] = true;

    oscillatingGrid[4+6][43] = true;
    oscillatingGrid[5+6][43] = true;
    oscillatingGrid[6+6][43] = true;

    oscillatingGrid[4+6][45] = true;
    oscillatingGrid[5+6][45] = true;
    oscillatingGrid[6+6][45] = true;

    oscillatingGrid[4+6][50] = true;
    oscillatingGrid[5+6][50] = true;
    oscillatingGrid[6+6][50] = true;

    //bottom 2 horizontals

    oscillatingGrid[14][40] = true;
    oscillatingGrid[14][41] = true;
    oscillatingGrid[14][42] = true;

    oscillatingGrid[14][46] = true;
    oscillatingGrid[14][47] = true;
    oscillatingGrid[14][48] = true;

    grid = oscillatingGrid;
}

void initializeGliderGun(vector<vector<bool>> &grid) {
    vector<vector<bool>> gliderGunGrid(rows, vector<bool>(cols, false));

    // Glider gun
    gliderGunGrid[5][1] = true;
    gliderGunGrid[5][2] = true;
    gliderGunGrid[6][1] = true;
    gliderGunGrid[6][2] = true;

    gliderGunGrid[3][13] = true;
    gliderGunGrid[3][14] = true;
    gliderGunGrid[4][12] = true;
    gliderGunGrid[5][11] = true;
    gliderGunGrid[6][11] = true;
    gliderGunGrid[7][11] = true;
    gliderGunGrid[8][12] = true;
    gliderGunGrid[9][13] = true;
    gliderGunGrid[9][14] = true;

    gliderGunGrid[6][15] = true;
    gliderGunGrid[4][16] = true;
    gliderGunGrid[8][16] = true;

    gliderGunGrid[5][17] = true;
    gliderGunGrid[6][17] = true;
    gliderGunGrid[7][17] = true;

    gliderGunGrid[6][18] = true;

    gliderGunGrid[8][21] = true;
    gliderGunGrid[8][22] = true;
    gliderGunGrid[9][21] = true;
    gliderGunGrid[9][22] = true;
    gliderGunGrid[10][21] = true;
    gliderGunGrid[10][22] = true;

    gliderGunGrid[7][23] = true;
    gliderGunGrid[11][23] = true;
    gliderGunGrid[6][25] = true;
    gliderGunGrid[7][25] = true;
    gliderGunGrid[11][25] = true;
    gliderGunGrid[12][25] = true;

    gliderGunGrid[8][35] = true;
    gliderGunGrid[8][36] = true;
    gliderGunGrid[9][35] = true;
    gliderGunGrid[9][36] = true;

    grid = gliderGunGrid;
}
void initializeStableGrid(vector<vector<bool>> &grid) {
    vector<vector<bool>> stableGrid(rows, vector<bool>(cols, false));
    //names/formations from wikipidia
    //block
    stableGrid[1][1] = true;
    stableGrid[1][2] = true;
    stableGrid[2][1] = true;
    stableGrid[2][2] = true;

    //beehive
    stableGrid[5][5] = true;
    stableGrid[5][6] = true;
    stableGrid[6][4] = true;
    stableGrid[6][7] = true;
    stableGrid[7][5] = true;
    stableGrid[7][6] = true;

    //boat
    stableGrid[10][10] = true;
    stableGrid[10][11] = true;
    stableGrid[11][10] = true;
    stableGrid[11][12] = true;
    stableGrid[12][11] = true;

    grid = stableGrid;
}

// Function to print the grid
void printGrid(const vector<vector<bool>> &grid) {
    system("clear");  // Clears the console (for Unix-like systems)
    for (int i = 0; i < cols; i ++) {
        cout << "=";
    }
    cout << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << (grid[i][j] ? "O" : " ");
        }
        cout << endl;
    }
    for (int i = 0; i < cols; i ++) {
        cout << "=";
    }
    cout << endl;
    usleep(100000); 
}

// Function to update the grid based on the rules of the game
void updateGrid(vector<vector<bool>> &grid) {
    vector<vector<bool>> newGrid(rows, vector<bool>(cols, false));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int neighbors = 0;

            //check neighbors
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) continue;  //skip
                    int ni = (i + dx + rows) % rows;  //wrap around
                    int nj = (j + dy + cols) % cols;
                    neighbors += grid[ni][nj] ? 1 : 0;
                }
            }

            //Conway's rules
            if (grid[i][j] && (neighbors == 2 || neighbors == 3)) {
                newGrid[i][j] = true;  //survives
            } else if (!grid[i][j] && neighbors == 3) {
                newGrid[i][j] = true;  //new cell
            }
        }
    }

    // update grid
    grid = newGrid;
}

int main() {

    cout << "\tWelcome to Conway's Game of Life!" << endl;

    cout <<"\tEnter the number to view the following options:" << endl;
    cout <<"\t1. Random" << endl;
    cout <<"\t2. One Glider" << endl;
    cout <<"\t3. Many Gliders" << endl;
    cout <<"\t4. Stable Life" << endl;
    cout <<"\t5. Oscillators" << endl;
    cout <<"\t6. Glider Gun" << endl;



    


    int option;
    cout << "Enter option number: ";
    cin >> option;

    vector<vector<bool>> grid;

    if (option == 2) {
        //TODO
        initializeOneGliderGrid(grid);
    }
    else if (option == 3) {
        initializeGliderGrid(grid);
    }
    else if (option == 4) {
        initializeStableGrid(grid);
    }
    else if (option == 5) {
        initializeOscillatingGrid(grid);
    }
     else if (option == 6) {
        initializeGliderGun(grid);
    }
    else {
        //random initialization
        initializeGrid(grid);
    }

    //main loop
    for (int i = 0; i < 1000; i++) {
        printGrid(grid);
        updateGrid(grid);
    }

    return 0;
}
