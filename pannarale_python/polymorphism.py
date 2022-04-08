class Vector:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def __str__(self):
        return '(' + str(self.x) + ', ' + str(self.y) + ')'
    
    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y)

    def __mul__(self, other):
        if isinstance(other, self.__class__):
            return other.x * self.x + other.y * self.y
        elif isinstance(other, int):
            return Vector(self.x * other, self.y * other)
        elif isinstance(other, float):
            return Vector(self.x * other, self.y * other)
        else:
            raise TypeError("Unsupported operand type(s) for *: '{}' and '{}'").format(self.__class__, type(other))
            
    def __rmul__(self, other):
         return Vector(other * self.x, other * self.y)

def line (m, x, q):
    return m * x + q


v1 = Vector(1, 2)
v2 = Vector(-1, 5)
print("Operator overriding")
print(v1 + v2)
print(v1.__add__(v2))
print(v1 * v2)
print(2.*v1)
print(2*v1)
print(v1*2.)
print(v1*2)
print("Polymorphism")
print(line(3, 2, 1))
print(line(2, v1, v2))
print(line(v1, v2, 1))
print(line(v1, 2, v2))
