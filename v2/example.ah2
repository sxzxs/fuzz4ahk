;https://github.com/maxbachmann/rapidfuzz-cpp
/*
("rapid_fuzz_cpp_ratio", "rapid_fuzz_cpp_partial_ratio", "rapid_fuzz_cpp_token_ratio", "rapid_fuzz_cpp_partial_token_ratio"
"rapid_fuzz_cpp_token_sort_ratio","rapid_fuzz_cpp_partial_token_sort_ratio","rapid_fuzz_cpp_token_set_ratio","rapid_fuzz_cpp_partial_token_set_ratio")
*/
#include <fuzz>
;#include <log> ;https://github.com/kazhafeizhale/ahk_log/tree/main/v2
;Simple Ratio
;score is 96.55171966552734
score := fuzz.ratio("this is a test", "this is a test!")
;logger.info(score)

;Partial Ratio
;score is 100
score := fuzz.partial_ratio("this is a test", "this is a test!")
;logger.info(score)

;Token Sort Ratio
;score is 90.90908813476562
score := fuzz.ratio("fuzzy wuzzy was a bear", "wuzzy fuzzy was a bear")
;logger.info(score)
;score is 100
score := fuzz.token_sort_ratio("fuzzy wuzzy was a bear", "wuzzy fuzzy was a bear")
;logger.info(score)

;Token Set Ratio
;score is 83.8709716796875
score := fuzz.token_sort_ratio("fuzzy was a bear", "fuzzy fuzzy was a bear")
;logger.info(score)
;score is 100
score := fuzz.token_set_ratio("fuzzy was a bear", "fuzzy fuzzy was a bear")
;logger.info(score)

;partial set ratio
score := fuzz.partial_token_set_ratio("a f u", "fuzzy fuzzy was a bear")
MsgBox(score)

score := fuzz.partial_token_set_ratio("was fuzz", "fuzzy fuzzy was a bear")
MsgBox(score)

score := fuzz.partial_token_set_ratio("fuzzbear", "fuzzy fuzzy was a bear")
MsgBox(score)