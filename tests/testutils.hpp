#include <string>
std::string randomSeq = "GATTATCAACTCCCCATGTTAAAGAGCGGTAGCGCCCGTGGTACTTGATGCTACATTTATTCTTTTAGGAAGACGGATACCTCAACCAAGTACAGGTCTTCAAACGAGCTCTGGGCCCCCCCAAGTTCCGCGTAGAACTTAGTGATCTAACCCGCACTAGCACTGGTGAGAAGGTTGACAACCTCTTCATTAGTTGTGTGTGTGCGTTATGTCATAGACGGTTTATAGGGTTGACCTCATGGGTCCCGACATATACTGGGAATCATATTCTTCGACCGGGGAGGTAAATACAACGGGTATCATCGTTATCATCCGGGTAGAGATGACTAAAAACGCTGCTAGGATAAGTATCATTTTATAGAGAAACTGGTACGAGGAAGATGCTTCGGGCGCGGTAGAACGGTTAGCTAATACCGCGAGCCCAGAACCAGAAAAAGTCTCTGCGCGTTGGTAGCCAAGCCATATAGCGTTTCCGGTAACGGGGTAAGTAGCGTGGCTTCTACGCCGACCGCTCACCTGCAACTAGCCTTAAGCAATGTACCTATGCTTGAATTCTTAGTCTTTAGGACCCGTGTCTGGAATCTTCAACGAGAAGTCCTCTGTCGAGGCCTGCAAAGGAATGTAAATGCTGATAGATCCTTAAAAAATAACGCGAACGTCCTGGTGGGACCCGCCCGAAGTCTTCATAGCCGCACAAGGAAAAGCAATTTGACCTATGATAGTACATAGAGGGCTGAGCTGGAGCGCGCACGAGGAGAGCCGTTCGTGATTAACGGAACCACTTGACGCTATCCCAGTGCCTCTAGCGAATGGCAACAGGGTTCGGACGCTCCACGAGCAGTTAAGGATAAAGAGTTAATGGAGGAAATGTGTAGCCAGTAGGCTTGTTCTGCATGATTGGTGACTTACCCGACGGCTGCTGTAATGGTGCTCAGCATTAATGGACAGAATCGCGCTCCACCCTGACAACCAATGGAGATCGGAGGCCGGCCCGCTGGTACTTGTGAATACTTAGCACCTCGGTATAGTACCGCTGTGTGCTGGCCTGGTGTACCCGTTGAGAGCAACATCTTCGAATAGATGCATGGCTTCAGAGCGGACGAGGGCGTTAAAAGACTCATGTGTCCTTGGAAAAAGGGAAACCGTAGCAGCGCAAAGAACTATTGCAGTCGTACTCAGGACGGATGGTATCAAAATGGGAGGCTTCCACACAGCCACCAAGGATTGAACTGGCAAGAAAGGTAGGAAGAAAGGGTTATATAACGCTCGACCGACAACAGCGAACTTAAATAATTGTGAGCATGATTTTACGTCGGGCGCTATTTCCCGTGTAAAGAGCGCGTCAAGATACCTAGCAGGGGGGCGAAGTTAACCAGTGAGCTGTTCACGATCGGGGTGGTTCAATGGAGAGGTGCATCTACTGGCGGTTAAGTATGCATGGCCCGTGGATGGTCCCCCAAACCTGCAAAACTAATAGTGTCAGCTTTACCAATTCACTATGAATTATTTTATGTTGTTCCGACTTACTCGTTCGATTACCAATGTTCGGCTTAAACACTCACGCCACCTAGTTAGGGATCTCTATTGATGATTCCTAAAGGCGAGTGCCAAGGTGTGGAGGAGATACCAGACCGATCACGTGGGTCGGTGATGCTCCGGCCACACAGGGTTCTCCATACTCCTGGAGGGTTCACACGTCTAATAACGACAGAGTCTCCAGGGCCTTGAACTTTAGAAGCTCGCGCTCTTTTGGTAGATGCAAGCTTATGCTACAAAGGGGGCCGACTGTTTTACGATACTCAAAGGAGGTGTATAGTCGGAGCGATCAGGGATCAGTGCAAACCTGGATGACGTTGATCGCTAGAGTGTCGAAAAGCCCCCAAGTCCAGAATTCCCAACTTTGACGTCCAGAATATGGCTTCCATCTTAGGTAATGGTGTGCAACGGCGTTTATTAGTGCTCCACAGACCCATGAGAAAATAATCCTGTACCTGTTTAAGCTGCAGAGATAAGGCCTCGGTCCTGGAGGCTGCGAATTCATGGTATGTCTATCTTGCGATAGCATCACTGGAAGGGTCAGGGATAATCACCGCATCCGGATATGAGTATCAGCTTCTGAGTGGTACTTAACTCTTTCCGTACATAACCCGTCAGATTAATACTGTCACTCCGTCTTGTACGTAATTCTTCGTTCTCGAGGGCTGCTTATGACAGGTTCGGGCCTGTCATCCGCGATTCTGTCAATGGCAACCTGGGGTAAACGGTTGGTCTATGTCGCCCCTCGCTCTGGTTCCATTGCGCCACGGACATGACATTTCCGACGGCAGCTTAAGGAAAGAGGATATCTTTCGCAGGGTGGAGGGCTCCGGCCTTGTCGCGTAACTGAATTGTTCCGGAGCTGTAGGCAGGGCAGACTTGATCGCTCACAAAGCTGCGCAACAAGTCGGATGCGTAGCACGTCAGTTCCATGATAGTACGTGAAGTCTTCAGACATGCGCATACTTAGCATTGACTAGGGCCGCACCCCTGAAGATAAATGCTGCCGCCCACAGTGTTACTGCGCAAGAGCGCATCCTGAGAGCGACTAGCGCAGTCTTGGATCATTTTACACGAAGAAATGCGGGTCTAGTCTATTCATACTTCAAGATGGGCAGGTAGCAGGGTGGCTCACTTTGTCAAGTAGGACCTGGCGCTGCCTGGACCATAGCCTGTTCCCGGCCCGGTTGGCAGTAACTATTTGCTCGCTAGCCGCTCCTGAACCACTAGCCCAGCGTGCCCACCCTCCGCATAGTGATAGCAGATATTAAAGAGCTCACGCTAAGCAGGAAAAGAATCTTTACCACGCGTAGTAGCAGGACTCTAGTGCATTGCTTGCTGATCATCGACAATTTAGTTGTGAATTGTGACATCAACCTATATCAGGTGCAGGTGGGCATTAGGTCAGCCCTCCTCGTCCACGTTACCACCTTCACCCGAAGGAATAGGCATGGTAAGGGCCAGGGATGTGGCCAGGTTGCAAAAGAAAGCCCAGAAGACGCAGACTTTCCACCCCGATCGCGTTATACAGCAAACAGTATTAACGCCTAGTCCTTCCCCTTGAATCGCTAGTTGTTGACAGGTAATAGTTTCCGGCTTATTGTCAACTTCACAAACTGTGCATAACAATGTCGTGATGCTTTAAGGGACTCCTACACAAATCCTAGACTGGATGTGCCTGGTGACCCGTCAGCCACCTTCTCATGAACCGGTGAGAAGCGGTTAAAGGCGAACTTCGTATAGCTCTTCCTCTAAGGCTGCGGACGTGTCAAGGGCCCGTGCCTAATGCGCGTGAATGGTCGTGAGGAGGGGATTCATAGCACGGATGAACGCGTTGAATGCAATGCGTAGACCCACATGGCTGTGATGAGGGGATGCATCGATAGAACGGGGGCTGTGAGCGCGCTTGTATAAGTACGCGTGGGGCATCCTGACCGCCACGCCGGACCAAAAAGGGTGGTGACTGGGAAGGCAAAAATCGGGGCGGTGTAGAGCTAAGGTTCTGGCTGCTATGACGAACTGCGGGCGTCTGGACCAGCGTTCATCAGGAGAACTATCCGGATCGAGCCGGGATCGGGTCGTTCCCTCCTTTGAGAAAACGACGGTGGATCGACGACGAACCCTTTGTCGAGAGGCTGCAGCCTCTTCGTTCTTCACTTTGTTGAGATGTATCTAGATCCATTTTTCGTTAAGGGTAAGATTGATGCCATAAACTAAAGCTCGGAGACCAGCCCACGACGGGCAGCACAGTTTCTCCCAGTAATCCTGGCTCACCCCGGATTGCTATAGCGCACCCTTAGACGGGCTACAAGGTATAAATGCAATGTTCCGTCAATGAATCGATTCCCTCGTTCCGAAGGTGAGGCCCACACATACTTTGCGAGTATTTTGGAAGAATGGGCGGCCTTGCCTGGCTGGTGCTCATCCTACGGCTAACGAAGCCGCAAAAAACGTTTGTGCATCTTTCTGCTAGATACAAGGAAAGTTTATGAGTGATACTAATTGATGATCTGACGTCCGGGCACATGTAGGTGTAGATAAACGTATAGTCAGACTCCAGCTATGCGGTTCAGCTCAGGTCAAAACACCGACAGCGCCCACTGCATAGTAGTCGGTTAGGCACGGTGACACCCAGGGATGGTAGTCCTGGACGGCGCCCTCCCCCTCCTCGGACCCAGATTATAGGTTAGTTGGGATATCTAGTCGTAAATTTCGGTACGGAACTTCTCTCGTGTCCAGATCCGAGAAACACTGACTGTGTCGAAACAAATACTTTCTGTAAACCATAACTTGGCGCGCAAGCACAGTGTGGTGCAATGATCGATGCGAAGTCGAAGACGTTAGTGACTCAAATCGGTGAATGGACTAGATCCAAGATATTTGGTGGGTCAGGCCTCACAATACATGGCGAGGATAATCTCCCATAGAGCTTAGATTTTAACATCCTAAGCGCGTCCACTTGATTGGTGAAGTGGTGCGTAGAGTTCTGTCTCAATATTACATCCGACGAAGTTGAGCTCTCCGGTATCGATGTCAGAGCAGCGGCGAGCCTATCTGCAATGAAATAACGACCGCAACTCCTCCGCCCAATTCAGCCAGCTAATAAGAGCGAGGTAGCCTGGTCATACGTATCGCGCCTCCATTCCTCATTACCAACTATTGAGCCATCTCTTTAAGTGACTCGCTAGCCGGGGTGTGCCAGGGGGCCTGGACGCCACTAATTCTATCCGAGTATTGCTAGATTGTTTAAAACCTCCCGTCGTCACAGTTTGCTAAATGCTCCGAACGAAATTCCGGGTAGGACGGTAGGGGGTTCAGAGGGTAGTATTGACAAGTGCGAGATGCTAGGTATTATTCTTAGTAGAATCCTGAAGTTTGATTCCTTCGGTCCTGGACGTAGCAAGGATGCGTGCCTGCCATACCTTAAAAGATTTTTAAACTGAATACCTACAGGACACTCAGGCCCCCACAGGATATAATTCCTGCCTAAAAAGCGTCCCTTCTATTCTGTATAAAGCCGATAAAATTGGCAGAATGCCTGCCTATTGAATGATTAGATTTCTTGATAGATCATTGCAATAAATTCTAAGACCACCGGGAGAGGACCGGCGCGGAAGTTGTTCTATGCTTTGTTCGAGTGTGGGTACTATGTAGGTTGAAGCCCGCTTGGTTGGATGCGTGACACGCGTTTAGTTCAATAGAAGTGGGAGTGCAACTCCCCTAGGTCGGATCCCTACTCTACAGTTATACACAACACAACCAACATTCACGCACGATCAGGGCTGTGTGCAATGGTAGTTGTCCAACAATTGCTATTGCTGCGCGATGAGCAACGGCTATTTAGCGCAAGAGCGACTCAAGGAACGAGTCATCATGACCATAACTTGCCAGGCCCCTTCTACACAGAATAAGCCGGCTAGGTGCTTAGTAACGGCAGTCGTTAACCTTCTTCGAGCACACTATTGATTCCTTACTCCCATGGCTCTGGAAGCAACCAGCTCCACGTGGCACCGGGTTCGCAGGGGAGGTTTGATCACAACCCTTACGAGATCCCTCCCATGCGACGCAGTCACGTGCAGAACGTGTATAAAGATCATCCATTGTAGCGTAAAGAGCGGAGTGTGTTAAGAATCGATTTGTATCGAGATTCCCTATACAAAAAGGGGTGGTCAAACTCATGTGACCGAATGGAAGGGTAGCCGCAATTGTGCTCTGTCTTTGACATACGCTGCCTGGGGGTATCGTGTCATTCTGCGCCTCGCAGGTCGTTCCCTTCTGACGACTAGTACTGATTATTTTCAAGCCAGACCGTAGACTAGAGTCCAATCAGTCAGCCTTTTAATGTCATGTTCCGCCCTCTGACGAGTGCATTTGTATATCCAAGACAATCTTACCAACCCGATTTTGATGAACGAGAGGGTTTGATCGACAGATGTGAAATGTTACATAAGTCCCGCCAACGCCACCCGACCTACAAGATGCCACGGTAAGCATCACCCCAATATAGTCGGAAGCATATCGTACTACGTGTTGACTAACGGACCACCGCCTTCGACCATGGATTCACAGCCTCAGCTAGGGCTCAGAATAGGGAAACAGACGTAATTTCAGTTCCACCCTTGCTGTTATTCAGCGCGGAGAAATTGTCAGACAACGACACGGCATCTCAGCTACTCATTATGTAGCAAGATATCTTCCGACATGGGGTATTTGCCAGGAAATAATTTTCCCGAGACATCTAGTAGCCCGCTTAGCCCTCGCGTCAAGTCAGGGGGTCCTTTGCCACATGGTTCTACAATATACGGTAGGTCCACGCTTATGAGCCTAATCCTACTCGTGTTGGTATAGGTGAGGCAGGAAAAGTGTCTTCCTTTGTCTCACGGGGTTTAACATGCGCACCTTTAAGGTACCGCGTTGAGCATGCGGTTCATCCGCGGCAGCGAGCTGCTAGGAGTTCAGCAGATCGAGCGTGTCTTTGTCTCCCCACATCCGTAAGTTCCTGAGCGCCGCGTTATGGGGCTCGGAGACGGACCTTGTCACAACAGTTGGAAGCCGGTATATTGTGTTAGGTCTGAGTGGTATTCTGACAAAGGAAATGCACTGTGAGTAAGCCCCTCTCAGGCGGACACCTGCGATGTGCTTAGTCCCCAACGATGCCCCTCAACGAGAACGTGCTTTAGGTGACCAACCGCCTGCAGTTAAATATGACGGTTCGACACAGGTAGGTTTCCGCCACCACTGCATATCCCTATACTGGACCGGTGACCCGGCCGTCCTGTTAACACTATCTCCGAACAAGTTTCGAGAGTCTGGACCCATCCTTTCGCGTACGGGATATCGCGTGACTCTCGGACGGATCACGTTGCATGATGTCTAGAGTTGCTTAGGATTCCCAGCCTTCTCAATCTTCTACCTGACTACGCCCGCAAGCCGACTACTTAACCTGTATTTGCTCCCCAGAGGCTGCAGATAGTAAAAGATGTGTGGAACCGCAACAAGGACGAAGCCGATCACGCTTCGACCTCTTGCCACATTGCGTTTCTTCAGCTGATATATGAACTGTAGTAGTCTTCATCTCGGGGATACTAGCCCTATAACCTGGAGCGCAGTTGAAGGTGCAATATCCTGCATGTAGGCGACCGCGTCAGATTCCCCCGATCCAATTGGAGCAGGAACAGTAAGTCCGACGATCCGCTACGTTTCATGCGTGCCGATATGTACACGTCCCCGTTTTTGATCCTGGCACATGTGCTTCGGTAGGGACCAGGGAGGTAGACCTGCAGTCGGGTTCGTTAGCTCGCAAAGCATTTGGGCTTGTACTATCTACAGCTGGGGGGGGATATCAGATACATAACGACCGTATGGGCTTGCGAGAACCATGGCTTCTCGAAATCGACCTCAAATCCTTGTCGGCTCTGTTCAATGGTGGTAACCGCAGCACTGCTTTAGGTCATCGGTGTTAATATGCTCTGTCTTTGCTGTCATTAGGCGAGTGTTACGCCTAATCTCAATCTGAAACTACGAAAAATCAGAGTCAACATGTGCCAATACCCGGACTGTTATTGTCTAGGACTGGTCAGACTCTCCCCGCCTTACAATCATCAACAAGATGTAGCACCGTTTCTGCAAATCCTACCGGGCTGTGGTTACACCGCGGATCGTGTCTACTTTGACCGAAATGGTCTGACATTCAGGATAATTGGCGCGCAAAGTACCCGCTCAGGTTATATGCTCGATAGGGCTCTGACGTCAGAATGGCTATCCGTACGAGAGCGATATGTTGTAACACCGAACTCTGACCTACCACCTTCTATTGAGCCAATCATGCGAGACTTGGAAATCAGTGTCTTAGAGGATAAATAATCATGTATCAAAGTGTTCATCCTATTATGACCCTGTTGCTGATGGATACGAGAGGGTTTATTATTTTCAGGGTGCATGCCACCGTCTACCGAGCCCCCACAATCCGGTGACAGCGCAACGTCGTGGAGATGACTTGCTTTCCCTCAGGACTGAGCATGTTATACCATTGGGGCCACCGTAGTGCAAACATAGCAGTAAAGGAATTTAATCTTGTCCGGTCACACGTGCGGAGATGCGTAACTGAGGGCCCGAAGCCGACTTCCCGGCTAGGAGCCTCTCTATTCGATTCCCATTCCAAAATCCGCCGGCTTCCGCTGTCCCCTTAATCCGCACTCAGAATACTCTCGAGCTATTCGGGCCCGATAAGACGTCGGGTATGCTTGCAAGACGTGGTAGCAAACACCGTTTCTATGGGCGTGTGGAGAGTCACGTCTGGTTCCATGATGGTATCCCGCTATCTCTTTTCAACTCCCGGCGTTCAAAGCCGATTACCGTCCTAGATTCCTCTGTGAGGATTAAAGGTGAGCCATTCCATCGTGCTCCGTGTGATGACGAAGGAAATGACGTACTAATCGAGCTGGATTAGGCGCGTACCTAATTCCCGAACTTGTGAATGTTCGATTTGGATCTGAGCATCTTCACCCCTGTCATTCGCTCCACCTCCTATTTCTTGTAAATGAATAAGAGACCTGGATGAAGTCATGTCTCCGGCTTATCCTTGCAATCAGCTGTCTGTAACTGGCACGAATCCTATTGTGTAATCTCTGCTTGACATGGGTGTGCGTTAGTCGAAACTATCACTATCTCTCTTATCCCACGGGCTCGCTTAACGTCACTATCCAGTAGGGAACAGAATGGTTAATTTCAAGAATGGCAGCCATGTGGTCCGTCCACGCCTGCTGAAGTACGCCGCAGCAATCATCCGACCGGATCTCCCTGCATTCGAGCTATTCACAAAAATAACAGAGAACGATATTTTTATGCCCAAAAAACGCCCGACGATCGCCACGCGTGATCACACTAGTAGCACCGAAATAACGAGGGCGAACCCTCAACATCCGTATACAATTCTGTGCCGGTGAGGCAAGATGCCATGTTATAGTTATTAACGAAAAGACGATGCTCTGCGTTCGGCATCGTAAACGTAGGAACGAGAGGGCCCATACCGGTATCCACCTGGTTGAGCCAGGAAAAAAGATCTCAGTCCTGTCAATAGAGTATTTCATACGTCAAGAAAAAAGCTGTGAAAGTCTCACTGGGTTGGAGTGCTGTCCTTATTAGACACTGGAGGGCCGGGTCGGCTGACCGCTAAGCCACCCAGTCGATCCCGTTCATCCCACCCCGCAGAGCGTCCGGCTATATGGTAGTATCCCATCGTTGCACGTCTGCAAGTACTGGAGCATCCCGAACTTCATAGTAGGTTGAGCTTCAAATATGCCGCCTCTACGTTTTTGGGCATTGTACCGCAAGGTCTATAACTTTGGACGCGACAGTGCCTCGCGGTTGCAAATCCGGTACTTTGTAATATGGACGTCACGATGATTGAGGATGGGTCATATTACCCTTGTCGTGAGACCGCTAACGAGCGCACACCCCAGAACATCCAATTCGCATAATCTCCTACTTCAAGCCATACCAGTCTCTATGTCTATAGGGCTGGAGCCTTAGGTCATGGCACAGTATCAGGGACTATGGTGTTGGAATGTTCGTACTGTATTTATAACTAGCAGTCAACGATCCATCTCGAGGAGGGACGATGTGTAACTTAGACTTCTATAGTCGTGAATCATACTGGTGAGTCTGGCTCAAAGATTTAACCTGAGAGTCTTTAGGCCTCTGAACGTGGAATGAAGTATTTGAAATAGAATTCGATCTTAGAATGATCCCTCACGCGCCCTGTGTGCAGAGTAGGTACCCGCATGTCGTGCGGCATGGCCGCGGAGGTGTCCGCGACTTCCGGTGTGGCAACGGTTGCCTTGTGAGGACGCATCTTAGAGTTGCCTCAGTACCACCCTCCGAGATTGTAGGCATAAGGCTGTCGAATCTACGAAGCCAGCAGCTAGCACCGGAAGAAATAGTTATGTAGGGCACGGGGTTCTATTAGCCCCTGGCTCTAATCAACGAAACGAAGCCGTTTCTAGTGGTTAAGCCAAAAATTAACGCTGACTCTAGGCATGCCCTGAACTTGCCACTACGTTCGGCTTGGAATCGAACCCAACGAAGAGTAAGGTACGTAATGCGTCTCGTGATGACTTAGCTGGCCGCGACGCAATCAGGCCTCGTGGCAGGCGTCGATCGGGTGAACACTTTTTCGCTAGGATACCTGAAAAAAATAGTCGACTCACGGTGTGGACGGTTTTTTATCCAGTGGCGGCGCGTATGCACGCCACCTAATTATCATTGCGATTGGGAATATGAGTGTCTTGGTTCGCACTTCACTAAGGGCTACTACATTCGCAGAGGAATACAGAATACACGATGACCGTACTGCTCTTTGTAAACTTCGAGACATACCTTCTGGCTAGCCGATCCAGCTTCGGGATATTTGGCGAGTCAATCCAACACGGGTAGAAGAAGGGGATGATAAGGTATTCGGCCACTGTTAGGTTACTGCAAATCGCGGGGCTCCCGCTCTTGAAAGTACAAAATTACCTAGCATCCGAGTCCATGAGAACTAGCCTTCCGTTCGTAATAGTGGGCGCACTCAGGTGGATCCGGCTTGCATCGAGATCAAACATCCTTCGCAATCGGCCACGGCATGGGCTAAGTCGTTATCCAACCCATAACGCTGCAACAATCGCCCGGTCACCCCACACTAACGTTCCATACGCGTCTATGACGAACCTATGCACCTAGATCCTGTGCGGACGTGATTGTTGCCCTTGAAGTTGATATTCGCAACGTTGCGTTCAACCAACAATCGGCTTGCTTAACAGTGATATGATAACTATTTTCACGGCTGCAAAGTTACTTTTCATACTGGATGAACCACAACTAATCTCTCCTGTCACGGTCGCCATGATTTCAATAGCACGATCCCTGTTAGCACGGAGTGCCTTTATACGAATCATACAACAGATTCGACTAAACCGGGACAGTTTGCCATCTAAGAAAAGATTTAACAAGCTCGGTAACCAGACACTAAGTATTTGTATCGCAAGGTGATTAGAAATGGTTTTCTCACGGTTGGCCCCACACTTTATGCTTCGAACTCCTAAGTAAACTTTGCAATACCAGACATCAGTGATCCTGCTATATTGTGGCTGGCGGGGCAAATGGCGGACATGGACCCGTAAGCGCCCAACGATTTGCCCATAAGTCCCGGGGTAGCACGGATGGGGTCTATCAATCACTGTGTAGTCGTGCTGCGACGCCGGGGAGAGTTCATTAGTGTGAGCTCTCAGGCAATAGCATAATCGCACGACCACCCATAAGAAGTATTTGCCTCCTCGTTTAGCGGCTAATTTTGAGTCAGGAGGTATCATCTTGGCTTTGTCAAGCCTTTCCTGTCCATGAAGCATAGTAATCTGAGTGTACAAAAAGCCATTTGCTGCATAGGGTAGTGAATAAGCCAACATGGGGACTTACCTTACCGTGGGATTCCATTCAAGAAATTCTGGGGTGTTGACCCACTTTACGCCAACTGTTGGCGGATAAGGCGCTACGTGACTGCCCACGTGCTCGGCACGACTATTATTCGATCGGAGGGAGCTTAGTGGGCCAGCGCCCAGCTTGGTGAAACTAACAACAACCAAGAGCACGACACTCTGTCTTTATGGTCTTCAGAAGAGGCATTCCAAACCGAGTGTAGAACGTTACGGACGACCGTTGGTACCTCAGTAACCTACGTCACTGTCAGAAGCCCTGGTTCTTGTTTGCCCGCTTCCTTAGGTAGTCAGGGAGTGGCGTTATTTCTTGAGCCAGCAAACCCTTTGGGGGTCCGAGCCTCCAATGCCTAACGTCCCCTCTTGACCAGCTGACGGCCTGGAGGACAGGGAACAATTGGCGTCATTGACGAGAGATGTAGCTCGGTGATTGAGCATTGGACTGCCAGGCTATTGTTAGAGCTCCTAGAGTATTCGCGCATTCGTAAGAACCTTCTGATATATTCGGGGTGTTTATTACTGAAGGTGGGGTCGCTTACCGCTTGTAACATTGCTCTTGTGGTGTGGATCGGGGTCCGCGGCTTGGTTGGTTAACCTGATTGAGTCATACCGCATTGGTCAATACTGTCCCACGTATACCGTGGCACTAGAATTTCTATATTTTACACTGAGGAAGAACAAGTTAGCGTGCCGAACGGGGCATTTTGCGGCCCCACCAGCCGGGCACATACAGTGATAGGACACATCTGGACTCCTCAATGAGTATTGTATCAAGTGCGGTGGCACCAGCAAAGGCAATAGAGGTCATCTGACAGTTGACGTAAGGAACGCGTTCCATACTAAAGTCCTTTTCGAAGTGTAGCTCACAGTGTGGGAGCGCTTATCCCTGACCGAACCGTCGGCGCTACGTAGAAATCCTAGTGTCCAGGCAGCACGTTCCAAGTTCGCCTGCAACCCTTAGACGCGATGCTGGTTGTAGATAAATAGTCATGTACCTGACGGCCAGAGCATGGTCTACTCACCTATAGAGAACTTAAGTGCGAGAAGAATGCTAAAGTCGACAGCTTCAAGAGTGCAGTAGAGAAAGAGATCACCGACGTTGTTCGTTTTCTGCGAAGTCTGGCCCTTCGCCCAGCGCACATGCCTTCGTAGAAAAATCAACGTGGACTCGCTTTTTAACTGTTAGTTTTATGCGCGCGAATTGGTTTAGGACGGTCGTGTGTGCGTACAGGTCGCGGTGGTTGTTCCCTGACGCAGATTCCGCTCCAAGTGATGGACCGTGATCCGGCTGGCTATAATTCGTTCATCGGCTGTATCCATAAATCAGCAACGGAAGGAGCGGATTACTTAATGTACCTTTTCTTACCTGTTCCAATTAGCTACAACATCATTACACATCCGTTTTGGATACAAACCTAAGCTGATGACCGCTCCGGGGGAGCTCCACGTGTTGGGTAATTAGAGACTCTCTCCAATGATTCCTATCTCCTCCAGCCTATAGGACCAACTGTACGTTCATACCTAACTAGTGGGCTAAGACTTCTGGGGACGCCACCGGAGCGCGAGTGATCGTAGACAGGCTCGCAGGCGATGATGCTAGTCTTCTAATGCTTGTTAATTTGGCCGACTCTAGGCTTACTTCGCTCTCCAGATGTATTACTAGTGCAGGGCCATGTTCTTCGAGCTTACAACGTGGAGAAGCCCGCCCCAAGACAGTCCACGTCAGACCCACTCGATCTCGGGGGTGAGGAGGACCGTTAATTTTAATCGGGGTGATTCTCCACCTCTTAGTGACTAGGCAACCGCAGATAGCCCCCTAACGTGAGCCTCTATGACTGCCGTTTAATTTTCGGCCTTAGTTGAGAGTAGCTTTTCCCGTTAAGAAAGACTCGATCGACTATCCGTACTAATCTTTCAAGCGGCCGGTTCATTTCCTCACCTGGCACTAGCCCAGTACCCAGGTGTTCGTGTTTATTTGTTGGGGCCCAAAGGCCTTTCGCATACCATATTAGAACACAGGTGCAACCCTCTGACTACCCGAGTCCTCGGAATTCACAACATTGGGTCAACCTAATTGCCAATGGCCGAATCTGCGCTCCCCTGTCGCTATTGAGGCGATGCGCACTATCCGCTACTGATACCTCACGGCTGGATGAGCGACGAACATAGCACAAGCAAGTTCCTTACGGGTGTTAAGCCGGGACGAAAATCATAATAATTCCTTACGCGGAGCCGCGACATTAGGCATTAACATAATCCAGAGGCTAAACGGATCCACACCCACCTTCATGCATCTAGTAAATAGTTGCGTAATATACGACCCACAGACCCGACCCACAGAGGCGTTTTTGGGGTTTTCAAGTACGCCGACCCCCCTCTTCGCAGGGTGCCGGAATTTGTTGTACCCACCCCCGCTTCCTTGCTAATTCTCTGATCGGAATGATTACTCTTGCTCGGTAGAATCACATCCGCTCGGCCCTGGCAAGGTCTGACACAGCCGTACGTTGACGTCAGAATAACTAGATGATCCGTTCTCCAGACAATATATGCTATCTTAAACCTAACCTCCCCTGGGTTGCGAATCAGGACCACTGGAAGCCGGCCGGCAATCTGCTGAATGGTTCGTCTATACAACACTGATCTTTTCCTTGGCAATCGGCCGAACTTGGGCACGTGACGACCTCCCCCCTGATGGTTTTTTTTCCGATAGCCGGCCGCCACAGCTCAATCATCAGTGTGCATGAGGAACCACTGAACTAGCGTCGTTGGTGGGAAAGAGAAAAAAGCCGTTGTCTCAACTCCGCCATTATCCTTCGGGCGGTCGCTGCGTTCCCCTAGAAACTTCCAGAGCAGACACACCAACCTGAGACTTAGATAAGGAACAGGAGTATTAGACAGCTAGGCTTACGACCTAATCTCACGGCCATCACCCATCGTAACCGGACCGAGGTTGTGAAGCGGCCTTCCGTGCGTGAATACACATCGGAGAAAAGAATAATCTTGAATAACCCCAAGGTGTCGCCGTACGGAGCCCTAACAGGTTTAGGATGGCATCTACCGGGCGACGTCGCACAACTCTTATGGAGTTGAAGAAGGGACGATAATCCCCGCGCTTATAGACGGGTCTAATCTCGACAGCTATCCCACTTATTAGCCTCGTCCCAGCAATAGTATTCACTATAGTCAAGAGTTCGAGTATAATCCTATTAACCCTATGGCGGCGGACTTCGCCACTTGCGGGAAGGGGGTGTGTAACTACGAGTAAGGTTACGGAAGAAAGTGTAACAAGTTGATCGGGAGAAGGTGCGCAAAACAACAGAAAACTCTAGCGATGGGACGATTGAGCCGTAGTCTAGGGTAGTGTTTGCAGAAACCGATAATACCGTCGTTAAACATTCGGTTGAGAGCAGCCCAAGCATGAGTAAGTGGTGCCCTGCAGAAACGGCTGTGTGAAGGACTACTCGTGCTTTTAGGAGCACTATAATTCTGATATCAGCCCGGGGTCGTTGGATGATATCCCTAGCCGTGGAATGTGCAGGACATAATTAGCAGTAACTAGCGCGCTTCACCGATACCCGCATCCGGTGATTGGAGTCAGCGGCTTAACCTTGTCTAACCCCCGGACAGAATTAAGGACGCATCATTGCATTCCTACGATTCCTCGACGGAAGCTTGAGAGAATAAAAGTGAAACAGTTCCTCTACGGGCCGGAGCGACCTGGGTCGGTAAAAACTTGTCTTGGCGAGTTACTCCGGGCTGAAGGAGATGATCTTTGCTCCCCCCGAGGTTCCTCGGCCACATCCGCGCCTGTTTCATCCCCTCAATGCGCACGGAACTACTATAGGATCGGTCGTCCAAGAGCTACGTGTACTTCTGACAACGCGCGAAGATAGACAAAGACGCTGCTCTTTTTATCATCTCTCTTCCATCAAATCCGCCTGGGATAGTCACTGGCAAAAACGCAATGATCGCGTTAGTAACTACAGATTCCGACGCGTTGTAAGTGGGTTAACTTTCAAATCTAAGGACAGCATGCGTCAAGTTCTCCAACAAGGGGGACTGAGAGTTAGCTTCCAGAATGCCTTGTAGGCAATCAAATGGTACTGTGATAAATATCGACAACAGTTGGACATACCTGTACCAAGACCGCAGCAGTAGACTTTACCATCAATCTTTTAATAGGAATTAGGCACATACTTCAGCATTCCAAGATAGAGAATGGTGCCCAGAAGCATCTAAAGGAGGCCAAGTACTCTCTTTCTGAGTCCTGCAACATCTAAAATAGTTTGCTGAGCATGCGCCAATACTGGGCGAACAAATGATTTCTGTGCGTTGGAGCCGATATGCGCAAACTAACCGGCACCTAGGGCACTCGTATAGTCCGTTCAAGGAACAGGGTGGTACAGTGCTGGGGAGATAATACCCGCCGGTCGCACGGGTTCCAATTGAAAGTCTGAAACTACTCGATCTAGTCCTAGGCAAACCCCTAACGAGCTTCAGTGCGTCGCTGTCATGGTCGGCCGATGAGCTAGGACCATGGTCGAGGGAGCTTAATTCACATGATTGCAATGATTTCACGCTAATGATTAGTAACGGGATTGACCTCTTCAAACCCGCGGTGGTCCAGCAGTCTACCTTTTGCTTATTACAAACGATATCATCCCAACCGCACAGGTACTCCGTACTAAGATGTTCCTTGTTTTAGAAAGGAAGCTAAGGGTAGACTTATGAGGGTGCATCTCGGCATATGCAACCTAGATCGCTACTTGTTCCACAAACGTCTGAGGCTTACCGGCCCATCGTGCCCGATACGAAGGTAATTTGCGCCATGGGATCCTTGAGTCAATCTACTACGCGGGACAAACGCCCTGGCGTGTAGTGGACAGTACTCAACTAATGAGGGTTTGGCTTGCTACCGCTACCCGCACGCTGTAGACCTCTACTCGCGCGCAACGACTCTGGAGAAACTCTATACAAGACCGGGCGACGTGTTTTCGCCTAGATCAAACGGACAGGCGCCGAGTTCCTGGCCCCATTGGTGTTATCGAAGGGTACTCATCCTGTGCCGGATTTCGTCGCGTCGGATATCCTACAGCAGATTTAGTCCGAGTTTCGCGATACATAAGTAATCACAATCGCGCCTAAATCATCCTAGCGCTTGTCAATCGCCACACCTTACCAAACTCCTTAAAGTTGCATCCCGTTCCGTATTTTAGGTGTTACAACTATAAACCGAAAGCAGGCTTTCGGATCTGTTATCATACGCGAAACTTTAAGATCTAGCCGGTCGATCCATCCGACTAACGTTGCGGAGGACGGTGGGAAATTCTAGGAAGCGAAAGGGTGCCTAGTGGGCCAAAGGTCGGCCGAGCTAAGAGCATCCAACACACCTCCCATGCTAGGATCAATCAGCAATCTAATCCCATCCGATACGAAACGGCGACAGCCAGCCCCGTTTTTCCCTGTTATCTGGTCGCGAGGTACGAGACTGTGCAAGTCGACTTCACCGGTGTACAAGAGACAACAATCAGTCCATTAATTGGTTTTCCGCGACACCCTATGAGGTCGGTTCTGCATGCGGCTCGAACTGGTGGTAGGTCTTCTCCTAAACCCTACCTACGGCGGCGGCCCCGGGGCCGCACGGGAAAGCGCGGGCCGTAGGCAATCATAAGGACTAGACGAGCAGATTAACTTTTCCCGTTTTGGTTGGAACAACAGTTTATATAGTCTGTCCTTCTGCTAGCGTCTGTCGTACAGGCGTGTGGCATGCTTAATCTTAACCATTTTACGAGAGTCAGATATGTTCCTCAGGACCGTAAGGTAGGTCACCTCCTCTTGTGACGGCTGTCTCGAACGTACCGCGTCCGTTGAGGGATATCTCCCGAAGTCGACGATTGTTACTCTGACGCCCGCCGCCGTTGCTGTAACCACAATTGCATATGGAATGATGTTCCATTGAACTAACGGTGTGCGAGGTCTTAGTTTGCACGAAATCCTTCGGGTAGATGGACGGAACAGTTACAGCGTGAGCGGACATCAACGCCAACCGTAAATTGCTAAACTTCTCGGGCCGGGCACGCCTGCCGGGACCCGTTATCCCATGGTCCTGCACAGATATACGGGCAGCCGACTCAAAAGAGCCGCTGGGGGTTTTTCATCAACCGAGAGATTCCGTCTGCCAAGCATAAGCAGACAGGTACAGGTGCCGCCTCGCGACAACTTACCATCTCTGACTTTTACCATAATCATGACGCGCGATCGGCCGGCCAACGCACAAAAGGTAGACCATTCGGCATACACAGTACAAGAAGTATGGCTATACTTTAACTAAGCGTGGCCATTATTCAAGTCAATTTAACACAATAACAAAAATCTCGCATATTCAACTCGCAGTAACCTGTTTATCTACAGGTACGGCCTGTTTGCGTGATGAACAGCAACAATGGGCCCATGCTAAAAGGTTTGTTTGGCTACACCTTATGGACACCATGGCTAAGCAATTCTAGTAAGAGTCGCTTAAGTGAAAAGTCCAGATACTCATGTCGCACAACCTGCAATAACCTGTGTGGCTCACCCATTTGCATGACGTGATCGCAGTAAACTCTCAAGGAGGTTTAGATGCGCCTTCCGTTCTTTGTGGAAGCATTGACGCGGCAAGGTTAGAGTGAGAGTCATCCGGCCCTCTCTCTCGCGCGATTCCTTTTAGGGCGGGACATACGGATATTAGTTCTGCCCGTATGCTTAACCTCGTTTTAGCTGTTTACAGCGACTAGCCTTGCGTGACTTCATGATTCCGACTGTCCGATAGTCGTTTATGCGGAGTAACTCTTAAAATTGTCGCCGATTAGAATCAGCTGAGGCTACGTCGTGTCAAAACTGTCAGCGGAAGCTGGCTATAGGCGTGAGCACATCCGTTTGCAATGCAATATTGCATAAGAATGGAGGTTCCCGCTGCTGTATTACGTGATAAAGTTTCTAGGTCTCCGCCGGCCATATCAGTGGCTGCTTAGGTGGTCGGGATTCGGGGTACCGCCGGGGCCAATTCTAATATACGTAGGTAAGCCGCTGAGCAGAGCTCTACGCCGGTGGAGTTCAATCAACGGAAAAGTACCAGTACAATATCAAGCGTAGGCGATTCTTGGTTTGTTGAGAGCAAAATTCCTCCTATCCGAGAGGCCACACGCAACCGCCTAAACCCCCATGGCAATGTATGTCCAACGAAAGCTCACCTTGTGTATATCAGTGGTCAATGGAACAAAGTGCAGTTCATCTGCACGACTCGGCGGCGGGGATTCTGACCTCTTTTATTGACGTTGGACCTTATCATTGACTGGTCCAAAGGCGATCGCTCGTGATATATGAAAAGGCCAGGGTCAAATAGCTGTTCCGTCGCCGCTGAGCAATTACCAGTATACTCCGTAGCGAGAAGAATCAAACCTGGTGCTCTCCTCCATAAAGCCCGTGCAGCTGCGTGAATGTGCCACCTGGTGGTGGTACGTTCTTCCAGGATCACCCTTGGTAATCGTGGTGACTCTGAAACAGATGTGTCGTAATGCTTCCCAACTACAAGCTTAGCTCATCTCACGTGGGAGTGTAACGCAGTGTGGGTGTTATAAGACATATGCCATAAGGACGCGCATTCGTCTTGCTTAACTAGCTTGAATCTCTTTGGCGCTCGCTCGGGTATAAAACCGCCTTGGTGATATTTTCGAGGGTGGGTAAGCCTAGAAACGCATATAGCGGTCGAGCTTCAATCCCCGTATGAGAGTGCTCATACTCGGGGGGTTGATGTAAACCATCCCCAACTGGACCGTGTATTACATTGTACCGACCTTGCGGTATACTTTTCAGGTCGTCAGGCTGAGTAAGTGCCAGTCAGCGGAACCCCGCATGCAAATACGAGCGTAAATGTCGCTAGGTCATATAAAAGGTCCTCCCACCCCAAATGGTCACGGCCCCTCCAACCCGAGGTGCTATCTCCCGTGCACTCCTTCGAGGTTCCAACGCTTGATGTACACTTTATAAACTACTAGGCTCTACCATTGACGTCTTATTTACTGTACACACACCCCTCTATCCAGTCAGAGCCAACCTTCGGCGTCCTCCTATCTTGGAGTTGCTTTTTGTCCGTTTTTGCCAGCACCAGCGTGGGAATCAAGATGAGTCATTGTGATACTCTGTGTGGTCATGTGGCTACTAAAGGCACGGTCCTTCACGCTATTGGCAGTGACCCGCCTCTGCTGTTCCAGACATAGTATGAACATCGCTGTATTGAGCCGCTGACAAGCTAGCTATCTCAGCACAGCTAATATGATTAAAGGGACAATCACTCCAGGTTTTTGAGGAAACGAGCATCTCTCCTTGAAGTGTCCCGGCCAAACGGTCCTAAAACCAGCGGTCCGACTTTGAGCGCGCAGCGAGTTGTGTTGAGGATTCGTGCTCTCTTGGTTCCGGTAGGAATCCTTCTTCGGAAACATAAGATCCTTTGCGTGCTAAACCAAGGGTTGGTATCGTGCACGCGCGCTGCCGATTGACGGAAGAAGGCACCAAGAGAATGACCCCAAAATATGTGCGGAGGAGAAGGCATGGGCTAGCGGTTTCGCTTTTTCTCTTCGCGAGCGTATACGTGATACGCCATTGCGCTTAACCTTCATTACAGGGCGAACTTTACTCCGGTCGCCAGCGGAGGCTAATCTGGACTTCTAAATCTCGTTTGTCAACGCGCTTCATACCCGCTACGTCCTGGGTTATATCTAATAGCGATAGACAAGTAACTCTGATTGGGGGGTTGCGGGCTTGTACATCCTATTGAGGTAGAATTATCTCAGCCTAAACGCAGGTGGCCCACTAACCGGCGAATAACGGTTGTGTAGTGTCGGCCACACCGGCCACAATCCAAGTCATGCGTACTTAGAATAGTAGAGTGACTGTTGCCGCGTTTTCAATAGGCCCATAATGGTACCACTATCGCGTCCCGCACTATTCCATTCATCTACGCTTCTATGGACGCCAGGAGTGATGAAGCTCATTCTGACACCGAGTGCCCACGCAATCAGAGTTGTGTAGTGGCCGATTGGCCTACCAATCACTGTGCTTCGCTATAGTGTCCCCCATAATCTAAGGGGGGATCCTTTAATCGGTCTCCTTCCGTCGCAATGGCGGCTGTTGCTAGACGGTATGGAGTAAACGGCTGCTACAACACATCGGAATGACGTTGTAGTTGGAGTTCTAGCCGGCATCCGTCAGAGTAAGCCACCAGTCTAGGCTGTTTGTATAATACCTTTATATTAGTATCATAACGCATTCAACAGCGCTCAGACGTCGGACAGTTCTACCTCAAACAAATCTCCCGAACGACCTCGTCTTCAGTGAGAACTTACTCTTTATCCACGCTCGTCGGAGCCGACCTGTTTCGAACAGGCGGGCGGTCTCGTCTGCGATTCAACATCCAACTCGACGGGCCGACAGCCTGTTGCGAGCTCTAAAGCCAGGCATCAGTGAGCAAGCTTGAACTACGCGTTGGCCAATTGACCTCAGAGGGCAGTCCCTTAGCGGACGTAGCCCAGCAACAAGACATCAATAGAAATTATGAGTTAATAATGGGCGCCGATCGAAGATGCATGTCGTGAATAACGAAAAGGAATCTATAGCCCCCAGTGGCTATCCAGACAGGCGGATTCCGGACCCTAAACACAAGTAAAAGTGGCGAACTTCTGAGGCATTAGACCGCGTATCAGTCAGGTCGACTTGGGGCTATTTTTCATCGTCAGCAGCTCAGGCTTCTTAAGGTGCTTTGTCCTTGAGCACAATCTTATATCTGCTGTCCAGTCCCATGGCTCCGAGAAACCGCGATCGATACGGGGAGAGACGCTTCGACGCATATTGACCCCGTCCCGGACATATATCCTAGGGCCACCGCCTGGCGCAGTTTAGCCAATGCTGCTCTTCTGTGAGCTAACTCTATGTATGCCTTAGACTCGAACCCTTATTTATACGACCTAGGACCAATCGAGTTGGGTGCGTTCTGATGTGGTTGGAAATATCTGTTCAGAGCCAGGAACAGGAGGACACTGGACGGCCGCTTCAGGCACCACATGTTTTGGTACGCAGGCACAGGAGTAACGGGCTTCGGATCGAAGGCACGGGTCCCTGTAGTGGCGGTGTGGCCAATTTTCAGGCGCCCGTTTGGGTGGAAGCAGATCCTACTTGAACTGCGGTCAAATGAACTACATCATCCGATCGGCATGTACTGGCGACTTCTTTTATTGATTCTGCCGATGCCCGAAGCAACACCCACTCCCAGGGTGGTTCCGCACGGGAGTTTACCCCCTGTATGGACCGCTGGAGGTCCGGGGTTAAACTATCCACGAATAGTATGATGGCCAGGAAGGTGTTGAAAAAGGGTGTTCGATAAAGATACGCCCGAAAACCATGTTTGTGAAGTCAACCTACCATGGACTAATAAATCGTCTAGCCTAAACGAATCAGTCGATGATTTGAAAGATGGGTTCCCAGATCCGAGTGCAGTCACTTCAAATTGAAACGCCCTATTCCCGGCCGCGGTTGCACAACACAATTCGCTAAAGAGGAAGACCCCGGCTCGTCCGAAAAGTGAAAGTCCGACAAGTAGCACATGTCGCGATAGCAGGCGAGGGTGTATAAGAATTGCTGCCAAAATTGGAACTAACTGTCCTAACGTGGCAATTACACTGATCCGCCGAACCGTTCTCGAGAAATCGCACTTAAAGACAGATGATTTGTCTACGCCAAGGCGAGGCTTCGAGATGGGATCAACAAGGGAGCTACTGTTGTGGCCCCGATTGCGACGACAAAGAAAACTGCCGACGTTTGCCCACAGTTCCGCAAAAGGTCAGACTCCAGCCGTAACACGTAGACGCTCTAGCTTTAGAATGGCAGTTAGGTTGGTCTGCTGAGCCACTAAGAACGCATTCGTCTATGAAGCCAGCTTGGAGCATCGACCCCGTGTCGTAGGTGTCATGCATTAAGTGAAGCTGCCATGCTAGACGCGGTCAGTGTACGAGACGGTCGATGCTTCATTACATATTCGAGATAGCGTGTTTGATATAGATTACTGCACCTGGGCGGGCGGTCAGACTGCCTTCTGCTGAGAGCCTTCCAGCGACTGGAATATTCAAGCGTACGAGTGGACTCACGACCTATATCATCTTTATTTTCTACACCACCGGAGCCCGTCTCTGAACATCTCAGCAATAATTGCTCAGGCGCAGAGGCCGACTGTAGGTTATAGTGGCGCAAGGCTCAGACGTAACAGAGAACGCTTAATGAGTCGAAGCGGCATTCCATGACGCCGTTACCTTGCCATGGGATAGAGTCTTCTGATAGAGGGGACTTCAGACAACCGGGGATCTGTGAGCGCTCGGCAGTAGTCTGGCTTATAAAAATCCGTCCGTTGTGTGGGCTGCTACGTGGTCAGAGAAGCAGAGTTTTATCCTCCCGGCAAGGGCTATAACTTTTAGAAGGGGCCAGATTATGAGTATGTCATCTGAGCAGCCTTACCCAGGGGTCACGTAGGCCAGCTGTGCAGCTTACGAGTAAGTACCTCTATCAGCTTAAAAAAGCTCTTGGTAAAGGCGACTGTGAGCAGTCTATTAGAATAAAGCTAAAGTCTATTACCCGAACGCAACATTTTTCCGGTTTTGATAGGGCCGGTGCCCGCGTTATCTCTCAGCGGGTTTTCATTCGCCCAATGTGCCCGCGCCCTTGGCGATGGGACAATCTTCCACGTAGAGTGATCGATTCTTCGGATACACACAATAGTCTCGGAACAGGTGACTGTCACCGCATCAGCACTATCCAGATTCAAACCACGCAACTCTTGTCGATGTCGAAGCGGTACAATTAGTTTCGTTCCTGCAGATTGGGTGGAATCCTCATGCCCCGGCTACCCTTAAGGATTTAACCTGAAAGAAATCATAAAATGCCAAAAGACAAAGCGCAGACCGCTGTCAGCAGGCAGCATAGTCCCTATGGAGCACAAAGTTCTTCGACCACCACTCATCCGTAGCCATCTGAGCGGGGAGATGCCGAGGTCAGATGCTATGGACGGCCAGGGTTAGCAACCAGCGCCCTCCCTCAGTCGGTCTCCGACAATTCGGGGTATCCACCATAACAGTTTCTGTTTTCCGAGCAAGAAGTTACGTGGCCCGCCCTGTCTGACATTCGTGCACTGGATTGTGTATGGCACATTCGTCTCTTCACCCCGTATAGGTACGGCACGAGCTAGTCAAGGCTGCCCGTAGATCTCGTTATCCCGCCTAAAGTGACGGTGCGTCTTCGACATCGGCGACGGACCTGCCTCATAAGGTGATTTATTTTATACAACGGGACCCGCCGGTCAGGACGGTGAAGTCAAGGTTCTATCTAAACTTCTGCTGTCGCAGTTCGCGTCAAGCCGAGAGGCATTCGACAAAGAAAGGGATATGGCACGGTTAATTTCCGCGATCCTCACCTTTCGGGCCACCACCGACTGAACTTACTGCCAAGCCTACTGAGCCAATATCCTCTTAGCAAGCAAGGGATTTCGTCCTCAGCATTGTTACGGTGACACACAGACTAGGGTGGGGACCATACTACTGAAAGGTCTCAACGTTCCATTCCCATACCTATACGCTGCATGTTACTCATAAGCGGGTTAGACAGTCAGTGAAGTAATGAGAGTCGGGGGACGTCGCGTGGGCCTAGATCTCAAAGTGCAGACCCCATTACAGAGAGCAATGAATTATATCATATATTTCCGAAAACCCGCCAGGCGTCGTTCAACGTTCACGCGCGCAGGAGTGGTTGAATAAGGACAAACGATTTCTCGAAAGGCCATTGATTGCACGAACTAGAAACAAGTACGGTTTATGTTGCTTGTATGTTCATGCGGTAACGGGTTCTTTACTCAAGCCTAGCCTGACTAGCGAGGAAATTTCGCCAGGGTTGGCCCGCCGGACTACCATATCTTGTGCAGGGAAGTGTGGCTACCGGTAAGCTGTTCTGACAAATTGATCTCGATGTCACTGTAGGCTTCGGCATCGAAGCGGAGTATACAGAAATGAGCAGAAATTGAAACAATCCCTGTATGGATGAACTTACTCCTACGTTTAGAGCTGAGAAACGTACTAGGTGCTTAAGGCGTCTGAGATCCAGACAGTAGTCGGCATACATACCATCCTCACGAGTGTTTAGAAAAATCGGCCTTGTTTGAGTTGCCTCGACCTCACTATACGTATTCGTTCTGAACGTCGACCTGCATTGTGAGGTAAAATAAGCTCGGCTTGTATGTGACTGTAATAGACGGAGTACTAAACTGACTAAGCCATCGCAAAACCAGTTCTAGATCGCTGTGGTTTCGTCCCGTTATCTTGTGATTGAATTTGCGCCCCGTATAGTGGGCACAATGACTATCTGGCAGTCCAGTCGGGACAGGGTTCCTGAGCTGCTTGGATGTGCTCACGCCGGAGCCCTAGGAGGGTCTAACCTTTGTTATGTCCGCACCACCTATCAGACGGTTTTCACGCCCTAGGGGCTCTGGGCAACTAGGAGCGTAGGCTTTGCGTGGTATCGTCGTGCTCTCTTACGCCTCTTATGGTTTATACGGTATTTGCAAATGTCGCGCAGTCGATCTGCAGATCCCGTCATATTCGTGCATAGGAATACTGAACGACTGTTCGCCGGTCGGCGCAATTCTGGTGTAGCGCTCCTTAACTCATGTGCATTACACTACAAAGGGAACAGAAGCCTTTAGAAAAGCAAATGGCCTCTATCTCTTTTGTAAATTCTGGAAGGACGCACGGTCGCATTCCGGATGCAACCGCCCCCCTGAAAGATCTGAAAGTTATTTAGCTTCTTGACCATAGCCAGGAATTAAAAGAGGGAAACAACTGACGAAAACGAGAGTGCGCACTTTTGCGTCTTTCATAAATGCTCGGCTCACTCTCAGGTTCGTCTAGTGCCAGGCATGGATGGCGAGGGATTGTGACAGTTTGCGCCTTGCCCTCCGCACGAACATCCCATGCGAGTCCTATCTGAACGCGCTCGCAACATGAGTAAATGAAGTTGGACGTTCTAAAAAGGGTAGGCCCATTTGCAAATGTGAAGGTAGCGGGATACGTTTTAACTCATAGTATTCATTCGTTCGGTATTAACTAGGTCTGACGTACGAGTCCATAACGGCGATTGGGTTCCCAGGGGCTTCTAACTTATCGTCTTGGCCAGCGGCAGTTGATGACTACCCAATTGGTGAGAGAGGATTTACTTTACCGACGATCCCCAGGCACAGCGTCCGAGGCTATCCTAGCTATCCTGTAAACGTCATGGAAGATCGCCCGAAACCTACCCGCTCGTCAGTACGAGTTGGAAGCGATAACGTCACTCAATTGGAACAATACTGTGTCGAGACGAGGATGTGAACGCGTTACCAGCCGGATAGCGATCGAACGAGCAGGATCGTGGGGCAAGAACAAACGTAAACGTCAAGCCGAACTACAAATTGTTGGACTAAGTGAGCACGCTATACAAATTTGCCAACTTCGCAGCTGGCTAAGCGCGCGTCGATCCAAACAGGACCTACAGTCGCGCGCTGGCCTATCCCCAATAAAAAAAGATATTAGACAGCGAATGCGCCACCTCTACATCTCGGGCCAAGATACATGTTGGTCGCTCTCGCGTACCCCGTAAGTGGTATCACAGCCCCACCAGATCGAGACTCGCGAGGCATCAGCCTGGTTGCCCATAAGAGCATACCCCGTTTCTGTCCCGAACCTAATAGCAGGCTACAGACTTGGCGTCAGTGAAATTCGAACGGCGTGAATCATAAAGAGATTCCTATTATTACATGAAACTGGACTCACAGGCCTCAGAGATATTAGGCGGCTAGCTCATCCTCATTAGTAGCTGCTCGCCATTGGTTCAACGCTCTGACGTGGGCATCGTTATGACCTTAAGCCGATCCTTCCAGCCTCCGCTCACGCTAACGACTCAGAGGTAGCTGGGGACACGCGGCGGGTCGCTTTCCGTGGTAGTTACGAATTTGCCGATGTGTCATACGCGCATTACAGTGATTTGACCGACAGTAGCAGGAGGATGCTATGTGCCATTCAACGGTGCAGTAGGCAAAGAACTTGGACTGACATAATACGTTCGTCCGAAGAATCGTGTTACTTCTAGTCAACAATAGATACCTGAAAGTATGATCACCTTCAATCGAAAAAGCCAGTAATGCCGGGTCGTAATACATGCAGGTCATTGACGTCTGCATTTCTCTTGAGCCCTTCATTCTTCGCCTTAGAAGATTGCACAATTTTTCAGCGGGGCACATACCTGCTTGGTCTCAATCGAATCGAATAGTAGAGACGCCACGCATTATGTGTCTCTTGTCTGATCCAAGTTAAGGCTGTTTATAGGGCTTGTCTTCAGATTGCCGCGCGAGCCATAGACTCGACAGACCACTATGAACGAATACCGGGTTCCAACTTACCGCTAAACAAAGGGTTACGCTGGAGGCCGACGCCCTTCCTCCCGAGGAGAACTGTCTGGCTCTCTATCAATGTAGATTAGATAATAGATGTATGACATTGACTCACTTATTGCGGTTGCTTCCATAACGAGAAAGGGTGTCTAGTGGCCCCAGCCTCGTACAAATATTCGCCCAGTTCTCAAATGTGGTTACGCCTAGGCTCCCAGAAAGCTTTTCCAAACCGAAGTCATAACACTTCTCAAGGGCTACTAAAGTGAATCGCAGGAGGAATTGCGCGGAACTACACTCCGGGATACGCCCAGAACAAGTAGGGGCGCGTCATTTCAGCTCAGCTACTCGTCACTTATCCTTAGTGCTCAGAAACTTAGCTGAGCACTAAGGGAATTTGTCTTCTAATAATACACTCCTGACGCCTGGCGGAGCGTTCCCTTTTTAAACTACGAACGCGCTTATCACATACCTGTTATTTAATTGACGTGTCGTGAAAGACACGTCCTCTTGCTGTATTTTACGAGCTAACGCAGCGGCATGGCGTGTCAGTGTGTCATGTGTGAAACCTCTCGCGTAAGCCGTGCGCGTCTCGCTTCCTCAACGGACGTGCAACTACTCCCGTGTAAGTGATCTCTTCCCACTACAACACATTAGGAGATTGCCCGGTGTACACTCGAAAAAGTCCAACATGAAGCAGGTGGGCACAAACTCAATTCGCATTTGACATTCATCGCTTCGGTCCACGGCTAATCCAGCGCGCCGTTGTTGGAATCCCGAAATGCGACTTGTATTCAAAGCTCACCTCTATTCGCATACACAGAACAAGTGCTGTAGGAAGACCTGGAGACGATCACGGCATGTCTACAACCCCTGCAGTGTAGAGAGCCGTTAAACTCGGGTGTAGTTCTGGTTCGGGCCGATGTGTTCTCGCTACCGATCATATTAATTTTACTAGAAGGCTCCGGGATGGGAGGCTTGCGAGGCCGATAATCGCTCTGCCAATTGCCAAGAGAGGCTATATTCTAGATGGGCTTATTCCTTTCTGAATGATAGCATTAACCCACCGCGGAGGGACGAGTGTCGCAGTCGGCAACGCCCAGGTGGAGGGTTCAACTAGCTCCGACCACGGCAACGCGTGCAGGCACGCCTCCGCCTCGGTTCCCCGGCTCCGACAAGTAGCTGCAAGTAATACATCAATTTGCCGAACTCTCTGGCGTCCTCGTCAGAATGACCCTTCAATTGTCACAAGGTCCGGTGTTTAGAGAACAGTTTGCTATCTGGGATCATAGAGATAGACTACCGGTAATAACTTTGTGCCACAATGTAGCTGACAGTACGGATCAGGCAGTCCTATATCTTTTCCGTTCCCGCAGCCCTTCGAGTAACTCGCGAGATCTAGAAGCTAAGGTCCAAACTCAGGATAGTACCGATTTAAACGGTACACCTAATATTGGACCCTCTCTAGATTTCAATGCATTTGATGTGAGTAGCCTGCTGCCGGATCCGCCGCGATTGTAGATGTGACTTCCTTAATGGTTAGTGACTGAGTGATATATGGGATGTTATGGAGTTTTTTTGTACTCGCACTACTAGTCGCCGTCTTTCATCTTGAATCAACTTTAGCCGGGACTTATGGGAGTGAATAGACCCGGCAGGCGGTGTGCTAATGTTATCTTGATAGCACTGGGTCATGACACGAACAATGCCGGCAATACTTTCAAAGAGTAACCTGGAATTTAAATTTGTCACCCGCGAACAAACCGGCCTAGAGTACATGGTCACAATACCATCGTAGCGCCGCGCAAAGAGGCCTCTTCTGTACCAGCTACGTGGAAGTGGGCGCAGGTCTGGTCGCTAGCGGCGTTGAACGAGCGAGCAAGGCCTGACACGCTAGCTTCTGCATGCGAGGCGTCTTATAAGCTGGCACCCCCTATATGTTGGGGAGCATCCACCCTTCTCAACACATGTTCTGATAAACACCCCTTTGACGTGGTCCTAGCGCGACTGACGCATAGTTCAGGGTGACTGAGATCTTCGGTGTGGTCTCCCCACCACTCAGATTGTTAACAAGCTGGGGTCGCCGTGTTTAGTTTTCATTCGTCGACATACCGCGGTGATCTCAGTAACTCATGAAGCTTTTAGTGACTACGGCGGCGAGTGTTAAAACCTAATTAGTCGCAGTTTCATTTAACGTAGTACCTAGAGAGCGATACACTCTTCCTCCCCGTAGAGAGATTCTCACGAAAAGTTCTGCGATTTGGCGTGTGACTCTCTTGCTCGAGGAAGTCTCTCAGAACATCCTTGAAATACTCAAGCTAAGTCATATACCACGCACTGAGGGAGGAAATCTTTGCTAACGAAGGGGATGCCGTTCTTTGCGGCGAGCAAGGGACGCAGATGTACATCTAGAACTGGATGGCGCTCGTAGAAGAGGGATAGTTTCCCGCAACCTCTGGGAATAAGGTAGTGTTCCCGTTTCCGACGCCCGCGACGAATCTACTAAGTATCTTGCTCGGCGATCCATCAAATTCTGGCGCGGCCCGGGATTTGTGGCTCCATTCGTCGTACTAATTCTTGTCCCATCGACGTTGGAGGCGCGCATTACTTTACAGCAAGCCGTAAGCAGACATACTGATACTCTGCGCTATTGGAACGCTAGTCACCCCATCTAAGACCTACGTCACTCCTGAATGCGGCTCCCCTTCTCGTCAGCGGACTCTCCACTCTACTCACCCCATACAACTCCAACTTTAGGGGCACGAGACTTTTCATGGTTCTAAGCGAAGATACTTTTATCTGACGCAAGCTCAGAGCCCTTGTGACCGTTAGATTGGCAGAATTCGAGTCCCAACTCTTCTGGATGGTAATCGGCTAGACACTTAAATGTACAGTAGACCACAGGTAGCATATGAGAAGGAACTCACGTACCATGGTGGGAGCTCCCAATAAGATGGGCTGCTATACTGCAATGAGACCTCCACATCAGGCGACGCCATACCAGTCGCGGATACTTGCTTCACCTTCAAATTGTACGAGGTCCCGCAGCAGGAAACTACGGCCTTTGTGGGTCCTTCGACTCAACGAAAGTACAGGGTACCTCACACTCTAGTTATCCTGAACTTTACAGTGAGCCACTGGGTGGCCTGCCAATATTCTTAAGTAAATATGGTCGTAAAGATTGACCTAACAACGAAATGGGTAACAGTCACCCGATGGCATCCGCCAGCAATACTTTTAAGGAGACATGAACGCCTTGTGGGTAACCCTGAATTGAGTCGTAGCAGCCCCCGACTACGCGCAGAACAATTCAATCCGCGCGTAACATTCTGCTAGACGGTTTGAGGTTGTGAACGGACTTTGGGAATATATGATCGTTCGACTGGTCGACGCACTGTTCAACTAGACTCAATCCGGTGTGGGAATAAACACCACATCTGCCCTACATCGACACTTTCCGCGCGTTCGACGGTTCGGTGCTACGACCTTTTTGTGATACCCTTTGGGCCTTGTTGCACGAATGAACTACCATGCAAGTAGTCTACGCGTCGAGTTCCACGTCAGGCCGGCGCCATTCCAAAGCTTATACAGATTACCTTGACTCAGGTCGACGCTTGGGACCAAGTGGCGTTGCCTCTGGTCGCACATAGATGCACATTCTCTACAGGGTAATTGAAGCTTGTAAAGTGCGTAATGAAAGCTATTTATATGTGGCTGCGTCGTCGGACTGCCGACATGCGCTCCCACAGGAGGTGCATTTTTTTGACTCAACCCTCGAGCTTAGCTTGGAAATGGCAAGCCCGCCTTATAAGCTTCATATGCTCGGAGGACGGTCCCTGAGCACGAACCAGTCGCAGCACGCTCATGATAGGTTTTCTGGTTCGGTCGGGGGCGCTCAGGATTGGTTCTTGATGGCTCTTGATGTCATAATTTTAATTTGCCAATTATTACCCCTTTGCGAAAAAATCACATCCGCCACGTCCTTCTACCACTGCCTTCTATCAGCAAAGTAGTCAGTTACCCAGTCCCGCACGTGACAACCCTCTAGATGTAATGAGCGTGCCGCCATTGTGCGCGAGATTGTAGAGGCTAGTCAATATTGGGGGCCAGTATTCACACTGATTTGAGGACAGTTAACCGATCCTATAATGGTCCTGCCCCACAGCGCCCCGAATTAGTTGGAGGTAGCACAGGGCTTAAATCGAACGCAGCAAAGGGGCCAATGTCAGTCTGAGAGTGTCCCGGATAAGTCGGATTACCCTTACGAGGGTGCTAGAACCCCCGGGAGTGGTCCGAAGATCAGGGCGTTCGGGTTACGTCTTGTGATTCTGTACGGACTCACCCTGACTCATAAATGAAGCGAGCAACCAATCACGCTTGCGCTCCTCTCCATGGACCTCTTGCTTCGGGGACGAAACCTCCCCACTTCCACGCTCCTTCGGCGCCAAGTGTACATGAGGCCTATACGAACGCACGGATTGTATCAACGGTTGTCAGTTTGCGGTTGCAATAAGTCCAACCTCCAACGTGTTCTTGGCCCCATTGTGTGTCAGTCACATCCCGAGCCACAGCGGCCGGTCTTGGTCACACTCTCGTATTTTGAGATGAAGTTGCTAGAGTGCCTCGAAGTCCCAGTTTTCGTTGCAGAGTCTGTGGTGCTTCGGGGTCCGCACCCCCCCGCCCGGGCCCAGGATGGGAGCCGCGTCCTCGGAGATGGGACCCACCCACCGTCGTTTTTAGAAGCTCACAAATCGGCTACATGCACGGCTATGCAACTAAGCCCGTCGTTCCCTCTGATCGACGTCCCGATCCTCCGGACTCGCACTTAACGCTTTCATATGAGCCAAAAACAGACGAGGCGGCGGCATAAGAGTGTAGGAATCCGTTTCGATCCGACGCAGGGCCGTAAGGGCACGATTCATTCCTAATGGAAATACGCACTCAATTCTGAGCAGCAAATATGATTAAAAAAGTGTCCGGCGCCCCTTATCCAAGGGAAACTTCGACGATATGTGGGGTAGACTTCCCATCGGCGTAGTACCAGATCGTGCTACACTCTCTCAAGGTTCCCAAACTATCGATTACGATGCTTCGAAAATTTTCTCAGCCTTGGCTAGACAATGGTTGGAATCCAAGAGCTAGTGTGCCGCCACGTGATGTTGTGAACCCTGTCTAGTACTCTAATGATTAGGGTATGTGACCTCTCAGTATGTGCCATTTAGGGACACCAAGCGGTCTGGGTCAATTCCAGTGGGGAATACTATCTAGGAACCTGAGCAAGACGAGGGAAGTCTAAGGAGGCAAGTATCCTGTGCGCGCTTTAGTCCGAAATTGGAGCAGAAACAAGTGGTTGGATAGCCAAAGCAAGGTGACCTCCCCGCTCGTCATCGCAACAAAGGCGGTATGACCCGCCCATCATGTGCCCGGAAACAATAATCTGTGTGTTGGGTCTGGAAAAGACATTTACGAATTCCATGGCAATAGTATGCAAATGGCCACTCTTGACGCATTCGTTATGTTGGACGACGTACTGCAGTCTGGTACTAGTCCATAATACATAGGGACACTACACAGGTGTCGACAAGACTAGTGGAGTCGTACGATCGCCCCCGCCTCTGATGGCGATATATCGCACGTGTGGTAGACTATCCACCGACATATTTGGTCCACATACAATGCTCCGCTGCGAGCATACCGATCGGATGTAACGATTGTGCCCAAGTCCGCGTACTAGCATCCGTCCTACAGGCCGCGAGATGTTTAATCCGAGTAGAGCTGAGGGTTAACTATGAATTTTGCAATGGCTTAGCACACCAGATGTTGAGGGGTATTAGTTTCGTACTGTTGTACTTACTATCGCAGGGCCCACCCACGCCCACTTACCTTCCAAGACAAGGTGAGAAATAGCAATGGGCAGGGTGATGCTCTGTGCTGAAGGACGGACAACGTACGTCGAACGGCGTTGTGTTCGACTAGAGTGCAGGGATAGTAGGCTGATCGCCGACACATTAAGGCAGACGAACCCAATAACAAGGCAAGGCTCCTCAGTAAGCACCGCGTCTGAGGCGGCATTCGGCTCAGCGACCCTTGGAATAGGCGCCAATAGCCTAAGGCCGCCAACCAGGATATTCGCTCTCAACCAACCGAGTATCACGCGAGCAGGAGCAGTCTATTATATAGGCAGGGTCCTGCGGGATTTGCTCTCGGGCTAGGGAAGAACGAAACTAGGATGAGTCGACGCGGCGACGGGTGCTGAGTTTCGTGGAAGCTTATGCTTCTCATCGTCGGGAAGTATACATATGCTTCAATCATCTCCTTGGATACTATTCTACTAGGCGATACCGACTTAACAGAGCGGCACATTCGGCTAGGCAACATGTCACATATGACAGGCACCAGCGAGAGCATCAGCGACCTCCCATTAAACACTACGTGTAGAGTCAGCATCTAAACATTATAAACCTTCGTGGAACTTTAATCCGTGCTCTGGTAGCTGTCACCGTTCTAACTCTCGCGAATAAAAGCGCTGCCCATAGCTTGTTGTACTGCCTACAGTGGTAGATGGAGAGCATTACACAGTTACATGCCTCTGCTGGTATGCCCTATACACGTCCTGAGTTCACCACACAGTAGAGTCTGCGTTATCTGCAATCCGGGCGATGATGAAGCCAGAGAACGTCCGGTAGCGCAGTAGGCCTCGGCGCTCAGGCAAAGCAATGAGCCGGCTGGGAATGTCTTTGCGGCAAGCAGAAGGTACTCGCCCATATACGGACTCACGTTAGTACCCCGAGACGTAATAAAATCAACATTCGACACGTTGGACCGTATCTGGTACGAGCTCGATAGAGCTTTAGAGGGGCGTACGCGATTGAATACTATGTCCTTATAGTCGGATTGCATAACCTAATGTCGGGGTAAAAGAGCCTACATTAACTGGAGTACCGATCTCAGATGGTGCCCTGTTGCATCTGTAATCCGTCCAGGTGCTTGAAGGTACGCAAAAGGTGCTAGCTGATTGATGAGTAAATAATGCATACCATCATGGCCAAGACTTGTGATGGCCAAATTCTTTTGCCCACGTCCAAGTAAATAGAACCACATTGCCCGAAGTGGGGATGAGGCGAAACTCGCATTTGCCAAAAGAGTACAGCTTTTAACCTCACCCCATGGGCGGTCGTACAAGAAGGGAAACGTGTTCCTAGTGACGAATTAAGCAGGTTTCCTACTCTTATAAGGCTGTTAATAAGTTGTGGAAGCGAGGCAAGACCTGGGATCTTCCTGAATTTGGGTTAGTTATGGCCCAGAGCTGGCTCTTACTCTTCATGTGGAAACTGGATGGGTAAGAGTCCATGATGAGTAATTTGTGGCGTGCGGGCTCAAATGTCCATAGTATATTTCTCGTGCTGAACGGACTGTGCGCACTACTGCCTGCACAAGTGGCACGTTTTTCACACGTGGGACGACTCAGCTATAAGTTCTACCGCTTGAGATCGCATTTACATATCTGCTACCTATATGCTAGAAGGAACCACGAGTTCCAGCAAGGAATGATTCATATGACTTCATGGTTGTAAGATATAGACGCCTCAACGATTTTCTCAAATGAGCGCTCGCCTAACCTAGCATTGGATTGCATGAGCCCATCGGCGCTCAACTCAGGTTTGACGCGGGATAATTAACAACCACATCAAGCCGGGCCCCGATTGGACCGCACGCCGCCCATCTCGTCTTATCAGGGCCGAACTCGTATTTGCGCTGTTCTCCTACACAGATCATGACCCAGACTCGAAAACCGCTCGGCTTCGGTGAGACGGGCACCCATAGCTCAAGGTTTGGTCTTAGATTAAGCCGATCTTCCGCATCGCCTGCCCATGAGGATCACACGCTCTTATTCTTCTTTGGACTGCGCCGTGTATACCCCGTTCAAGCCGAGAACTACATTTCACTGATAGTTTGTGGCGACTTACTCCCTCGCTCGTTCTGCCCAGTGGAAACTGGCCAAAGGCCTGAGGCACAACTACCTAAGACGACAGCCTGCTATTCGGCTGTATTCCTTTTGGGCCCCCACACTCTGGAAGGCACTACAAGATATTCACCTTCCCTAATAACTGGGGGATCGTCGTGCTGTGGAACTCTCTAGCACCGCGACATCCGCGAGTTGCGGGCCCCGTCATCTGGAGGTTTCTCTCGTGTCCTTCCAGGGTAGCCATCGGCGCGTTAGTATGTATATTTCGCGGTAATACTACTGGCGCCGAATCTGACCCCGCACAGGTTATAGCAGCGAAACATACCCTGTGGTGTACCCACACGAAGATGACCATCTAGAGGAGGAGGAAACTGCCAAGATACGACTTTGCGCTTCAAAGGGTGGCCACACGGGCAACCAGCACTTGCGCGGAAACGAGTTCAACAATACATGTAGAACCTCAAAACGTCGGATACACTTTTATGCCGCTGAGCTCGTGGGAGCGGCCCTGTGAGTGCGCTATTTCACATCTTCTCCTGACGTGAGTTACCACTGTCACTGGTAAGCACAGACGTTTAGAACATTTTCGTCCCAACCGTAACCGGTGCCGGTTGCAGCGGGCGGTAGGTGGGCTGCTATAGCTGTGGTTGAAGCCTGGCGCGAAGTTTGACTATAAAGAGGGTGATGCAATTGTGCTATTCATGCTATCTAGACGTCTGTCTGGTGATCAGGCGGGCGTAGGTCTCGGGTTACGTACTGCCCCTGTCCGCCTGAATCGCACACGTTTGTTAAAGCGCTTCGGTGCCTGGTTTTCAACGCAGTCGACGTAACAACTTATTCTTGTTTCGATATCCGATTGTCATACCGACGCCTCGAGTCTCGAGCAATCTCAGCGCCACTTGTCTTCCAGAGGAGCCTTTCTTTTGCCCAGTATCTTTCCTTTTTACTCACTGTGATAGTGAGCTGCATGCCGTTTCATCTGCTTGTGGCTGGGCTGCAGAACAGTTAGCTAGTAGTTTGTTGTACAGAGTTTTCGCCGCGCTACAACGCGCGTATGGAGACCGTTGTCATCCCTATGATAACAGTATATATTCCGGTAGTCGGAACCGTCACAGAGGGCTAAAGATAACTTCGTACTGATCACGCGCATTTCCTACGGGAGATGCGTGTCCAGGCGTTAGGCCGGGGAGTGCCAGGGCTGCATAGCGTACTCCTCCGCCCATCGAGTACCATGACCAGTGAGCACCGGGTGTGTCGATTGTTTGTTGCGGATGACCTTGAGAAAGACGACCGTCGGGGCGGCCTCAGAAAAGCCGGTACAGACTTCAGCTAACCTCGGGGTACATACTTACGGTGAAGTGGAGAGAGATCGGATCCGCTGAGTCGGTGTGAAAATAGAATTGTGTGGTTCTGATACGAGGTTTTATTGCGAGCTGTTTTTGTGCCATATGAGCCACCTGGTTCCACCTGGTGGGTCACGTGGGGGGAGGCGTATAGTCCGGAAGATTTCTCTCTATAGCACCGATGATGGATGCACCAGCACTCCCTGTCGGTTTTCTACTGGCCCCTGCGCGCTATCGCGCCCGCAGACATTGACAAAAAGAAAGGAATATCTCCACATTGGCATTACCGATTACCCTGGGCGTGCGTATGTTTTAAAGGCTCCGTACACCATACCTAATCTCAAGATCCCGGGGGCTCGCCCGCCAGATTGTTCGATCTTCATTTATTCCAAAGGCTCGTCTCGAAAGGTCGGGTCTGTTAGGTTCGAGGACTATACATGGAATCGAATGCATAGACGGTTTAAAGGGGGCTATTCTCATGAGAGCCTGATATGGGGGGATTGTGCAAGCACTTGAAGGCTGCAGCATAACTAGGTGCCGATTCATGTCTATGGGTGACCCACTTCACATCAGCGGTGTCACGCGGGGATGCGCGCAATTGTATGTCACCTCGGGGTCGACGTTCGTAGGCCAATTAAGAGCCGATCTTATCTTGAGCGTTTAAACGGTGGCGAATTGAGATACGTGTCCCAGACCGGGCTTGTGAACCTACCCGAATCACAGCGGGAGGACCCAGGTCATGCCCCGGAAGCAAATACTTGTCACCGCTACCACCTTTCTGTGCCCTTTCGAACGGCTCTAGTGGTACGCTAGCCTAAGGAGGACCCTGGCCCCCAGGCTTGCTAGTTTAGATAATCAATGCATCATATTCCAGATCAACTGATTTCGCAAACACGTTTGACGATTACCGGGCCCTCCCGGGTGAGGAGTTCGTCCGTCCCCGGGGTATATTCTCCTCCCCCTGAGCTGTCAGCTTTCGACTAAGTGGACCGCCCGGATTAAACGACATGGTTATTGAGGGACTCTGAAACCAGGGACCAAGAGGGCCGGTTAGATTGGTCCACTCCTAATCGGCTTTTCTTGGTTGATTCGTCTTTTTGGGAGTGCTTGATGGCGTTTGGGGGGCTAATTCTTTCCACTATGTGAGATGAGACTGTTACGATCTTTTAACCAGTACTACTAACGAGTTGAACGATGCGTTAATGACGAGGCGGTATTACGTGACACCCGGTATCCGAGCAGTACTCTTTGTGTCTGGACAGGCGTGCCATGGTACGTGGATCGTCGTCGCGACTGAGCCAGGGATTATCGAGCCCTCTTCCCTGGTCAGCACGCTACGATCGTATAATACCTAAGCCGCGGTAAGAGGCGTCGGGGAGGCTATAGGAATGATAAAACGTAGTTGTGCATACCCTGGTAGCCTGAAGCAGGACGGCTCGAAGATCACGTCGATGGGCTATGATAAGGATAGGTGGATGAACAAACAGAGTTAGGCTATATGTAGGTAAAACCGGATAAAGGAGACACGGCTATGACTCCACGTAGCCGAAATGGGTGGAAGAGTTGTGCCCCATTAGTTCATCGTCAGTAAGCACGCCGCTAGGCTCGCACCAGAGTGCCTATCGATCATGAGAGTGAGGGCTACTTTCTAAATCACGGAAGTATGAGGAACATGCCTTTGGCAGAGCCTGTCAGTATTCGTTGGGTGACAAGCACGACCAGTGCCACTCGGAGAAGCCGGGCCGCTAACTCCGGGACGACGCTAAGTATGAACTACAGTTATCAGCTGTACGCTGTATAAGATTAAGGGTGGCATGCAGGACTTTATGATTGTAGCACATTGAAATGAAGTTAGGTGACTCAGCTACTCCCAGAAAAAGCAACAAACACTGCAACATGATTACGCGCGTTTTGAACATAAACTTGGGGGGGACTCACCCTGAATTTCTAATGCAAATACAATAATTCGAGCATCGTCCTAGATGGTCCCTCGCCAATTGGATGAGGTGTCCCACATTGTCGGCACGCGTACAAACCACGGACTTATCGTAAAGTACGCAGAACCACATGTCTGTATTAACTGGTCAACGCAAATACTGAGACGTCTATTTTTCGTGCTCAACTTCCCCTAGTCTGGATCGGTGCTGCGCCGCTACACTCCGTTGAGTGCTGTAGTCTCTTACTTGACACGCTTTTTGCAGAGCCACGGGCTTTGTACACTCGAGCCGGAGCTCAGGTTCCTCGGTCACGACCCCTAACCAACTACAACTCCGAATTCTGTGCACGTCGTATTACTGGATCTTCTAGAGTGAGGGTTCTACTAACGCTACCAAGCGCCAAATTGGAGCGAATACCATTCCATACCGGAATTGCCCGCCGCCCTTCAGGGGAAATCTTCCAGTCACATCGCTGGTGCTAGCTGTGCCACGTTGGGTTCCTTGTAAGAACTTCTGTTACTTGATCCGCCTCTTAAAGTCGGTTACCCAGGCAGGGATTCCGAGACCCCCTTACATGCGCTATCTACGGGGACGCTGTCTATCGTATGAGTGTTTGACTTGTAATTCCCGGACACGGAGGCGTTATCTCGCAGCCAGTGGCGCGAACGCAGCACCCGGACAGCAGTCTCCGAAGCACCATCCGCATCTAAAGTAACTCGGGCATCCGCGGGTGCAGCGTTTGGAGATTGTATGCCACGTTCTTCGGAGTTTTCAGTGTGGCACGACCGTGGATGGATTAATATCCCGCCATCTCGGCGAGTCCAGCCTTGCGTAGTCCGGCTTTACATTATCCGCCCAAAGCCAAATCTCTCAAGAAGGTGCTTGAAATGCTGAGAGAATGCGACCAGCGCCATGGGCGATCAAGATTGTAGCAAATTAACCTAAGCCGTCGCTACAGACTCTAAGTTAATAAAGACGGCCATGGGTCATTTTTCGAAATACTTCGGTCTGTGGTACACAGCTTTTAGTAGAGGCCCATGTCCGCATGTTAGCCTGCCATAAGTGCCCCTCAACTAACTCTGAAGCGTATGTGTGGTTAACTGCGGTGCTTCTAAGCATCCGGTCGGAGGGCCCGCGTATTTTTATCAGCGAGAATCTAAAGGCCGCACGATTCGGAGTCTAGAGAACCGCCACGCGGAGCCTTCGGCGACAGTTTTCTTCGTTACGTAGCTAGTCCACGGAGCCTAAGCTGCCACATGCGACAGTCGGACTCTAGTTGATTGTGTTAGGTGAAAATAAAAACTTGGACAAACGCCTCGGAATGCACGTTCTAATCCTCAACACCGAGGGGCTCCCCCATTGCTCTGAACTTATACCCATCTGATCTAGTCGGTGTGCGGAGTGTTGGGACCATACAATACATAAGCTCTTATTAGGCGCAGATCCTGGAACAGCAAACTGTCACAAGATTGCGCTGGGCACCGAGCTCTTAGTGAGGCGAACCGTTGGCAAGCTTAGCGAACACTTCCGTCGTAGACTGGTCCTCACATCGGTAACAGTACGAATGCGTTCAGAGCAGTGTTACGCAACCGCTTTGCCAA";