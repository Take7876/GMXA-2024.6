#ifndef DFS_GMXA_HPP
#define DFS_GMXA_HPP

#include "gmxa/graph/dfs.hpp"

std::vector<std::tuple<int, int, int>> depthFirstSearch(std::ostream&, const std::vector<std::vector<std::vector<bool>>>&, \
                                                        std::vector<std::vector<std::vector<bool>>>&, int, int, int);

/** Functions not used within the main function **/
std::vector<std::tuple<int, int, int>> _calculateSearchIndex(int, int, int, int, int, int);
int _applyPeriodicBoundary(int, int);

#endif
