#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <functional>
#include <cassert>

struct IGraph {
    virtual ~IGraph() {}
        
        // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

struct ListGraph: public IGraph
{
public:
    ListGraph(int size)
    : adjacencyLists(size)
    {
    }
    
    ListGraph(const IGraph &graph)
    : adjacencyLists(graph.VerticesCount())
    {
        for (int i = 0; i < graph.VerticesCount(); i++)
        {
            adjacencyLists[i] = graph.GetNextVertices(i);
        }
    }
    
    ~ListGraph()
    {
    }
    
    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].push_back(to);
    }

    int VerticesCount() const override
    {
        return static_cast<int>(adjacencyLists.size());
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }
    
    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<int> prevVertices;
        
        for (int from = 0; from < adjacencyLists.size(); from++)
        {
            for (int to: adjacencyLists[from])
            {
                if (to == vertex)
                {
                    prevVertices.push_back(from);
                }
            }
        }
        return prevVertices;
    }
    
private:
    std::vector<std::vector<int>> adjacencyLists;
};

void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, std::function<void(int)> &func)
{
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;
    
    while (!qu.empty())
    {
        int currentVertex = qu.front();
        qu.pop();
        
        func(currentVertex);
        
        for (int nextVertex: graph.GetNextVertices(currentVertex))
        {
            if (!visited[nextVertex])
            {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void BFS(const IGraph &graph, std::function<void(int)> func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        if (!visited[i])
            BFS(graph, i, visited, func);
    }
}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, std::function<void(int)> &func)
{
    visited[vertex] = true;
    func(vertex);
    
    for (int nextVertex: graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
            DFS(graph, nextVertex, visited, func);
    }
}

void DFS(const IGraph &graph, std::function<void(int)> func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        if (!visited[i])
            DFS(graph, i, visited, func);
    }
}

void topologicalSort(const IGraph &graph, int vertex, std::vector<bool> &visited, std::deque<int> &sorted)
{
    visited[vertex] = true;
    
    for (int nextVertex: graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
            topologicalSort(graph, nextVertex, visited, sorted);
    }
    
    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph &graph)
{
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        if (!visited[i])
            topologicalSort(graph, i, visited, sorted);
    }
    
    return sorted;
}

int main(int argc, const char * argv[]) {
    ListGraph listGraph(9);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 5);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(1, 5);
    listGraph.AddEdge(1, 6);
    listGraph.AddEdge(3, 2);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(3, 6);
    listGraph.AddEdge(5, 4);
    listGraph.AddEdge(5, 6);
    listGraph.AddEdge(6, 4);
    listGraph.AddEdge(7, 8);
    
    BFS(listGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    DFS(listGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    for (int vertex: topologicalSort(listGraph))
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    // Нужно продемонстрировать работу конструктора копирования, проинициализировав
    // графы разных классов друг от друга. Далее, показать, что вершины и ребра
    // успешно скопированы: число вершин осталось прежним, произвести BFS и DFS.
    // ArcGraph arcGraph(listGraph);
    // MatrixGraph matrixGraph(arcGraph);
    // SetGraph setGraph(matrixGraph);
    
    return 0;
}
