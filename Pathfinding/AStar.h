#pragma once

#include <queue>
#include <vector>
#include <functional>
#include "PathFinderAlgo.h"

namespace pf {
	using unit = unsigned int;
	using HeuristicFunction = std::function<unit(const PathFinderAlgo&, const PathFinderAlgo&, int)>;

	struct Node {
		Node() : pos(0,0), parent(-1, 1), a(0), b(0), c(0) {}
		Node(const PathFinderAlgo pos, unit a) : pos(pos), parent(-1, 1), a(a), b(0), c(0) {}
		Node(const PathFinderAlgo pos,const PathFinderAlgo parent, unit a, unit b, unit c) : pos(pos), parent(parent), a(a), b(b), c(c) {}

		PathFinderAlgo pos;
		PathFinderAlgo parent;
		unit a;
		unit b;
		unit c;


	};

	inline bool operator <(const Node& i, const Node& j) { return i.a < j.a; }
	
	class AStar {
	public:
		AStar();

		std::vector<PathFinderAlgo> findPath(const PathFinderAlgo& startPos, const PathFinderAlgo targetPos, HeuristicFunction heuristicFunc, int weight);

		void loadMap(const std::string& fileName);
		void setDiagonalMovement(bool enable);

		bool isValid(const PathFinderAlgo pos) const;

	private:
		std::vector<PathFinderAlgo> buildPath() const;
		bool isValid(const PathFinderAlgo& pos) const;
		bool isBlocked(int index) const;
		int covertTo1D(const PathFinderAlgo pos) const;

		int m_weight;
		int m_size;
		unit m_nrOfDirections;
		PathFinderAlgo m_dimensions;
		PathFinderAlgo m_startPos;
		PathFinderAlgo m_targetPos;
		std::priority_queue<Node> m_openList;
		std::vector<bool> m_closedList;
		std::vector<Node> m_cameFrom;
		std::vector<int> m_grid;
		std::vector<PathFinderAlgo> m_direction;
		HeuristicFunction m_heuristic;

	};

	namespace heuristic {
		unit manhattan(const PathFinderAlgo& v1, const PathFinderAlgo& v2, int weight);
		unit euclidean(const PathFinderAlgo& v1, const PathFinderAlgo& v2, int weight);

	}

}