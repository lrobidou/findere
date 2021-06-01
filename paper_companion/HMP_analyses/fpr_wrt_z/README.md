# False positive rate and construction false positive rate of findere wrt z

We propose an experiment to show the evolution of false positive rate (as well as the false positive rate) of findere with respect to the value of `z`. 


## Reproduce the result

### download and compile findere

```
git clone --recursive https://github.com/lrobidou/findere
cd findere
```

### Compile findere
```
git submodule update --init --recursive
chmod +x build.sh
./build.sh
```

### Execute the experiment
The file data/scenario3.json contains the default parameters used by this experiment. You can override those parameters by passing them throught the command line. 
Thus, either:
- modify the file data/scenario3.json so that the parameters "i" and "q" match with the location of the input and query files on your disk
- or pass them thought command line (-i and -q)

The results were obtained by using:
```
./bin/paper -s data/scenario3.json -b 2674199464 -z 30 -t fastq > courbeU.json
```

### print the result
By default, this will print and plot the result. You can comment out `plt.show()` to stop plotting the results.
```
python3 paper_companion/HMP_analyses/fpr_wrt_z/analyse.py
```

This will print:
```
z  AMQ_FPR  findere_FPR  construction_FPR
0 0.050038  0.050038  0.0
1 0.050038  0.002876  5.7e-05
2 0.050038  0.000571  0.000137
3 0.050038  0.000564  0.000251
4 0.050038  0.000707  0.000389
5 0.050038  0.000822  0.000515
6 0.050038  0.000963  0.000639
7 0.050038  0.001116  0.000795
8 0.050038  0.001296  0.000967
9 0.050038  0.001459  0.001132
10 0.050038  0.001719  0.001385
11 0.050038  0.001923  0.0016
12 0.050038  0.002209  0.001877
13 0.050038  0.002633  0.002301
14 0.050038  0.003086  0.002756
15 0.050038  0.00406  0.003687
16 0.050038  0.007435  0.006967
17 0.050038  0.028798  0.02754
18 0.050038  0.266194  0.262376
19 0.050038  0.892673  0.892207
20 0.050038  0.996508  0.996507
21 0.050038  0.997436  0.997436
22 0.050038  0.99751  0.99751
23 0.050038  0.997807  0.997807
24 0.050038  0.999148  0.999148
25 0.050038  0.999814  0.999814
26 0.050038  0.999996  0.999996
27 0.050038  1.0  1.0
28 0.050038  1.0  1.0
29 0.050038  1.0  1.0
```

The first column is the value of z. 
The second one is the FPR of the AMQ (here, a traditional Bloom filter) (in a scale from 0 to 1: 0.05 is 5%). 
The third one is the FPR of findere.
The last column is the construction false positive rate of findere.

This shows that the FPR of findere is lower than the FPR of Bloom filter, as long as z < 18. With recommended z value, the FPR of findere is two order of magnitude lower than the Bloom filter's one.