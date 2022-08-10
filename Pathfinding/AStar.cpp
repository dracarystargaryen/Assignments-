#include "AStar.h"
#include <fstream>
#include <string>
#include <algorithm>

using namespace std::placeholders;

namespace pf {

	AStar::AStar():
	m_weight(1),
	m_dimensions(0, 0),
	m_startPos(0, 0),
	m_targetPos(0, 0),
	m_size(0),
	m_nrOfDirections(4) {

		m_directions = { {-1, 0}, {1, 0}, {0, 1}, {0, -1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1} };
	}
     
	//Declares algorithm's position and the heuristic function to find the path
	std::vector<PathFinderAlgo> AStar::findPath(const PathFinderAlgo& startPos, const PathFinderAlgo targetPos, HeuristicFunction heuristicFunc, int weight) {
		m_startPos = startPos;
		m_targetPos = targetPos;
		m_weight = weight;
		m_heuristic = std::bind(heuristicFunc, _1, _2, _3);
		m_cameFrom.resize(m_size);
		m_closedList.resize(m_size, false);

		unit aNew, bNew, cNew;
		PathFinderAlgo currentPos;

		while (!m_openList.empty()) {
			currentPos = m_openList.top().pos;

			if (currentPos == m_targetPos) {
				break;
			}
			m_openList.pop();
			m_closedList[covertTo1D(currentPos)] = true;

			for (unit x = 0; x < m_nrOfDirections; ++x) {
				const auto neighborPos = currentPos + m_direction[x];
				const auto neighborIndex = covertTo1D(neighborPos);

				if (!isValid(neighborPos) || isBlocked(neighborIndex) || m_closedList[neighborIndex] == true) {
					continue;
				}

				cNew = m_cameFrom[covertTo1D(currentPos)].c + 1;
				bNew = m_heuristic(neighborPos, m_targetPos, m_weight);
				aNew = cNew + bNew;

				if (m_cameFrom[neighborIndex].a == 0 || aNew < m_cameFrom[neighborIndex].a) {
					m_openList.push(Node(neighborPos, aNew));
					m_cameFrom[neighborIndex] = { neighborPos, currentPos, aNew, bNew, cNew };


				}
			}
		}
		return buildPath();

	}
	
	//Algorithm builds their path in the game
	std::vector<PathFinderAlgo> AStar::buildPath() const {
		std::vector<PathFinderAlgo> path;
		auto currentPos = m_targetPos;
		auto currentIndex = covertTo1D(currentPos);

		while (!(m_cameFrom[currentIndex].parent == currentPos)) {
			path.push_back(currentPos);
			currentPos = m_cameFrom[currentIndex].parent;
			currentIndex = covertTo1D(currentPos);
		}
		std::reverse(path.begin(), path.end());

		return path;

	}
	
	//Map begins loading 
	void AStar::loadMap(const std::string& fileName) {
		std::ifstream file(fileName);
		if (file.is_open()) {
			std::string line;
			while(std::getline(file, line)){
				if (line.find('w') != std::string::npos) {
					line.erase(std::remove_if(line.begin(), line.end(),
						[](unsigned char c) { return (c == 'w' || c == ':') ? true : false;  }), line.end());
					m_dimensions.i = std::stoi(line);
				}
				else if (line.find('h') != std::string::npos) {
					line.erase(std::remove_if(line.begin(), line.end(),
						[](unsigned char c) {return (c == 'h' || c == ':') ? true : false; }), line.end());
					m_dimensions.j = std::stoi(line);
				}
				else {
					line.erase(std::remove(line.begin(), line.end(), ','), line.end());

					for (const auto& c : line) {
						m_grid.push_back(c - 48);
					}
				}
			}
			m_size = m_dimensions.i * m_dimensions.j;
			file.close();
		}
	}
	//Set diagonal movements if the direction is diagonal
	void AStar::setDiagonalMovement(bool enable) {
		m_nrOfDirections = (enable) ? 8 : 4;
	}
	//If the path is valid
	bool AStar::isValid(const PathFinderAlgo& pos) const
	{
		return (pos.i >= 0) && (pos.i < m_dimensions.i) &&
			(pos.j >= 0) && (pos.j < m_dimensions.j);
	}
	//If the path is blocked
	bool AStar::isBlocked(int index) const {
		return (m_grid[index] == 0);
	}
	
	//Position is declared in 1D array
	int AStar::covertTo1D(const PathFinderAlgo pos) const {
		return (pos.j * m_dimensions.i) + pos.i;
	}
	//Heuristic function using Manhattan algorithm
	unit heuristic::manhattan(const PathFinderAlgo& v1, const PathFinderAlgo& v2, int weight) {
		const auto delta = PathFinderAlgo::getDelta(v1, v2);
		return static_cast<unit>(weight * (delta.i + delta.j));
	}
	
	//Also using Euclidean function
	unit heuristic::euclidean(const PathFinderAlgo& v1, const PathFinderAlgo& v2, int weight) {
		const auto delta = PathFinderAlgo::getDelta(v1, v2);
		return static_cast<unit>(weight * sqrt((delta.i * delta.y) + (delta.i * delta.j)));
	}
}
