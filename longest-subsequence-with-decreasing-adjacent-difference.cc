class Solution {
public:

    void get_ind_array(vector<vector<pair<int, int>>>&a, vector<int> & nums)
    {
        int n = nums.size();

        vector<int> num_to_ind(301, -1);
        for(int i=0; i < n; i++)
        {
            for(int j=0; j < 301; j++)
            {
                int el1=-1, el2=-1;
                if(nums[i]-j >= 0 && num_to_ind[nums[i]-j] != -1)
                {
                    el1 = num_to_ind[nums[i]-j];
                }

                if(nums[i] + j <= 300 && num_to_ind[nums[i]+j] != -1)
                {
                    el2 = num_to_ind[nums[i]+j];
                }
                a[i][j] = {el1, el2};
            }

            num_to_ind[nums[i]] = i;
        }
    }

    void get_dp_array(vector<vector<int>>&dp, vector<int> &nums, vector<vector<pair<int, int>>> & ind)
    {
        int n = nums.size();

        for(int i=1; i < n; i++)
        {
            for(int j=0; j < 301; j++)
            {
                if(ind[i][j].first != -1)
                   dp[i][j] = max(dp[i][j], dp[ind[i][j].first][j] + 1);

                if(ind[i][j].second != -1)
                   dp[i][j] = max(dp[i][j], dp[ind[i][j].second][j] + 1);
            }

            //maintaining dp by a prefix array
            for(int j=299; j >= 0; j--)
            {
                dp[i][j] = max(dp[i][j+1], dp[i][j]);
            }
        }        
    }

    int longestSubsequence(vector<int>& nums) 
    {
        int n = nums.size();
        vector<vector<pair<int, int>>> ind(n, vector<pair<int, int>>(301));
        vector<vector<int>> dp(n, vector<int> (301, 1));

        get_ind_array(ind, nums);
        get_dp_array(dp, nums, ind);

        int ans=0;
        for(int i=0; i < n; i++)
        {
            ans = max(ans, dp[i][0]);
        }
        return ans;
    }
};
