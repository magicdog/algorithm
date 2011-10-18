#include <iostream>
#include <string>

using namespace std;

bool isMatch_genaral(string Source, string match);
bool isMatch_number(string Source, string match);
bool isMatch_status(string Source, string match);
bool isMatch_kmp(string Source, string match);

int main()
{
	string SourceString = "abbbaabaca";
	string MatchString = "ababaca"; 
	cout << "source string :" << SourceString << endl;
	cout << "match string :" << MatchString << endl;
	cout << "General algorithm: " <<isMatch_genaral(SourceString,MatchString) << endl;
	//cout << "Based on number string algorithm: " <<isMatch_number(SourceString,MatchString) << endl;
	cout << "Based on status machine algorithm: " <<isMatch_status(SourceString,MatchString) << endl;
	cout << "kmp algorithm: " <<isMatch_kmp(SourceString,MatchString) << endl;
	return 1;
}

bool isMatch_genaral(string Source, string match)
{
	bool isMatch = false;
	int sLength = Source.size();
	int mLength = match.size();
	int matchCount =0;
	for(int i=0; i<=sLength-mLength; i++)
	{
		for(int j=0; j<mLength; j++)
		{
			if(Source.at(i+j) != match.at(j))
				break;
			else matchCount++;
		}
		if(matchCount == mLength)
			return true;
		matchCount = 0;
	}
	return isMatch;
}

bool isMatch_number(string Source, string match)
{
	bool isMatch = false;
	int sLength = Source.size();
	int mLength = match.size();
	int yuShu = 17;
	int d = 10;                              //jin zhi
	int sNumber = 0;
	int mNumber = 0;
	int *ts = new int(sLength);
	int h = 1;								 //
	int i=0;
	for(i=0; i<sLength; i++)
		ts[i] = 0;
	for(i=0; i<mLength; i++)
	{
		mNumber = (mNumber*d + match[i] - '0')%yuShu;
		ts[0] = (ts[0]*d +	Source[i] - '0')%yuShu;
		if(i != 0)
			h = (h*d)%yuShu;
	}
	for(i=0; i<=sLength-mLength; i++)
	{
		if(ts[i] == mNumber)
		{
			int matchCount = 0;
			for(int j=0; j<mLength; j++)
			{
				if (Source.at(i+j) == match.at(j))
					matchCount++;
			}
			if(matchCount == mLength)
				return true;
		}
		else
		{
			if(i != sLength-mLength)
			{
				int temp = ((ts[i] - (Source.at(i)-'0')*h)*d+Source.at(i+mLength)-'0')%yuShu;
				if(temp < 0)
					temp += yuShu;
				ts[i+1] = temp;
			}
		}
	}	
	return isMatch;
}

bool isMatch_status(string Source, string match)
{
	bool isMatch = false;
	string letters = "abc";
	int lLength = letters.size();
	int sLength = Source.size();
	int mLength = match.size();
	int **status;
	status = new int*[mLength+1];
	int i;
	for(i=0;i<mLength+1;i++)
	{
		status[i] = new int(lLength);
	}
	for(i=0; i<mLength+1;i++)
	{
		for(int j=0;j<lLength;j++)
		{
			status[i][j] = 0;
		}
	}

	for(i=0; i<mLength+1;i++)
	{
		for(int j=0;j<lLength;j++)
		{
			int k = mLength+1<i+2? mLength+1:i+2;
			char *pq = new char[i+1];
			pq[i] = letters.at(j);
			int m;
			for(m=0;m<i;m++)
			{
				pq[m] = match[m];
			}
			bool stop = true;
			while(stop && k>0)
			{ 
				k--;
				int count =0;
				for(m=0;m<k;m++)
				{
					if(match[k-m-1] == pq[i-m])
						count++;
					if(count == k)
					{
						stop = false;
						break;
					}					
				}
			}
			status[i][j] = k;
		}
	}
/*
	for(i=0; i<mLength+1;i++)
	{
		for(int j=0;j<lLength;j++)
		{
			cout << status[i][j] << "  "; 
		}
		cout << endl;
	}
*/
	int result = 0;
	for(i=0; i<sLength;i++)
	{
		int index = 0;
		for(int j=0;j<lLength;j++)
		{
			if(Source[i] == letters[j])
			{
				index = j;
				break;
			}
		}
		result = status[result][index];
	}
	if(result == mLength)
		isMatch = true;
	return isMatch;
}

bool isMatch_kmp(string Source, string match)
{
	bool isMatch = false;
	int sLength = Source.size();
	int mLength = match.size();
	int i;
	int *jump = new int[mLength];
	//create the status function
	for(i=1; i<mLength; i++)
		jump[i] = 0;
	jump[0] = -1;
	int j=-1;
	for(i=0; i<mLength; i++)
	{
		if(j==-1 || match[i] == match[j])
		{
			i++;j++;jump[i]=j;
		}
		else
		{	
			j=jump[j];
		}
	}
/*
	for(i=0; i<mLength; i++)
	{
		cout << jump[i] << endl;
	}
*/
	j=0;
	for(i=0; i<sLength;)
	{
		if (j == -1) {i++;j++;}
        if (Source[i]==match[j]) {
           i++; j++;
        } else {
           j=jump[j];
        }
		if (i<sLength && j == mLength -1) {return true;}
	}
	return isMatch;
}
