# Impact of the suppression of stretches positive call using a bloom filter.

We propose an experiment in which we index 31-mers from a metagenomic read set (hmp sample SRS014107, reads1) using a bloom filter.

Then, 31-mers from a second metagenomic read set (hmp sample SRS016349, reads2) are queried through the so created bloom filter. 

During the query, when z consecutive 31-mers are positive for the bloom filter, they form what we call a z-stretch. 

In the following experiment, we propose to filter out those z-stretches: any 31-mer the belongs to one z-stretch is considered as non indexed. This leads to a modification of the false positive calls.

## Method

Using a set representation we propose a *ground truth* bit vector that represents for each 31-mer of the query its membership to the indexed set. This bit vector is provided in the `kmertruth_K31_hmp.txt.gz` file.

When querying 31-mers of the query we create a *bf query* bit vector that contains for each queried 31-mers a '1'  if it is positive for the bloom filter, or a '0' else.

Comparing the two bit vectors enables to compute the number of streches and the false positive rate for various z values. We use the provided script `analyse_bf_FPs.py' for doing so.

## Results with a bloom filter, initialy set up with 5% false positive rate

Here we detail results obtained with a bloom filter with 5% false positive rate. The corresponding *bf query* bit vector is provided in the `kmer_query_BF_K31_hmp.txt.gz` file.

Here are values obtained for a few values of z. Complete results are provided in file `analyse_FP_k31_e5.txt`

| z    | #strch  | #TP     | #FP     | #FN    | #TN       | FPR%    | FNR%    |
| ---- | ------- | ------- | ------- | ------ | --------- | ------- | ------- |
| 0    | NA      | 4341814 | 5352422 | 0      | 101656172 | 5.00186 | 0.0     |
| 1    | 4821848 | 9143324 | 540743  | 10169  | 101656172 | 0.52912 | 0.11109 |
| 2    | 253222  | 9600802 | 58782   | 34652  | 101656172 | 0.05779 | 0.35963 |
| 3    | 20738   | 9613606 | 21273   | 59357  | 101656172 | 0.02092 | 0.61364 |
| 4    | 8600    | 9585992 | 17880   | 90364  | 101656172 | 0.01759 | 0.93386 |
| 5    | 9443    | 9540667 | 16935   | 136634 | 101656172 | 0.01666 | 1.4119  |

The full results are provided in the `analyse_FP_k31_e5.txt` file

## Results with a bloom filter, with various false positive rate

We propoposed the same analyses with various false positive rate (1, 2, 5, 10, and 20%). Corresponding results are proposed in files `analyse_FP_k31_e1.txt`,  `analyse_FP_k31_e2.txt`, `analyse_FP_k31_e5.txt`, `analyse_FP_k31_e10.txt`, and `analyse_FP_k31_e20.txt`. 

