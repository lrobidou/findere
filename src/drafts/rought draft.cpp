std::string generateRandomLetter() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 3);  // distribution in range [1, 4]
    int randomInt = dist4(rng);
    if (randomInt == 0) {
        return "A";
    } else if (randomInt == 1) {
        return "C";
    } else if (randomInt == 2) {
        return "T";
    }
    return "G";
}

std::string generateRandomSequence(unsigned long size) {
    std::string s = "";
    while (s.size() < size) {
        s += generateRandomLetter();
    }
    return s;
}

std::string mutate(const std::string& s, int percent_similarity_target, unsigned long blockLength) {
    unsigned long long size = s.size();
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, size - 1 - blockLength);  // distribution in range [1, 6]

    std::string smut = s;

    double diff = 1;
    int same = 0;
    while ((double)diff > ((double)percent_similarity_target / 100)) {
        same = 0;
        // std::cout << "muting" << std::endl;
        int start = dist(rng);
        smut = smut.replace(start, blockLength, generateRandomSequence(blockLength));
        for (unsigned long long i = 0; i < size; i++) {
            if (s[i] == smut[i]) {
                same++;
            }
            diff = 1 - (((double)size - (double)same) / (double)size);
        }
        std::cout << "diff" << diff << std::endl;
    }
    return smut;
}