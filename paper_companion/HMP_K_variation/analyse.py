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


def plot_time(the_dic):
    ks = []
    times_bf = []
    times_findere = []
    fpr_bf = []
    fpr_findere = []
    for k in the_dic:
        ks.append(k)

        the_k = the_dic[k]
        for z in the_k:
            the_z = the_k[z]
            for b in the_z:
                the_b = the_z[b]
                times_bf.append(the_b["time"]["queryNormalFilter"])
                times_findere.append(the_b["time"]["queryBfSkip"])
                fpr_bf.append(
                    100
                    * the_b["normalfilter"]["FP"]
                    / (the_b["normalfilter"]["FP"] + the_b["normalfilter"]["TN"])
                )
                fpr_findere.append(
                    100
                    * the_b["queryBFSkip"]["FP"]
                    / (the_b["queryBFSkip"]["FP"] + the_b["queryBFSkip"]["TN"])
                )
    print(ks)
    print(times_bf)
    print(times_findere)
    plt.plot(ks, times_findere, label="time_findere (z=3)")
    plt.plot(ks, times_bf, label="time_BF")
    plt.xlabel("K")
    plt.ylabel("time (%)")
    plt.legend(loc="best")
    plt.show()

    plt.plot(ks, fpr_findere, label="fpr_findere (z=3)")
    plt.plot(ks, fpr_bf, label="frp_BF")
    # plt.title("K = " + str(k) + "; epislon = " + str(b))
    plt.xlabel("K")
    plt.ylabel("FPR (%)")
    plt.legend(loc="best")
    plt.show()

    for x, y, z in zip(ks, fpr_findere, times_findere):
        print(x, round(y, 2), z / 1000)


def main():
    with open("kvar.json", "r") as fichier:
        runs = json.load(fichier)

    kez = []
    kze = []
    for run in runs:
        kez_keys = run["param"]["k"], run["param"]["bits"], run["param"]["z"]
        kze_keys = run["param"]["k"], run["param"]["z"], run["param"]["bits"]
        run.pop("param")
        kez.append((*kez_keys, run))
        kze.append((*kze_keys, run))
    kze_results = from_tuple_to_nested_dict(kze)
    plot_time(kze_results)


if __name__ == "__main__":
    main()
