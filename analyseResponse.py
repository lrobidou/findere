import matplotlib.pyplot as plt


def read_file0n(filename, n, xlimit):
    les_x = []
    les_y = []
    with open(filename, "r") as fichier:
        for ligne in fichier:
            for i, x in enumerate(ligne):
                if x == "0":
                    # contenu.append(0)
                    pass
                elif x == "1":
                    les_x.append(i)
                    les_y.append(n)
                else:
                    print("erreur, x=", x)
                if i >= xlimit:
                    return les_x, les_y
    return les_x, les_y


def diff(filename1, filename2, n, xlimit):
    les_x = []
    les_y = []
    with open(filename1, "r") as fichier1, open(filename2, "r") as fichier2:
        for ligne1, ligne2 in zip(fichier1, fichier2):
            for i, (x1, x2) in enumerate(zip(ligne1, ligne2)):
                if x1 == x2:
                    # contenu.append(0)
                    pass
                else:
                    les_x.append(i)
                    les_y.append(n)
                # else:
                #     print("erreur, x=", x)
                if i >= xlimit:
                    return les_x, les_y
    return les_x, les_y


if __name__ == "__main__":
    nmax = 1000000
    les_x_truth, les_y_truth = read_file0n("truth.txt", 1, nmax)
    les_x_responseQuery, les_y_responseQuery = read_file0n("responseQuery.txt", 2, nmax)
    les_x_responseQTF, les_y_responseQTF = read_file0n("responseQTF.txt", 3, nmax)
    les_x_responseQTFPlus, les_y_responseQTFPlus = read_file0n(
        "responseQTFPlus.txt", 4, nmax
    )
    les_x_truthPlusZ, les_y_truthPlusZ = read_file0n("truthPlusK.txt", 5, nmax)

    plt.plot(les_x_truth, les_y_truth, "o", markersize=2)
    plt.plot(*diff("truth.txt", "responseQuery.txt", 1.5, nmax), "o", markersize=2)
    plt.plot(les_x_responseQuery, les_y_responseQuery, "o", markersize=2)
    plt.plot(les_x_responseQTF, les_y_responseQTF, "o", markersize=2)
    plt.plot(les_x_responseQTFPlus, les_y_responseQTFPlus, "o", markersize=2)
    plt.plot(
        *diff("truthPlusK.txt", "responseQTFPlus.txt", 4.5, nmax), "o", markersize=2
    )
    plt.plot(les_x_truthPlusZ, les_y_truthPlusZ, "o", markersize=2)
    plt.show()
