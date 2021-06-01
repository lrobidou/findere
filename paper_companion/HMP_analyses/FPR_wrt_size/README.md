# False positive rate of findere and Bloom filters wrt the Bloom filter size

We propose an experiment to show the evolution of the false positive rate of both findere and Bloom filters with respect to the size taken by the filter.


## Reproduce the result

### download and compile findere

```
git clone --recursive https://github.com/lrobidou/findere
cd findere
```
### Modify the parameters
In the file src/mainPaperFixedSize.cpp: 
Modify the values of `input_filenames` and `queryFile` to match with the position of the fastas files on your disk. 

### Compile findere
```
git submodule update --init --recursive
chmod +x build.sh
./build.sh
```

### Execute the experiment
```
./bin/paperFixedSize > fixSize.json
```

### print the result
By default, this will print and plot the result. You can comment out `plt.show()` to stop plotting the results.
```
python3 paper_companion/HMP_analyses/FPR_wrt_size/FP_analysis.py
```

This will print:
```
size FPR_findere (z=3) FPR_BF
6644980503 0.03734084808813575 2.0413191772531785
9864424526 0.033250627049226635 1.3795805236940737
13083868549 0.030977437289684214 1.0405744700243864
16303312573 0.029775269628387738 0.8372451536416362
19522756596 0.029139023581559287 0.7004132900366711
22742200619 0.028213401998869354 0.6028771036734281
25961644643 0.028039491578302354 0.5265033446347547
29181088666 0.027579531777458487 0.4688724723153855
32400532689 0.027420351474480496 0.42184633432993507
35619976713 0.027227434450572838 0.3841519634196631
```

The first column is the size of the filter (in bit). 
The second one is the false positive rate of findere (in %). Here, z = 3. 
The third column is the false positive rate of the Bloom filter.

This shows that with the same size, the FPR of findere is lower than the Bloom filter's FPR.


The results with kbf can be obtained by following the instructions here : https://github.com/lrobidou/kbf/blob/master/cookbook/README.md. Results are in folder tests_with_kbf.