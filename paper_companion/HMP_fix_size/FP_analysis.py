import json
from collections import defaultdict
import matplotlib.pyplot as plt


def from_tuple_to_nested_dict(list_of_tuples):
    dic = defaultdict(dict)  # dict where the default values are dicts.
    for a, b, c, d in list_of_tuples:  # Each tuple is "key1, key2, value"
        # print(a, b, c, d)
        if not b in dic[a]:
            dic[a][b] = {}
        dic[a][b][c] = d
    return dic


def plot_frp(the_dic):
    for k in the_dic:
        sizes = []
        fprs_bf = []
        fprs_findere = []
        the_k = the_dic[k]
        for size in the_k:
            the_size = the_k[size][3]
            sizes.append(the_size["findere"]["BFSize(bits)"])
            fprs_bf.append(
                100
                * the_size["normalfilter"]["FP"]
                / (the_size["normalfilter"]["FP"] + the_size["normalfilter"]["TN"])
            )
            fprs_findere.append(
                100
                * the_size["findere"]["FP"]
                / (the_size["findere"]["FP"] + the_size["findere"]["TN"])
            )
        plt.plot(sizes, fprs_findere, label="FPR_findere (z=3)")
        plt.plot(sizes, fprs_bf, label="FPR_BF")
        plt.title("K = " + str(k) + "; z = 3")
        plt.xlabel("size")
        plt.ylabel("FPR (%)")
        plt.legend(loc="best")
        plt.show()


def main():
    with open("fixSize.json", "r") as fichier:
        runs = json.load(fichier)

    kez = []
    kze = []
    for run in runs:
        kez_keys = run["param"]["k"], run["param"]["bits"], run["param"]["z"]
        kze_keys = run["param"]["k"], run["param"]["z"], run["param"]["bits"]
        run.pop("param")
        kez.append((*kez_keys, run))
        kze.append((*kze_keys, run))
    kez_results = from_tuple_to_nested_dict(kez)
    plot_frp(kez_results)


if __name__ == "__main__":
    main()
