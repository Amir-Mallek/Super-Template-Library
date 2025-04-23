# Monotonic Stack

```cpp
stack<T> s;
void add(T val)
{
    while(!s.empty() && s.top() <= val)
        s.pop();
    s.push(val);
}
T get( /* threshhold */ )
{
    T res /*= initial value */;
    while(!s.empty() && /* condition */ ){
        res = s.top();
        s.pop();
    }
    return res;
}
```