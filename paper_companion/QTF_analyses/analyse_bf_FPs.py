import sys


def get_size_stretch(line_BF, i):
    assert line_BF[i] == "1"
    size = 0
    while i+size< len(line_BF) and line_BF[i+size] == "1":
        size += 1
    return size

def get_nb_fp_nb_internal_fp_nb_fn(line_BF, line_truth, i):
    size_stretch = get_size_stretch(line_BF, i)
    nb_fp = 0 
    truthstretch = line_truth[i:i+size_stretch]
    bfstretch = line_BF[i:i+size_stretch]

    nb_fn = truthstretch.count("1") # if we remove this stretch we would create that number of FN
    for pos_in_stretch in range(size_stretch):
        local_pos = pos_in_stretch + i
        assert line_BF[local_pos] == "1"
        if line_truth[local_pos] == "0":
            nb_fp += 1

    return size_stretch, nb_fp, 0, nb_fn
    ## USELESS FOR SIMPLE RESULTS (not checking the positions of the FP) - This explains the previous 'return' line
    pos_first_internal_tp = i
    for pos_in_stretch in range(size_stretch):
        local_pos = pos_in_stretch + i
        if line_truth[local_pos] == "1":
            break
        pos_first_internal_tp = local_pos
        
    pos_last_internal_tp = i + size_stretch - 1
    for pos_in_stretch in range(size_stretch):
        local_pos =  i + size_stretch - 1 - pos_in_stretch
        if line_truth[local_pos] == "1":
            break
        pos_last_internal_tp = local_pos
        
    nb_internal_fp = 0
    if pos_first_internal_tp < pos_last_internal_tp - 1: # at least one internal position in the stretch 
        
        for pos_in_stretch in range(pos_first_internal_tp + 1, pos_last_internal_tp):
            if line_truth[pos_in_stretch] == "0":
                nb_internal_fp += 1
    
    return size_stretch, nb_fp, nb_internal_fp, nb_fn
        

def get_nb_tp_fp_fn_tn(line_truth, line_BF):
    nb_tp = 0
    nb_fn = 0
    nb_fp = 0
    nb_tn = 0
    for i in range(len(line_BF)):
        if line_BF[i] == '1':
            if line_truth[i] == '1':
                nb_tp += 1
            else:
                nb_fp += 1
        if line_BF[i] == '0':
            if line_truth[i] == '1':
                nb_fn += 1
        if line_BF[i] == '0':
            if line_truth[i] == '0':
                nb_tn += 1
    return nb_tp, nb_fp, nb_fn, nb_tn
        
        


def main():
    if len(sys.argv) != 3:
        sys.stderr.write(f"Usage: python {sys.argv[0]} file_truth file_BF\n")
        sys.exit()
    filenameTruth = sys.argv[1]
    filenameBF = sys.argv[2]

    size_stretcht_to_nb_FP = {}
    size_stretcht_to_nb_internalFP = {}
    size_stretcht_to_nb_FN = {}
    
    sum_nb_tp = sum_nb_fp = sum_nb_fn = sum_nb_tn = n = 0
    size_stretch_to_nb = {}
    with open(filenameTruth, "r") as file_truth, open(filenameBF, "r") as file_BF:
        for line_truth, line_BF in zip(file_truth, file_BF):
            line_truth = line_truth.strip()
            line_BF = line_BF.strip()
            n = len(line_truth)
            assert n == len(line_BF)
                          
            sum_nb_tp, sum_nb_fp, sum_nb_fn, sum_nb_tn = get_nb_tp_fp_fn_tn(line_truth, line_BF)
            assert (sum_nb_tp + sum_nb_fp + sum_nb_fn + sum_nb_tn == n)
            i = 0
            while i<n:
                if line_BF[i] == "1":
                    size_stretch, nb_fp, nb_internal_fp, nb_fn = get_nb_fp_nb_internal_fp_nb_fn(line_BF, line_truth, i)
                    # init results for this `size_stretch`:
                    if size_stretch not in size_stretcht_to_nb_FP:
                        size_stretcht_to_nb_FP[size_stretch] = 0
                    if size_stretch not in size_stretcht_to_nb_internalFP:
                        size_stretcht_to_nb_internalFP[size_stretch] = 0
                    if size_stretch not in size_stretcht_to_nb_FN:
                        size_stretcht_to_nb_FN[size_stretch] = 0
                    # update results for this `size_stretch`:
                    size_stretcht_to_nb_FP[size_stretch] += nb_fp
                    size_stretcht_to_nb_internalFP[size_stretch] += nb_internal_fp
                    size_stretcht_to_nb_FN[size_stretch] += nb_fn

                    if size_stretch not in size_stretch_to_nb:
                        size_stretch_to_nb[size_stretch] = 0
                    size_stretch_to_nb[size_stretch] += 1
                    i += size_stretch
                else:
                    i += 1 
            break
                
    if n == 0: exit(0)
    
    
    print(f"Query size: {n}")
    FPR = 100*sum_nb_fp/float(sum_nb_tn+sum_nb_fp)
    FNR = 100*sum_nb_fn/float(sum_nb_tp+sum_nb_fn)
    
    print("z\t#strch\t#TP\t#FP\t#FN\t#TN\tFPR%\tFNR%\t")
    print(f"0\tNA\t{sum_nb_tp}\t{sum_nb_fp}\t{sum_nb_fn}\t{sum_nb_tn}\t{round(FPR,5)}\t{round(FNR,5)}")
    
    QTF_TP = QTF_FN = 0
    QTF_TN = sum_nb_tn
    QTF_FP = sum_nb_fp
    for i in sorted(size_stretcht_to_nb_FP.keys()):
        if i in size_stretcht_to_nb_FP:
            nb_stretches = size_stretch_to_nb[i]
            QTF_FP -= size_stretcht_to_nb_FP[i]
            QTF_TN += size_stretcht_to_nb_FP[i] # one FP removed removes one TN
            QTF_FN += size_stretcht_to_nb_FN[i] 
            QTF_TP = n - (QTF_FP+QTF_FN+QTF_TN) # finaly
            
            QTF_FPR = 100*QTF_FP/float(QTF_TN+QTF_FP)
            QTF_FNR = 100*QTF_FN/float(QTF_TP+QTF_FN)
            print(f"{i}\t{nb_stretches}\t{QTF_TP}\t{QTF_FP}\t{QTF_FN}\t{QTF_TN}\t{round(QTF_FPR,5)}\t{round(QTF_FNR,5)}")
            

    
main()