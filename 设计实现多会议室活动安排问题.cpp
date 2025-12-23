#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> PII;
vector<PII> a;

void quick_sort(vector<PII> a, int l, int r)
{
    if (l >= r)
    {
        return ;
    }

    int random_number = l + rand() % (r - l + 1);
    int x = a[random_number].second;

    int i = l - 1, j = r + 1;
    while (i < j)
    {
        do
        {
            i ++ ;
        }
        while (a[i].second < x);
        do
        {
            j -- ;
        }
        while (a[j].second > x);
        if (i < j)
        {
            swap(a[i], a[j]);
        }
    }

    quick_sort(a, l, j);
    quick_sort(a, j + 1, r);
}

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i ++ )
    {
        int start, end;
        cin >> start >> end;
        a.push_back({start, end});
    }

    quick_sort(a, 0, n - 1);

    int res = 0;
    for (int time = 0; time <= a.back().second; time ++ )
    {
        int cover = 0;
        for (int i = 0; i < a.size(); i ++ )
        {
            if (time > a[i].first && time <= a[i].second)
            {
                cover ++ ;
            }
        }
        res = max(res, cover);
    }

    cout << res << endl;
    return 0;
}