#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
long long Resi(int N, int *A, int *B) {
	std::vector<std::pair<int,int> > events;
	for(int i=0;i<N;i++)
        events.push_back({A[i],B[i]}),events.push_back({B[i],B[i]});
    std::sort(events.begin(),events.end());
    __gnu_pbds::tree<int,__gnu_pbds::null_type,std::less<int>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update> s;
    long long sol=0;
    for(auto p:events)
        if(p.first==p.second)
            s.erase(p.second);
        else
            s.insert(p.second),sol+=std::min(s.order_of_key(p.second),s.size()-1-s.order_of_key(p.second));
    return sol;
}
