# DSA01-<RegisterNumber>-Assignment1

Name: <your name>
Register number: <your register number>
Compiler: g++ 13.3.0 (Ubuntu)
Compile command: `g++ -std=c++17 -Wall -Wextra -o <name> <name>.cpp`

## Assumptions
- All money is stored as integer paise in `long long`.
- Peak hours: 8:00 up to (not including) 10:00 and 17:00 up to (not including) 20:00.
- Student / senior concession is 50% off (the brief does not give a rate).
- Task 12: the weekend discount replaces the peak surcharge on weekends; passes cover two zones.

## Running each task
| Task | Files | Run | Result |
|---|---|---|---|
| 1 | Task01/task01_oop_vs_procedural.cpp | `./task01_oop_vs_procedural` | OOP and procedural versions give identical fares; only OOP protects the balance |
| 2 | Task02/task02_constants.cpp | `./task02_constants` | constexpr table, enum class vs enum demonstrated |
| 3 | Task03/task03_datatypes.cpp | `./task03_datatypes` | double error grows with n; paise is exact; day total exceeds int |
| 4 | task04_predict.cpp, task04_corrected.cpp | run both | `-Wsign-compare` warning on the original; corrected version removes the surprise |
| 5 | task05_predict.cpp, task05_peak_expressions.cpp | run both | `-Wparentheses` warning on the no-parentheses peak expression |
| 6 | Task06/task06_fare_switch.cpp | `./task06_fare_switch` | matches expected output; 10:00 and 20:00 are off-peak |
| 7 | Task07/task07_procedural_vs_oop.cpp | `./task07_procedural_vs_oop` | procedural balance drops below Rs 50; class refuses |
| 8 | task08a_cin.cpp, task08b_getline.cpp, input.txt | `./task08a_cin < input.txt` | bad lines skipped, run continues |
| 9 | Task09/task09_tests.cpp | `./task09_tests` | 14/14 table tests and 5-journey hand total (9200 paise) pass |
| 10 | Task10/task10_totals.cpp | `./task10_totals` | int overflows at 3,000,000 journeys; float loses precision; double and paise agree here |
| 11 | Task11/task11_final_design.cpp, fares.cfg | `./task11_final_design fares.cfg` | fares loaded from file; floor rule still enforced |
| 12 | Task12/task12_redesign.cpp | `./task12_redesign` | 6/6 fare tests pass; pass and floor behaviour shown |

Each `*.output.txt` is the captured output; `*.warnings.txt` holds compiler warnings (Tasks 4 and 5).

## Before you submit
- Task 4 and Task 5: write your own prediction first, then compare with the actual output and explain each difference.
- Make at least one git commit per task folder, then add screenshots of code and output.
