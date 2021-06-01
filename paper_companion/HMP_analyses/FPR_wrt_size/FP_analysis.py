import json
from collections import defaultdict
import matplotlib.pyplot as plt


def from_tuple_to_nested_dict(list_of_tuples):
    dic = defaultdict(dict)  # dict where the default values are dicts.
    for a, b, c, d in list_of_tuples:
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
        print("size", "FPR_findere (z=3)", "FPR_BF")
        for x, y, z in zip(sizes, fprs_findere, fprs_bf):
            print(x, y, z)
        plt.plot(sizes, fprs_findere, label="FPR_findere (z=3)")
        plt.plot(sizes, fprs_bf, label="FPR_BF")
        plt.title("K = " + str(k) + "; z = 3")
        plt.xlabel("size")
        plt.ylabel("FPR (%)")
        plt.legend(loc="best")
        plt.show()


def main():
    # open the file, read the content
    with open("fixSize.json", "r") as fichier:
        runs = json.load(fichier)

    # create a dict from the content to make it easier to manipulate
    kez = []
    for run in runs:
        kez_keys = run["param"]["k"], run["param"]["bits"], run["param"]["z"]
        run.pop("param")
        kez.append((*kez_keys, run))
    kez_results = from_tuple_to_nested_dict(kez)

    # plot the result of the experiment
    plot_frp(kez_results)


if __name__ == "__main__":
    main()
