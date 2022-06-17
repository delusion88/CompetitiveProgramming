n = int(input())
a, b = map(int, input().split())
if (abs(a - b) == n - 1 or abs(a - b) == 1):
    print((n - 1) // 2)
elif (a == b):
    print(n // 2)
else:
    minhole =  (min(abs(a - b) - 1, (n - 2) - (abs(a - b) - 1)));
    near = minhole * 2 + (n - (2 + minhole * 3) + 1) // 2;
    z = max(((n - 2 * minhole - 2) // 3) * 2 + minhole, n - 2 - (((n - 2 * minhole - 2) // 3) + minhole));
    follow = max(minhole, n - 2 - minhole)
    change = minhole + (minhole + (minhole % 2)) + (n - minhole - 1) / 2; 
    print(min({follow, change, near, z}));