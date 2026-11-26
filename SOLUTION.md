# CrossArray

`CrossArray.hpp` implements the required interface without library includes.
Each inserted row owns its allocation; copying and assignment make independent
copies. The row table is value-initialized so unused slots contain null pointers.
Doubling transfers row pointers to a larger table without moving the integers.
Element counts are cached for constant-time comparison, with ties returning the
current object. Identity comparison checks object addresses.

Insertion takes O(size) time. Append uses geometric allocation for amortized
O(size) time; a reallocation additionally copies the existing row. Copying takes
O(capacity + total elements), doubling takes O(capacity), and access and comparison
take O(1). Storage is O(capacity + total elements).

Run `make test` for deterministic boundary checks and 100,000 randomized appends
compared with a vector model, with address and undefined-behavior sanitizers.
Libraries are used only in the local tests, not the submitted class.

## Submission record

- Submission 879525: Git URL submission, compile error, score 0. The judge
  included the URL literally as `/src.hpp`, so its header-testing configuration
  requires source submission despite advertising Git support.
- The client now supports `submit --problem-id 1410 --source CrossArray.hpp`.
  `make` also packages the header as `code` for the documented artifact layout.
