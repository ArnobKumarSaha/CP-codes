#include <bits/stdc++.h>
using namespace std;

struct Mo
{
    static constexpr int MAX_VALUE = 100005;
    vector<int> cnt, arr, answers;
    int current_answer, N, Q, BLOCK_SIZE;
    vector< tuple<int, int, int> > queries;

    void initialize()
    {
        BLOCK_SIZE = static_cast<int>(sqrt(N));
        arr.assign(N,0);
        answers.assign(Q,0);
        queries.reserve(Q);
    }
    void Sort()
    {
        int BLOCK_SIZE = static_cast<int>(sqrt(N));
        auto mo_cmp = [BLOCK_SIZE](const tuple<int, int, int> &x,
                                   const tuple<int, int, int> &y) -> bool
        {
            int block_x = std::get<0>(x) / BLOCK_SIZE;
            int block_y = std::get<0>(y) / BLOCK_SIZE;
            if(block_x != block_y)
                return block_x < block_y;
            return std::get<1>(x) < std::get<1>(y);
        };
        std::sort(queries.begin(), queries.end(), mo_cmp);
    }
    void process(int number, int type)
    {
        /// Do something here.
    }
    long long get_answer()
    {
        return current_answer;
    }

    void add(int number)
    {
        process(number, 1);
    }

    void Remove(int number)
    {
        process(number, -1);
    }
public:
    Mo()
    {
        cnt = vector<int>(MAX_VALUE, 0);
        current_answer = 0;
    }
    void takeInput()
    {
        scanf("%d%d",&N, &Q);
        initialize();
        for(int i = 0; i < N; i++) scanf("%d",&arr[i]);

        for(int i = 0; i < Q; i++)
        {
            int le, rg;
            scanf("%d%d",&le,&rg);
            le--, rg--;
            queries.emplace_back(le, rg, i);
        }
        Sort();
    }
    void Solve()
    {
        int mo_left=0, mo_right=-1;
        for(const auto &q: queries)
        {
            int left, right, answer_idx;
            std::tie(left, right, answer_idx) = q;

            while(mo_right < right)
            {
                mo_right++;
                add(arr[mo_right]);
            }
            while(mo_right > right)
            {
                Remove(arr[mo_right]);
                mo_right--;
            }

            while(mo_left < left)
            {
                Remove(arr[mo_left]);
                mo_left++;
            }
            while(mo_left > left)
            {
                mo_left--;
                add(arr[mo_left]);
            }

            answers[answer_idx] = get_answer();
            //cout<<answer_idx<<' '<<answers[answer_idx]<<endl;
        }
    }
    void printAnswer()
    {
        for(int i = 0; i < Q; i++) if(answers[i]) printf("Yes\n"); else printf("No\n");
    }
    void doEverything()
    {
        takeInput();
        Solve();
        printAnswer();
    }
    /*** Make a variable of this Mo class ...like  " Mo var_name " and call doEverything() function */
};

int main()
{
    Mo solver;
    solver.doEverything();
    return 0;
}

