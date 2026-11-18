# DSA01-192525129-Assignment4

Name: Shaik Rafiqhuddin
Register Number: 192525129
Course: Object Oriented Programming with C++ (DSA0120)
Assignment 4 - CO4: Designing Reusable Class Hierarchies

Compiler: g++ 11.4.0
Compile command for every program: `g++ -std=c++17 -Wall -Wextra <file>.cpp -o <name>`
Task 4 sanitizer build: g++ -std=c++17 -Wall -Wextra -g -fsanitize=address defective.cpp -o defective_asan
Task 3 experiment build: g++ -std=c++17 -Wall -Wextra -DNO_VIRTUAL construction_trace.cpp -o trace_novirt

## Tasks

- Task01/payroll_hierarchy.cpp - repaired payroll class hierarchy (abstract base, overridden pay()). Result: all staff processed in one base-pointer loop; total payroll 231200.00.
- Task02/university_people.cpp - Person/Student/Staff with virtual bases; TeachingAssistant diamond resolved; ResearchScholar multilevel. Result: one shared Person sub-object (TA = 176 bytes vs 240 bytes with composition).
- Task02/task2_predict.cpp, task2_predict_no_virtual.cpp - predict-the-output programs. Result: "Person Student Staff TA" with virtual; "Person Student Person Staff TA" without.
- Task03/construction_trace.cpp - constructors in derived and member classes with full construction/destruction traces; -DNO_VIRTUAL rebuild runs the 3.4 experiment (232 bytes, Person built twice).
- Task03/task3_complete.cpp - completed TODO 1 (member initializer list). Result: 192311001 Kavya (19) Salem-636001, matches expected output. task3_swapped.cpp reproduces the -Wreorder warning.
- Task04/defective.cpp - the defective bank accounts program with destructor evidence; under AddressSanitizer it reports new-delete-type-mismatch and an 800-byte leak. fixed.cpp repairs it with virtual rate(), virtual destructor, override and a reference instead of a copy. task4_predict.cpp prints 3.5 4 3.5.
- Task05/cart_four_ways.cpp - direct object, pointer, reference and new/delete, method chaining via this, and the array-of-pointers search for the highest-total cart. task5_complete.cpp - completed TODO 1/2. Result: 324.00, matches expected output.
- Task06/fleet.cpp - vehicle rental fleet with abstract Vehicle, per-type charge(), late return charge, and the ElectricBus extension added without changing any existing class.

Each TaskXX/output.txt holds the captured program output; Task04/asan_report.txt holds the AddressSanitizer report.

## Exact build and run steps

All supplied inputs are constructed inside the programs; no stdin input file is required. Start from the repository root. Use one terminal command below at a time. The defective Task04 program intentionally demonstrates undefined behavior; use the sanitizer commands to inspect it, not as a repaired solution.

```sh
g++ -std=c++17 -Wall -Wextra Task01/payroll_hierarchy.cpp -o payroll_hierarchy
./payroll_hierarchy
g++ -std=c++17 -Wall -Wextra Task02/task2_predict.cpp -o task2_predict
./task2_predict
g++ -std=c++17 -Wall -Wextra Task02/task2_predict_no_virtual.cpp -o task2_predict_no_virtual
./task2_predict_no_virtual
g++ -std=c++17 -Wall -Wextra Task02/university_people.cpp -o university_people
./university_people
g++ -std=c++17 -Wall -Wextra Task03/construction_trace.cpp -o construction_trace
./construction_trace
g++ -std=c++17 -Wall -Wextra Task03/task3_complete.cpp -o task3_complete
./task3_complete
g++ -std=c++17 -Wall -Wextra Task03/task3_predict.cpp -o task3_predict
./task3_predict
g++ -std=c++17 -Wall -Wextra Task03/task3_swapped.cpp -o task3_swapped
./task3_swapped
g++ -std=c++17 -Wall -Wextra Task04/defective.cpp -o defective
./defective
g++ -std=c++17 -Wall -Wextra Task04/fixed.cpp -o fixed
./fixed
g++ -std=c++17 -Wall -Wextra Task04/task4_predict.cpp -o task4_predict
./task4_predict
g++ -std=c++17 -Wall -Wextra Task05/cart_four_ways.cpp -o cart_four_ways
./cart_four_ways
g++ -std=c++17 -Wall -Wextra Task05/task5_complete.cpp -o task5_complete
./task5_complete
g++ -std=c++17 -Wall -Wextra Task06/fleet.cpp -o fleet
./fleet
```

For Task03 non-virtual comparison:
```sh
g++ -std=c++17 -Wall -Wextra -DNO_VIRTUAL Task03/construction_trace.cpp -o trace_novirt
./trace_novirt
```

For Task04 AddressSanitizer checks:
```sh
g++ -std=c++17 -Wall -Wextra -g -fsanitize=address Task04/defective.cpp -o defective_asan
./defective_asan
ASAN_OPTIONS=new_delete_type_mismatch=0 ./defective_asan
```

## Publication history

These are present-time publication commits made on 18 November 2026. They do not claim earlier progressive development history. Output images have a numeric upload prefix but retain their descriptive names and captured contents.
