# compute the difference between two files


def diff(filename1, filename2):
    les_x = []
    les_y = []
    with open(filename1, "r") as fichier1, open(filename2, "r") as fichier2:
        for ligne1, ligne2 in zip(fichier1, fichier2):
            for i, (x1, x2) in enumerate(zip(ligne1, ligne2)):
                if not x1 == x2:
                    les_x.append(i)
                    les_y.append(1)
    return les_x, les_y


if __name__ == "__main__":
    print(diff("responseQTF.txt", "responseQTFSkip.txt"))

