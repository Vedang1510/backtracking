#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

// Function to check if a cell (x, y) is safe to move
bool isSafe(int x, int y, vector<vector<int>> maze, int n, vector<vector<int>> visited){
    // Check if x and y are within bounds, and the cell is not visited and is a valid path (i.e., maze[x][y] == 1)
    if(x >= 0 && x < n && y >= 0 && y < n && maze[x][y] == 1 && !visited[x][y]){
        return true;
    }
    return false;
}

// Function to solve the maze using backtracking
void solveMaze(int x, int y, vector<vector<int>> maze, int n, vector<string> &ans, vector<vector<int>> &visited, string path){
    // Base case: if we've reached the bottom-right corner
    if(x == n-1 && y == n-1){
        ans.push_back(path);
        return;
    }
    
    // Mark the current cell as visited
    visited[x][y] = 1;
    
    // Direction vectors: Down, Left, Right, Up
    vector<pair<char, pair<int,int>>> direction = {{'D',{1,0}},{'L',{0,-1}},{'R',{0,1}},{'U',{-1,0}}};
    
    // Explore all possible directions
    for (auto dir : direction){
        char d = dir.first;          // Direction character
        int newX = x + dir.second.first;  // New row index
        int newY = y + dir.second.second; // New column index
        
        // If it's safe to move to the next cell, recursively solve the maze
        if(isSafe(newX, newY, maze, n, visited)){
            solveMaze(newX, newY, maze, n, ans, visited, path + d);
        }
    }
    
    // Backtrack: Unmark the current cell as visited
    visited[x][y] = 0;
}

// Main function to find and display all paths from top-left to bottom-right in the maze
void ratInMaze(vector<vector<int>> maze){
    int n = maze.size();  // Size of the maze
    vector<vector<int>> visited(n, vector<int>(n, 0));  // 2D array to track visited cells
    vector<string> ans;   // Vector to store all possible paths
    
    // Start solving the maze from the top-left corner (0,0)
    solveMaze(0, 0, maze, n, ans, visited, "");
    
    // Print all the paths found
    for(auto path : ans)
        cout << path << " ";
}

int main()
{
    // Example maze (4x4)
    vector<vector<int>> maze = {{1, 0, 0, 0},
                                {1, 1, 0, 1}, 
                                {1, 1, 0, 0},
                                {0, 1, 1, 1}};
    
    // If the starting cell is blocked, return -1
    if(maze[0][0] != 1)
        return -1;

    // Find and print all paths
    ratInMaze(maze);
    
    return 0;
}
