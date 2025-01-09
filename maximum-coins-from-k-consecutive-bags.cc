class Solution {
public:
    vector<vector<long long>> create_vector(vector<vector<int>>& coins)
    {
        long long n = coins.size();
        sort(coins.begin(), coins.end());

        vector<vector<long long>> new_coins;
        
        new_coins.push_back({0,coins[0][0]-1,0});
        new_coins.push_back({coins[0][0], coins[0][1], coins[0][2]});
        for(int i=1; i < n; i++)
        {
            if(coins[i][0] - coins[i-1][1] > 1)
            {
                new_coins.push_back({coins[i-1][1]+1, coins[i][0]-1, 0});
            }
            new_coins.push_back({coins[i][0], coins[i][1], coins[i][2]});
        }
        new_coins.push_back({coins[n-1][1]+1, coins[n-1][1]+1, 0});  
        return new_coins;      
    }
    
    long long maximumCoins(vector<vector<int>>& coins, int k) 
    {
        long long n = coins.size(), INF = 1e10;
        sort(coins.begin(), coins.end());

        vector<vector<long long>> new_coins = create_vector(coins);
        n = new_coins.size();
        long long l=0, r=k-1, rmax=coins[coins.size()-1][1], sums=0, ans=0;
        for(int i=0; i < n; i++)
        {
            if(new_coins[i][1] > k-1)
            {
                sums += (k-new_coins[i][0])*new_coins[i][2];
                break;
            }
            sums += (new_coins[i][1]-new_coins[i][0]+1)*new_coins[i][2];
        }

        ans = sums;
        while(r <= rmax)
        {
            //left end to nearest segment
            auto itr1 = upper_bound(new_coins.begin(), new_coins.end(), vector<long long>{l, INF, INF});
            long long l_cur1 = (*itr1)[0], r_cur1 = (*itr1)[1], c_cur1 = (*itr1)[2], ind1 = itr1-new_coins.begin();
            //right end to nearest segment
            auto itr2 = upper_bound(new_coins.begin(), new_coins.end(), vector<long long>{r,INF, INF});

            long long l_cur2 = (*itr2)[0], r_cur2 = (*itr2)[1], c_cur2 = (*itr2)[2], ind2 = itr2-new_coins.begin();
            long long minm = min(l_cur1-l, l_cur2-r-1), prc1=new_coins[ind2-1][2];
            if(minm == 0)
            {
                minm++;
                prc1 = new_coins[ind2][2];
            }
            sums += (prc1*minm)-(new_coins[ind1-1][2]*minm);
            ans = max(ans, sums);

            l += minm, r += minm;
        }
        return ans;
    }
};
