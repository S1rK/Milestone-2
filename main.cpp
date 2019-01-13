#include <iostream>
#include <fstream>
#include "solve_problem/dfs.h"
#include "solve_problem/bfs.h"
#include "solve_problem/best_first_search.h"
#include "solve_problem/a_star.h"
#include "test.h"
#include <vector>
#include "server/parallelServer.h"
#include "server/testClientHandler.h"
#include <unistd.h>

vector<int> split(const char splitBy, const string str);

namespace boot {
    int main() {
        using namespace server_side;

        Server* s = new ParallelServer;
        ClientHandler* ch = new MyTestClientHandler;

        s->open(25565, ch);

        sleep(1);
        if (s->isOpen()) {
            s->wait();
        }

        s->close();

        return 0;
    }

    int main2() {

        vector<vector<int>> table = {
                {8, 0, 8, 6, 8, 2,10, 2, 4, 1, 9, 9, 5,10, 1, 1, 1, 0, 7, 3, 1, 6, 9, 3, 9, 7, 7, 9, 5, 6, 4, 5, 1, 6,-1, 1, 7},
                {4,10, 2, 3, 0, 5, 2, 1,10, 2, 4, 5, 4, 3, 3, 4,10, 2, 3, 9, 6, 9, 1, 6, 7, 7, 5, 8, 7, 2,-1, 3, 2, 5,-1, 9, 2},
                {1, 5, 8, 9, 0, 1, 2, 4, 7, 8, 2, 9, 8, 4, 2, 2,10, 8, 8, 2, 3, 3, 1, 5,10,-1, 2, 7, 1, 4,-1,-1,-1, 0,-1, 5, 6},
                {8, 6, 2, 4,10, 8, 9, 9, 7, 1, 0, 8, 8, 2, 4, 2, 1, 7, 6, 8, 3,-1, 8, 1, 8, 6, 1, 3, 3, 0, 7, 3, 4, 0, 9,10, 0},
                {7, 6, 2,10, 7, 8, 1,-1, 5, 8, 8, 1, 1, 5, 8, 9, 9, 1, 8, 5, 1, 8, 4, 5, 4, 5, 8, 7, 6, 6, 8, 2, 0, 8, 8, 8, 8},
                {9, 3, 0, 3, 5,10,-1, 9, 0, 8, 3, 8, 2,10,10, 7, 1, 8, 4, 2,10, 5, 4, 7, 4, 4, 6,10, 9, 0, 3, 5,10, 0, 0, 3, 5},
                {10, 5, 1, 7, 5,10, 6, 6, 6, 5, 8, 9, 4, 3, 9, 0,10, 4, 9, 5, 3,10, 3, 9, 3, 4,-1, 8, 5, 0,10, 5, 2, 3, 7, 6,-1},
                {1,10, 0, 9, 9, 1, 0, 2,-1, 0, 6,10, 1,10,10, 0, 7, 5, 2, 7, 7, 6, 9, 0, 3, 2, 4, 9,-1, 5, 7,-1, 9, 8, 6, 3, 4},
                {10, 0, 1, 0, 6,10, 2, 6,-1,-1, 3, 9, 9, 8, 3, 7, 4, 3, 4, 5,-1, 9, 3, 5,10, 2, 3,-1,10, 2, 0, 0, 7, 8,-1,10, 2},
                {7, 4, 8, 0, 8, 7,-1, 3,-1, 0,-1, 7, 9, 6, 7, 6, 1,10, 6, 0, 5, 8, 1, 2, 8, 3, 0,10, 7,10, 1, 2, 6, 9, 7, 3, 8},
                {6, 0, 4, 7, 7,10, 8, 0, 1, 6, 2, 6, 4, 6, 6, 7, 5, 5, 8, 2,10, 2, 6, 8,10, 8,10, 9, 9, 0, 2, 0, 9, 6, 5, 4, 2},
                {7, 0, 9, 4, 7, 4, 5, 8, 2, 2, 4, 3, 6, 1, 4, 7, 4, 9,-1, 5,10, 3, 4, 9, 7,10, 3, 5, 2, 9, 7, 0,-1, 5,10, 7, 1},
                {6, 6, 8, 2,10, 4,-1, 4,-1, 2, 9, 6, 5, 7, 0, 4, 9,10, 4, 9, 0, 9, 2, 6, 7, 1,10, 5, 6, 6, 5,10, 4, 5, 7, 6, 8},
                {3, 9, 1, 4, 8, 2,-1, 2,-1, 7, 8, 3, 6, 6, 9, 4, 6,-1, 4,-1, 1, 4, 5, 9, 2, 0, 1, 9, 3, 7, 0, 1,10, 5, 6,-1, 9},
                {10, 8, 9, 1,10, 7, 0,10, 9,10,10, 1, 9, 3, 7, 5, 9, 3, 8, 6, 6, 7, 1, 1, 5, 6, 2, 7, 2, 3, 4, 9, 9, 9,10, 2, 8},
                {10, 2, 8, 5,-1, 2, 5, 8, 7, 0, 5, 1, 3, 0, 4, 3, 9, 5, 9, 7, 7, 2,-1, 2, 8, 4, 1, 5, 9, 6, 0, 4, 0, 9, 1,-1, 0},
                {4, 4, 5,10, 2, 5, 2, 3, 2, 2, 0, 4, 5, 3,10, 9, 3, 6, 2, 9, 9, 1, 4, 3, 2,10, 3, 1, 8, 6, 7, 4, 6, 7, 5, 1, 8},
                {4,-1, 9, 7, 5, 5, 3,10, 8, 3, 3, 9, 5, 6, 1,10, 7, 4, 9, 9, 5, 9, 8, 9, 9, 1, 6, 9, 7, 5, 3, 5, 4, 6, 3, 0, 1},
                {9, 0, 1, 5, 1, 3, 8, 0, 1, 2, 5, 0, 9, 9, 3, 4, 0, 2, 0,10, 7, 0,10, 3, 7, 0, 8, 9, 0, 1, 0, 2, 0, 3, 4,10, 3},
                {6, 6, 1,-1,10, 7, 1, 5, 2, 3, 5, 8,10, 7, 3, 0, 6, 8, 5, 1,10, 0, 6, 6, 8, 0, 7,-1, 0, 7, 9, 5, 5, 7, 1, 5, 4},
                {3, 6, 4,10, 7, 8, 2, 9, 8, 3, 4, 3, 8, 7, 6, 6, 2, 7, 9, 6, 6, 0, 0, 6, 5, 9, 2, 3, 3, 3,10, 7,10, 6, 7, 2, 9},
                {10, 1, 2,-1, 7, 0, 5,10, 2, 8, 4, 7, 8, 7, 7, 5, 2, 5, 7, 4, 2, 4, 3,10, 6, 8, 5, 2, 1, 4, 9, 0, 1, 4, 0, 2, 2},
                {10, 4, 9,10, 9,10, 9,10, 7, 9, 0, 1, 6, 5, 3, 0, 6, 4, 7, 9,10, 4, 4, 9, 8, 1, 7, 8, 0, 0, 9, 3, 8, 5, 3, 7, 6},
                {7, 4, 6, 0, 7, 7, 8, 6, 8, 9, 1, 2, 9, 3, 4, 9, 0, 8,10, 1, 0, 5, 9, 8, 7, 9, 3, 3,10, 7, 9, 8, 3, 2,10, 3, 6},
                {9, 2, 1, 8, 4, 8, 1, 8, 6, 0, 3, 9, 1, 7, 3, 8, 5, 8, 5, 4, 4,10, 5, 0, 9, 2, 1, 9, 0, 6, 8, 4, 4,-1,-1,-1,10},
                {7, 7, 0, 8, 4, 4, 1, 9, 8, 0, 9, 8,10, 5, 5, 2, 8, 1, 5, 9, 9,10, 6, 5, 9, 8, 1, 4, 4, 7, 6,10, 4, 9, 1, 8, 2},
                {1, 6, 7, 2, 8, 7, 6,10, 1, 0, 9, 5,10, 7, 6, 4, 9, 2, 2, 5, 1, 9, 2, 1, 6, 8, 3, 0, 8, 1, 0, 6, 9, 8, 3,-1, 0},
                {5, 5, 7,10, 1, 8, 4, 4, 0,10,10, 1, 1, 2, 8, 4, 8, 0, 6, 8, 3, 8, 5, 5, 3, 8,10, 8, 5,10, 1,10, 2, 5, 0,-1, 6},
                {9, 0, 8, 1, 3, 5, 6, 0, 7, 9, 2, 1, 6, 8, 1, 2, 1, 5, 0, 0,10, 0, 4, 9, 0, 0, 4, 7, 4, 3, 6, 9, 6, 5,10, 0, 3},
                {1, 7, 2, 0, 5, 6,10, 6, 6,10,10, 2, 1, 0, 2, 7, 1, 1, 8, 3, 5, 0,10, 1, 8, 2, 6, 3, 0, 9, 3, 2, 4, 9, 8, 5, 3},
                {1, 3, 2, 1, 1, 6, 3,-1, 0, 4, 8, 7, 3, 4, 7, 6, 1, 9, 7, 0,10, 4, 6, 5, 7, 8, 2,10, 1, 2, 6, 7, 8, 2, 3,10, 9},
                {3, 6, 4, 9, 2,10, 9, 8, 2, 7, 6, 6, 8, 3, 7, 9, 3, 7, 0, 0, 3, 2, 4, 5, 8, 7, 2,10,10, 4,10, 2,10,-1, 6,-1, 0},
                {6, 4, 4,10, 8, 3, 0, 7, 3, 8, 4, 7, 3, 1, 5, 6, 0, 2, 2, 6, 2, 1, 4, 3, 1, 4, 0, 5, 7, 1, 6, 5,10, 7, 5,-1, 3},
                {4, 8, 0, 2,10, 9, 3, 3, 8, 7, 7, 8,10, 6,10, 2, 4,10, 0,10, 7, 8, 7, 1, 9, 5,10, 4, 2, 0, 9, 7, 1, 8, 3, 8, 9},
                {2, 2, 5, 1, 7, 1, 8, 2,10, 3,10, 5, 7, 9,10,10,10, 0, 4, 4, 2,10, 2, 0, 1, 6, 9,10, 7, 4, 6,10, 8, 4, 8, 0,10},
                {3, 1, 0, 8, 1, 4, 7, 9, 3, 7, 3, 6, 6, 6, 3, 9, 9, 3, 9, 3, 3, 7, 5,10, 0, 8, 2, 2, 5, 4, 9, 8, 5, 3, 2, 6, 4},
                {10, 1, 9, 5, 9, 2, 6,10, 3, 4,10,-1,10, 7, 9, 2, 1, 2, 0, 4, 6,10, 2, 0, 0, 3, 4, 1, 4, 4, 0, 4,10, 6, 2, 5, 6}};

/*        vector<vector<int>> table = {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
*/

        TableGraph* t = new TableGraph(table);

        ManhattanDistance mh = ManhattanDistance(State<pInt>({36, 36}));
        AStar<pInt>* alg1 = new AStar<pInt>(mh);
        BestFirstSearch<pInt>* alg2 = new BestFirstSearch<pInt>(mh);
        BFS<pInt>* alg3 = new BFS<pInt>();
        DFS<pInt>* alg4 = new DFS<pInt>();
        SearchInfo<pInt>* s = alg1->solve(t);

        list<pInt> l = s->getPath();
        for (pInt p : l) {
            cout << p.first << ", " << p.second <<endl;
        }
        cout << "with the cost of: " << s->getCost() << endl;
        cout << "with number of develops: " << s->getNumOfDevelopeNodes() << endl;

        delete alg1;

        return 0;
    }


    int main3() {
        ifstream reader("graphs.txt");
        ofstream writer("solution.txt");

        string line;
        getline(reader, line);
        int numberOfGraphs = stoi(line);

        for (int i = 0; i < numberOfGraphs; ++i) {
            vector<vector<int>> table;
            getline(reader, line);  // size point
            int size = stoi(line);
            getline(reader, line);  // start point
            getline(reader, line);  // end point

            for (int j = 0; j < size; ++j) {
                getline(reader, line);
                table.push_back(split(',', line));
            }
            TableGraph* t = new TableGraph(table);
            ManhattanDistance mh = ManhattanDistance(State<pInt>({size - 1, size - 1}));

            BestFirstSearch<pInt>* alg1 = new BestFirstSearch<pInt>(mh);
            DFS<pInt>* alg2 = new DFS<pInt>();
            BFS<pInt>* alg3 = new BFS<pInt>();
            AStar<pInt>* alg4 = new AStar<pInt>(mh);

            vector<Searcher<pInt>*> sa = {alg1, alg2, alg3, alg4};

            for (int k = 0; k < sa.size(); ++k) {
                SearchInfo<pInt>* s = sa[k]->solve(t);
                writer << s->getCost() << "," << s->getNumOfDevelopeNodes() << endl;
                delete s;
            }
            delete alg1;
            delete alg2;
            delete alg3;
            delete alg4;
        }


        return 0;
    }
}

int main() {
    return boot::main3();
}


vector<int> split(const char splitBy, const string str) {
    vector<int> split_line;
    string string1 = "";
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != splitBy) {
            string1 += str[i];

        } else {
            split_line.push_back(stoi(string1));
            string1 = "";
        }
    }

    split_line.push_back(stoi(string1));

    return split_line;
}