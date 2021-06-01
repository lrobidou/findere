# Stability of findere wrt K

We propose an experiment to show the stability of the false positive rate and the query time of findere with respect to the value of `K` .

## Reproduce the result

### download and compile findere

```
git clone --recursive https://github.com/lrobidou/findere
cd findere
```
### Modify the parameters
In the file src/mainPaperKVariation.cpp: 
Modify the values of `input_filenames` and `queryFile` to match with the position of the fastas files on your disk. 

### Compile findere
```
git submodule update --init --recursive
chmod +x build.sh
./build.sh
```

### Execute the experiment
```
./bin/paperKVariation > kvar.json
```

### print the result
By default, this will print and plot the result. You can comment out `plt.show()` to stop plotting the results.
```
python3 paper_companion/HMP_K_variation/analyse.py
```

This will print:
```
K fpr_findere time_findere_query fpr_bf time_bf
21 0.21 8.99 5.0 20.183
23 0.13 8.716 5.0 20.174
25 0.1 8.627 5.0 20.486
27 0.09 8.682 5.0 20.613
29 0.08 8.588 5.0 20.603
31 0.06 8.536 5.0 20.906
33 0.06 8.54 5.0 21.186
35 0.05 8.65 5.0 21.073
```

The first column is the value of K (not k !). 
The second one is the FPR of findere (in %). Here, z = 3. 
The third one is the time taken by findere (z = 3) to perform the query.
The fourth one is the FPR of a BF (in %). Since we chose the size of both findere and BF such that a BF having this size would end up having a FPR of 5%, the BF have a FPR of 5%. 
The last column is the time taken by a BF to perform the same query.

This shows that the FPR and the query time of findere are as stable as the FPR and the query time of BF wrt K. 

Beware that the value of the memory might change for each line, as the number of n-mer might not be the same as the numner of (n+1)-mer.

To date, the last version of libbf has a bug (https://github.com/mavam/libbf/blob/5478275d8a4e9a5cc163b44c34517c515bd898ec/src/hash.cpp#L13) that is not fixed. For a high value of K, the hash function of Bloom filters crash. Thus, we experienced problems with a value of K > 35. That is why the experiment stops at K = 35.