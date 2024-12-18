#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

const int MAX_VERTICES = 10001;
const long long INFINITY_VAL = numeric_limits<long long>::max();

vector<pair<int, int>> adjacencyList[MAX_VERTICES];

void processSources(const vector<int>& sources, int totalNodes) {
    for (int i = 0; i < sources.size(); ++i) {
        int source = sources[i];
        vector<long long> shortestDistances(totalNodes + 1, INFINITY_VAL);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> minHeap;

        shortestDistances[source] = 0;
        minHeap.push(make_pair(0, source));

        while (!minHeap.empty()) {
            pair<long long, int> top = minHeap.top();
            long long currentDistance = top.first;
            int currentNode = top.second;
            minHeap.pop();

            if (currentDistance > shortestDistances[currentNode]) {
                continue;
            }

            for (int j = 0; j < adjacencyList[currentNode].size(); ++j) {
                pair<int, int> neighbor = adjacencyList[currentNode][j];
                int adjacentNode = neighbor.first;
                int edgeWeight = neighbor.second;

                if (shortestDistances[currentNode] + edgeWeight < shortestDistances[adjacentNode]) {
                    shortestDistances[adjacentNode] = shortestDistances[currentNode] + edgeWeight;
                    minHeap.push(make_pair(shortestDistances[adjacentNode], adjacentNode));
                }
            }
        }

        long long maxDistance = 0;
        int countAtMaxDistance = 0;

        for (int vertex = 1; vertex <= totalNodes; ++vertex) {
            if (shortestDistances[vertex] != INFINITY_VAL) {
                if (shortestDistances[vertex] > maxDistance) {
                    maxDistance = shortestDistances[vertex];
                    countAtMaxDistance = 1;
                } else if (shortestDistances[vertex] == maxDistance) {
                    countAtMaxDistance++;
                }
            }
        }

        if(maxDistance==0){
            countAtMaxDistance = 1;
        }

        cout << source << " " << maxDistance << " " << countAtMaxDistance << "\n";
    }
}

void readGraph(int edgeCount) {
    for (int i = 0; i < edgeCount; ++i) {
        int nodeA, nodeB, edgeLength;
        cin >> nodeA >> nodeB >> edgeLength;
        adjacencyList[nodeA].push_back(make_pair(nodeB, edgeLength));
        adjacencyList[nodeB].push_back(make_pair(nodeA, edgeLength));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int vertexCount, edgeCount, sourceCount;
    cin >> vertexCount >> edgeCount >> sourceCount;

    readGraph(edgeCount);

    vector<int> sources(sourceCount);
    for (int i = 0; i < sourceCount; ++i) {
        cin >> sources[i];
    }

    processSources(sources, vertexCount);

    return 0;
}
