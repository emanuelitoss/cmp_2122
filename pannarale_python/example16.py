import mymodule

print("++++ executing namespace " + __name__ + " in file: " +  __file__)

# Local a variable
a = 'test string'

# Any object in mymodule can be used and there is no confusion with local a
print("mymodule.a: %f" % mymodule.a)
print("local a: ", a)

# Use line function from mymodule
print(mymodule.line(2.34, q=0.5))

# Function p1 is defined in mymodule but cannot be used because
# behind __name__ == "__main__" in mymodule
print(mymodule.p1(2.34, q=0.5))
