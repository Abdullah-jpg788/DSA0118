# Notes kept out of the source files

## Q3 predictions (before running)
1. charge(2) -> int overload (exact match)
2. charge(2.0f) -> double overload (float to double is a promotion, better than float to int conversion)
3. charge(2.5) -> double overload, express=false, insured=false
4. charge(2.5, true) -> double overload, express=true
5. charge(2.5, true, true) -> double overload, both options
6. charge(Parcel) -> Parcel overload

Q3 ambiguity: in q3_ambiguous.cpp, charge(2.5) and charge(2.5, true) each match two overloads equally well
(the 1/2-parameter ones and the one with default arguments), so the compiler reports an ambiguous call.

## Q1 predictions
value -> 45000 unchanged; reference -> 40500; pointer -> 40500; stacking 10% then 15% in place -> 40500 then 34425.

## Q5 q5_function_twice prediction
First call: Seat 1, Seat 2, Seat 3 (bus fills), Issued 3. Second call: all Waiting, Issued 3.

## Q7 Diagnose / Objective / Redesign / Prediction
- A. Diagnosis: the Q4 shifting array moves K-1 elements for every transaction after the K-th, so adds cost O(K).
  Going from the last 10 to the last 50 transactions makes each add about five times more work.
- B. Objective: add in constant time, so the time for K=50 is within 1.5x of K=10, with identical
  newest / oldest / balance values.
- C. Redesign: circular buffer with a start index; slot (start + count) % K, overwrite the oldest when full.
  Same K-element array plus one extra int; no library container.
- D. Prediction (written before running): K=10 speed-up small (about 1.5x to 3x), K=50 large (about 5x to 15x);
  redesigned K=10 and K=50 times close to each other.
