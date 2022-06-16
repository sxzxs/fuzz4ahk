#include <rapidfuzz/fuzz.hpp>
#include <string>
#include <iostream>
#include <spd_logger.h>
#include <string.h>
#include <algorithm>
#include <corecrt_wstring.h>
#include <codecvt>
using namespace std;


bool mycomp(std::pair<std::string, double> i, std::pair<std::string, double> j) 
{
    return (i.second > j.second);
}

template <typename Sentence1,
          typename Iterable, typename Sentence2 = typename Iterable::value_type>
std::vector<std::pair<Sentence2, double>>
extract(const Sentence1& query, const Iterable& choices, const double score_cutoff = 0.0)
{
  std::vector<std::pair<Sentence2, double>> results(choices.size());

  rapidfuzz::fuzz::CachedTokenSetRatio<typename Sentence1::value_type> scorer(query);

  #pragma omp parallel for
  for (size_t i = 0; i < choices.size(); ++i) {
    double score = scorer.similarity(choices[i], score_cutoff);
    results[i] = std::make_pair(choices[i], score);
  }

  return results;
}

std::string wstr_utf8(const std::wstring& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.to_bytes(str);
}
std::wstring utf8_wstr(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.from_bytes(str);
}

extern "C" _declspec(dllexport) double rapid_fuzz_cpp_ratio(const wchar_t *s1, const wchar_t *s2)
{
    int rtn = rapidfuzz::fuzz::ratio(wstr_utf8(s1), wstr_utf8(s2));
	return rtn;
}

extern "C" _declspec(dllexport) double rapid_fuzz_cpp_partial_ratio(const wchar_t *s1, const wchar_t *s2)
{
    double rtn = rapidfuzz::fuzz::partial_ratio(wstr_utf8(s1), wstr_utf8(s2));
	return rtn;
}

extern "C" _declspec(dllexport) double rapid_fuzz_cpp_token_ratio(const wchar_t *s1, const wchar_t *s2)
{
    double rtn = rapidfuzz::fuzz::token_ratio(wstr_utf8(s1), wstr_utf8(s2));
	return rtn;
}

extern "C" _declspec(dllexport) double rapid_fuzz_cpp_partial_token_ratio(const wchar_t *s1, const wchar_t *s2)
{
    double rtn = rapidfuzz::fuzz::partial_token_ratio(wstr_utf8(s1), wstr_utf8(s2));
	return rtn;
}

extern "C" _declspec(dllexport) double rapid_fuzz_cpp_token_sort_ratio(const wchar_t *s1, const wchar_t *s2)
{
    double rtn = rapidfuzz::fuzz::token_sort_ratio(wstr_utf8(s1), wstr_utf8(s2));
	return rtn;
}

extern "C" _declspec(dllexport) double rapid_fuzz_cpp_partial_token_sort_ratio(const wchar_t *s1, const wchar_t *s2)
{
    double rtn = rapidfuzz::fuzz::partial_token_sort_ratio(wstr_utf8(s1), wstr_utf8(s2));
	return rtn;
}

extern "C" _declspec(dllexport) double rapid_fuzz_cpp_token_set_ratio(const wchar_t *s1, const wchar_t *s2)
{
    double rtn = rapidfuzz::fuzz::token_set_ratio(wstr_utf8(s1), wstr_utf8(s2));
	return rtn;
}

extern "C" _declspec(dllexport) double rapid_fuzz_cpp_partial_token_set_ratio(const wchar_t *s1, const wchar_t *s2)
{
    double rtn = rapidfuzz::fuzz::partial_token_set_ratio(wstr_utf8(s1), wstr_utf8(s2));
	return rtn;
}


int main()
{
    std::string a = "abcdef";
    std::string b = "abcde";
    TRACE(rapidfuzz::fuzz::ratio(b, a));
    TRACE(rapidfuzz::fuzz::partial_ratio("ab ab", "ab cd"));
    TRACE(rapidfuzz::fuzz::token_sort_ratio("ab", "ab cd"));
    TRACE(rapidfuzz::fuzz::token_set_ratio("cd b cd ab cd", "ab cd"));

    std::vector<std::string> all{"heqiang hetong hetong", "hetong", "heliang" };
    std::string query("hetong hetong");

    auto rtn = extract(query, all);
    std::sort(rtn.begin(), rtn.end(), mycomp);//12 26 32 33 45 53 71 80
    TRACE(json(rtn).dump());
    TRACE(rapid_fuzz_cpp_ratio(L"hetong", L"hetong"));
    TRACE(rapid_fuzz_cpp_token_set_ratio(L"hetong", L"hetong heliang"));
    TRACE(rapid_fuzz_cpp_partial_token_set_ratio(L"hetong", L"1hetong2 heliang heqiang"));
}
