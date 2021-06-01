# Usage of `findere`on metagenomic data

We propose an experiment in which `findere` is used to index a metagenomic sample and to query another metagenomic sample.

The two samples are Illumina sequencing of human gut. 

## Data

We chose randomly two metagenomic samples from the Human Microbiome Project, indexing reads1 from sample SRS014107 and querying reads1 from sample SRS016349. 

Theses samples contains respectively 4.2 million reads of average size 92 characters and 2.3 million read of average size 96 characters.

## Download 

[SRS014107](https://www.ncbi.nlm.nih.gov/biosample/?term=SRS014107)

[SRS016349](https://www.ncbi.nlm.nih.gov/biosample/?term=SRS016349)

Note: only reads1 from each sample was used in our experiments.

## Execute `findere` tests

TODO Lucas

### Experiments with respect to the `z`value

TODO Lucas

### Experiments with respect to the space used

TODO Lucas

### Experiments with respect to the `K` value

To execute the experiment, follow the instruction in the directory wrt_k.

## Plot results

In each of the two directories dedicated to the proposed experiments wrt to `z`or the space used, we propose 

- a text file containing the results of our tests 
- a R script that may be used to reproduce the figures proposed in the `findere`manuscript.

In the directory of the experiment wrt `K` value, we propose: 
- a python file that opens the output of findere, then extracts, prints and plots them. 
- a txt tile containing the results of our tests 
- a R script that may be used to reproduce the figures proposed in the `findere`manuscript.
