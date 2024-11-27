class Point:
    def __init__(self, x, h):
        self.x = x
        self.h = h 

    def interval(self):
        return (self.x - self.h, self.x + self.h)

    def check(self, x):
        return self.x - self.h <= x <= self.x + self.h


def solve(points):
    points.sort(key=lambda p: p.x)

    marked_count = 0

    # mark first point
    marked_count += 1

    for i in range(1, len(points) - 1):
        can_mark = False

        # Check left
        if not points[i].check(points[i-1].x):
            can_mark = True

        # Check right
        if not points[i].check(points[i+1].x):
            can_mark = True

        if can_mark:
            marked_count += 1

    # mark last point
    marked_count += 1

    return marked_count


n = int(input())

points = []
for _ in range(n):
    x, h = map(int, input().split())
    points.append(Point(x, h))

print(solve(points))
