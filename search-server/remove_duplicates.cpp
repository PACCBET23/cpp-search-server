#include "remove_duplicates.h"

using namespace std::string_literals;

void RemoveDuplicates(SearchServer& search_server) {
    std::set<int> id_remove;
    std::set<std::set<std::string_view>> unique_word_plus_id;
    for (const int document_id : search_server) {
        std::set<std::string_view> unique_words;
        for (auto& [word, _] : search_server.GetWordFrequencies(document_id)) {
            unique_words.insert(word);
        }
        if (unique_word_plus_id.count(unique_words)) {
            id_remove.insert(document_id);
        }
        else {
            unique_word_plus_id.insert(unique_words);
        }
    }
    for (auto id_ : id_remove) {
        std::cout << "Found duplicate document id "s << id_ << std::endl;
        search_server.RemoveDocument(id_);
    }
}