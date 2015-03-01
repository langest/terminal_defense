Content
============

The game content (towers, viruses and projectiles) are defined from files. 

# Towers #

The tower content file could look like:
```
4
i i 10 10 0.8 0 1 28 0
d D 15 15 0.8 1 1 18 1
y Y 15 15 0.8 1 1 18 2
w # 8 8 0.8 2 0
```
A description of the values
X: is the Xth parameter
```
<number of towers>
<1: tower id/build button> 
<2: graphics for the tower> 
<3: build cost> 
<4: initial sell value> 
<5: sell value decay rate>
<6: type (more on this later)>
<7: attacking type>
<if 7 is non-zero, then 8: recharge rate (time between attacks, lower is more frequent attacks)>
<if 7 is non-zero, then 9: projectile id (what projectile this thingie spawns)>

Newline between towers for some readability, but not a requirement.
```

The "type" specifies what tower behaviour. The currently supported type are:
* 0: Homing projectile shooter (have a target virus, if it dies, the projectile will travel to the location where the virus died and "despawn")
* 1: Direction projectile shooter (don't have a target, but shoots a projectile that travel in one direction)
* 2: Wall (does not shoot, blocks virus path)
