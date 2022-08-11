#pragma once


namespace pf {
	class PathfinderAlgo {

	public:
		inline PathFinderAlgo(int i, int j) : i(i), j(j) {}
		inline PathFinderAlgo() = default;

		inline bool operator == (const PathfinderAlgo p) const {return (i == p.i) && (j == p.j); }
		inline const PathFinderAlgo operator + (const PathFinderAlgo& p) { return PathFinderAlgo(i + p.i, j + p.j); }

		static PathfinderAlgo getDelta(const PathFinderAlgo& v1, const PathFinderAlgo& v2) { return PathfinderAlgo(abs(v1.i - v2.i), abs(v1.j - v2.j)); }

		int i;
		int j;
	};
}