import random


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        return str(self.x) + ', ' + str(self.y)


point_list = []
for i in range(4):
    point_list.append(Point(random.randint(
        1, 100) / random.randint(2, 10), random.randint(1, 100) / random.randint(2, 10)))

temp = 0
for i in point_list:
    print(i, '\t', sep='', end='')
    temp += 1
    if (temp % 2 == 0):
        print('\n', end='')

random.shuffle(point_list)
print("Second Times")
for i in point_list:
    print(i, '\t', sep='', end='')
    temp += 1
    if (temp % 2 == 0):
        print('\n', end='')
