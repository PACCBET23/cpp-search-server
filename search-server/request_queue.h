#pragma once
#include "search_server.h"

#include <deque>

class RequestQueue {
public:
    RequestQueue(const SearchServer& search_server)
        : search_server_(search_server)
        , no_results_requests_(0)
        , current_time_(0) {
    }
    // сделаем "обертки" для всех методов поиска, чтобы сохранять результаты для нашей статистики
    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) ;
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status) ;
    std::vector<Document> AddFindRequest(const std::string& raw_query) ;
    int GetNoResultRequests() const ;
    
private:
    struct QueryResult {
        uint64_t timestamp;
        int results;
    };
    std::deque<QueryResult> requests_;
    const SearchServer& search_server_;
    int no_results_requests_;
    uint64_t current_time_;
    const static int min_in_day_ = 1440;

  /*!!тут возможно добавить RequestQueue::!!*/  void AddRequest(int results_num) {
        // новый запрос - новая секунда
        ++current_time_;
        // удаляем все результаты поиска, которые устарели
        while (!requests_.empty() && min_in_day_ <= current_time_ - requests_.front().timestamp) {
            if (0 == requests_.front().results) {
                --no_results_requests_;
            }
            requests_.pop_front();
        }
        // сохраняем новый результат поиска
        requests_.push_back({ current_time_, results_num });
        if (0 == results_num) {
            ++no_results_requests_;
        }
    }
};