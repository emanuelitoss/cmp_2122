class Sheep:
    members = []
    name = "Just another sheep"

    def __init__(self, name=name):
        """I construct Sheep instances"""
        self.name = name
        self.owners = []
        print('{0} speaking: I am constructed :-)'.format(self.name))

    def flock(self):
        self.members.append(self.name)
        print('{0} flock count: {1}'.format(self.name, len(self.members)))

    def __del__(self):
        print('{0} speaking: I am destructed :-('.format(self.name))

    def __str__(self):
        info = '(members = {0}, name = {1})'.format(str(self.members), str(self.name))
        return info 

    def add_owner(self, shepard):
        self.owners.append(shepard)
        print('{0} owners count: {1}'.format(self.name, len(self.owners)))

class Lamb(Sheep):
    siblings = 0

    def __str__(self):
        info = '(members = {0}, name = {1}, siblings = {2})'.format(str(self.members), str(self.name), str(self.siblings))
        return info 

    def set_siblings(self, s):
        self.siblings = s
        print('{0} speaking: I have {1} siblings'.format(self.name, self.siblings))
        for i in range(s):
            self.flock()
        

montauciel = Sheep("Montauciel")
montauciel.flock()
montauciel.add_owner("The big bad wolf")
dolly = Lamb("Dolly")
dolly.flock()
dolly.add_owner("Mary")
dolly.set_siblings(3)
print(dolly.owners)
print(montauciel.owners)
