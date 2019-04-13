class Solution {
public:
    int Pairs(vector<int>& nums) {
        return PairsCount(nums.begin(),nums.end());
    }//function API.
private:
    int PairsCount(vector<int>::iterator begin, vector<int>::iterator end){
    	if(end-begin<=1){
    		return 0;
    	}
    	auto mid=begin+(end-begin)/2;
    	int count=PairsCount(begin,mid)+PairsCount(mid,end);
    	for(auto i=begin,j=mid;i!=mid;i++){
    		while(j!=end && *i>2*(*j))++j;
    		count+=(j-mid);
    	}
    	Merge(begin,mid,end);//merge sub-array to reduce complexity.
    	return count;
    }
    void Merge(vector<int>::iterator begin, vector<int>::iterator mid, vector<int>::iterator end){
    	vector<int> tmp(end-begin);
        auto i=begin,j=mid;
        int flag=0;
        for(;i!=mid && j!=end;tmp[flag++]=((*i<*j)?*(i++):*(j++)));
        for(;i!=mid;tmp[flag++]=*(i++));
        for(;j!=end;tmp[flag++]=*(j++));

        for(auto k=begin,w=tmp.begin();k!=end;k++,w++){
        	*k=*w;
        }//Merge two sorted array.
    }
};
