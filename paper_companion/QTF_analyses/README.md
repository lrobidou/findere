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
|1	|	4821848	|	4331645	|	540743	|	10169	|	106467851	|	0.50533	|	0.23421|
|2	|	253222	|	4307162	|	58782	|	34652	|	106949812	|	0.05493	|	0.7981|
|3	|	20738	|	4282457	|	21273	|	59357	|	106987321	|	0.01988	|	1.3671|
|4	|	8600	|	4251450	|	17880	|	90364	|	106990714	|	0.01671	|	2.08125|
|5	|	9443	|	4205180	|	16935	|	136634	|	106991659	|	0.01583	|	3.14693|
|6	|	6997	|	4164157	|	15976	|	177657	|	106992618	|	0.01493	|	4.09177|
|7	|	6446	|	4119715	|	15296	|	222099	|	106993298	|	0.01429	|	5.11535|
|8	|	7719	|	4058629	|	14630	|	283185	|	106993964	|	0.01367	|	6.52227|
|9	|	6226	|	4003398	|	13827	|	338416	|	106994767	|	0.01292	|	7.79435|
|10	|	5855	|	3945410	|	13265	|	396404	|	106995329	|	0.0124	|	9.12992|

The full results are provided in the `analyse_FP_k31_e5.txt` file

## Results with a bloom filter, with various false positive rate

We propoposed the same analyses with various false positive rate (1, 2, 5, 10, and 20%). Corresponding results are proposed in files `analyse_FP_k31_e1.txt`,  `analyse_FP_k31_e2.txt`, `analyse_FP_k31_e5.txt`, `analyse_FP_k31_e10.txt`, and `analyse_FP_k31_e20.txt`. 

