# Image vectorization project
PBM to EPS image vectorization project done alone during the [MAP401] teaching unit at the Université Grenoble Alpes
 
# How to use it ?
Make sure to **compile** the files before use with the command  : ```make```

Once compiled, all commands will **run** with the **prefix** ```./main```

The **first** command returns the image (PBM) information **before any simplification** :
```./main -i <file.pbm>```

The **second** command returns the image (PBM) information **after simplification** :

```./main -ia <file.pbm> <threshold distance> <simplification degree>```

There are three possible types of simplifications :
 - **1** which corresponds to the douglas peucker algorithm with **Bézier curves of degree 1 (segments)**
 - **2** which corresponds to the douglas peucker algorithm with **Bézier curves of degree 2**
 - **3** which corresponds to the douglas peucker algorithm with **Bézier curves of degree 3**


