import example11

print('===== Running 12example.py ===== ')

x = float(input("Insert x:"))
y = example11.line(x)
print(y)

# A much shorter way
print(example11.line(float(input("Insert x:"))))
