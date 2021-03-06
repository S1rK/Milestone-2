#ifndef MILESTONE_2_SEARCH_ALGORITHMS_H
#define MILESTONE_2_SEARCH_ALGORITHMS_H

#include "../solve_problem/solver.h"
#include "../solve_problem/searchable.h"
#include <list>

using namespace algorithm;
using namespace std;

template <class T>
class SearchInfo {
    //int cost;
    //int develope;
    list<T> path;

    list<T> createStateList(State<T> endState) {
        list<T> stateList;
        State<T>* current = endState;
        stateList.push_front(current->ge);

        while (current->getParent() != nullptr) {
            current = current->getParent();
            stateList.push_front(current);
        }
        return stateList;
    }


public:
    SearchInfo(State<T> last) {
        //this->cost = cost;
        //this->develope = developedNodes;
        //this->path = path;
        path = createStateList(last);
    }
    //int getCost() { return this->cost; }
    //int getNumOfDevelopeNodes() { return this->develope; }
    list<T> getPath() { return this->path; }
};

template <class T>
using GraphSearch = Solver<Searchable<T>*, SearchInfo<T>*>;

template <class T>
class Searcher : public GraphSearch<T> {
public:
    virtual SearchInfo<T>* solve(Searchable<T>* searcher) {
        return new SearchInfo<T>(make_search(searcher));
    }
    virtual ~Searcher() {}

protected:
    virtual State<T>* make_search(Searchable<T>* searcher) = 0;
};


template <class T>
class DFS : public Searcher<T> {
public:
    virtual ~DFS() {}

protected:
    virtual State<T>* make_search(Searchable<T>* searcher);
};

template <class T>
class BFS : public Searcher<T> {
public:
    virtual ~BFS() {}

protected:
    virtual State<T>* make_search(Searchable<T>* searcher);
};



template <class T>
class HeuristicFunction {
public:
    double operator()(State<T> current, State<T> goal) = 0;
};


template <class T>
class HeuristicSearcher : public Searcher<T> {

private:
    const HeuristicFunction<T>& h;

public:
    explicit HeuristicSearcher(const HeuristicFunction<T>& h) : h(h) {}
    virtual ~HeuristicSearcher() {}

protected:
    virtual State<T>* make_search(Searchable<T>* searcher) = 0;
};

template <class T>
class BestFirstSearch : public Searcher<T> {
public:
    explicit BestFirstSearch(const HeuristicFunction<T>& h) : HeuristicSearcher<T>(h) {}
    virtual ~BestFirstSearch() {}

protected:
    virtual State<T>* make_search(Searchable<T>* searcher);
};

template <class T>
class AStar : public Searcher<T> {
public:
    explicit AStar(const HeuristicFunction<T>& h) : HeuristicSearcher<T>(h) {}
    virtual ~AStar() {}

protected:
    virtual State<T>* make_search(Searchable<T>* searcher);
};

#endif
