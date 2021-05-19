import matplotlib.pyplot as plt

START = 1000
N = 1000000


def read_file0n(filename, n):
    les_x = []
    les_y = []
    with open(filename, "r") as fichier:
        for ligne in fichier:
            for i, x in enumerate(ligne):
                if i < START:
                    continue
                if x == "1":
                    les_x.append(i)
                    les_y.append(n)
                if i >= START + N:
                    return les_x, les_y
    return les_x, les_y


def diff(filename1, filename2, n):
    les_x = []
    les_y = []
    with open(filename1, "r") as fichier1, open(filename2, "r") as fichier2:
        for ligne1, ligne2 in zip(fichier1, fichier2):
            for i, (x1, x2) in enumerate(zip(ligne1, ligne2)):
                if i < START:
                    continue
                if x1 != x2:
                    les_x.append(i)
                    les_y.append(n)
                if i >= START + N:
                    return les_x, les_y
    return les_x, les_y


def myplot(filename, n):
    plt.plot(*read_file0n(filename, n), "o", markersize=2, label=filename)


if __name__ == "__main__":
    myplot("truthQuery.txt", 1)
    # plt.plot(*diff("truth.txt", "responseQuery.txt", 1.5, nmax), "o", markersize=2)
    # plt.plot(*read_file0n("responseQuery.txt", 2, nmax), "o", markersize=2)

    myplot("responseQTF.txt", 3)
    myplot("responseQTFKPlusZ.txt", 4)
    plt.plot(
        *diff("truthKPlusZQuery.txt", "responseQTFKPlusZ.txt", 4.5), "o", markersize=2
    )
    myplot("truthKPlusZQuery.txt", 5)
    plt.legend(loc="best")
    plt.show()
