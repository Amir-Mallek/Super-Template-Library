# Basic Template

During the competition, make sure to write the following file once :

## `template.cpp`
```cpp
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
typedef vector<int> vi;
/*not complete*/

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    /*Later : ifdef LOCAL  input output files*/

}
```

## Compilation & Execution configuration

Learn how to modify quickly the CLion configuration to be able to :

- Add `-DLOCAL` to the compilation command
    - ICPC 2025 compilation command : 

            g++ -x c++ -g -O2 -std=gnu++20 -static {files}
- Disable at first the CLion addons, i.e :

        sgt.query( l : a, r : b );