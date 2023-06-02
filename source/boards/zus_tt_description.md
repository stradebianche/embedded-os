- L0 is addressing 512 GiB of memory space, pointing to first L1 entry
- L1 single entry is addressing 1 GiB of memory, pointing to L2


     L0                           L1                         L2
+----------+                 +----------+               +----------+
|          |   ->(512 GiB)   |  1st     |   ->(1 GiB)   |  1st     |   ->(2MiB)
+----------+                 |  2nd     |   -----       |   ...    |     (512 entries, 2MiB each)
                                 ...            |       |  512th   |
                             |  512th   |       |       +----------+
                             +----------+       ----->  |  1st     |   ->(2MiB)
                                                        |   ...    |     (512 entries, 2MiB each)
