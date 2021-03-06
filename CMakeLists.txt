cmake_minimum_required(VERSION 3.12)
project(Milestone_2)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES
        old_main.cpp

        server/server.h
        server/serialServer.h server/serialServer.cpp
        server/clientHandler.h server/clientHandler.cpp
        server/testClientHandler.cpp server/testClientHandler.h
        server/sockets/sockets.h server/sockets/sockets.cpp
        server/parallelServer.h server/parallelServer.cpp
        server/fdbuf.h server/fdbuf.cpp
        server/threads/threads.h server/threads/threads.cpp

        solve_problem/solver.h
#        algorithms/search_algorithms.h
        solve_problem/searchable.h
        solve_problem/state.h
        solve_problem/search_algorithms.h solve_problem/search_algorithms.cpp
#        algorithms/search_algorithms.cpp
        cache/fileCacheManager.h
        cache/cacheManager.h
#        algorithms/state_for_test.h
        solve_problem/algo_imp.h
        solve_problem/searchable_table.h solve_problem/searchable_table.cpp
        solve_problem/a_star.h
        solve_problem/best_first_search.h
        solve_problem/bfs.h
        solve_problem/dfs.h
        solve_problem/search_solver.h
        server/my_client_handler.h server/my_client_handler.cpp
        exceptions.h
        )

find_package(Threads)
add_executable(Milestone_2 ${SOURCES} cache/fileCacheManager.tpp cache/fileUtils.cpp cache/fileUtils.h cache/stringCacheManager.cpp cache/stringCacheManager.h cache/stringStreamer.h main.cpp)
target_link_libraries(Milestone_2 ${CMAKE_THREAD_LIBS_INIT})