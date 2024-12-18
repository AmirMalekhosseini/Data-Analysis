import sys
from collections import defaultdict


def main():
    
    max_result = float('-inf')
    current_max = 0
    
    number_of_nodes = int(input().strip())
    list_of_edges = []
    
    for i in range(number_of_nodes - 1):
        u, v = map(int, input().split())
        list_of_edges.append((u, v))

    graph_dic = defaultdict(list)
    for u, v in list_of_edges:
        graph_dic[u].append(v)
        graph_dic[v].append(u)

    def dfs(current, parent):
        
        nonlocal current_max
        
        max_combined = 0
        max_path_1 = 0
        max_path_2 = 0

        for neighbor in graph_dic[current]:
            if neighbor == parent:
                continue
            combined_path = dfs(neighbor, current)

            if current_max > max_path_1:
                max_path_2 = max_path_1
                max_path_1 = current_max
            else:
                if(max_path_2 < current_max):
                    max_path_2 = current_max
                
            if(max_combined < combined_path):
                
                max_combined = combined_path

        max_combined = max(max_combined, max_path_1 + max_path_2)
        
        max_path_1 += 1
        current_max = max_path_1
        return max_combined

    number_of_edges = len(list_of_edges)
    for vertex in range(1, number_of_edges + 2):
        
        for neighbor in graph_dic[vertex]:
            
            current_max = 0
            first_path = dfs(neighbor, vertex)
            current_max = 0
            second_path = dfs(vertex, neighbor)
            
            max_so_far = first_path * second_path
            if(max_result < max_so_far):
                max_result = max_so_far

    sys.stdout.write(str(max_result))
    sys.stdout.flush()


if __name__ == "__main__":
    main()
