# ONLY for Jupyter notebook
#%matplotlib notebook
#%matplotlib inline

# Import modules 
import matplotlib.pyplot as plt
import math

# Data, settings and initial conditions
g = 9.8
t = 0.
h = 0.
theta = math.radians(45.)
v0 = 1.
dt = 0.01
        
# Compute velocity components
v0x = v0*math.cos(theta)
v0y = v0*math.sin(theta)
print("v0_x: %.3f m/s \t v0_y: %.3f m/s"%(v0x,v0y))

# Results containers
x = []
y = []

# Evolve
xi = 0.
yi = h
while yi>=0:
    x.append(xi)
    y.append(yi)
    t += dt
    xi = v0x*t
    yi = h + v0y*t - 0.5*g*t*t

# Plot results
plt.plot(x, y, label="trajectory", color='red', marker='.')
plt.legend()

# Only for script
plt.show()
# or
#plt.savefig("./gravity1.png")
