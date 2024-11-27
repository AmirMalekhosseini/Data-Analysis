def longest_common_increasing_subsequence(arr1, arr2):
    m = len(arr2)
    dp = [0] * m
    
    for num1 in arr1:
        current_max_len = 0
        for j in range(m):
            if arr2[j] < num1:
                current_max_len = max(current_max_len, dp[j])
            elif arr2[j] == num1:
                dp[j] = current_max_len + 1
    
    return max(dp)

def main():
    n = int(input().strip())
    arr1 = list(map(int, input().split()))
    m = int(input().strip())
    arr2 = list(map(int, input().split()))
    
    result = longest_common_increasing_subsequence(arr1, arr2)
    print(result)

if __name__ == "__main__":
    main()
