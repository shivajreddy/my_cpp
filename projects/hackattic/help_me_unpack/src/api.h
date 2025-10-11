#ifndef GET_DATA_H
#define GET_DATA_H

#include <optional>
#include <string>

using std::optional;
using std::string;

// string get_data(const char* URL);
optional<string> get_data(const char* URL);

void post_response();

#endif // !GET_DATA_H
