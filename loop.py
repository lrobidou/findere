import matplotlib.pyplot as plt
import numpy as np


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


def plot_file(filename, label, options):
    les_x = []
    les_y = []
    for nb_elem, nb_bits, fpr, fnr in read_file(filename):
        les_x.append(nb_bits / nb_elem)
        les_y.append(fpr)
    plt.plot(les_x, les_y, options, label=label)


def get_m_and_n(filename):
    bit_per_elem = []
    fpr_mini = []

    with open(filename, "r") as fichier:
        for ligne in fichier:
            nb_elem, nb_bits, fpr, fnr = ligne.strip().split()
            nb_elem = int(nb_elem)
            nb_bits = int(nb_bits)
            bit_per_elem.append(nb_bits / nb_elem)

            lne = -(np.log(2) ** 2) * nb_bits / nb_elem
            print(nb_bits / nb_elem, lne)
            fpr_mini.append(np.exp(lne) * 100)
    return bit_per_elem, fpr_mini


def main():
    plot_file("bf1.txt", "BF (one hash function)", "x-")
    plot_file("bfopti.txt", "BF (optimal hash function)", "x--")
    plot_file("findere1.txt", "findere (one hash function)", "o-")
    plot_file("findereopti.txt", "findere (otpimal hash function)", "o--")
    plt.title("FPR wrt number of bits per element")
    les_x, les_y = get_m_and_n("bf1.txt")
    print(les_x, les_y)
    plt.plot(les_x, les_y)
    plt.xlabel("bits / element")
    plt.ylabel("FPR (%)")
    plt.legend(loc="best")
    plt.show()


if __name__ == "__main__":
    main()
