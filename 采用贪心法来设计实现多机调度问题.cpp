#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;
int v[N];          // 存储作业时间
int machine[N] = {0};    // 全局变量默认就是0，加个={0}更清晰
int job_machine[N]; // 记录每个作业分配到哪台机器
int job_start[N];  // 记录每个作业的开始时间

void quick_sort(int v[], int l, int r)
{
    if (l >= r)
    {
        return ;
    }
    
    int random_number = l + rand() % (r - l + 1);
    int x = v[random_number];
    int i = l - 1, j = r + 1;
    
    while (i < j)
    {
        do
        {
            i ++ ;
        } 
        while (v[i] < x);
        do
        {
            j -- ;
        } 
        while (v[j] > x);
        if (i < j)
        {
            swap(v[i], v[j]);
        }
    }
    
    quick_sort(v, l, j);
    quick_sort(v, j + 1, r);
}

int main()
{
    int n, m;
    cin >> n >> m;

    // 输入作业时间
    for (int i = 0; i < n; i ++ )
    {
        cin >> v[i];
        job_machine[i] = -1;
        job_start[i] = 0;
    }

    quick_sort(v, 0, n - 1);
    reverse(v, v + n);
    
    // 处理 m > n 的情况
    int actual_m = min(m, n);  // 实际使用的机器数
    
    // 贪心分配作业
    for (int i = 0; i < n; i ++ )
    {
        // 找到当前最闲的机器（只在实际使用的机器中找）
        int min_time = machine[0];
        int min_machine = 0;
        
        for (int j = 1; j < actual_m; j ++ )
        {
            if (machine[j] < min_time)
            {
                min_time = machine[j];
                min_machine = j;
            }
        }
        
        // 分配作业
        job_start[i] = min_time;
        job_machine[i] = min_machine;
        machine[min_machine] += v[i];
    }
    
    // 计算最短完成时间
    int max_finish_time = 0;
    for (int i = 0; i < actual_m; i ++ )
    {
        if (machine[i] > max_finish_time)
        {
            max_finish_time = machine[i];
        }
    }

    cout << "\n========== 调度方案 ==========" << endl;
    cout << "\n作业分配情况（按作业从大到小排序）：" << endl;
    cout << "序号 | 执行时间 | 机器编号 | 开始时间 | 结束时间" << endl;
    cout << "-----|----------|----------|----------|----------" << endl;
    
    for (int i = 0; i < n; i ++ )
    {
        int endTime = job_start[i] + v[i];
        printf("%-4d | %-8d | %-8d | %-8d | %-8d\n", 
               i + 1, v[i], job_machine[i] + 1, job_start[i], endTime);
    }
    
    cout << "\n各机器的负载情况：" << endl;
    for (int i = 0; i < actual_m; i ++ )
    {
        cout << "机器 " << i + 1 << " 的总工作时间: " << machine[i] << endl;
    }
    
    cout << "\n全部作业的最短完成时间: " << max_finish_time << endl;
    cout << "==============================" << endl;

    return 0;
}