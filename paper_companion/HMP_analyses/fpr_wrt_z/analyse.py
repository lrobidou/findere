import matplotlib.pyplot as plt
import json
from collections import defaultdict


def from_tuple_to_nested_dict(list_of_tuples):
    dic = defaultdict(dict)  # dict where the default values are dicts.
    for a, b, c, d in list_of_tuples:
        if not b in dic[a]:
            dic[a][b] = {}
        dic[a][b][c] = d
    return dic


def kez_frp_en_fonction_de_z_u(the_dic):
    for k in the_dic:
        the_k = the_dic[k]
        for epsilon in the_k:
            the_epsilon = the_k[epsilon]
            tab = "z  AMQ_FPR  findere_FPR  construction_FPR\n"

            liste_z = []
            queryBf = []
            normQuery = []
            for z in the_epsilon:
                the_z = the_epsilon[z]

                fprQTF = the_z["queryBF"]["FP"] / (
                    the_z["queryBF"]["FP"] + the_z["queryBF"]["TN"]
                )

                fprNorm = the_z["normalfilter"]["FP"] / (
                    the_z["normalfilter"]["FP"] + the_z["normalfilter"]["TN"]
                )

                fprConstr = the_z["resultsOnSmallTruth"]["FP"] / (
                    the_z["resultsOnSmallTruth"]["FP"]
                    + the_z["resultsOnSmallTruth"]["TN"]
                )
                liste_z.append(z)
                queryBf.append(fprQTF)
                normQuery.append(fprNorm)

                tab += (
                    str(z)
                    + " "
                    + str(round(fprNorm, 6))
                    + "  "
                    + str(round(fprQTF, 6))
                    + "  "
                    + str(round(fprConstr, 6))
                    + "\n"
                    # + "\\\\\n"
                )
            plt.plot(liste_z, queryBf, label="FPR - findere")
            plt.plot(liste_z, normQuery, label="FRP - bloom filter")
            plt.title("K = " + str(k) + "; $\epsilon$ = " + str(epsilon) + "%")
            plt.xlabel("z")
            plt.ylabel("FPR (\%)")
            plt.legend(loc="best")
            plt.show()
            print(tab)


def main():
    with open("courbeU.json", "r") as fichier:
        runs = json.load(fichier)

    kez = []
    for run in runs:
        kez_keys = run["param"]["k"], run["param"]["epsilon"], run["param"]["z"]
        run.pop("param")
        kez.append((*kez_keys, run))
    kez_results = from_tuple_to_nested_dict(kez)
    kez_frp_en_fonction_de_z_u(kez_results)


if __name__ == "__main__":
    main()
