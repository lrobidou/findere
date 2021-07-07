import matplotlib.pyplot as plt


def read_file(filename):
    liste = []
    with open(filename, "r") as fichier:
        for ligne in fichier:
            nb_elem, nb_bits, fpr, fnr = ligne.strip().split()
            nb_elem = int(nb_elem)
            nb_bits = int(nb_bits)
            fpr = float(fpr)
            fnr = float(fnr)
            liste.append([nb_elem, nb_bits, fpr, fnr])
    return liste


def plot_file(filename, label, options, color):
    les_x = []
    les_y = []
    for nb_elem, nb_bits, fpr, fnr in read_file(filename):
        les_x.append(nb_bits / nb_elem)
        les_y.append(fpr)
    plt.plot(les_x, les_y, options, label=label, c=color)


def plot_fpc_fraction(filename, filenamefpc, label, options, color):
    nbBitsPerElementFilename = []
    fprs = []
    for nb_elem, nb_bits, fpr, fnr in read_file(filename):
        nbBitsPerElementFilename.append(nb_bits / nb_elem)
        fprs.append(fpr)

    nbBitsPerElementFilenamefpc = []
    fpcs = []
    for nb_elem, nb_bits, fpr, fnr in read_file(filenamefpc):
        nbBitsPerElementFilenamefpc.append(nb_bits / nb_elem)
        fpcs.append(fpr)
    les_x = nbBitsPerElementFilename

    les_y = [(x - y) / (fprs[0] - fpcs[0]) * 100 for x, y in zip(fprs, fpcs)]

    assert nbBitsPerElementFilename == nbBitsPerElementFilenamefpc

    plt.plot(les_x, les_y, options, label=label, c=color)


def plot_files(prefix, color):
    prefix = prefix + "_"
    plot_file(
        prefix + "findereopti.txt",
        prefix + "findere (otpimal hash function)",
        "o--",
        color,
    )
    plot_file(
        prefix + "findereoptiCfp.txt",
        prefix + "findere Cfp (otpimal hash function)",
        "o-",
        color,
    )
    # plot_fpc_fraction(
    #     prefix + "findereopti.txt",
    #     prefix + "findereoptiCfp.txt",
    #     prefix + "(fpcs fraction (%))",
    #     "-",
    #     color,
    # )


def main():
    plot_files("K31z20", "mediumvioletred")
    plot_files("K31z19", "violet")
    plot_files("K31z18", "darkviolet")
    plot_files("K31z16", "indigo")
    plot_files("K31z15", "mediumblue")
    plot_files("K31z10", "dodgerblue")
    plot_files("K31z3", "azure")
    plot_files("K31z0", "darkslategray")

    plt.title("FPR wrt number of bits per element")
    plt.xlabel("bits / element")
    plt.ylabel("FPR (%)")
    plt.legend(loc="best")
    plt.xlim(0, 14)
    plt.show()


if __name__ == "__main__":
    main()
