import numpy as numpy
import matplotlib.pyplot as plt


def lire(filename):
    contenu = []
    with open(filename, "r") as fichier:
        for ligne in fichier:
            contenu += [int(x) for x in ligne]
    return contenu


def trouver_prochain(seq, debut, nombre):
    for pos_courante in range(debut, len(seq)):
        if seq[pos_courante] == nombre:
            return pos_courante


def extraire_prochain_stretch(seq, debut):
    # la position debut n'est pas encre testée, faisons le
    pos_stretch = trouver_prochain(seq, debut, 1)
    if not pos_stretch:
        return None, None
    fin_stretch = trouver_prochain(seq, pos_stretch, 0)
    if not fin_stretch:
        fin_stretch = len(seq)
    return pos_stretch, fin_stretch


def reconstituer(liste_pos_stretch, maxlen):
    reconstit = []
    debut = 0
    for pos_stretch, fin_stretch in liste_pos_stretch:
        if pos_stretch is not None:
            reconstit += [0 for _ in range(pos_stretch - debut)]
            if fin_stretch != maxlen:
                reconstit += [1 for _ in range(fin_stretch - pos_stretch)]
            else:
                reconstit += [1 for _ in range(maxlen - pos_stretch)]
        else:
            reconstit += [0 for _ in range(maxlen - debut)]
        debut = fin_stretch
    return reconstit


def trouver_FP(test, liste_pos_stretch):
    FP = 0
    FPendebut = 0
    FPenfin = 0
    for pos_stretch, fin_stretch in liste_pos_stretch:
        stretch = test[pos_stretch:fin_stretch]
        if 0 in stretch:
            # print(len(stretch))
            if stretch[0] == 0:
                FPendebut += 1
            if len(stretch) > 0 and stretch[-1] == 0:
                FPenfin += 1
            # print("FP")
            FP += stretch.count(0)
    print("nb FP = ", FP)
    print("nb FPendebut = ", FPendebut)
    print("nb FPenfin = ", FPenfin)


def trouver_erreurs(truth, test):
    debut = 0
    liste_pos_stretch = []
    while debut is not None:
        pos_stretch, fin_stretch = extraire_prochain_stretch(test, debut)
        liste_pos_stretch.append((pos_stretch, fin_stretch))
        debut = fin_stretch

    # print(liste_pos_stretch)
    # reconstit = reconstituer(liste_pos_stretch, len(truth))
    # assert truth == reconstit
    liste_pos_stretch.pop(-1)
    trouver_FP(truth, liste_pos_stretch)
    # for i in range(len(truth)):
    #     if truth[i] == 1:
    #         if test[i] == 1:
    #             assert True  # TP
    #         else:
    #             assert False  # FN, impossible
    #     else:
    #         if test[i] == 1:
    #             assert False  # FP
    #         else:
    #             assert True  # TN


if __name__ == "__main__":
    bigKEmulatedFromQTFBloomFilter = lire("bigKEmulatedFromQTFBloomFilter.txt")
    bigTruth = lire("bigTruth.txt")
    smallQtfFromTruth = lire("smallQtfFromTruth.txt")
    bigKEmulatedFromSmallTruth = lire("bigKEmulatedFromSmallTruth.txt")
    bigKEmulatedFromQTF = lire("bigKEmulatedFromQTF.txt")
    trouver_erreurs(bigTruth, bigKEmulatedFromQTFBloomFilter)

# 3592475 3592533
# 3592568 3592626
# ^CTraceback (most recent call last):
#   File "analyseSubK.py", line 63, in <module>
#     trouver_erreurs(bigKEmulatedFromSmallTruth, bigKEmulatedFromQTF)
#   File "analyseSubK.py", line 43, in trouver_erreurs
#     assert reconstit == truth[0 : len(reconstit)]
# KeyboardInterrupt
