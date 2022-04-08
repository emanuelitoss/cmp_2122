class Sheep:
    x = 0
    name = "Just another sheep"

    def __init__(self, name=name):
        """I construct Sheep instances"""
        self.name = name
        print(self.name, 'speaking: I am constructed :-)')

    def flock(self):
        self.x = self.x + 1
        print(self.name, "flock count:", self.x)

    def __del__(self):
        print(self.name, 'speaking: I am destructed :-(')

    def __str__(self):
        info = '(x = {0}, name = {1})'.format(str(self.x), str(self.name))
        return info 

class Lamb(Sheep):
    siblings = 0

    def __str__(self):
        info = '(x = {0}, name = {1}, siblings = {2})'.format(str(self.x), str(self.name), str(self.siblings))
        return info 

    def set_siblings(self, s):
        self.flock()
        self.siblings = s
        print(self.name, 'speaking: I have', self.siblings, 'siblings')
        
montauciel = Sheep("Montauciel")
montauciel.flock()
dolly = Lamb("Dolly")
dolly.set_siblings(3)
dolly.flock()
print(dolly)
print(montauciel)
