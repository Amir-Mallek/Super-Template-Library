# Environment

## 3 Important Steps
- Setup the compilation and execution configurations
- Setup the IDE view
- Type & save the `template.cpp` file before viewing problems

## IDE configuration

Learn how to modify quickly the CLion configuration to be able to :

- Add `-DLOCAL` to the compilation command
    - ICPC 2025 compilation command : 

            g++ -x c++ -g -O2 -std=gnu++20 -static {files}
- Disable at first the CLion addons, i.e :

        sgt.query( l : a, r : b );

## `template.cpp`
```cpp
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
typedef long long ll;
typedef vector<int> vi;
/*not complete*/

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    /*Later : ifdef LOCAL ...           */
    /*Later : when should we use solve()*/
}
```