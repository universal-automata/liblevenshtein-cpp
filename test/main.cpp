#include <cstdio>
#include <string>

#include "../src/distance/standard_distance.h"
#include "../src/distance/transposition_distance.h"
#include "../src/distance/merge_and_split_distance.h"

using namespace std::literals;

int main(int argc, char* argv[]) {
    liblevenshtein::StandardDistance distance;
    liblevenshtein::TranspositionDistance transposition;
    liblevenshtein::MergeAndSplitDistance merge_and_split;

    for (int i = 1; i < argc; i += 1) {
      printf("d(\"%s\", \"%s\") = %d =?= %d = d(\"%s\", \"%s\")\n",
             argv[i], argv[i],
             distance.between(argv[i], argv[i]),
             distance.between(argv[i], argv[i]),
             argv[i], argv[i]);
      printf("t(\"%s\", \"%s\") = %d =?= %d = t(\"%s\", \"%s\")\n", argv[i],
             argv[i], transposition.between(argv[i], argv[i]),
             transposition.between(argv[i], argv[i]), argv[i], argv[i]);
      printf("m(\"%s\", \"%s\") = %d =?= %d = m(\"%s\", \"%s\")\n", argv[i],
             argv[i], merge_and_split.between(argv[i], argv[i]),
             merge_and_split.between(argv[i], argv[i]), argv[i], argv[i]);
      for (int j = i + 1; j < argc; j += 1) {
        printf("d(\"%s\", \"%s\") = %d =?= %d = d(\"%s\", \"%s\")\n",
               argv[i], argv[j],
               distance.between(argv[i], argv[j]),
               distance.between(argv[j], argv[i]),
               argv[j], argv[i]);
        printf("t(\"%s\", \"%s\") = %d =?= %d = t(\"%s\", \"%s\")\n", argv[i],
               argv[j], transposition.between(argv[i], argv[j]),
               transposition.between(argv[j], argv[i]), argv[j], argv[i]);
        printf("m(\"%s\", \"%s\") = %d =?= %d = m(\"%s\", \"%s\")\n", argv[i],
               argv[j], merge_and_split.between(argv[i], argv[j]),
               merge_and_split.between(argv[j], argv[i]), argv[j], argv[i]);
        }
    }
}
