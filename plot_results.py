import matplotlib.pyplot as plt
import json
from collections import defaultdict


def from_tuple_to_nested_dict(list_of_tuples):
    dic = defaultdict(dict)  # dict where the default values are dicts.
    for a, b, c, d in list_of_tuples:  # Each tuple is "key1, key2, value"
        # print(a, b, c, d)
        if not b in dic[a]:
            dic[a][b] = {}
        dic[a][b][c] = d
    return dic


def kez_temps_to_graph(the_dic):

    for k in the_dic:
        the_k = the_dic[k]
        for epsilon in the_k:
            the_epsilon = the_k[epsilon]

            tab = "\\begin{tabular}{|*{4}{c|}}\n"
            tab += "    \\hline\n"
            tab += "    z & time(ms) & simple query & \\toolK & \\toolK \\skip\\\n    \\hline\n"

            liste_z = []
            queryBf = []
            queryBfSkip = []
            queryNormalFilter = []
            print(k, epsilon)
            for z in the_epsilon:
                the_z = the_epsilon[z]

                tps = the_z["time"]

                liste_z.append(z)
                queryBf.append(tps["queryBf"])
                queryBfSkip.append(tps["queryBfSkip"])
                queryNormalFilter.append(tps["queryNormalFilter"])

                tab += (
                    "    "
                    + str(z)
                    + " & "
                    + str(tps["queryNormalFilter"])
                    + " & "
                    + str(tps["queryBf"])
                    + " & "
                    + str(tps["queryBfSkip"])
                    + "\\\n"
                )
            plt.plot(liste_z, queryBf, label="query QTF skip disabled")
            plt.plot(liste_z, queryBfSkip, label="query QTF skip enabled")
            plt.plot(liste_z, queryNormalFilter, label="query old way")
            plt.title("K = " + str(k) + "; $\epsilon$ = " + str(epsilon) + "%")
            plt.xlabel("z")
            plt.ylabel("time (ms)")
            plt.legend(loc="best")
            # plt.show()
            tab += "\\hline"
            print(tab)


def kze_frp_fnr_to_graph(the_dic):
    for k in the_dic:
        the_k = the_dic[k]
        for z in the_k:
            print("k = ", k, "; z = ", z)
            the_z = the_k[z]

            les_x = []
            queryBF_FPR = []
            queryBF_FNR = []
            queryBFSkip_FPR = []
            queryBFSkip_FNR = []
            resultsOnSmallTruth_FPR = []
            resultsOnSmallTruth_FNR = []
            normalfilter_FPR = []
            normalfilter_FNR = []
            tab = "\\begin{tabular}{|*{7}{c|}}\n"
            tab += "    $FP_{BF}$ & FPR simple query & FPR \\toolK & FPR \\toolK \\skip & construction FPR\\ & proportion of construction FPR (\%) & non constrction FPR \\\\ \n    \\hline\n"

            for epsilon in the_z:
                the_e = the_z[epsilon]

                tab += (
                    "    "
                    + str(epsilon)
                    + " & "
                    + str(the_e["normalfilter"]["FPR"])
                    + " & "
                    + str(the_e["queryBF"]["FPR"])
                    + " & "
                    + str(the_e["queryBFSkip"]["FPR"])
                    + "&"
                    + str(the_e["resultsOnSmallTruth"]["FPR"])
                    + "&"
                    + str(
                        round(
                            the_e["resultsOnSmallTruth"]["FPR"]
                            / the_e["queryBF"]["FPR"],
                            2,
                        )
                    )
                    + "&"
                    + str(
                        round(
                            the_e["queryBF"]["FPR"]
                            - the_e["resultsOnSmallTruth"]["FPR"],
                            5,
                        )
                    )
                    + "\\\\ \n"
                )
                les_x.append(epsilon)
                queryBF_FPR.append(the_e["queryBF"]["FPR"])
                # queryBF_FNR.append(the_e["queryBF"]["FNR"])
                queryBFSkip_FPR.append(the_e["queryBFSkip"]["FPR"])
                # # queryBFSkip_FNR.append(the_e["queryBFSkip"]["FNR"])
                resultsOnSmallTruth_FPR.append(the_e["resultsOnSmallTruth"]["FPR"])
                # # resultsOnSmallTruth_FNR.append(the_e["resultsOnSmallTruth"]["FNR"])
                normalfilter_FPR.append(the_e["normalfilter"]["FPR"])
                # # normalfilter_FNR.append(the_e["normalfilter"]["FNR"])
                # les_y.append(the_e["results"]["FPR"])
                print()
            tab += "\\hline\n"
            tab += "\\end{tabular}"
            # print(tab)

            plt.plot(les_x, queryBF_FPR, label="queryBF_FPR", linewidth=8)
            # plt.plot(les_x, queryBF_FNR, label="queryBF_FNR")
            plt.plot(les_x, queryBFSkip_FPR, "--", label="queryBFSkip_FPR", linewidth=6)
            # # plt.plot(les_x, queryBFSkip_FNR, label="queryBFSkip_FNR")
            # plt.plot(les_x, resultsOnSmallTruth_FPR, label="resultsOnSmallTruth_FPR", linewidth=4)
            # # plt.plot(les_x, resultsOnSmallTruth_FNR, label="resultsOnSmallTruth_FNR")
            plt.plot(les_x, normalfilter_FPR, label="normalfilter_FPR", linewidth=2)
            # # plt.plot(les_x, normalfilter_FNR, label="normalfilter_FNR")
            plt.title("K = " + str(k) + "; z = " + str(z))
            plt.xlabel("$\epsilon$")
            plt.ylabel("%")
            plt.legend(loc="best")
            plt.show()


def print_tab(*rows):
    t = list(zip(*rows))
    l_col = []
    for col in t:
        l_col.append(max([len(str(x)) for x in col]) + 3)

    first = True
    for row in rows:
        for i_col in range(len(row)):
            col = row[i_col]
            print("|" + str(col) + (l_col[i_col] - len(str(col))) * " ", end="")
        print("|")
        if first:
            first = False
            for i_col in range(len(row)):
                print("|" + (l_col[i_col]) * "-", end="")
            print("|")
    print()


def print_tab_latex(*rows):
    tab = "\\begin{tabular}{|*{7}{c|}}\n"
    tab += "    \\hline\n"

    t = list(zip(*rows))
    l_col = []
    for col in t:
        l_col.append(max([len(str(x)) for x in col]) + 3)
    first = True
    for row in rows:
        tab += "    "
        for i_col in range(len(row)):
            col = row[i_col]
            tab += str(col) + (l_col[i_col] - len(str(col))) * " "
            if i_col != len(row) - 1:
                tab += "&"
            else:
                tab += "\\\\\n"

        # print("")
        if first:
            first = False
            # for i_col in range(len(row)):
            #     print("|"+ (l_col[i_col])*"-", end="")
            # print("|")
            tab += "    \\hline\n"
    tab += "    \\hline\n"
    tab += "\\end{tabular}"
    print(tab)


def kze_to_tab(the_dic):
    # for k in the_dic:
    k = 31
    the_k = the_dic[k]
    for z in the_k:
        the_z = the_k[z]
        for e in the_z:
            the_e = the_z[e]

            liste_col = [
                "",
                "TxFN",
                "TxFP",
                "FP structure",
                "Temps indexation",
                "Temps Query",
                "Memoire",
            ]
            fdb = [
                "FdB",
                the_e["normalfilter"]["FNR"],
                the_e["normalfilter"]["FPR"],
                "x",
                the_k[0][e]["time"]["computeBf"],
                the_k[z][e]["time"]["queryBf"],
                the_k[0][e]["queryBF"]["BFSize(bits)"],
            ]
            qtf_noskip = [
                "QTF no skip",
                the_e["queryBF"]["FNR"],
                the_e["queryBF"]["FPR"],
                the_e["resultsOnSmallTruth"]["FPR"],
                the_e["time"]["computeBf"],
                the_e["time"]["queryBf"],
                the_e["queryBF"]["BFSize(bits)"],
            ]
            qtf_skip = [
                "QTF skip",
                the_e["queryBFSkip"]["FNR"],
                the_e["queryBFSkip"]["FPR"],
                the_e["resultsOnSmallTruth"]["FPR"],
                the_e["time"]["computeBf"],
                the_e["time"]["queryBfSkip"],
                the_e["queryBFSkip"]["BFSize(bits)"],
            ]
            print("k = ", k, "; z = ", z, "; e = ", e)
            print_tab_latex(liste_col, fdb, qtf_noskip, qtf_skip)
            # print("|"  + "|".join(liste_col) + "|")
            # print("|"  + "|".join(["---" for _ in liste_col]) + "|")
            # print("|"  + "|".join([str(x) for x in fdb]) + "|")
            # print("|"  + "|".join([str(x) for x in qtf_noskip]) + "|")
            # print("|"  + "|".join([str(x) for x in qtf_skip]) + "|")


def kez_frp_en_fonction_de_z_u(the_dic):
    for k in the_dic:
        the_k = the_dic[k]
        for epsilon in the_k:
            the_epsilon = the_k[epsilon]

            # if you want he output to be in latex:
            # tab = "\\begin{tabular}{|*{4}{c|}}\n"
            # tab += "    \\hline\n"
            # tab += "    z & FPR of QTF\\hline\n"

            # if not:
            tab = ""

            liste_z = []
            queryBf = []
            normQuery = []
            print(k, epsilon)
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
                    "    "
                    + str(z)
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
            tab += "\\hline"
            print(tab)


def main():
    with open("courbeU.json", "r") as fichier:
        runs = json.load(fichier)

    kez = []
    kze = []
    for run in runs:
        kez_keys = run["param"]["k"], run["param"]["epsilon"], run["param"]["z"]
        kze_keys = run["param"]["k"], run["param"]["z"], run["param"]["epsilon"]
        run.pop("param")
        kez.append((*kez_keys, run))
        kze.append((*kze_keys, run))
    kez_results = from_tuple_to_nested_dict(kez)
    kze_results = from_tuple_to_nested_dict(kze)

    # kez_temps_to_graph(kez_results)
    # kze_frp_fnr_to_graph(kze_results)
    kez_frp_en_fonction_de_z_u(kez_results)
    # kze_to_tab(kze_results)

    # # print(json.dumps(sorted_results, indent=4, sort_keys=True))
    # # for k in results:
    # for k in results:
    #     for z in results[k]:
    #         les_x = []
    #         les_y = []
    #         for epsilon in results[k][z]:
    #             les_x.append(epsilon)
    #             les_y.append(results[k][z][epsilon]["results"]["FPR"])
    #         plt.plot(les_x, les_y, label="z = " + str(z))
    #     plt.legend(loc="best")
    #     plt.title("K = " + str(k))
    #     plt.savefig("K = " + str(k) + ".png")
    #     plt.clf()
    #     # plt.show()


if __name__ == "__main__":
    main()
