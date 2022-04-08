# A first Python program: no preamble, no main, no types
a = 2.3
b = 4.5
c = a/b

# Plain print
print(a,b,c)

# Plain print of more variables
print('c = a/b = ', c)

# printf style works, but Python has the powerful
# String format() method!
print('a = %.3f, b = %.3g, c = %2.4g' % (a,b,c))

# Print using ""
print("a = {0}, b = {1}, c = {2}".format(a, b, c))

# Print using ''
print('a = {0}, b = {1}, c = {2}'.format(a, b, c))

# Python style formatted output: {position:format}
# format syntax: minimum width . significant digits (for g), digits after the point (for f)
print('a = {1:.3f}, b = {2:.3g}, c = {0:2.4g}'.format(a, b, c))

# Woah... internal variable names on the fly without separate declarations 
print('value = {v:.3f}, error = {err:.3g}, # measurements = {N:3d}'.format(N=1000, v=-1.23454335, err=0.1))
