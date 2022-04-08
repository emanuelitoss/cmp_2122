class Sheep:
    name = "Just another sheep"

    def __init__(self, name=name):
        """I construct Sheep instances"""
        self.name = name
        self.owners = []
        self.flock()
        print('{0} speaking: I am constructed :-)'.format(self.name))

    def flock(self):
        global flock
        flock += 1
        print('{0} flock count: {1}'.format(self.name, flock))

    def __del__(self):
        print('{0} speaking: I am destructed :-('.format(self.name))

    def __str__(self):
        info = '(name = {0})'.format(str(self.name))
        return info 

    def add_owner(self, shepard):
        self.owners.append(shepard)
        print('{0} owners count: {1}'.format(self.name, len(self.owners)))

    @staticmethod
    def try_to_talk():
        print("Baaaahhh!")

class Lamb(Sheep):
    siblings = 0

    def __str__(self):
        info = '(name = {0}, siblings = {1})'.format(str(self.name), str(self.siblings))
        return info 

    def set_siblings(self, s):
        self.siblings = s
        print('{0} speaking: I have {1} siblings'.format(self.name, self.siblings))
        for i in range(s):
            self.flock()
        
flock = 0
montauciel = Sheep("Montauciel")
montauciel.add_owner("The big bad wolf")
dolly = Lamb("Dolly")
dolly.add_owner("Mary")
dolly.set_siblings(3)
print(dolly.owners)
print(montauciel.owners)
print(flock)
flock += 1
print(flock)

# Class Sheep can talk
Sheep.try_to_talk()

# As can Sheep instances
dolly = Sheep()
dolly.try_to_talk()
