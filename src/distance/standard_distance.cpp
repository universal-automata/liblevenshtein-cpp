#include "standard_distance.h"
#include "../collection/symmetric_immutable_pair.hpp"


namespace liblevenshtein {

    int StandardDistance::between(std::string v, std::string w) {
        SymmetricImmutablePair<std::string> key(v, w);

        int distance = get_distance(key);
        if (distance > -1) {
            return distance;
        }

        if (v.empty()) {
            return set_distance(key, w.length());
        }

        if (w.empty()) {
            return set_distance(key, v.length());
        }

        char a = v[0]; std::string s = v.substr(1);
        char b = w[0]; std::string t = w.substr(1);

        // Discard identical characters
        while (a == b && !(s.empty() || t.empty())) {
            a = s[0]; v = s; s = v.substr(1);
            b = t[0]; w = t; t = w.substr(1);
        }

        // s.length() = 0 || t.length() == 0
        if (a == b) {
            if (s.empty()) {
                return set_distance(key, t.length());
            }
            return set_distance(key, s.length());
        }

        distance = between(s, w);
        if (0 == distance) {
            return set_distance(key, 1);
        }

        int min_distance = distance;

        distance = between(v, t);
        if (0 == distance) {
            return set_distance(key, 1);
        }

        if (distance < min_distance) {
            min_distance = distance;
        }

        distance = between(s, t);
        if (0 == distance) {
          return set_distance(key, 1);
        }

        if (distance < min_distance) {
          min_distance = distance;
        }

        return set_distance(key, 1 + min_distance);
    }
}
