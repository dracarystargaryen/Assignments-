#pragma once

namespace pf {
	class PathFinderAlgo {
	public:
		inline PathFinderAlgo(int i, int j) : i(i), j(j) {}
		inline PathFinderAlgo() = default;

		inline bool operator == (const PathFinderAlgo& v) const { return (i == v.i) && (j == v.j); }
		inline const PathFinderAlgo operator+ (const PathFinderAlgo& v) const { return PathFinderAlgo(i + v.i, j + v.j); }

		static PathFinderAlgo getDelta(const PathFinderAlgo v1, const PathFinderAlgo v2) { return PathFinderAlgo(abs(v1.i - v2.j), abs(v1.j - v2.j)); }

		int i;
		int j;
     };
}