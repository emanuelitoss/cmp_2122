class Sheep:
    x = 0

    def __init__(self):
        """I construct Sheep instances"""
        print('I am constructed')

    def flock(self):
        self.x = self.x + 1
        print("So far", self.x)

    def __del__(self):
        print('I am destructed', self.x)

dolly = Sheep()

dolly.flock()
dolly.flock()
dolly.flock()

print(type(dolly))
print(dir(dolly))
print(type(Sheep))
print(dir(Sheep))

dolly = 13

print('dolly contains', dolly)
