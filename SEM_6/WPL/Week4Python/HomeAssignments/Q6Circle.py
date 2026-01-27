"""
6. Write a Python class named Circle constructed by a radius and two methods
which will compute the area and the perimeter of a circle.
"""

PI = 3.14159

class Circle:
    def __init__(self, r):
        self.r = r
        self.A = 0
        self.P = 0

    def calcArea(self):
        self.A = PI * self.r * self.r       

    def calcPerimeter(self):
        self.P = 2 * PI * self.r
    
obj = Circle(7)
obj.calcArea()
obj.calcPerimeter()
print(f"Circle of radius {obj.r} has Area {obj.A} and Perimeter {obj.P} ")