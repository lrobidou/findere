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


def main():
    with open("resultsPrecise.json", "r") as fichier:
        runs = json.load(fichier)

    list_of_tuples = []
    for run in runs:
        keys = run["param"]["k"], run["param"]["z"], run["param"]["epsilon"]
        run.pop("param")
        list_of_tuples.append((*keys, run))
    results = from_tuple_to_nested_dict(list_of_tuples)

    # print(json.dumps(sorted_results, indent=4, sort_keys=True))
    # for k in results:
    for k in results:
        for z in results[k]:
            les_x = []
            les_y = []
            for epsilon in results[k][z]:
                les_x.append(epsilon)
                les_y.append(results[k][z][epsilon]["results"]["FPR"])
            plt.plot(les_x, les_y, label="z = " + str(z))
        plt.legend(loc="best")
        plt.title("K = " + str(k))
        plt.savefig("K = " + str(k) + ".png")
        plt.clf()
        # plt.show()


if __name__ == "__main__":
    main()
