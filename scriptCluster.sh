#!/bin/bash

#SBATCH --job-name=LeNomDeMonSuperJob
#SBATCH --cpus-per-task=1
#SBATCH --mem-per-cpu=150G

./build/thirdparty/libbf/bin/main -i "/groups/genscale/NGSdatasets/TARA/tara_set3/QQSS/11SUR1QQSS11/AHX_ACXIOSF_6_1_C2FGHACXX.IND4_clean.fastq.gz" -k 32 -z 10 --epsilonpercent 2 -q "data/Salmonella enterica.fasta"
