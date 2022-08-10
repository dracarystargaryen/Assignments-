#pragma once

namespace pf {
	class PathFinderAlgo {
	public:
		inline PathFinderAlgo(int i, int j) : i(i), j(j) {}
		inline PathFinderAlgo() = default; //Pathfinding algorithm declared

		inline bool operator == (const PathFinderAlgo& v) const { return (i == v.i) && (j == v.j); } //operator passing through each function
		inline const PathFinderAlgo operator+ (const PathFinderAlgo& v) const { return PathFinderAlgo(i + v.i, j + v.j); }
                
		//Delta calls for the start time of when the algorithm begins 
		static PathFinderAlgo getDelta(const PathFinderAlgo v1, const PathFinderAlgo v2) { return PathFinderAlgo(abs(v1.i - v2.j), abs(v1.j - v2.j)); }

		int i;
		int j;
     };
}
