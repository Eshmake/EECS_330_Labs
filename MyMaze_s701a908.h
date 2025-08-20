#ifndef _MYMAZE_H_
#define _MYMAZE_H_

#include <iostream>
#include <cstdlib>


#include "MyDisjointSets_s701a908.h"

class MyMaze 
{
  public:
	
    // constructor
	explicit MyMaze(const size_t r, const size_t c) : 
        numRows(r), numCols(c), dSets(r * c)
	{
        // code begins
        leftRightWalls = new bool*[numRows];
        topDownWalls = new bool*[numRows + 1]; 

        for (size_t i = 0; i < numRows; ++i) {
            leftRightWalls[i] = new bool[numCols];
        }

        for (size_t i = 0; i < numRows + 1; ++i) { 
            topDownWalls[i] = new bool[numCols];
        }

        for (size_t i = 0; i < numRows; ++i) {
            for (size_t j = 0; j < numCols; ++j) {
                leftRightWalls[i][j] = true;
            }
        }

        for (size_t i = 0; i < numRows + 1; ++i) {
            for (size_t j = 0; j < numCols; ++j) {
                topDownWalls[i][j] = true;
            }
        }

        std::srand(std::rand()); 
        // code ends
	}

    // destructor
    ~MyMaze(void)
    {
        // code begins
        for (size_t i = 0; i < numRows; ++i) {
            delete[] leftRightWalls[i];
        }
        
        delete[] leftRightWalls;

        for (size_t i = 0; i < numRows + 1; ++i) { 
            delete[] topDownWalls[i];
        }

        delete[] topDownWalls;

        // code ends
    }

    // builds a random maze
    // the top wall of the first cell (the top-left corner) should be open as the entrance
    // the bottom wall of the last cell (the bottom-right corner) should be open as the exit
    // algorithm hint: keep breaking walls until the entrance and exit become connected
	void buildMaze(void)
	{
        // code begins

        size_t totalCells = numRows * numCols;
        while (dSets.find(0) != dSets.find(totalCells - 1)) 
        {
            size_t cell = rand() % totalCells;
            bool horiz = rand() % 2; 

            size_t row = cell / numCols;
            size_t col = cell % numCols;

            if (horiz) 
            {
                if (col + 1 < numCols && dSets.find(cell) != dSets.find(cell + 1)) 
                {
                    leftRightWalls[row][col + 1] = false;
                    dSets.unionSets(cell, cell + 1);
                }
            } 
            else 
            {
                if (row + 1 < numRows && dSets.find(cell) != dSets.find(cell + numCols)) 
                {
                    topDownWalls[row + 1][col] = false;
                    dSets.unionSets(cell, cell + numCols);
                }   
            }
        }

        topDownWalls[0][0] = false;
        topDownWalls[numRows][numCols - 1] = false;

        // code ends
	}

    // prints the maze
    // for top-down walls you can use '-' (ASCII code 45)
    // for left-right walls you can use '|' (ASCII code 124)
    // feel free to try out other symbols if your system supports extended ASCII and/or UTF-8
    void printMaze(std::ostream& out = std::cout)
    {
        // code begins
   
        std::cout << " ";
    
        for (size_t c = 0; c < numCols; ++c) {
            if (c == 0) {
                std::cout << "  "; 
            } 
            else {
                std::cout << "- ";
            }
        }
        std::cout << std::endl;

        for (size_t r = 0; r < numRows; ++r) {
            for (size_t c = 0; c < numCols; ++c) {
                if (leftRightWalls[r][c]) {
                    std::cout << "|";
                } 
                else {
                    std::cout << " ";
                }
                std::cout << " ";
            }
        
            std::cout << "|" << std::endl;

            for (size_t c = 0; c < numCols; ++c) {
                if (c == 0) {
                    std::cout << " ";
                }
                if (topDownWalls[r + 1][c]) {
                    std::cout << "- ";
                } 
                else {
                    std::cout << "  ";
                }
            }
            std::cout << std::endl;
        }

        // code ends
    }

  private:
	size_t numRows = 0;         // the number of rows of the maze
	size_t numCols = 0;         // the number of columns of the maze
    MyDisjointSets dSets;       // the disjoint set class that keeps track of maze cell connection
    bool** leftRightWalls;      // the 2D array that indicates whether walls between left-right neighbors present
    bool** topDownWalls;        // the 2D array that indicates whether walls between the top-down neighbors preset

};


#endif // __MYMAZE_H__