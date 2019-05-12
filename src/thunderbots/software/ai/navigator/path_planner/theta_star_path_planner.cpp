#include "ai/navigator/path_planner/theta_star_path_planner.h"

/**
 * This file contains the implementation of a theta star path planner
 * which returns an optimal path that avoids obstacles
 */


ThetaStarPathPlanner::ThetaStarPathPlanner(Field field, Ball ball,
                                           const std::vector<Obstacle> &obstacles)
    : field_(field), ball_(ball), obstacles_(obstacles)
{
    numRows = (int)field_.length() / GRID_DIVISION_IN_METERS;
    numCols = (int)field_.width() / GRID_DIVISION_IN_METERS;
    closedList =
        std::vector<std::vector<bool>>(numRows, std::vector<bool>(numCols, false));

    cellDetails = std::vector<std::vector<GridCell>>(
        numRows, std::vector<GridCell>(numCols, ThetaStarPathPlanner::GridCell(
                                                    -1, -1, DBL_MAX, DBL_MAX, DBL_MAX)));

    unblocked_grid =
        std::vector<std::vector<bool>>(numRows, std::vector<bool>(numCols, true));

    for (unsigned row = 0; row < numRows; row++)
    {
        for (unsigned col = 0; col < numCols; col++)
        {
            Point p(col * GRID_DIVISION_IN_METERS, row * GRID_DIVISION_IN_METERS);
            for (unsigned index = 0; index < obstacles.size(); index++)
            {
                if (obstacles[index].getBoundaryPolygon().containsPoint(p))
                {
                    unblocked_grid[row][col] = false;
                    break;
                }
            }
        }
    }
}

// A Utility Function to check whether given GridCell (row, col)
// is a valid GridCell or not.
bool ThetaStarPathPlanner::isValid(int row, int col)
{
    // Returns true if row number and column number
    // is in range
    return (row >= 0) && (row < numRows) && (col >= 0) && (col < numCols);
}

// A Utility Function to check whether the given GridCell is
// blocked or not
bool ThetaStarPathPlanner::isUnBlocked(int row, int col)
{
    // Returns true if the GridCell is not blocked else false
    return unblocked_grid[row][col];
}

// A Utility Function to check whether destination GridCell has
// been reached or not
bool ThetaStarPathPlanner::isDestination(int row, int col, CellCoordinate dest)
{
    return (row == dest.first && col == dest.second);
}

// A Utility Function to calculate the 'h' heuristics.
double ThetaStarPathPlanner::calculateHValue(int row, int col, CellCoordinate dest)
{
    // Return using the distance formula
    return ((double)sqrt((row - dest.first) * (row - dest.first) +
                         (col - dest.second) * (col - dest.second)));
}

// A Utility Function to trace the path from the source 
// to destination 
std::vector<Point> ThetaStarPathPlanner::tracePath( std::vector<std::vector<GridCell>> cellDetails, CellCoordinate dest) 
{ 
	int row = dest.first; 
	int col = dest.second; 
	std::vector<Point> path_points = std::vector<Point>();

	std::stack<CellCoordinate> Path; 

	while (!(cellDetails[row][col].parent_i_ == row 
			&& cellDetails[row][col].parent_j_ == col )) 
	{ 
		Path.push (std::make_pair (row, col)); 
		int temp_row = cellDetails[row][col].parent_i_; 
		int temp_col = cellDetails[row][col].parent_j_; 
		row = temp_row; 
		col = temp_col; 
	} 

	Path.push (std::make_pair (row, col)); 
	while (!Path.empty()) 
	{ 
		CellCoordinate p = Path.top(); 
		Path.pop(); 
		path_points.push_back(Point(p.first * GRID_DIVISION_IN_METERS, p.second * GRID_DIVISION_IN_METERS));
	} 

	return path_points; 
} 


//==========================//
std::optional<std::vector<Point>> ThetaStarPathPlanner::findPath(
    const Point &start, const Point &dest, const std::vector<Obstacle> &obstacles,
    const ViolationFunction &violation_function)
{
    if (true)
    {
        return std::make_optional<std::vector<Point>>({start, dest});
    }
    else
    {
        return std::nullopt;
    }
}
