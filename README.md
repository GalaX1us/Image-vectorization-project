# Image vectorization project
PBM to EPS image vectorization project

This program simplifies the contours of a PBM image and converts the result into an EPS file
 
# How to use it
Make sure to **compile** the files before use with the command  : ```make```

Once compiled, all commands will **run** with the **prefix** ```./main```

The **first** command returns the image (PBM) information **before any simplification** :

```./main -i <file.pbm>```

The **second** command returns the image (PBM) information **after simplification** :

```./main -ia <file.pbm> <simplification tolerance> <simplification degree>```

There are three possible types of simplifications :
 - ```1``` which corresponds to the douglas peucker algorithm with **Bézier curves of degree 1 (segments)**
 - ```2``` which corresponds to the douglas peucker algorithm with **Bézier curves of degree 2**
 - ```3``` which corresponds to the douglas peucker algorithm with **Bézier curves of degree 3**

The **third** command **writes** the outlines of the image to a text file:

```./main -fa <file.pbm>```

The **fourth** command **writes** the simplified outlines of the image to a text file:

```./main -f <file.pbm> <simplification tolerance> <simplification degree>```

The **fifth** command **converts** the simplified image to an **.eps** file:

```./main -e <file.pbm> <simplification tolerance> <fill/stroke> <simplification degree>```

There are two different options when converting to an eps file :
 - ```fill``` will fill the space between the different contours
 - ```stroke``` will only display the simplified contours

# Tests
There are different unit tests to verify that our algorithm correctly simplifies the image contours

Command to run **simplification tests** with **Bezier 2** curves : ```./testunitaires_2```

Command to run **simplification tests** with **Bezier 3** curves : ```./testunitaires_3```

Command to run tests about **image manipulation** : ```./test_image```

Command to run test about **geometric calculation** : ```./test_geom```
