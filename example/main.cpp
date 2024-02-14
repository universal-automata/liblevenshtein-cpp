#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <google/protobuf/stubs/common.h>

#include <liblevenshtein/collection/dawg.h>
#include <liblevenshtein/collection/sorted_dawg.h>
#include <liblevenshtein/serialization/serializer.h>
#include <liblevenshtein/transducer/algorithm.h>
#include <liblevenshtein/transducer/transducer.h>

#include "command_line.h"

namespace ll = liblevenshtein;
namespace demo = liblevenshtein::demo;

template <ll::Algorithm Type>
void query(ll::Dawg *dawg, const std::string &query_term, const demo::CommandLine &cli) {
  ll::Transducer<Type, ll::Candidate> transduce(dawg->root());

  // NOTE: ll:Candidate is an alias for std::pair<std::string, std::size_t>
  for (const ll::Candidate& candidate : transduce(query_term, cli.max_distance())) {
    // spelling candidate for query_term
    const std::string& term = candidate.first;

    // minimum number of operations required to transform query_term into term
    const std::size_t& distance = candidate.second;

    std::cout << "d(\"" << query_term << "\", \"" << term << "\") = "
              << distance << std::endl;
  }
}

std::string &prompt(std::string &query_term) {
  std::cout << std::endl;
  std::cout << "Enter a query term (or nothing to exit)." << std::endl;
  std::cout << "query> ";
  std::getline(std::cin, query_term);
  return query_term;
}

auto main(int argc, char *argv[]) -> int {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  demo::CommandLine cli(argc, argv);
  if (!cli.parse_opts()) {
    return static_cast<int>(cli.return_code());
  }

  ll::Dawg *dawg = ll::deserialize_protobuf(cli.serialization_path());

  if (dawg == nullptr) {
    std::vector<std::string> terms;

    // populate with your spelling candidates
    std::ifstream dictionary_file(cli.dictionary_path());
    if (dictionary_file.is_open()) {
      std::string term;
      while (std::getline(dictionary_file, term)) {
        terms.push_back(term);
      }
      dictionary_file.close();
    }

    std::sort(terms.begin(), terms.end()); // must be sorted for now

    // NOTE: If (dawg == nullptr) then the construction of the dictionary
    // failed, probably because terms wasn't sorted lexicographically in
    // ascending order.
    dawg = ll::sorted_dawg(terms.begin(), terms.end());
  }

  std::string query_term;

  while (prompt(query_term) != "") {
    switch (cli.algorithm()) {
    case ll::Algorithm::STANDARD:
      query<ll::Algorithm::STANDARD>(dawg, query_term, cli);
      break;
    case ll::Algorithm::TRANSPOSITION:
      query<ll::Algorithm::TRANSPOSITION>(dawg, query_term, cli);
      break;
    case ll::Algorithm::MERGE_AND_SPLIT:
      query<ll::Algorithm::MERGE_AND_SPLIT>(dawg, query_term, cli);
      break;
    }
  }

  std::cout << std::endl;
  std::cout << "Exiting ..." << std::endl;

  /**
   * If you had initialized the transducer as
   * ll::Transducer<ll::Algorithm::TRANSPOSITION, std::string>, you'd iterate
   * over the results as follows:
   * for (const std::string& term : transduce(query_term, max_distance)) {
   *     // do something with term, which is guaranteed to require no more
   *     // than max_distance operations to transform it into the query_term.
   * }
   */

  // save the dictionary for reuse
  serialize_protobuf(dawg, cli.serialization_path());

  delete dawg;

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
