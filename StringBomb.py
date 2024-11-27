t = int(input())

def output_final_len(s):
    stack = []
    for char in s:
        
        # Check for "AB" or "BB" patterns to delete
        if stack and ((stack[-1] == 'B' and char == 'B') or (stack[-1] == 'A' and char == 'B')):
            stack.pop()
        else:
            stack.append(char)
    return len(stack)

answer=[]
for _ in range(t):
    s = input().strip()
    answer.append(output_final_len(s))
    
for _ in range(len(answer)):
    print(answer[_])