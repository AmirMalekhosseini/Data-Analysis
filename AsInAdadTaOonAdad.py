from collections import deque


def is_valid_move(move, visited, upper_limit):
    
    return move not in visited and move >= 0 and move < upper_limit


def bfs_minimum_steps(start, target):
    
    if start >= target:
        return start - target 

    queue = deque([(start, 0)]) 
    visited = set([start])  
    upper_bound = 2 * target  

    while queue:
        current_value, step_count = queue.popleft()

        # Option 1: Multiply by 2
        multiplied = current_value * 2
        if multiplied == target:
            return step_count + 1
        if is_valid_move(multiplied, visited, upper_bound):
            visited.add(multiplied)
            queue.append((multiplied, step_count + 1))

        # Option 2: Subtract 1
        decremented = current_value - 1
        if decremented == target:
            return step_count + 1
        if is_valid_move(decremented, visited, upper_bound):
            visited.add(decremented)
            queue.append((decremented, step_count + 1))


def main():
    """Main function to execute the program."""
    start_number, target_number = map(
        int, input().split())
    minimum_moves = bfs_minimum_steps(start_number, target_number)
    print(minimum_moves)


# Execute the program
if __name__ == "__main__":
    main()
