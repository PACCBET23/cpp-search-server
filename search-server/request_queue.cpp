#include "request_queue.h"

template <typename DocumentPredicate>
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
        const auto result = search_server_.FindTopDocuments(raw_query, document_predicate);
        AddRequest(result.size());
        return result;
    }

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status) {
        const auto result = search_server_.FindTopDocuments(raw_query, status);
        AddRequest(result.size());
        return result;
    }

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query) {
        const auto result = search_server_.FindTopDocuments(raw_query);
        AddRequest(result.size());
        return result;
    }//возможно это удалить!!!!!!!!!!

int RequestQueue::GetNoResultRequests() const {
        return no_results_requests_;
    }